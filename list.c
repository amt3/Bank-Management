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
#include"list_stack.h"

void init(list *l) {
	l->head = NULL;
	l->tail = NULL;
	l->length = 0;
}
void traverse(list *l) {
	info *p = l->head;
	printf("\n");
	while(p != l->tail){
		printf("NAME : %s \nACCOUNT NO. : %ld\n\n", p->name, p->acc_no);
		p = p->next;	
	}
	if(p)
		printf("NAME : %s \nACCOUNT NO. : %ld\n\n", p->name, p->acc_no);
	else
		printf("YET NO ACCOUNTS IN THE BANK\n");
}
void append(list *l, info a){
	info *temp;
	temp = (info *)malloc(sizeof(a));
	*temp = a;
	if(l->head == NULL) {
		l->head = l->tail = temp;
		temp->next = temp;
		temp->prev = temp;
	}
	else {
		temp->next = l->head;
		temp->prev = l->tail;
		l->tail->next = temp;
		l->tail = temp;
		l->head->prev = temp;
	}
	(l->length)++;
}

info *search(list *l, long int a) {
	long int m;
	info *p;
	if(l->head) {
		m = (l->tail->acc_no - l->head->acc_no) / 2;
		if(a < m) {
			p = l->head;
			while(p != l->tail) {
				if(p->acc_no == a)
					return p;
				p = p->next;		
			}
			if(p) {
				if(p->acc_no == a)
				return p;	
			}
		}
		else {
			p = l->tail;
			while(p != l->head){
				if(p->acc_no == a)
					return p;
				p = p->prev;	
			}
			if(p) {
				if(p->acc_no == a)
					return p;	
			}	
		}
	} 
	return NULL;
}

void searchname(char *str) {
	info *p = l->head;
	if(l->head) {
		while(p != l->tail) {
			if((strcmp(p->name, str)) == 0) {
				push(*p);
			}
			p = p->next;
		}
		if(p) {
			if((strcmp(p->name, str)) == 0)
				push(*p);
		}
	}
}

void removelist(list *l, info *p) {
	if((p == l->head) && (l->length == 1)) {		
		l->head = NULL;
		l->tail = NULL;
	}
	else {
		if((p == l->head) && (l->length != 1)) {
			p->next->prev = p->prev;
			l->head = p->next;
		}
		else {
			if(p == l->tail) {
				p->prev->next = p->next;
				p->next->prev = p->prev;
				l->tail = p->prev;
			}
			else {
				p->prev->next = p->next;
				p->next->prev = p->prev;
			}
		}
	}
	(l->length)--;
	free(p);			
}
void save_info(list *l) {
	info *p = l->head;
	FILE *fp;
	fp = fopen("data.txt", "w");
	while(p != l->tail){
		fprintf(fp, "%s %d/%d/%d %s %s %s %d %lf %d/%d/%d %ld %d/%d/%d", p->name, p->dob.date, p->dob.month, p->dob.year, p->addrs, 				p->aadhar, p->cont_no, p->acc_type, p->amount, p->dod.date, p->dod.month, p->dod.year, p->acc_no, p->doc.date, p->doc.month, p->doc.year);
		p = p->next;
	}
	if(p)
		fprintf(fp, "%s %d/%d/%d %s %s %s %d %lf %d/%d/%d %ld %d/%d/%d", p->name, p->dob.date, p->dob.month, p->dob.year, p->addrs, 				p->aadhar, p->cont_no, p->acc_type, p->amount, p->dod.date, p->dod.month, p->dod.year, p->acc_no, p->doc.date, p->doc.month, p->doc.year);
	fclose(fp);
}
