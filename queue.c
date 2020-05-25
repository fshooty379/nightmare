//queue.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void Queue_init(Queue *q) {
	q->l = 1;
	q->r = 0;
}

int Queue_size(Queue *q) {
	return q->r - q->l + 1;
}

void Queue_push(Queue *q, int val) {
	if (q->r >= N * N * 2) {
		printf("Queue_push\n");
		exit(0);
	}
	q->data[++q->r] = val;
}

int Queue_pop(Queue *q) {
	if (Queue_size(q) <= 0) {
		printf("Queue_pop\n");
		exit(0);
	}
	return q->data[q->l++];
}

// queue
void queue_init(queue *q) {
	q->l = 1;
	q->r = 0;
}

int queue_size(queue *q) {
	return q->r - q->l + 1;
}

void queue_push(queue *q, int val) {
	if (q->r >= N) {
		printf("queue_push\n");
		exit(0);
	}
	q->data[++q->r] = val;
}

int queue_pop(queue *q) {
	if (queue_size(q) <= 0) {
		printf("queue_pop\n");
		exit(0);
	}
	return q->data[q->l++];
}

int min(int a, int b) {
	return a < b ? a : b;
}

int queue_cmp(queue* a, queue* b) { // 队列字典序的比较
	int n = min(queue_size(a), queue_size(b));
	for (int i = 0; i < n; i++) {
		if (a->data[a->l + i] != b->data[b->l + i]) {
			return a->data[a->l + i] < b->data[b->l + i];
		}
	}
	return queue_size(a) < queue_size(b)?1:0;
}

void queue_print(queue* q) {
	for (int i = q->l; i < q->r; i++) {
		printf("%d-> ", q->data[i]);
	}
	printf("%d\n", q->data[q->r]);
}


