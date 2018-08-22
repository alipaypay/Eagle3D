#include<stdlib.h>
#include <pthread.h>
#include "decode_audio.h"
#include "packet_queue.h"
#include "xplayer.h"
#include "EagleLog.h"
#include "libswresample/swresample.h"

decode_audio_u * init_decode_audio(AVFormatContext *fmt_ctx ,decode_audio_u * decode_audio_var) {

	/* start to find audio stream  */
	int i;
	decode_audio_var->audio_stream = -1;
	for (i = 0; i < fmt_ctx->nb_streams; i++) {
		if (fmt_ctx->streams[i]->codec->codec_type
				== AVMEDIA_TYPE_AUDIO ) {	//only find the first audio stream
			decode_audio_var->audio_stream = i;
			break;
		}
	}

	if (decode_audio_var->audio_stream < 0) {
		LOGE("can not find audio stream ");
		return NULL;
	}


	/* audio codec  */
	decode_audio_var->ptr_audio_codec_ctx = fmt_ctx->streams[decode_audio_var->audio_stream]->codec;
	if ((decode_audio_var->ptr_audio_codec = avcodec_find_decoder(
			decode_audio_var->ptr_audio_codec_ctx->codec_id)) == NULL) {
		LOGE("find audio decoder failed");
		return NULL;
	}

	// open audio decoder
	if (avcodec_open2(decode_audio_var->ptr_audio_codec_ctx, decode_audio_var->ptr_audio_codec ,NULL) < 0) {
		LOGE("open audio decoder failed");
		return NULL;
	}

	/* init packet_queue */
	packet_queue_init(&decode_audio_var->audio_queue);
	decode_audio_var->audio_queue.packet_max_num = AUDIO_PACKET_MAX_NUM;

	//audio frame
	decode_audio_var->audio_decoded_frame = av_frame_alloc();
	if(decode_audio_var->audio_decoded_frame == NULL){
		LOGE("audio_decoded_frame alloc_frame failed");
		return NULL;
	}

	decode_audio_var->audio_pkt_size = 0;	//use for the decode function

	int n = decode_audio_var->ptr_audio_codec_ctx->channels
			* /*2*/av_get_bytes_per_sample(decode_audio_var->ptr_audio_codec_ctx->sample_fmt); //
	LOGI("av_get_bytes_per_sample = %d" ,av_get_bytes_per_sample(decode_audio_var->ptr_audio_codec_ctx->sample_fmt) );
	decode_audio_var->bytes_per_sec = decode_audio_var->ptr_audio_codec_ctx->sample_rate * n;

	return decode_audio_var;
}


int  decode_audio(decode_audio_u *decode_audio_var , uint8_t * audio_mem_addr ,AVFormatContext *fmt_ctx) {

	static int audio_buf_index = 0;
	static AVPacket pkt ;
	static struct SwrContext *swr_ctx = NULL;
	for(;;) {
		while(decode_audio_var->audio_pkt_size > 0) {
			int got_frame = 0;

			int len = avcodec_decode_audio4( decode_audio_var->ptr_audio_codec_ctx, decode_audio_var->audio_decoded_frame, &got_frame, &pkt );

			if( len < 0 ) { //decode failed ,skip frame
				LOGE("Error while decoding audio frame");
					decode_audio_var->audio_pkt_size = 0;
					break;
			}

			decode_audio_var->audio_pkt_size -= len;
			if( got_frame ) {
					//acquire the large of the decoded audio info...
					int data_size = av_samples_get_buffer_size(NULL, decode_audio_var->ptr_audio_codec_ctx->channels,
							decode_audio_var->audio_decoded_frame->nb_samples,
							decode_audio_var->ptr_audio_codec_ctx->sample_fmt, 1);

					decode_audio_var->audio_size = data_size;  //audio data size
					if(audio_buf_index != 0){
						decode_audio_var->audio_frame_pts += (double) ((audio_buf_index + 1) /decode_audio_var->bytes_per_sec );
					}
					audio_buf_index += data_size;
					//log_chris(ANDROID_LOG_ERROR ,TAG ,"data_size = %d" ,data_size);
#if 1//add 20130705 //ffmpeg 1.2.1 decode aac to AV_SAMPLE_FMT_FLTP (32bits per sample),but i want AV_SAMPLE_FMT_S16
					if(decode_audio_var->ptr_audio_codec_ctx->sample_fmt == AV_SAMPLE_FMT_FLTP){

						if(NULL == swr_ctx){ //init swrContext ,only one time

							swr_ctx = swr_alloc_set_opts(NULL,
										decode_audio_var->ptr_audio_codec_ctx->channel_layout,		//for out
										AV_SAMPLE_FMT_S16,			//for out
										decode_audio_var->ptr_audio_codec_ctx->sample_rate,		//for out
										decode_audio_var->ptr_audio_codec_ctx->channel_layout,
										AV_SAMPLE_FMT_FLTP,
										decode_audio_var->ptr_audio_codec_ctx->sample_rate,
										0,
										NULL);

							if(swr_init(swr_ctx)<0)
							{
								LOGE("swr_init() for AV_SAMPLE_FMT_FLTP fail");
								return -1;
							}
						}//end init

						uint8_t pTemp[data_size/2];
						uint8_t *pOut = (uint8_t *)&pTemp;
						int in_samples = decode_audio_var->audio_decoded_frame->nb_samples;
						int outCount = swr_convert(swr_ctx,
													   (uint8_t **)&pOut,
													   in_samples,
													   (const uint8_t **)decode_audio_var->audio_decoded_frame->extended_data /*extended_data*/,
													   in_samples);
						outCount = outCount * decode_audio_var->ptr_audio_codec_ctx->channels *av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
						//log_chris(ANDROID_LOG_ERROR ,TAG ,"outCount = %d ,in_samples =%d" ,outCount ,in_samples);
						memcpy(audio_mem_addr , pOut,outCount);  //return result
						//--
						if(decode_audio_var->audio_pkt_size == 0){
							av_free_packet(&pkt);
						}
						//--
						return outCount;
					}


#endif

					return data_size;


			}else{ //no data

				LOGI("no data\n");
					 decode_audio_var->audio_pkt_size = 0;
					 if( pkt.data)
						av_free_packet(&pkt);
					 continue;
			}
		} //end while


		/* next packet */
		if(packet_queue_get(&decode_audio_var->audio_queue, &pkt ,decode_audio_var->finish_mark ,decode_audio_var->handle) < 0) {
			LOGE(".....queue get  audio failed.,decode_audio_var->file_over =%d...",decode_audio_var->finish_mark);
			LOGE(".....");
			if (swr_ctx)   swr_free(&swr_ctx);
			return -1;
		}
		//log_chris(ANDROID_LOG_ERROR,TAG, "....after.queue get  audio");
//		if(pkt.data == decode_audio_var->flush_pkt.data ){	//used to seek
//			avcodec_flush_buffers(decode_audio_var->ptr_audio_codec_ctx);
//			__android_log_print(ANDROID_LOG_INFO,"chris_magic", ".....FLUSH audio....");
//			continue;
//		}

		audio_buf_index = 0;
		int64_t pts1 = pkt.pts;

//		decode_audio_var->audio_frame_pts =
//				(double) pts1
//						* av_q2d(
//								fmt_ctx->streams[decode_audio_var->audio_stream]->time_base)
//						* 1000;
		((media_handle_union_t *)decode_audio_var->handle)->global_clock_time =
				(double) pts1
										* av_q2d(
												fmt_ctx->streams[decode_audio_var->audio_stream]->time_base)
										* 1000; //in millisecond
		decode_audio_var->audio_pkt_size = pkt.size;
	}
}
