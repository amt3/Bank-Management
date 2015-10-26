#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"list.h"

void view_costmers();
int date_difference(); 
double interest_savings(double);
double interest_fixed(double, float, int);
void creat_acc();
void transaction(long int);
void balence(long int);
void modify_acc(long int);
void close_account(long int);
void menu();

enum bank { savings = 1, fixed1, fixed2, current};
enum transaction { deposite = 1, withdraw};

int date_dafference(){
	return 0;	
}

double interest_savings(double p){
	return p;
}

double interest_fixed(double p, float r, int n) {    // p is the investment amount of Fixed Deposite, n is duration of FD & r is rate on FD
	if(n <= 0)
		return p;
	return (interest_fixed(p*(1 + (r/400)), r, n - 1));
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
	printf("enter your name\n");
	scanf(" %[^\n]", new.name);
	while(new.name[i] != '\0') {
		if(new.name[i] == ' ')
			new.name[i] = '_';
		i++;	
	}
	printf("enter your date of birth in dd mm yy\n");
	scanf("%d %d %d", &new.dob.date, &new.dob.month, &new.dob.year);
	printf("enter your address\n");
	scanf(" %[^\n]", new.addrs);
	i = 0;
	while(new.addrs[i] != '\0') {
		if(new.addrs[i] == ' ')
			new.addrs[i] = '_';
		i++;	
	}
	printf("do you have adhar number :\n1.YES\n2.NO\n");
	scanf("%d", &a);
	if(a == 1) {
		printf("enter your aadhar number\n");
		scanf("%s", new.aadhar);
	}
	else 
		strcpy(new.aadhar,"-----------");
	printf("enter your contact number\n");
	scanf("%ld", &new.cont_no);
	printf("enter acc type\n1.savings\n2.fixed1 (for 1 year)\n3.fixed2 (for 2 year)\n4.current\n");
	scanf("%d", &new.acc_type);
	printf("enter amount to deposite\n");
	scanf("%lf", &new.amount);
	printf("enter todays date dd mm yy\n");
	scanf("%d%d%d", &new.dod.date, &new.dod.month, &new.dod.year);
	append(l, new);
	fprintf(fp,"%s %d/%d/%d %s %s %ld %d %lf %d/%d/%d %ld", new.name, new.dob.date, new.dob.month, new.dob.year, new.addrs, 		new.aadhar, new.cont_no, new.acc_type, new.amount, new.dod.date, new.dod.month, new.dod.year, new.acc_no);
	printf("\t\tYOUR ACCOUNT IS CREATED SUCCESSFULLY.....\n");
	fclose(fp);
	printf("NAME : %s\nACCOUNT NO. : %ld\n", new.name, new.acc_no);
}

void view_costmers() {
	traverse(l);
}

void transaction(long int a) {
	info *trans;
	int flag = 0, b;
	double money;
	long int c;
	printf("please re-enter your account number\n");
	scanf("%ld", &c);
	if(a == c) {	
		trans = search(l, a);
		if(trans == NULL) {
			printf("ACCOUNT BER IS INVALID...\n");
		}
		else {
			if((trans->acc_type == fixed1) || (trans->acc_type == fixed2))
				printf("TRANSACTION IS NOT ALLOWED ACCOUNT IS FIXED...\n");
			else {
				printf("1.Deposite\n2.withdraw");
				scanf("%d", &b);
				if(b == deposite) {
					printf("Enter amount to deposite\n");
					scanf("%lf", &money);
					trans->amount = trans->amount + money;
				}
				else {
					 if(b == withdraw) {
						printf("Enter amount to wihdraw\n");
						scanf("%lf", &money);
						if(money > trans->amount)
							printf("TRANSACTION INVALID YOU DO NOT HAVE ENOUGH BALENCE\n");				
						else {
							trans->amount = trans->amount - money;
						}
					}
					else	
						printf("INVALID CHOICE...\n");
				}	 	
			}
		}
	}
	else
		printf("account number does not match\n");
	save_info(l);
}

void balence(long int a) {
	info *p;
	p = search(l, a);
	if(p) {
		switch(p->acc_type) {
				case fixed1:						// on fixed account of 1 year rate of interest is 8 % p.a.
					printf("AVAILABLE BALENCE AFTER 1 YEAR : Rs %lf", interest_fixed(p->amount, 8, 4));
					break;						// compound interest is on 3 month so 4 * 1(duration of FD)
				case fixed2:						// on fixed account of 2 year rate of interest is 8.25% p.a
					printf("AVAILABLE BALENCE AFTER 2 YEAR : Rs %lf\n", interest_fixed(p->amount, 8.25, 8));
					break;						// compound interest is on 3 month so 4 * 2(duration of FD)
				case savings:
					printf("AVAILABLE BALENCE : Rs %lf\n", interest_savings(p->amount));
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
	long int b;
	float deposite;
	printf("please re-enter your account number\n");
	scanf("%ld", &b);
	if(a == b) {
		p = search(l, a);
		if(p) {
			deposite = p->amount;
			switch(p->acc_type) {
				case fixed1:						// on fixed account of 1 year rate of interest is 8 % p.a.
					p->amount = interest_fixed(p->amount, 8.00, 4 * 1);// compound interest is on 3 month so 4 * 1(duration of FD)
					break;				
				case fixed2:						// on fixed account of 2 year rate of interest is 8.25% p.a
					p->amount = interest_fixed(p->amount, 8.25, 4 * 2);// compound interest is on 3 month so 4 * 2(duration of FD)
					break;				
				case savings:
					p->amount = interest_savings(p->amount);
					break;				
				case current:
					printf("YOU DIDN'T GET INTEREST\n");
					break;
				default:
					printf("INVALID ACCOUNT");
					break;
			}
			printf("NAME : %s\nAMOUNT :Rs. %lf\nINTEREST : %lf\n", p->name, p->amount, p->amount - deposite);
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
