#ifndef __OPENSL_AUDIO_PLAY_H
#define __OPENSL_AUDIO_PLAY_H


#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include "libavformat/avformat.h"
#include "decode_audio.h"

struct openslgs_info_t {
	// engine interfaces
	SLObjectItf engineObject;
	SLEngineItf engineEngine;

	// output mix interfaces
	SLObjectItf outputMixObject;
	SLEnvironmentalReverbItf outputMixEnvironmentalReverb;

	// buffer queue player interfaces
	SLObjectItf bqPlayerObject;
	SLPlayItf bqPlayerPlay;
	SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
	SLEffectSendItf bqPlayerEffectSend;
	SLMuteSoloItf bqPlayerMuteSolo;
	SLVolumeItf bqPlayerVolume;

} openslgs;



void opensl_play_audio(decode_audio_u *decode_audio_var ,AVFormatContext *fmt_ctx);

#endif
