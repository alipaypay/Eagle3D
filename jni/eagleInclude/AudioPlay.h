#ifndef AUDIO_PLAY_H
#define AUDIO_PLAY_H

#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000
#include <Component.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <EagleLog.h>
#include <assert.h>
// for native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
extern "C"{
 #include <libavcodec/avcodec.h>
 #include <libavformat/avformat.h>
 #include <libswscale/swscale.h>
 #include <libswresample/swresample.h>
 #include <libavutil/avutil.h>

}


using namespace std;
class AudioPlay:public Component{
private:
	AVFormatContext *pFormatCtx ;
	int              delay_time, videoFlag;
	AVCodecContext  *aCodecCtx;
	AVCodec         *aCodec;
	AVFrame         *aFrame;
	AVPacket        packet;
	AVStream* audioStream;
	SwrContext* swrContext;



	uint8_t *audio_pkt_data;
	int audio_pkt_size;
	uint8_t *audio_buf;


	DECLARE_ALIGNED(16,uint8_t,audio_buf2) [AVCODEC_MAX_AUDIO_FRAME_SIZE * 4];


	int outSampleRate;//44100;
	int  frameFinished;

	// engine interfaces
   SLObjectItf engineObject;
   SLEngineItf engineEngine;

	// output mix interfaces
   SLObjectItf outputMixObject;
   SLEnvironmentalReverbItf outputMixEnvironmentalReverb;

	// buffer queue player interfaces
    SLObjectItf bqPlayerObject;
    SLPlayItf bqPlayerPlay;
   static  SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
  SLEffectSendItf bqPlayerEffectSend;
   SLMuteSoloItf bqPlayerMuteSolo;
   SLVolumeItf bqPlayerVolume;

	// aux effect on the output mix, used by the buffer queue player
     static const SLEnvironmentalReverbSettings reverbSettings;

	// file descriptor player interfaces
   SLObjectItf fdPlayerObject;
  SLPlayItf fdPlayerPlay;
  SLSeekItf fdPlayerSeek;
   SLMuteSoloItf fdPlayerMuteSolo;
   SLVolumeItf fdPlayerVolume;

	// pointer and size of the next player buffer to enqueue, and number of remaining buffers
    static short *nextBuffer;
    static unsigned nextSize;
    static int nextCount;

    int pack_size;
    bool is_play;


	 void CreateSLContent();
	static void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context);
	 void createBufferQueueAudioPlayer(int rate, int channel,int bitsPerSample);
	 void Init();
	 int LoadAudio(const char* fileName);
	 void PlayAudio();
public:
	AudioPlay();
	AudioPlay(const char* fileName);
	virtual	void Pause();
	virtual	void Resume();
	virtual void Render();
	virtual	void ApplicationQuit();
	int DecodeAudio(AVFormatContext	*pFormatCtx);
};

#endif
