//queue.h
#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 55
typedef struct Queue {
	int data[N * N * 2];
	int l, r;
} Queue;

typedef struct queue {
	int data[N];
	int l, r;
} queue;

void Queue_init(Queue *q);
int Queue_size(Queue *q);
void Queue_push(Queue *q, int val);
int Queue_pop(Queue *q);

void queue_init(queue *q);
int queue_size(queue *q);
void queue_push(queue *q, int val);
int queue_pop(queue *q);
//int min(int a, int b);
int queue_cmp(queue* a, queue* b);
void queue_print(queue* q);
#endif

