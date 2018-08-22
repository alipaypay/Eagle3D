#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libavcodec/avcodec.h"
#include "opensl_audio_play.h"
#include "EagleLog.h"
#include "xplayer.h"

/*	the following variable be initialized in the function opensl_play_audio*/
static decode_audio_u *g_decode_audio = NULL;
static AVFormatContext *g_fmt_ctx = NULL;

static int  loop_mark = 0;
static int   create_engine_mark = 0;
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio ,do not use in ffmpeg-2.0
uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
// this callback handler is called every time a buffer finishes playing
void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context){
	int len=decode_audio(g_decode_audio , audio_buf ,g_fmt_ctx);

	if((len == -1 ) || ( ( (media_handle_union_t *)g_decode_audio->handle )->stop_mark == 1 )){
		loop_mark = 1;
		return ;
	}
	( (media_handle_union_t *)g_decode_audio->handle )->audio_prepared = 1;
	if( ( (media_handle_union_t *)g_decode_audio->handle )->video_prepared != 1){
		//video did not prepared
		while(1){
			usleep(500);
			LOGI("===video prepared ,prepared = %d"  ,( (media_handle_union_t *)g_decode_audio->handle )->video_prepared);
			if(( (media_handle_union_t *)g_decode_audio->handle )->video_prepared == 1){
				LOGI("===video prepared  ....ok!");
				break;  //video prepared
			}
		}
	}
	LOGI("Play Start~~~~~~~~~~~");
	//log_chris(ANDROID_LOG_ERROR ,TAG ,"after decode audio function .");
	(*openslgs.bqPlayerBufferQueue)->Enqueue(openslgs.bqPlayerBufferQueue,audio_buf,len);
	LOGI("Play End~~~~~~~~~~~");
}

void createEngine(){

	  SLresult result;
	  // create engine
	  result = slCreateEngine(&openslgs.engineObject, 0, NULL, 0, NULL, NULL);
	  assert(SL_RESULT_SUCCESS == result);
	  // realize the engine
	  result = (*openslgs.engineObject)->Realize(openslgs.engineObject, SL_BOOLEAN_FALSE);
	  assert(SL_RESULT_SUCCESS == result);
	  // get the engine interface
	  result = (*openslgs.engineObject)->GetInterface(openslgs.engineObject, SL_IID_ENGINE, &openslgs.engineEngine);
	  assert(SL_RESULT_SUCCESS == result);
	  // create output mix
	  const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
	  const SLboolean req[1] = {SL_BOOLEAN_FALSE};
	  result = (*openslgs.engineEngine)->CreateOutputMix(openslgs.engineEngine, &openslgs.outputMixObject, 1, ids, req);
	  assert(SL_RESULT_SUCCESS == result);
	  // realize the output mix
	  result = (*openslgs.outputMixObject)->Realize(openslgs.outputMixObject, SL_BOOLEAN_FALSE);
	  assert(SL_RESULT_SUCCESS == result);

	  create_engine_mark = 1;
}

void createBufferQueueAudioPlayer(){
    SLresult result;

    // configure audio source
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};

    SLDataFormat_PCM pcm;
    pcm.formatType = SL_DATAFORMAT_PCM;
//    pcm.numChannels = ffmpeg_info.dec_ctx->channels;//璺�涓���㈢��channelMask 瑕����瀵� 涓�浼�浼���ラ��
    pcm.numChannels = g_decode_audio->ptr_audio_codec_ctx->channels;//this must be to pair with the following channelMask

//    pcm.samplesPerSec = ffmpeg_info.dec_ctx->sample_rate*1000;
    pcm.samplesPerSec = g_decode_audio->ptr_audio_codec_ctx->sample_rate*1000;
    pcm.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
    pcm.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
    pcm.channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;  //绔�浣�澹� 杩����������audiotrack CHANNEL_OUT_STEREO = (CHANNEL_OUT_FRONT_LEFT | CHANNEL_OUT_FRONT_RIGHT)寰���扮��
    pcm.endianness = SL_BYTEORDER_LITTLEENDIAN;

    SLDataSource audioSrc = {&loc_bufq, &pcm};



    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, openslgs.outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND,
            /*SL_IID_MUTESOLO,*/ SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
            /*SL_BOOLEAN_TRUE,*/ SL_BOOLEAN_TRUE};
    result = (*openslgs.engineEngine)->CreateAudioPlayer(openslgs.engineEngine, &openslgs.bqPlayerObject, &audioSrc, &audioSnk,
            3, ids, req);
    assert(SL_RESULT_SUCCESS == result);

    // realize the player
    result = (*openslgs.bqPlayerObject)->Realize(openslgs.bqPlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);

    // get the play interface
    result = (*openslgs.bqPlayerObject)->GetInterface(openslgs.bqPlayerObject, SL_IID_PLAY, &openslgs.bqPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);

    // get the buffer queue interface
    result = (*openslgs.bqPlayerObject)->GetInterface(openslgs.bqPlayerObject, SL_IID_BUFFERQUEUE,
            &openslgs.bqPlayerBufferQueue);
    assert(SL_RESULT_SUCCESS == result);

    // register callback on the buffer queue
    result = (*openslgs.bqPlayerBufferQueue)->RegisterCallback(openslgs.bqPlayerBufferQueue, bqPlayerCallback, NULL);
    assert(SL_RESULT_SUCCESS == result);


    assert(SL_RESULT_SUCCESS == result);
    // get the volume interface
    result = (*openslgs.bqPlayerObject)->GetInterface(openslgs.bqPlayerObject, SL_IID_VOLUME, &openslgs.bqPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);

    // set the player's state to playing
    result = (*openslgs.bqPlayerPlay)->SetPlayState(openslgs.bqPlayerPlay, SL_PLAYSTATE_PLAYING);
    assert(SL_RESULT_SUCCESS == result);
}

void opensl_play_audio(decode_audio_u *decode_audio_var ,AVFormatContext *fmt_ctx){
	/**********must be init the g_fmt_ctx and g_decode_audio before init opensl******/
	g_decode_audio = decode_audio_var;
	g_fmt_ctx = fmt_ctx;

	LOGI("in opensl_play_audio ,before createEngine");
	if(create_engine_mark == 0){
		//init opensl
		createEngine();
		LOGI("in opensl_play_audio ,after createEngine");
	}
	createBufferQueueAudioPlayer();
	LOGI("in opensl_play_audio ,before bqPlayerCallback()");
	bqPlayerCallback(NULL,NULL);

	for(;;){
		//log_chris(ANDROID_LOG_ERROR ,TAG ,"in opensl_play_audio ,before getchar()");
		//getchar();
		if(loop_mark == 1){
			LOGE("loop_mark = 1,exit opensl_play_audio");
			loop_mark = 0;
			break;
		}
		usleep(200);
	}
	return ;
}
