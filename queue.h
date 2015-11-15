typedef struct trans_his {			//structure for transaction HISTORY 
	char ttype[10];				//tansaction type withdrawl or deposite
	long acc_no;				//account number
	int d, m, y;				//date of transaction in (dd mm yyyy)
	double amount, total;
	struct trans_his *next;			//amount deposited and total amount in account
}trans_his;

typedef struct queue {
	struct trans_his *head, *tail;
}queue;

void qinit(queue *q);
void enqueue(queue *q, trans_his h);
trans_his *dequeue(queue *q);
int qempty(queue *q);
int qfull(queue *q); 
void qprint(queue *q);
