#include "packet_queue.h"
#include "xplayer.h"
#include "EagleLog.h"
/* packet queue handling */
void packet_queue_init(PacketQueue *q) {
	memset(q, 0, sizeof(PacketQueue));

	q->first_pkt = q->last_pkt = NULL;
	q->nb_packets = 0;

	pthread_mutex_init(&q->mutex, NULL);
	pthread_cond_init(&q->cond, NULL);

	pthread_cond_init(&q->full_cond, NULL);
}

int packet_queue_put(PacketQueue *q, AVPacket *pkt ,int handle) {
	AVPacketList *pkt1;
 //(media_handle_union_t *)handle

	/* duplicate the packet */
	if (av_dup_packet(pkt) < 0){
		LOGE("av_dup_packet failed");
		return -1;}

	pkt1 = av_malloc(sizeof(AVPacketList));
	if (!pkt1){
		LOGE("av_malloc failed");
		return -1;
	}
	pkt1->pkt = *pkt;
	pkt1->next = NULL;
	pthread_mutex_lock(&q->mutex);


	if(q->nb_packets == q->packet_max_num){
		pthread_cond_wait(&q->full_cond, &q->mutex);
		if(((media_handle_union_t *)handle)->stop_mark == 1){
			LOGE("==stop_mark ==1 ,and exit packet_queue_put");
			return -1;
		}

	}
	if (!q->last_pkt) //empty queue
		q->first_pkt = pkt1;
	else
		q->last_pkt->next = pkt1;
	q->last_pkt = pkt1;
	q->nb_packets++;
	pthread_cond_signal(&q->cond); //have data

	pthread_mutex_unlock(&q->mutex);
	return 0;
}

int packet_queue_get(PacketQueue *q, AVPacket *pkt ,int block ,int handle) {
	AVPacketList *pkt1;
	int ret;

	pthread_mutex_lock(&q->mutex);
	for(;; ){
		pkt1 = q->first_pkt;

		if(pkt1 == NULL){
			LOGE(" pkt1 == NULL");
		}
		if (pkt1) {
			q->first_pkt = pkt1->next;
			if (!q->first_pkt)
				q->last_pkt = NULL;
			q->nb_packets--;
			*pkt = pkt1->pkt;
			av_free(pkt1);

			pthread_cond_signal(&q->full_cond);
			ret = 0;
			break;
		} else if ( block) { //if block == 1 ,mean file_over is 1
		      ret = -1;
		      break;
		} else {
			//empty queue
			LOGE("empty queue ,and wait ,pkt1 == NULL");
			//display buffering
			//call_java_onerror(g_obj ,100);

			pthread_cond_wait(&q->cond, &q->mutex);
			if(((media_handle_union_t *)handle)->stop_mark == 1){
				LOGE("==stop_mark ==1 ,and exit packet_queue_get");
				return -1;
			}
		}
	}
	//log_chris(ANDROID_LOG_ERROR ,TAG ,"get from queue ,q->nb_packets = %d" ,q->nb_packets);
	pthread_mutex_unlock(&q->mutex);
	return ret;
}

int  empty_queue(PacketQueue *q){
	AVPacketList *pkt1;

	pthread_mutex_lock(&q->mutex);
	for (;;) {
		pkt1 = q->first_pkt;
		if (pkt1) {
			q->first_pkt = pkt1->next;
			if (!q->first_pkt)
				q->last_pkt = NULL;
			q->nb_packets--;
			av_free_packet(&pkt1->pkt);
			av_free(pkt1);
			if(q->nb_packets == 0) break;
		}
	}
//	q->first_pkt = q->last_pkt = NULL;
//		q->nb_packets = 0;
	pthread_mutex_unlock(&q->mutex);
	return 0;
}
