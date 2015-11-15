/*****************************************************************************
 * Copyright (C) AMIT GANESH PAGRUT amtpagrut@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"queue.h"
void qinit(queue *q) {
	q->head = NULL;
	q->tail = NULL;
}
void enqueue(queue *q, trans_his h) {
	struct trans_his *temp;
	temp = (trans_his *)malloc(sizeof(trans_his));
	if(temp == NULL) {
		exit(1);
	}
	strcpy(temp->ttype, h.ttype);
	temp->acc_no = h.acc_no;
	temp->d = h.d;
	temp->m = h.m;
	temp->y = h.y;
	temp->amount = h.amount;
	temp->total = h.total;
	temp->next = NULL;	
	if(q->tail)
		q->tail->next = temp;
	else
		q->head = temp;
	q->tail = temp;
}

int qempty(queue *q) {
	return q->head == NULL;
}
int qfull(queue *q) { 
	return 0;
}

void qprint(queue *q) {
	trans_his *t = q->head, *p;
	if(t == NULL)
		return;
	while(t) {
		p = t;
		printf("%d/%d/%d	[%s]	  %lf	%lf\n", t->d, t->m, t->y, t->ttype, t->amount, t->total);
		t = t->next;
		free(p);
	}
}
