#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"list.h"

typedef struct trans_date {
	int d, m , y;
}trans_date;  

void view_costmers();
int date_difference(); 
double simple_interest(double, float, int);
double compound_interest(double, float, int);
void creat_acc();
void transaction(long int);
void balence(long int);
void modify_acc(long int);
void close_account(long int);
void menu();

enum bank { savings = 1, fixed1, fixed2, current};

enum transaction { deposite = 1, withdraw};

float rates = 4.00, ratef1 = 8.00, ratef2 = 8.25;

int cheak_date(int d, int m, int y) {
		if(m > 12 || d > 31 || m <= 0 || d <= 0)
			return 0;
		else {
			if(d == 31) {
				if(((m <= 6) && (m % 2 == 0)) || (( m > 6) && (m % 2 != 0)))
					return 0;
				else
					return 1;			
			}
			else {
				if(d >= 29 && m == 2) {
					if(y % 100 == 0) {
						if(y % 400 == 0)
							return 1;
						else
							return 0;						
					}
					else {
						if(y % 4 == 0)
							return 1;
						else
							return 0;					
					}	
				}
				else
					return 1;
			}
		}
}

int date_difference(trans_date a,info *p) {
	int d1, d2;	
	d1 = days(p->dod.date, p->dod.month, p->dod.year);
	d2 = days(a.d, a.m, a.y);
	d2 = d2 + (a.y - p->dod.year) * 365;
	if(a.m <= 2)
		a.y--;
	while(p->dod.year <= a.y) {
		if(a.y % 100 == 0) {
			if(a.y % 400 == 0)
				d2++;						
		}
		else {
			if(a.y % 4 == 0)
				d2++;					
		}
		a.y--;		
	}
	
	printf("day %d\n", d2 - d1);
	return(d2 - d1);
}

int days(int a,int m, int y) {
	switch (m) {
		case 1:
			a = a + 0;
			break;
		case 2:
			a = a + 31;
			break;
		case 3:
			a = a + 59;
			break;
		case 4:
			a = a + 90;
			break;
		case 5:
			a = a + 120;
			break;
		case 6:
			a = a + 151;
			break;
		case 7:
			a = a + 181;
			break;
		case 8:
			a = a + 212;
			break;
		case 9:
			a = a + 243;
			break;
		case 10:
			a = a + 273;
			break;
		case 11:
			a = a + 304;
			break;
		case 12:
			a = a + 334;
			break;
	}
	return a;
}
/*p is the investment amount of savings account,
 * days is duration of duratin
 *& r is rate on FD*/

double simple_interest(double p, float rate, int days){
	float n;
	double si;
	if(days == 0)
		return p;
	n = days / 365.00;
	printf("n is %lf\n", n);
	si = (p * n * rate) / 100.00;
	printf("si is %lf\n", si);
	p = p + si;
	return p;
}

/* p is the investment amount of Fixed Deposite,
 * n is duration of FD
 *& r is rate on FD*/
double compound_interest(double p, float r, int n) {  
	if(n <= 0)
		return p;
	return (compound_interest(p*(1 + (r/400)), r, n - 1));
}

void creat_acc() {
	info new;
	FILE *fp;
	int a, i = 0, count = 0;
	fp = fopen("data.txt", "a+");
	if(fp == NULL) {
		printf("error");
		return;
	}
	if(l->tail)
		new.acc_no = 100000000 + (l->tail->acc_no % 10 + 1);
	else
		new.acc_no = 100000000;
	
	printf("\nName : ");
	scanf(" %[^\n]", new.name);
	while(new.name[i] != '\0') {
		if(new.name[i] == ' ')
			new.name[i] = '_';
		i++;	
	}

	DOB:

	printf("\nDate Of Birth (dd mm yy) : ");
	scanf("%d %d %d", &new.dob.date, &new.dob.month, &new.dob.year);
	if(cheak_date(new.dob.date, new.dob.month, new.dob.year) == 0) {
		printf("\nERROR IN DATE\n");		
		goto DOB;
	}	
	
	printf("\nAddress : ");
	scanf(" %[^\n]", new.addrs);
	i = 0;
	while(new.addrs[i] != '\0') {
		if(new.addrs[i] == ' ')
			new.addrs[i] = '_';
		i++;	
	}
	
	printf("\ndo you have adhar number :\n1.YES\n2.NO\n");
	scanf("%d", &a);
	if(a == 1) {
		printf("\nUID NO. : ");
		scanf("%s", new.aadhar);
	}
	else 
		strcpy(new.aadhar,"-----------");

	CONT:
	printf("\nContact No. : ");
	scanf("%s", new.cont_no);
	if(strlen(new.cont_no) > 10) {
		printf("\nEnter Valid Cont_no\n");
		goto CONT;	
	}
	
	TYPE:
	
	printf("\nChoose Account Type : \n1.savings(Interest rate 4 p.c.p.a)\n2.fixed1(Interest rate 8 p.c.p.a)\n3.fixed2(Interest rate 8.25 p.c.p.a)\n4.current\n");
	scanf("%d", &new.acc_type);
	if(new.acc_type <= 0 || new.acc_type >= 4)		
		goto TYPE;
	
	printf("\nAmount To Deposite : ");
	scanf("%lf", &new.amount);

	DATE:
	
	printf("\nTodays date (dd mm yy) : ");
	scanf("%d%d%d", &new.dod.date, &new.dod.month, &new.dod.year);
	if(cheak_date(new.dod.date, new.dod.month, new.dod.year) == 0) {
		printf("\nDate Error...\n");		
		goto DATE;
	}	
	
	append(l, new);
	
	fprintf(fp,"%s %d/%d/%d %s %s %s %d %lf %d/%d/%d %ld", new.name, new.dob.date, new.dob.month, new.dob.year, new.addrs,new.aadhar, new.cont_no, new.acc_type, new.amount, new.dod.date, new.dod.month, new.dod.year, new.acc_no);
	
	printf("\n\t\tYOUR ACCOUNT IS CREATED SUCCESSFULLY.....\n");
	fclose(fp);
	printf("NAME : %s\nACCOUNT NO. : %ld\n", new.name, new.acc_no);

}

void view_costmers() {
	
	traverse(l);
}

void transaction(long int a) {
	info *trans;
	trans_date t;
	int flag = 0, b, days;
	double money;
	long int c;
	
	transacc:
	
	printf("please re-enter your account number\n");
	scanf("%ld", &c);
	if(a == c) {	
		trans = search(l, a);
		if(trans == NULL) {
			printf("ACCOUNT NUMBER IS INVALID...\n");
		}
		else {
			printf("Enter Todays Date(dd mm yy) : ");
			scanf("%d%d%d", &t.d, &t.m, &t.y);
			
			days = date_difference(t, trans);
			
			if((trans->acc_type == fixed1) || (trans->acc_type == fixed2))
				printf("TRANSACTION IS NOT ALLOWED ACCOUNT IS FIXED...\n");
			else {
				TRANS:
				printf("1.Deposite\n2.withdraw\n");
				scanf("%d", &b);
				if(b < 0 || b > 2) {
					printf("INVALID CHOICE...\n");
					goto TRANS;
				}
				
				trans->dod.date = t.d;
				trans->dod.month = t.m;
				trans->dod.year = t.y;
				
				if(b == deposite) {
					printf("Enter amount to deposite\n");
					scanf("%lf", &money);
					trans->amount = simple_interest(trans->amount, rates, days);
					trans->amount = trans->amount + money;
				}
				else {
					 if(b == withdraw) {
						printf("Enter amount to wihdraw\n");
						scanf("%lf", &money);
						trans->amount = simple_interest(trans->amount, rates, days);
						if(money > trans->amount) {
							printf("TRANSACTION INVALID YOU DO NOT HAVE ENOUGH BALENCE\n");
							return;
						}				
						else
							trans->amount = trans->amount - money;
							printf("REMAINING AMOUNT : Rs %lf\n", trans->amount);				
					}	
				}	 	
			}
		}
	}
	else {
		printf("account number does not match\n");
		goto transacc;
	}
	save_info(l);
}

void balence(long int a) {
	info *p;
	int days;
	trans_date t;
	printf("Enter Todays Date : ");
	
	BAL:
	
	scanf("%d%d%d", &t.d, &t.m, &t.y);
	if(cheak_date(t.d, t.m, t.y) == 0) {
		printf("\nDate Error...\n");
		goto BAL;
	}
	
	p = search(l, a);	

		if(p) {
			days = date_difference(t, p);
			/* on fixed account of 1 year rate of interest is 8 % p.a. quaterly compounding
			 * on fixed account of 2 year rate of interest is 8.25% p.a quaterly compounding
			 * on savings account rate interest is 4 %
	        	 * On current account there will be no interest
			 */
		switch(p->acc_type) {
				case fixed1:	
					printf("AMOUNT DEPOSITED :Rs. %lf\nBALENCE AFTER 1 YEAR : Rs %lf", p->amount, compound_interest(p->amount, ratef1, 4 * 1));
					break;					
				case fixed2:				
					printf("AMOUNT DEPOSITED :RS.%lf\nBALENCE AFTER 2 YEAR: Rs %lf\n", p->amount, compound_interest(p->amount, ratef2, 4 * 2));
					break;	
				case savings:				
					printf("AVAILABLE BALENCE : Rs %lf\n", simple_interest(p->amount, rates, days));
					break;				
				case current:
					printf("AVAILABLE BALENCE : Rs %lf\n", p->amount);
					break;
				default:
					printf("INVALID ACCOUNT");
					break;
		}	
	}
	else
		printf("INVALID ACCOUNT NUMBER\n");	
}

void modify_acc(long int a) {
	
}

void close_account(long int a) {
	info *p;
	int days, d;
	trans_date t;
	long int b;
	float deposite;
	printf("please re-enter your account number\n");
	scanf("%ld", &b);
	if(a == b) {
		printf("Enter Todays Days :");
		
		CLOSE:
		
		scanf("%d%d%d", &t.d, &t.m, &t.y);
		if(cheak_date(t.d, t.m, t.y) == 0) {
			printf("\nDate Error...\n");
			goto CLOSE;
		}
		
		p = search(l, a);

		days = date_difference(t, p);

		if(p) {
			deposite = p->amount;
			/* on fixed account of 1 year rate of interest is 8 % p.a. quaterly compounding
		 	 * on fixed account of 2 year rate of interest is 8.25% p.a quaterly compounding
			 * If you close fixed account before maturity 2% rate penalty will be considered and interest calculated by simple interest
		 	 * on savings account rate interest is 4 %
			 * On current account there will be no interest
			 */
			switch(p->acc_type) {
				case fixed1:
					if(days < 365) {
						printf("YOU ARE BREAKING YOUR FIXED ACCOUNT BEFORE MATURITY PENALTY OF 2 RATE WILL BE CONSIDERED\n");
						printf("Do You Want To Continue\n1.YES\n2.NO\n");
						scanf("%d", &d);
						if(d == 2)
							return;
						else
							p->amount = simple_interest(p->amount, ratef1 - 2, days);
					}
					else					
						p->amount = compound_interest(p->amount, ratef1, 4 * 1);
					printf("NAME : %s\nACC_NO.: %ld\nAMOUNT :Rs. %lf\nINTEREST : %lf\n", p->name, p->acc_no, p->amount, p->amount 							- deposite);
					break;				
				case fixed2:
					if(days < (2 * 365)) {
						printf("YOU ARE BREAKING YOUR FIXED ACCOUNT BEFORE MATURITY PENALTY OF 2 RATE WILL BE CONSIDERED\n");
						printf("Do You Want To Continue\n1.YES\n2.NO\n");
						scanf("%d", &d);
						if(d == 2)
							return;
						else 
							p->amount = simple_interest(p->amount, ratef2 - 2, days);
					}	
					else							
						p->amount = compound_interest(p->amount, ratef2, 4 * 2);
					printf("NAME : %s\nACC_NO.: %ld\nAMOUNT :Rs. %lf\nINTEREST : %lf\n", p->name, p->acc_no, p->amount, p->amount 							- deposite);
					break;				
				case savings:
						p->amount = simple_interest(p->amount, rates, days);
						printf("NAME : %s\nACC_NO.: %ld\nAMOUNT :Rs. %lf\n", p->name, p->acc_no, p->amount);
					break;				
				case current:
					printf("YOU DIDN'T GET INTEREST\n");
					printf("NAME : %s\nACC_NO.: %ld\nAMOUNT :Rs. %lf\n", p->name, p->acc_no, p->amount);
					break;
				default:
					printf("INVALID ACCOUNT");
					break;
			}
			
			removelist(l, p);
			printf("YOUR ACCOUNT IS SUCCESSFULLY CLOSED\n");
			save_info(l);
		}	
		else
			printf("ACCOUNT NUMBER IS INVALID\n");	
	}
	else
		printf("account number does not match\n");
	
}

void menu() {
	int choice, count = 1;
	info t;
	long int a;
	while(1) {
		printf("MENU :\n1.CREAT NEW ACCOUNT\n2.VIEW COSTMERS LIS\n3.TRANSACTION\n4.BALENCE ENQUIRY\n5.MODIFY ACCOUNT\n6.CLOSE ACCOUNT\n7.EXIT\n");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				creat_acc();
				break;
			case 2:
				view_costmers();
				break;
			case 3:	
				printf("Enter your account number\n");
				scanf("%ld", &a);
				transaction(a);
				break;
			case 4:	
				printf("Enter your account number\n");
				scanf("%ld", &a);
				balence(a);				
				break;
			case 5:
				printf("Enter your account number\n");
				scanf("%ld", &a);				
				modify_acc(a);
				break;
			case 6:
				printf("Enter your account number\n");
				scanf("%ld", &a);				
				close_account(a);
				break;
			case 7:
				return;
				break;
			default:
				printf("Enter valid choice\n");	
				break;
		}
	}	
}
