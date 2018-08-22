#include <AudioPlay.h>




const SLEnvironmentalReverbSettings AudioPlay::reverbSettings =
		SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

SLAndroidSimpleBufferQueueItf AudioPlay::bqPlayerBufferQueue = NULL;
;

short* AudioPlay::nextBuffer = NULL;
unsigned AudioPlay::nextSize = 0;
int AudioPlay::nextCount = 0;



AudioPlay::AudioPlay() :
		Component() {

	Init();
}

AudioPlay::AudioPlay(const char* fileName) :
		Component() {

	Init();
	LoadAudio(fileName);
}

void AudioPlay::Init() {
	pFormatCtx = NULL;
	delay_time = 0;
	videoFlag = 0;
	aCodecCtx = NULL;
	aCodec = NULL;
	aFrame = NULL;
	frameFinished = 0;

	engineObject = NULL;
	engineEngine = NULL;

	outputMixObject = NULL;
	outputMixEnvironmentalReverb=NULL;
	bqPlayerObject = NULL;
	bqPlayerPlay = NULL;
	bqPlayerEffectSend = NULL;
	bqPlayerMuteSolo = NULL;
	bqPlayerVolume = NULL;

	fdPlayerObject = NULL;
	fdPlayerPlay = NULL;
	fdPlayerSeek = NULL;
	fdPlayerMuteSolo = NULL;
	fdPlayerVolume = NULL;
	audioStream=NULL;
	swrContext=NULL;
	outSampleRate=8000;
	is_play=false;
	pack_size=0;
}

void AudioPlay::createBufferQueueAudioPlayer(int rate, int channel,
		int bitsPerSample) {

	SLresult result;

	// configure audio source
	SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {
			SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };

	//    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, 2, SL_SAMPLINGRATE_16,
	//        SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
	//        SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN};
	SLDataFormat_PCM format_pcm;
	format_pcm.formatType = SL_DATAFORMAT_PCM;
	format_pcm.numChannels = channel;

	format_pcm.samplesPerSec = rate * 1000;

	format_pcm.bitsPerSample = bitsPerSample;

	format_pcm.containerSize = 16;

	if (channel == 2) {
		format_pcm.channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
	} else {
		format_pcm.channelMask = SL_SPEAKER_FRONT_CENTER;

	}

	format_pcm.endianness = SL_BYTEORDER_LITTLEENDIAN;
	SLDataSource audioSrc = { &loc_bufq, &format_pcm };

	// configure audio sink
	SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX,
			outputMixObject };

	SLDataSink audioSnk = { &loc_outmix, NULL };

	// create audio player
	const SLInterfaceID ids[3] = { SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND,
	/*SL_IID_MUTESOLO,*/SL_IID_VOLUME };
	const SLboolean req[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
	/*SL_BOOLEAN_TRUE,*/SL_BOOLEAN_TRUE };

	result = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject,
			&audioSrc, &audioSnk, 3, ids, req);

	assert(SL_RESULT_SUCCESS == result);

	// realize the player
	result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the play interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY,
			&bqPlayerPlay);
	assert(SL_RESULT_SUCCESS == result);

	// get the buffer queue interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
			&bqPlayerBufferQueue);
	assert(SL_RESULT_SUCCESS == result);

	// register callback on the buffer queue
	result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue,
			bqPlayerCallback, NULL);
	assert(SL_RESULT_SUCCESS == result);

	// get the effect send interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
			&bqPlayerEffectSend);
	assert(SL_RESULT_SUCCESS == result);


#if 0   // mute/solo is not supported for sources that are known to be mono, as this is
	// get the mute/solo interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_MUTESOLO, &bqPlayerMuteSolo);
	assert(SL_RESULT_SUCCESS == result);

#endif

	// get the volume interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME,
			&bqPlayerVolume);
	assert(SL_RESULT_SUCCESS == result);

	// set the player's state to playing
	result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
	assert(SL_RESULT_SUCCESS == result);


}

// this callback handler is called every time a buffer finishes playing
void AudioPlay::bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq,
		void *context) {
	assert(bq == bqPlayerBufferQueue);
	assert(NULL == context);
	// for streaming playback, replace this test by logic to find and fill the next buffer
	if (--nextCount > 0 && NULL != nextBuffer && 0 != nextSize) {
		SLresult result;
		// enqueue another buffer
		result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue,
				nextBuffer, nextSize);
		// the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
		// which for this code example would indicate a programming error
		assert(SL_RESULT_SUCCESS == result);
	}
}

void AudioPlay::CreateSLContent() {
	SLresult result;

	// create engine
	result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
	assert(SL_RESULT_SUCCESS == result);

	// realize the engine
	result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the engine interface, which is needed in order to create other objects
	result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE,
			&engineEngine);
	assert(SL_RESULT_SUCCESS == result);

	// create output mix, with environmental reverb specified as a non-required interface
	const SLInterfaceID ids[1] = { SL_IID_ENVIRONMENTALREVERB };
	const SLboolean req[1] = { SL_BOOLEAN_FALSE };
	result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1,
			ids, req);
	assert(SL_RESULT_SUCCESS == result);

	// realize the output mix
	result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the environmental reverb interface
	// this could fail if the environmental reverb effect is not available,
	// either because the feature is not present, excessive CPU load, or
	// the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
	result = (*outputMixObject)->GetInterface(outputMixObject,
			SL_IID_ENVIRONMENTALREVERB, &outputMixEnvironmentalReverb);
	if (SL_RESULT_SUCCESS == result) {
		result =
				(*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
						outputMixEnvironmentalReverb, &reverbSettings);
	}

}

int AudioPlay::DecodeAudio(AVFormatContext *pFormatCtx) {
	this->pFormatCtx = pFormatCtx;

	int i = 0;
	for (i = 0; i < this->pFormatCtx->nb_streams; i++) {
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
			audioStream = pFormatCtx->streams[i];
			break;
		}
	}
	if (audioStream ==NULL) {
		 av_free(aFrame);
		return -1;
	}

	aCodecCtx = audioStream->codec;
	aCodec = avcodec_find_decoder(aCodecCtx->codec_id);
	if(aCodec==NULL || (avcodec_open2(aCodecCtx, aCodec, NULL) < 0)){
		LOGE("Error: no codec found");
		av_free(aFrame);
		return -1;

	}else if(avcodec_open2(aCodecCtx, aCodec, NULL) != 0){
		LOGE("Couldn't open the context with the decoder");
		av_free(aFrame);
		return -1;
	}

	audioStream->discard=AVDISCARD_DEFAULT;
	int64_t outChannelLayout=AV_CH_LAYOUT_MONO;
	AVSampleFormat outSampleFormat = AV_SAMPLE_FMT_S16;


	swrContext=swr_alloc_set_opts(
			NULL,
			outChannelLayout,
			outSampleFormat,
			outSampleRate,
			av_get_default_channel_layout(aCodecCtx->channels),
			aCodecCtx->sample_fmt,
			aCodecCtx->sample_rate,
			0,
			NULL
	);

	if (swrContext==NULL) {
		av_free(aFrame);
		avcodec_close(aCodecCtx);
		avformat_close_input(&pFormatCtx);

		return -1;
	}

	if (swr_init(swrContext) != 0)
	{
	    av_free(aFrame);
	    avcodec_close(aCodecCtx);
	    avformat_close_input(&pFormatCtx);
	    swr_free(&swrContext);
	    LOGE("Couldn't initialize the SwrContext");
	    return -1;
	}

	av_init_packet(&packet);


	CreateSLContent();
	createBufferQueueAudioPlayer(aCodecCtx->sample_rate,
								aCodecCtx->channels, SL_PCMSAMPLEFORMAT_FIXED_16);
	return 0;
}

int AudioPlay::LoadAudio(const char* fileName) {
	//avcodec_register_all();
	av_register_all();

	aFrame = av_frame_alloc();
	if (aFrame == NULL) {
		return -1;

	}

	avformat_network_init();
	pFormatCtx =NULL;

	if (avformat_open_input(&pFormatCtx, fileName, NULL, NULL) != 0) {
		LOGE("Couldn't open input stream.\n");
		av_free(aFrame);
		return -1;
	}
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		LOGE("Couldn't find stream information.\n");
		av_free(aFrame);
		//av_close_input_file(pFormatCtx);
		return -1;
	}
	av_dump_format(pFormatCtx, 0, fileName, 0);
	DecodeAudio(pFormatCtx);
	return 0;
}

void AudioPlay::Pause() {

}

void AudioPlay::Resume() {

}

void AudioPlay::Render() {
	PlayAudio();

}

void AudioPlay::ApplicationQuit() {

}

void AudioPlay::PlayAudio(){

		if(is_play){

			return;
		}
		int len1,len2,decoded_data_size;
		int64_t dec_channel_layout;
		int wanted_nb_samples,resampled_data_size;

		if ( av_read_frame(pFormatCtx, &packet) == 0 ) {

			if (packet.stream_index == audioStream->index) {
				 AVPacket decodingPacket = packet;
				 int data_size;

				 audio_pkt_data = decodingPacket.data;
				 audio_pkt_size = decodingPacket.size;
			while(audio_pkt_size>0){
				is_play=true;
				decoded_data_size=av_samples_get_buffer_size(NULL, aCodecCtx->channels,
							aFrame->nb_samples, aCodecCtx->sample_fmt, 1);
				if(swrContext != NULL){
					len1 = avcodec_decode_audio4(aCodecCtx, aFrame, &frameFinished,
							&decodingPacket);
					if(len1<0 || frameFinished==0){

						break;
					}
					audio_pkt_data+=len1;
					audio_pkt_size-=len1;




					dec_channel_layout=(aFrame->channel_layout
							&& aFrame->channels
									== av_get_channel_layout_nb_channels(
									aFrame->channel_layout)) ?
											aFrame->channel_layout :
									av_get_default_channel_layout(
									aFrame->channels);
					wanted_nb_samples=aFrame->nb_samples;

				   int sample_per_buffer_divider = 2* av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
//
				   const uint8_t **in=(const uint8_t **) aFrame->extended_data;
				   uint8_t *out[] = { audio_buf2 };



					len2=swr_convert(
										swrContext,
										out,
										sizeof(audio_buf2)/sample_per_buffer_divider,
										(const unsigned char**)aFrame->extended_data,
										aFrame->nb_samples
					);


					if(len2<0){
						LOGE("swr_convert() failed");
						return;
					}

					if(len2==sizeof(audio_buf2)/sample_per_buffer_divider){

						swr_init(swrContext);
					}
					audio_buf = audio_buf2;
					data_size = len2 * sample_per_buffer_divider;
					(*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue,
							audio_buf, data_size);
				}else{

										data_size = decoded_data_size;
										(*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue,
												aFrame->data[0], data_size);
									}


			}

		}
			is_play=false;
			av_free_packet(&packet);
		}
}



