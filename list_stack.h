#include<stdio.h>
typedef struct date {
	int date, year, month;
}date;

typedef struct info {
	char name[32], addrs[60], aadhar[16], cont_no[10];
	double amount;
	int acc_type;
	long int acc_no;
	date dob, doc;
	date dod;
	struct info *next, *prev;
}info;

typedef struct list {
	info *head, *tail;
	int length;	
}list;

list *l;

void init(list *);
void traverse(list *);
void append(list *, info);
info *search(list *, long int);
void removelist(list *, info *);
void save_info(list *); 

#define MAX 256
typedef struct stack {
	info b[MAX];
	int i;
}stack;

stack *s;

void stackinit();
void push(info a);
info *pop();
int stackempty();
int stackfull();
