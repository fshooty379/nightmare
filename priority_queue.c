//priority_queue.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
//#include "queue.c"
#include "priority_queue.h"


void pq_init(priority_queue* q) {
	q->size = 0;
}

int pq_size(priority_queue *q) {
	return q->size;
}

int pq_cmp(node a, node b) { 
	if (a.g + a.h != b.g + b.h) {
		return a.g + a.h < b.g + b.h;
	}
	return queue_cmp(&a.path, &b.path)? 1:0;
}

void swap(node *x, node *y) {
	struct node tmp = *x;
	*x = *y;
	*y = tmp;
}

void pq_push(priority_queue *q, node val) {
	if (q->size >= N * N * 200) {
		printf("pq_push\n");
		exit(0);
	}
	int p = ++q->size;
	q->data[p] = val;
	while (p > 1 && pq_cmp(q->data[p], q->data[p / 2])) {
		swap(&q->data[p / 2], &q->data[p]);
		p /= 2;
	}
}

node pq_pop(priority_queue *q) {
	if (q->size <= 0) {
		printf("pq_pop\n");
		exit(0);
	}
	node res = q->data[1];
	q->data[1] = q->data[q->size--];
	int p = 1, t;
	while (p * 2 <= q->size) {
		if (p * 2 + 1 > q->size || pq_cmp(q->data[p * 2], q->data[p * 2 + 1])) {
			t = p * 2;
		}
		else {
			t = p * 2 + 1;
		}
		if (pq_cmp(q->data[t], q->data[p])) {
			swap(&q->data[p], &q->data[t]);
			p = t;
		}
		else {
			break;
		}
	}
	return res;
}





