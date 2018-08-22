#include <stdio.h>

#include <unistd.h>

#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include "EagleLog.h"
#include "xplayer.h"
#include "opensl_audio_play.h"
#include "opengl_video_play.h"

//------use to av_read_frame start
static int interrupt_cb(void *ctx)
{
	int ret =0;
	media_handle_union_t * media_handle = (media_handle_union_t *)ctx;
    // do something
	if(1 == media_handle->stop_mark ){
		ret = 1;	//
	}else{
		ret = 0;
	}
	LOGI("in interrupt_cb function ,ret = %d ,stop_mark = %d" ,ret ,media_handle->stop_mark);

    return ret;
}
static const AVIOInterruptCB int_cb = { interrupt_cb, NULL };
//------use to av_read_frame end

// read data thread
void * read_data_thread(void *opaque){
	media_handle_union_t * media_handle= (media_handle_union_t *)opaque;
	if (media_handle == NULL) {
		LOGE("media handle is null ,in read_data_thread");
		return;
	}

	LOGI("==##in read_data_cb");
	read_thread((int)media_handle);		//to read the media data
	LOGI("==##read_data thread exit");
}

//decode video packet to picture queue
void *decode_video_packt_thread(void *opaque){
	//decode video ,and then to put into rgb565 data queue
	LOGI(" in decode_video_packt_thread");
	media_handle_union_t * media_handle = (media_handle_union_t *) opaque;
	if (media_handle == NULL) {
		LOGE("media handle is null ,in decode_video_packt_thread");
		return;   //ok
	}
	int ret = 0;
	while(1){
		ret = decode_video(media_handle->decode_video_var ,media_handle->ptr_format_ctx);

		if( media_handle->stop_mark == 1 || ret == VIDEO_PACKET_GET_NON_PACKET){
			LOGE("==media_handle->stop_mark = %d or VIDEO_PACKET_GET_NON_PACKET ,and set finish_mark" ,media_handle->stop_mark);
			media_handle->finish_mark = 1;
			LOGE("== decode_video thread over");
			break; //exit the xplayer decode video function
		}
	}

}

//play audio
void *play_audio_thread(void *opaque){
	media_handle_union_t * media_handle= (media_handle_union_t *)opaque;
	if (media_handle == NULL) {
		LOGE("media handle is null");
		return;   //audio thread over
	}

	//LOGI("in xplayer_play before opensl  handle = %d" ,media_handle);
	//in this function ,new a thread to play audio
	opensl_play_audio(media_handle->decode_audio_var ,media_handle->ptr_format_ctx);
	//LOGE("==play audio thread over ");

}
//play video
void *play_video_thread (void *opaque){

	opengl_start();

}


/* init fuction ,return a Handle for the input file, if failed return -1*/
PLAYER_HANDLE init_media(const char *media_src ) {
LOGI("file name :%s",media_src);
	media_handle_union_t * media_handle;
	if ((media_handle = malloc(sizeof(media_handle_union_t))) == NULL) {
		LOGE("memory allocate failed");
	//	return call_java_onerror(g_obj ,MALLOC_MEMORY_FAIL);
	}

	av_register_all();
	avformat_network_init();	// register network

    /* get default parameters from command line */
	media_handle->ptr_format_ctx = NULL;
//	media_handle->ptr_format_ctx = avformat_alloc_context();
//    if (!media_handle->ptr_format_ctx) {
//    	log_chris(ANDROID_LOG_ERROR ,TAG ,"avformat_alloc_context function failed  ");
//        return call_java_onerror(g_obj ,MALLOC_MEMORY_FAIL);
//    }
	LOGI("before avformat_open_input ");
//	media_handle->ptr_format_ctx->flags |= AVFMT_FLAG_NONBLOCK;
//	media_handle->ptr_format_ctx->interrupt_callback = int_cb;  //parameter
//	media_handle->ptr_format_ctx->interrupt_callback.opaque = (void *)media_handle;
	int ret =avformat_open_input(&media_handle->ptr_format_ctx, media_src, NULL, NULL);
	if( ret != 0){
		LOGE("avformat_open_input failed ,ret = %d" ,ret);
		//return call_java_onerror(g_obj ,AVFORMAT_OPEN_INPUT_FAIL);
	}
	media_handle->ptr_format_ctx->flags |= AVFMT_FLAG_NONBLOCK;
	media_handle->ptr_format_ctx->interrupt_callback = int_cb;  //parameter
	media_handle->ptr_format_ctx->interrupt_callback.opaque = (void *)media_handle;

	//set probesize and max_analyze_duration
	media_handle->ptr_format_ctx->probesize  = 6000000 ;// 5000000 ->5M
	media_handle->ptr_format_ctx->max_analyze_duration2  = 6000000 ;//5000000 ->5M ;
	LOGI("before avformat_find_stream_info ");
	if (avformat_find_stream_info(media_handle->ptr_format_ctx ,NULL) < 0) {
		LOGE("av_find_stream_info failed in init function ");
		//return call_java_onerror(g_obj ,AVFORMAT_FIND_STREAM_INFO);
	}
	LOGI("before av_dump_format ");
	/*printf the stream info */
	av_dump_format(media_handle->ptr_format_ctx , 0 ,media_src ,0);

	/*	init audio stream */
	media_handle->decode_audio_var = (decode_audio_u *)malloc(sizeof(decode_audio_u));
	if(media_handle->decode_audio_var == NULL){
		LOGE("decode_audio_var malloc failed ");
	//	return call_java_onerror(g_obj ,MALLOC_MEMORY_FAIL);
	}
	if(init_decode_audio(media_handle->ptr_format_ctx ,media_handle->decode_audio_var) == NULL){
		LOGE("init_decode_audio init failed ");
	//	return call_java_onerror(g_obj ,INIT_DECODE_AUDIO_FAIL);
	}

	LOGI("after init_decode_audio ...");
	/*	init video stream 	*/
	media_handle->decode_video_var = (decode_video_u *)malloc(sizeof(decode_video_u));
	if(media_handle->decode_video_var == NULL){
		LOGE("decode_video_var malloc failed ");
	//	return call_java_onerror(g_obj ,MALLOC_MEMORY_FAIL);
	}
	LOGI("before init_decode_video...");
	if (init_decode_video(media_handle->ptr_format_ctx ,media_handle->decode_video_var) == NULL){	//init video decode
		LOGE("init_decode_video failed...");
	//	return call_java_onerror(g_obj ,INIT_DECODE_VIDEO_FAIL);
	}
	LOGI("after init_decode_video...");

	/*	init opengl es varibale */
	if( init_opengl_variable((int)media_handle) < 0){
		LOGE("init_opengl_variable failed...");
	//	return call_java_onerror(g_obj ,INIT_OPENGL_VARIABLE_FAIL);
	}

	//initialize the auido_prepared and video prepared
	media_handle->audio_prepared = 0;
	media_handle->video_prepared = 0;

	//initialize markable variable
	media_handle->stop_mark = 0;   //if 1 ,exit play and free memory
	media_handle->finish_mark  = 0;			//
	media_handle->decode_video_var->finish_mark = 0;
	media_handle->decode_audio_var->finish_mark = 0;

	av_init_packet(&media_handle->flush_pkt);
	media_handle->flush_pkt.data = "FLUSH";

	media_handle->decode_video_var->handle = (PLAYER_HANDLE) media_handle;
	media_handle->decode_audio_var->handle = (PLAYER_HANDLE) media_handle;
	//LOGI("in init ,media_handle->seek_mark =%d.,media_handle = %d" ,media_handle->seek_mark ,media_handle);
	//new a thread to read data
	pthread_create(&media_handle->id_read_data, NULL, read_data_thread, (void *)media_handle);
	//new a thread to decode video packet to picture queue
	pthread_create(&media_handle->id_decode_video_packet, NULL, decode_video_packt_thread, (void *)media_handle);
	return (PLAYER_HANDLE) media_handle;
}



/********* read data thread**************/
int read_thread(PLAYER_HANDLE handle ) {

	LOGI(" in read_thread");
	media_handle_union_t * media_handle = (media_handle_union_t *) handle;
	if (media_handle == NULL) {
		LOGE("media handle is null");
//		return -1;
//		return call_java_onerror(g_obj ,NULL_POINTER_EXCEPTION);
	}
	LOGI(" after media_handle acquire");
	AVPacket packet;
	AVFormatContext *fmt_ctx_tmp = media_handle->ptr_format_ctx;
	int audio_stream = media_handle->decode_audio_var->audio_stream;
	int video_stream = media_handle->decode_video_var->video_stream;
	PacketQueue *video_queue_tmp = &media_handle->decode_video_var->video_queue;
	PacketQueue *audio_queue_tmp = &media_handle->decode_audio_var->audio_queue;  //????in here ,can not use like this ,stack memory
	/* start to read the packet from the media file */
	while (av_read_frame(fmt_ctx_tmp, &packet) >= 0) {
		//log_chris(ANDROID_LOG_INFO ,TAG ,"in av_read_frame ,stop_mark = %d" ,media_handle->stop_mark);
		if(media_handle->stop_mark == 1 ){
			LOGE("==press stop_mark button in av_read_frame");
			return 0;
			break;
		}


		if (packet.stream_index == video_stream) {
			//log_chris(ANDROID_LOG_INFO ,TAG ,"##video put in queue ,pakcet.num = %d" ,video_queue_tmp->nb_packets);
			if(-1 == packet_queue_put(video_queue_tmp, &packet ,(int)media_handle) ){
				LOGE("==video packet_queue_put failed.");
				break;
			}

		} else if (packet.stream_index == audio_stream) {
			if( -1 == packet_queue_put( audio_queue_tmp, &packet ,(int)media_handle) ){
				LOGE("==audio packet_queue_put failed.");
				break;
			}
			//log_chris(ANDROID_LOG_INFO ,TAG ,"##audio put in queue ,pakcet.num = %d ,audio_queue.nb_packets = %d" ,audio_queue_tmp->nb_packets ,media_handle->decode_audio_var->audio_queue.nb_packets);
		}
	}

	media_handle->stop_mark = 1;
	//set file_over_mark
	media_handle->finish_mark = 1;
	media_handle->decode_video_var->finish_mark = 1;
	media_handle->decode_audio_var->finish_mark = 1;
	LOGI(".....finish_mark = %d ,and player over" ,media_handle->finish_mark);
	return 0;
}

//
void xplayer_play(PLAYER_HANDLE handle ){

	LOGI(" in xplayer_play");
	media_handle_union_t * media_handle = (media_handle_union_t *) handle;
	if (media_handle == NULL) {
		LOGE("media handle is null");
		return;   //ok ????
	}
	//new a thread to play audio
	 pthread_create(&media_handle->id_play_audio, NULL, play_audio_thread, (void *)media_handle);

	 //new a thread to play video
	 pthread_create(&media_handle->id_play_video, NULL, play_video_thread, (void *)media_handle);
}


//
int player_stop(PLAYER_HANDLE handle){
	media_handle_union_t * media_handle = (media_handle_union_t *) handle;
	if (media_handle == NULL) {
		LOGE("media handle is null");
		return -1;
	}

	media_handle->stop_mark = 1;  //stop and exit the player ,free  memory
	//signal the video_queue and audio_queue  pthread_cond_t full_cond
	pthread_cond_signal(&media_handle->decode_video_var->video_queue.full_cond);
	pthread_cond_signal(&media_handle->decode_audio_var->audio_queue.full_cond);
	//
	pthread_cond_signal(&media_handle->decode_video_var->video_queue.cond);
	pthread_cond_signal(&media_handle->decode_audio_var->audio_queue.cond);

	//picture_queue
	pthread_cond_signal(&media_handle->decode_video_var->rgb565_queue.cond_empty);

	usleep(200 *1000);
	LOGI("~~== player_stop function over");

	//free memory
	frame_queue_destroy(&media_handle->decode_video_var->rgb565_queue);
	//free video decode
	av_free(media_handle->decode_video_var->yuv_frame);
	av_free(media_handle->decode_video_var->decoded_frame);
	av_free(media_handle->decode_video_var->decoded_video_buf);
	avcodec_close(media_handle->decode_video_var->ptr_video_codec_ctx);
	sws_freeContext(media_handle->decode_video_var->img_convert_ctx);
	free(media_handle->decode_video_var);
	//free audio decode
	free(media_handle->decode_audio_var);
	//
	avformat_free_context(media_handle->ptr_format_ctx);
	//free media_handle
	free(media_handle);
}
