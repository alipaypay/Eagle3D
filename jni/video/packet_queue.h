#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H
#include <pthread.h>
#include "libavformat/avformat.h"

#define VIDEO_PACKET_MAX_NUM			50
#define AUDIO_PACKET_MAX_NUM			50



/* audio | video  packet queue*/
typedef struct PacketQueue {
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;

	pthread_mutex_t mutex;
	pthread_cond_t cond;

	pthread_cond_t full_cond;

	int packet_max_num;
} PacketQueue;


void packet_queue_init(PacketQueue *q);


/*
 * return value: return -1 error
 * */
int packet_queue_put(PacketQueue *q, AVPacket *pkt ,int handle);  //handle => media_handle



int packet_queue_get(PacketQueue *q, AVPacket *pkt ,int block ,int handle);



int  empty_queue(PacketQueue *q);


#endif
