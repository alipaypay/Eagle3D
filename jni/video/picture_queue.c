
#include "picture_queue.h"
//#include "decode_video.h"
#include "opengl_video_play.h"
#include "xplayer.h"
#include "EagleLog.h"
/*==================       video frame                  ======================*/
/* frame queue handling */
int frame_queue_init(Rgb565Queue *q, int frame_size) {
	memset(q, 0, sizeof(Rgb565Queue));

	q->front = q->rear = 0;                                 //empty queue
	pthread_mutex_init(&q->mutex, NULL);

	/* condition variable */
	pthread_cond_init(&q->cond_empty, NULL);
	pthread_cond_init(&q->cond_full, NULL);
	/*      init rgb_data array     */
	int i;
	for (i = 0; i < VIDEO_PACKET_NUM; i++) {
		if ((q->rgb565_data[i] = malloc(frame_size)) == NULL){ //malloc rgb565 memory
			LOGE("rgb565 memory malloc failed");
				return -1;
		}
	}

	return 0;
}

int frame_queue_put(Rgb565Queue *q, AVFrame *pFrame ,int size ,double video_frame_pts  ) {

        pthread_mutex_lock(&q->mutex);
        /* judge the queue is full or not*/
        if( (q->rear + 1) % VIDEO_PACKET_NUM  == q->front){                             //queue is full
                pthread_cond_wait(&q->cond_full ,&q->mutex);                    //block in here
        }

        memcpy(q->rgb565_data[q->rear] ,pFrame->data[0] ,size);	//error???
        q->frame_pts[q->rear] = video_frame_pts;
        q->rear = ( q->rear +1 ) % VIDEO_PACKET_NUM;
        pthread_cond_signal(&q->cond_empty); //have data

        //trigger  buffer status
     //   call_java_onprepare(g_obj);

       // log_chris(ANDROID_LOG_ERROR ,TAG ,"in frame_queue_put ,q->rear = %d ,q->front = %d ,size = %d" ,q->rear ,q->front ,size);
        pthread_mutex_unlock(&q->mutex);
        return 0;
}

int frame_queue_get(Rgb565Queue *q ,void *decode_video_var,double* video_frame_pts ,uint8_t * video_data ,int handle) {

        pthread_mutex_lock(&q->mutex);
        /* judge the queue is empty or not*/
        if( q->rear == q->front){                               //queue is empty
        	LOGE("video queue is empty ,q->rear = %d" ,q->rear);
                pthread_cond_wait(&q->cond_empty ,&q->mutex);                   //block in here
				if(((media_handle_union_t *)handle)->stop_mark == 1){
					LOGE("==stop_mark ==1 ,and exit frame_queue_get");
					return -1;
				}
        }

//        memcpy(video_data , q->rgb565_data[q->front] ,TEXTURE_WIDTH *TEXTURE_HEIGHT/*decode_video_var->frame_rgb565_size*/);
   //    LOGI("______----------_____________________:%d",getPixelsSize());
        memcpy(video_data , q->rgb565_data[q->front] ,getPixelsSize()/*decode_video_var->frame_rgb565_size*/);

        (*video_frame_pts) = q->frame_pts[q->front];
        q->front = ( q->front +1 ) % VIDEO_PACKET_NUM;

        pthread_cond_signal(&q->cond_full); //have data

        pthread_mutex_unlock(&q->mutex);
        return 0;
}


void frame_queue_destroy(Rgb565Queue *q ){
	/*      free rgb_data array     */
	int i;
	for (i = 0; i < VIDEO_PACKET_NUM; i++) {
		if(q->rgb565_data[i])
			free(q->rgb565_data[i]);
	}
}
