#include<stdio.h>
#include"list.h"
#include<stdlib.h>
void init(list *l) {
	l->head = NULL;
	l->tail = NULL;
	l->length = 0;
}
info *traverse(list *l) {
	info *p = l->head;
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
	return NULL;
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
		fprintf(fp, "%s %d/%d/%d %s %s %s %d %lf %d/%d/%d %ld", p->name, p->dob.date, p->dob.month, p->dob.year, p->addrs, 				p->aadhar, p->cont_no, p->acc_type, p->amount, p->dod.date, p->dod.month, p->dod.year, p->acc_no);
		p = p->next;
	}
	if(p)
		fprintf(fp, "%s %d/%d/%d %s %s %s %d %lf %d/%d/%d %ld", p->name, p->dob.date, p->dob.month, p->dob.year, p->addrs, 				p->aadhar, p->cont_no, p->acc_type, p->amount, p->dod.date, p->dod.month, p->dod.year, p->acc_no);
	fclose(fp);
}
