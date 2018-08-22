#ifndef XPLAYER_H
#define XPLAYER_H


#include <pthread.h>

#include "libavformat/avformat.h"
#include "decode_audio.h"
#include "decode_video.h"

/*big structure for the player*/
typedef struct media_handle_union {

	/*AVFormatContext for input file*/
	AVFormatContext *ptr_format_ctx;

	//video struct
	decode_video_u *decode_video_var;

	//audio struct
	decode_audio_u *decode_audio_var;

	//sys clock time
	double global_clock_time ;

	//seek
	int seek_mark ;
	int seek_pos;   	//80 == 80%
	AVPacket flush_pkt;

	//status
	int stop_mark;
	int finish_mark;
	int read_data_thread_exit_mark;

	//sync
	int audio_prepared;
	int video_prepared;

	//
	pthread_t id_read_data; //read data thread
	pthread_t id_decode_video_packet;
	pthread_t id_play_audio; //play audio thread
	pthread_t id_play_video;	//play video thread
} media_handle_union_t;



/*
 * 	Function
 *
 * */
typedef int PLAYER_HANDLE;
/*
 * init fuction
 * @param[in] media_src the input file
 * return: Handle for the input file
 * */
PLAYER_HANDLE init_media(const char *media_src );

/*
 * get video frame
 * @param[in] handle       the return value of the init_media
 * @param[in out] pts      the pts of the video frame
 *
 * return : the data of rgb565
 * */
uint8_t * get_video_frame(PLAYER_HANDLE handle ,double *video_frame_pts ,uint8_t * video_mem_addr ,int back_play_mark);


/*
 * get audio frame
 * @param[in] handle             the return value of the init_media
 * @param[in out] pts            the pts of the audio frame
 * @param[in out] audio_size     the size of the audio frame
 *
 * return : the data of audio ,such as pcm
 * */
uint8_t * get_audio_frame(PLAYER_HANDLE handle  , int *audio_frame_size ,double * audio_frame_pts  ,uint8_t * audio_mem_addr );

/*
 * the main thread to read data and put packet into queue
 * @param[in] handle       the return value of the init_media
 *
 * return : 0 success
 * */
int read_thread(PLAYER_HANDLE handle ) ;


/*
 *
 * @param[in] handle       the return value of the init_media
 *
 * return : 0 success
 * */
int player_stop(PLAYER_HANDLE handle);

/*
 *
 * @param[in] handle       the return value of the init_media
 *
 * return : 0 success
 * */
int player_release(PLAYER_HANDLE handle);

int seek_frame(PLAYER_HANDLE handle ,int seek_pos);

void xplayer_play(PLAYER_HANDLE handle );

void xplayer_decode_video(PLAYER_HANDLE handle);
#endif
