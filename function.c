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
#include<string.h>
#include<stdlib.h>
#include"list_stack.h"
#include"queue.h"

typedef struct trans_date {			//structure for transaction date
	int d, m ,y;
}trans_date;  

typedef struct staff {				//structure to store staff information
	char name[40], cont_no[10];
	int t;
	struct staff *next;
}staff;

void view_account();
int date_difference(); 
double simple_interest(double, float, int);
double compound_interest(double, float, int);
void creat_acc();
void transaction(long int);
void balence(long int);
void trans_history(long int a);
void modify_acc(long int);
void staff_info();
void close_account(long int);
void menu();

enum bank { savings = 1, fixed1, fixed2, current};

enum transaction { deposite = 1, withdraw};

float rates = 4.00, ratef1 = 8.00, ratef2 = 8.25;

/* this function cheaks the entered date is valid or not*/
int cheak_date(int d, int m, int y) {
		if(m > 12 || d > 31 || m <= 0 || d <= 0 || y < 1900)
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

/* This Function Calculates Number Of Days Between Two Entered Dates*/
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


/* function to calculate simple interest on amount
 * p is the investment amount of savings account,
 * days is duration of duratin
 * & r is rate on FD
 */
double simple_interest(double p, float rate, int days) {			
	float n;
	double si;
	if(days == 0)
		return p;
	n = days / 365.00;						//convert days to equivalent year
	si = (p * n * rate) / 100.00;
	p = p + si;
	return p;
}

/* Function calculate compound interest on amount by using recursion
 * p is the investment amount of Fixed Deposite,
 * n is duration of FD
 * & r is rate on FD
 */
double compound_interest(double p, float r, int n) {  
	if(n <= 0)
		return p;
	return (compound_interest(p*(1 + (r/400)), r, n - 1));
}

/* Function to creat account and append it to linked list */
void creat_acc() {	
	system("clear");
	info new;
	FILE *fp;
	int a, i = 0;
	
	fp = fopen("data.txt", "a+");
	
	if(fp == NULL) {
		printf("error");
		return;
	}
	
	if(l->tail)
		new.acc_no = 100000000 + (l->tail->acc_no % 10 + 1);
	else
		new.acc_no = 100000000;
	
	printf("\nFull Name (ALL LETTERS MUST BE IN CAPITAL) : ");
	scanf(" %[^\n]", new.name);
	
	while(new.name[i] != '\0') {
		if(new.name[i] == ' ')
			new.name[i] = '_';
		i++;	
	}

	DOB:

	printf("\nDate Of Birth (dd mm yyyy) : ");
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
	
	printf("\ndo you have PAN/AADHAR number :\n1.YES\n2.NO\n");
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
	
	if(strlen(new.cont_no) != 10) {
		printf("\nEnter Valid Cont_no...\n");
		goto CONT;	
	}
	
	TYPE:
	
	printf("\nChoose Account Type : \n1.savings(Interest rate 4 p.c.p.a)\n2.fixed1(For 1 year Interest rate 8 p.c.p.a)\n3.fixed2(For 2 year Interest rate 8.25 p.c.p.a)\n4.current\n");
	
	scanf("%d", &new.acc_type);
	
	if(new.acc_type <= 0 || new.acc_type > 4)		
		goto TYPE;
	
	printf("\nAmount To Deposite : ");
	scanf("%lf", &new.amount);

	DATE:
	
	printf("\nTodays date (dd mm yyyy) : ");
	scanf("%d%d%d", &new.dod.date, &new.dod.month, &new.dod.year);
	
	if(cheak_date(new.dod.date, new.dod.month, new.dod.year) == 0 || new.dod.year < 2015) {
		printf("\nEnter Valid Date...\n");		
		goto DATE;
	}	
	
	new.doc = new.dod;
	
	append(l, new);						//Function witch append new account entered in linked list 
	
	fprintf(fp,"%s %d/%d/%d %s %s %s %d %lf %d/%d/%d %ld %d/%d/%d", new.name, new.dob.date, new.dob.month, new.dob.year, new.addrs,new.aadhar, new.cont_no, new.acc_type, new.amount, new.dod.date, new.dod.month, new.dod.year, new.acc_no, new.doc.date, new.doc.month, new.doc.year);
	
	printf("\n\t\tYOUR ACCOUNT IS CREATED SUCCESSFULLY.....\n");
	
	fclose(fp);
	
	printf("NAME : %s\nACCOUNT NO. : %ld\nAvailable Balence : %lf\n", new.name, new.acc_no, new.amount);
	
	fp = fopen("transaction_history.txt", "a"); 		//opens a file to store transaction history
	
	if(fp == NULL) {
		printf("ERROR\n");
		return;
	}
	
	trans_his t;
	
	strcpy(t.ttype, "deposite");
	t.acc_no = new.acc_no;
	t.d = new.dod.date;
	t.m = new.dod.month;
	t.y = new.dod.year;
	t.amount = new.amount;
	t.total = new.amount;
	fwrite(&t, 1, sizeof(trans_his), fp);
	fclose(fp);
}

/* Function shows view Account Holder Information */
void view_account() {	
	system("clear");
	int ch, i = 0,count = 0;;
	long int a;
	info *x;
	char name[40];
	
	info :
	
	printf("1.View All Account\n2.Search By Name\n3.Search By Account Number\n4.Exit\n");
	scanf("%d", &ch);
	system("clear");
	switch(ch) {
		case 1:
			traverse(l);
			break;
		
		case 2:
			printf("Enter Full Name(LETTERS MUST BE CAPITAL) : ");
			scanf(" %[^\n]", name);
			
			while(name[i] != '\0') {
				if(name[i] == ' ')
					name[i] = '_';
				i++;
			}
			
			s = (stack *)malloc(sizeof(stack));
			stackinit(s);
			searchname(name);
			
			while(!stackempty()) {
				x = pop(s);
				count++;
				printf("-------------------------------------------------------------------------------------------------\n");
				
				switch(x->acc_type) {
					case 1:
						printf("Name : %s\nDate Of Birth : %d/%d/%d\nAddress : %s\nUID : %s\nCont_no : %s\nAccount Type : Savings\nBalence :Rs. %lf\nAccount Number : %ld\nCreated On: %d/%d/%d\n", x->name, x->dob.date, x->dob.month, x->dob.year, x->addrs, x->aadhar, x->cont_no, x->amount, x->acc_no, x->doc.date, x->doc.month, x->doc.year);
						break;
				
					case 2:
						printf("Name : %s\nDate Of Birth : %d/%d/%d\nAddress : %s\nUID : %s\nCont_no : %s\nAccount Type : Fixed1\nBalence :Rs. %lf\nAccount Number : %ld\nCreated On: %d/%d/%d\n", x->name, x->dob.date, x->dob.month, x->dob.year, x->addrs, x->aadhar, x->cont_no, x->amount, x->acc_no, x->doc.date, x->doc.month, x->doc.year);
						break;
	
					case 3:
						printf("Name : %s\nDate Of Birth : %d/%d/%d\nAddress : %s\nUID : %s\nCont_no : %s\nAccount Type : Fixed2\nBalence :Rs. %lf\nAccount Number : %ld\nCreated On: %d/%d/%d\n", x->name, x->dob.date, x->dob.month, x->dob.year, x->addrs, x->aadhar, x->cont_no, x->amount, x->acc_no, x->doc.date, x->doc.month, x->doc.year);
						break;
	
					case 4:
						printf("Name : %s\nDate Of Birth : %d/%d/%d\nAddress : %s\nUID : %s\nCont_no : %s\nAccount Type : Current\nBalence :Rs. %lf\nAccount Number : %ld\nCreated On: %d/%d/%d\n", x->name, x->dob.date, x->dob.month, x->dob.year, x->addrs, x->aadhar, x->cont_no, x->amount, x->acc_no, x->doc.date, x->doc.month, x->doc.year);
						break;
				}
			
			}
			
			if(count == 0)
				printf("No Result Found For %s\n", name);
			break;
		
		case 3:
			printf("Enter Account Number\n");
			scanf("%ld", &a);
			
			x = search(l, a);
			if(x) {
				printf("------------------------------------------------------------------------------------------------\n");
				
				switch(x->acc_type) {
					case 1:
						printf("Name : %s\nDate Of Birth : %d/%d/%d\nAddress : %s\nUID : %s\nCont_no : %s\nAccount Type : Savings\nBalence :Rs. %lf\nAccount Number : %ld\nCreated On: %d/%d/%d\n", x->name, x->dob.date, x->dob.month, x->dob.year, x->addrs, x->aadhar, x->cont_no, x->amount, x->acc_no, x->doc.date, x->doc.month, x->doc.year);
						break;
				
					case 2:
						printf("Name : %s\nDate Of Birth : %d/%d/%d\nAddress : %s\nUID : %s\nCont_no : %s\nAccount Type : Fixed1\nBalence :Rs. %lf\nAccount Number : %ld\nCreated On: %d/%d/%d\n", x->name, x->dob.date, x->dob.month, x->dob.year, x->addrs, x->aadhar, x->cont_no, x->amount, x->acc_no, x->doc.date, x->doc.month, x->doc.year);
						break;
				
					case 3:
						printf("Name : %s\nDate Of Birth : %d/%d/%d\nAddress : %s\nUID : %s\nCont_no : %s\nAccount Type : Fixed2\nBalence :Rs. %lf\nAccount Number : %ld\nCreated On: %d/%d/%d\n", x->name, x->dob.date, x->dob.month, x->dob.year, x->addrs, x->aadhar, x->cont_no, x->amount, x->acc_no, x->doc.date, x->doc.month, x->doc.year);
						break;
					
					case 4:
						printf("Name : %s\nDate Of Birth : %d/%d/%d\nAddress : %s\nUID : %s\nCont_no : %s\nAccount Type : Current\nBalence :Rs. %lf\nAccount Number : %ld\nCreated On: %d/%d/%d\n", x->name, x->dob.date, x->dob.month, x->dob.year, x->addrs, x->aadhar, x->cont_no, x->amount, x->acc_no, x->doc.date, x->doc.month, x->doc.year);
						break;
				}
			
			}
			else
				printf("Account Number Is Not Found\n");
			break;
			
		case 4:
			return;
		default:
			printf("Invalid Choice....\n");
			goto info;
	}
	printf("---------------------------------------------------------------------------------------------------------\n");
}

/* Function for Deposition and withdrawal from account */
void transaction(long int a) {
	info *trans;
	trans_date t;
	trans_his h;
	int b, days;
	double money;
	long int c;
	FILE *fp;
	fp = fopen("transaction_history.txt", "a");
	if(fp == NULL) {
		printf("ERROR\n");
		return;
	}
	transacc:
	
	printf("please re-enter your account number\n");
	scanf("%ld", &c);
	if(a == c) {	
		trans = search(l, a);
		if(trans == NULL) {
			printf("ACCOUNT NUMBER IS INVALID...\n");
		}
		else {
			h.acc_no = a;
			
			transdate:
			
			printf("Enter Todays Date(dd mm yyyy) : ");
			scanf("%d%d%d", &t.d, &t.m, &t.y);
			
			if(cheak_date(t.d, t.m, t.y) == 0) {
				printf("\nEnter Valid Date...\n");
				goto transdate;
			}
			
			days = date_difference(t, trans);
			
			if((trans->acc_type == fixed1) || (trans->acc_type == fixed2))
				printf("TRANSACTION IS NOT ALLOWED ACCOUNT IS FIXED...\n");
			
			else {
				system("clear");
				TRANS:
				printf("1.Deposite\n2.withdraw\n3.Exit\n");
				scanf("%d", &b);
				if(b < 0 || b > 3) {
					printf("INVALID CHOICE...\n");
					goto TRANS;
				}
				
				if(b == 3)
					return;
				
				h.d = trans->dod.date = t.d;
				h.m = trans->dod.month = t.m;
				h.y = trans->dod.year = t.y;
				system("clear");
				if(b == deposite) {
					printf("Enter amount to deposite\n");
					scanf("%lf", &money);
					h.amount = money;
					strcpy(h.ttype, "deposite");
					trans->amount = simple_interest(trans->amount, rates, days);
					trans->amount = trans->amount + money;
					h.total = trans->amount;
					printf("Deposition is completed...\n");
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
						else {
							h.amount = money;
							strcpy(h.ttype, "Withdraw");
							trans->amount = trans->amount - money;
							h.total = trans->amount;
							printf("Transaction Completed\nREMAINING AMOUNT : Rs %lf\n", trans->amount);				
						}
					}	
				}
				fwrite(&h, 1, sizeof(trans_his), fp);
				fclose(fp);	 	
			}
		}
	}
	else {
		printf("account number does not match\n");
		goto transacc;
	}
	save_info(l);
}

/* Function For Balance Inquiry */
void balence(long int a) {
	system("clear");
	info *p;
	int days;
	trans_date t;

	p = search(l, a);	
	
	if(p) {
		
		/* on fixed account of 1 year rate of interest is 8 % p.a. quaterly compounding
		 * on fixed account of 2 year rate of interest is 8.25% p.a quaterly compounding
		 * on savings account rate interest is 4 %
	         * On current account there will be no interest
		 */
		printf("----------------------------------------------------------------------------------------------------------------\n");
		switch(p->acc_type) {
				case fixed1:	
					printf("AMOUNT DEPOSITED :Rs. %lf\nBALENCE AFTER 1 YEAR : Rs %lf\n", p->amount, compound_interest(p->amount, ratef1, 4 * 1));
					break;					
				
				case fixed2:				
					printf("AMOUNT DEPOSITED :RS.%lf\nBALENCE AFTER 2 YEAR: Rs %lf\n", p->amount, compound_interest(p->amount, ratef2, 4 * 2));
					break;	
				
				case savings:
					printf("Enter Todays Date : ");
	
					BAL:
	
					scanf("%d%d%d", &t.d, &t.m, &t.y);
					if(cheak_date(t.d, t.m, t.y) == 0) {
						printf("\nEnter Valid Date...\n");
						goto BAL;
					}

					days = date_difference(t, p);				
					
					printf("AVAILABLE BALENCE : Rs %lf\n", simple_interest(p->amount, rates, days));
					break;				
				
				case current:
					printf("AVAILABLE BALENCE : Rs %lf\n", p->amount);
					break;
				
				default:
					printf("INVALID ACCOUNT");
					break;
		}
		printf("----------------------------------------------------------------------------------------------------------------\n");
	}
	else
		printf("INVALID ACCOUNT NUMBER\n");	
}

/* function to modify account informaation*/
void modify_acc(long int a) {
	system("clear");
	info *p;
	p = search( l, a);
	int ch, i = 0;
	if(p) {
		system("clear");
		while(1) {
			printf("\n1.name\n2.Date Of Birth\n3.Address\n4.Contact Number\n5.UID(If Not Entereed Or In Case Incorrect\n6.Complete Modification\n");
			printf("\n Enter choice which you want to modify : ");
			scanf("%d",&ch);
			switch(ch) {
				
				case 1:
					printf("Name : %s\n\n", p->name);
					printf("Enter Name : ");
					scanf(" %[^\n]", p->name);
					while(p->name[i] != '\0') {
						if(p->name[i] == ' ')
						p->name[i] = '_';
						i++;
					}
					break;
				
				case 2:
					printf("DOB : %d/%d/%d\n\n", p->dob.date, p->dob.month, p->dob.year);
					printf("Enter Date Of Birth (dd mm yyyy) : ");
					mdate:
					scanf("%d%d%d", &p->dob.date, &p->dob.month, &p->dob.year);
					if(cheak_date(p->dob.date, p->dob.month, p->dob.year) == 0){
						printf("Enter valid date...\n");
						goto mdate;	
					}
					break;
				
				case 3:
					printf("Address : %s\n\n", p->addrs);
					printf("Enter Address : ");
					scanf(" %[^\n]", p->addrs);
					while(p->addrs[i] != '\0') {
						if(p->addrs[i] == ' ')
							p->addrs[i] = '_';
						i++;
					}
					break;
				
				case 4:
					printf("Contact No. : %s\n\n", p->cont_no);
					printf("Enter Contact Number : ");
					mcont_no:
				        scanf("%s", p->cont_no);
					if(strlen(p->cont_no) < 10 || strlen(p->cont_no) > 10) {
						printf("Enter valid Cont_no\n");
						goto mcont_no;
					}
					break;
				
				case 5:
					printf("UId : %s\n\n", p->aadhar);
					printf("Enter UID : ");
					scanf("%s", p->aadhar);	
					break;
				
				case 6:
					save_info(l);
					return;
					break;
				
				default:
					printf("Invalid Choice\n");
			}
		}	
	}
	else
		printf("Account Number Is Invalid\n");		
}

/* Function For Transaction History */
void trans_history(long int a) {				//function for printing transaction history from file
	system("clear");
	trans_his h;
	info *p;
	trans_date t;
	queue q;
	int ch;
	
	qinit(&q);
	
	p = search(l, a);
	
	if(p == NULL) {
		printf("Account Number Is Invalid...");
		return;
	}
	
	his :
	
	printf("1.ALL TRANSACTION\n2.FROM DATE\n3.EXIT TRANSACTION HISTORY\n");
	scanf("%d", &ch);
	FILE *fp;
	fp = fopen("transaction_history.txt", "r");
	if(fp == NULL) {
		printf("Yet No Transaction Through Bank As Yet No Account is Created\n");
		return;
	}
	system("clear");
	switch(ch) {
		case 1:
			while(fread(&h, 1, sizeof(trans_his), fp)) {
				if(h.acc_no == a)
					enqueue(&q, h);
			}
			break;
		
		case 2:
			hisdate :
			
			printf("Enter Date (dd mm yyyy) : \n");
			scanf("%d%d%d", &t.d, &t.m, &t.y);
			
			if(cheak_date(t.d, t.m, t.y) == 0) {
				printf("\nDate Error...\n");
				goto hisdate;
			}
			
			while(fread(&h, 1, sizeof(trans_his), fp)) {
				if(h.acc_no == a) {
					if(h.y > t.y) 	
						enqueue(&q, h);
					else {
						if((h.y == t.y) && (h.m > t.m)) 
							enqueue(&q, h);
						else { 
							if((h.y == t.y) && (h.m == t.m) && (h.d >= t.d))
								enqueue(&q, h);
						}
					}
				}
			}
			break;
		
		case 3:
			return;
		
		default:
			printf("Invalid Choice\n");
			goto his;
	}
	printf("Account Number : %ld\n", a);
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("DATE	TYPE OF TRANSACTION	AMOUNT(Rs.)	AVAILABLE BALENCE(Rs.)\n");
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	qprint(&q);
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	fclose(fp);
}

/* Function For Staff Information*/
void staff_info(char *opass) {
	system("clear");
	FILE *fp, *fd;
	char str[40], *npass;
	staff **a, *t, *temp, p;
	int i = 0, ch, to, flag;
	
	a = (staff **)malloc(sizeof(staff *) * 4);
	
	for(i = 0; i < 4; i++) {
		a[i] = (staff *)malloc(sizeof(staff));
		a[i]->next = NULL;	
	}		
	
	strcpy(a[0]->name, "BANK MANAGER");
	strcpy(a[1]->name, "Front Desk Officer");
	strcpy(a[2]->name, "Clerk");
	strcpy(a[3]->name, "Service And Security");
	
	fp = fopen("staff.txt", "a+");
	
	while(fscanf(fp, "%s %s %d", p.name, p.cont_no, &p.t) != EOF) {
		temp = (staff *)malloc(sizeof(staff));		
		strcpy(temp->name, p.name);
		strcpy(temp->cont_no, p.cont_no);
		to = temp->t = p.t;
		temp->next = NULL;
		t = a[to];
		if(a[to]->next) {
			while(t->next)
				t = t->next;
			t->next = temp;
		}
		else
			a[to]->next = temp;
	}
	while(1) {

		BM :
		
		printf("\n1.View Staff Record\n2.Enter Staff Record\n3.Delete Staff Record\n4.Exit\n");
		scanf("%d", &ch);
		flag = 0;
		switch(ch) {
		
			case 1:
				system("clear");
				for(i = 0; i < 4; i++) {
					t = a[i]->next;
					printf("\n%s :\n", a[i]->name);
					while(t) {
						printf("\tname : %s\n\tcont_no : %s\n\t-------\n", t->name, t->cont_no);
						t = t->next;
					}
				}
				break;
		
			case 2:	
				staffadm :
				printf("Enter Admin Password only admin can change staff info.\n");
				scanf("%s", str);
				npass = (char *)malloc(sizeof(str));
				strcpy(npass, str);
				if((strcmp(opass, npass)) == 0) {
					system("clear");
					
					staffin :
					
					printf("Enter Staff Post\n1.Bank Manager\n2.Front Desk Officer(FDO)\n3.Clerk\n4.Services And Security\n5.Exit\n");
					scanf("%d", &to);
					if(to == 5)
						return;
					else {
						 if(to < 0 || to > 5) {
							printf("Invalid Choice\n");
							goto staffin;
						}
					}
					to--;
					if(to == 0 && (a[0]->next != NULL)) {
						printf("Bank Manager position is filled\n");
						goto BM;		
					}
				
					temp = (staff *)malloc(sizeof(staff));
				
					printf("Enter staff name\n");
					scanf(" %[^\n]", str);
				
					i = 0;
					while(str[i] != '\0') {
						if(str[i] == ' ')
							str[i] = '_';
						i++;
					}
				
					strcpy(temp->name, str);
				
					staffinfo :
				
					printf("Enter staff cont_no\n");
					scanf("%s", temp->cont_no);
				
					if(strlen(temp->cont_no) > 10 || strlen(temp->cont_no) < 9) {
						printf("Ente valid Number\n");
						goto staffinfo;
					}
				
					temp->t = to;
					temp->next = NULL;
				
					fprintf(fp, "%s	%s %d", temp->name, temp->cont_no, temp->t);
				
					t = a[to];
					if(a[to]->next) {
						while(t->next)
							t = t->next;
						t->next = temp;
					}
					else {
						a[to]->next = temp;
					}
				}
				else {
					printf("password doesn't match\n");
					goto staffadm;
				}
				break;
				
			case 3:	
				stfadmd :		
				printf("Enter Admin Password only admin can change staff info.\n");
				scanf("%s", str);
				npass = (char *)malloc(sizeof(str));
				strcpy(npass, str);
				if((strcmp(opass, npass)) == 0) {
					system("clear");
					staffdel :
					printf("Enter staff Post :\n1.Bank Manager\n2.Front Desk Officer\n3.Clerk\n4.Service And Security\n5.Exit\n");
					scanf("%d", &to);
					if(to == 5)
						return;
					else if(to < 1 || to > 5) {
						printf("Invalid chice");
						goto staffdel;
					}
					to--;
					printf("Enter name : ");
					scanf(" %[^\n]", str);
					i = 0;
					while(str[i] != '\0') {
						if(str[i] == ' ')
							str[i] = '_';
						i++;
					}
					t = a[to];
				
					while(t) {
						temp = t->next;
						if(t->next) {
							if((strcmp(temp->name, str)) == 0) {
								flag = 1;
								break;	
							}
						}
						t = t->next;
					}
					if(flag) {
						t->next = temp->next;
						free(temp);
						fp = fopen("staff.txt", "w");
						for(i = 0; i < 4; i++) {
							t = a[i]->next;
							while(t) {
								fprintf(fp, "%s	%s %d", t->name, t->cont_no, t->t);
								t = t->next;
							}
						}
						printf("Staff Record Deleted\n");
					}
					else
						printf("Name Does not exists\n");
				}
				else {
					printf("password doesn't match\n");
					goto stfadmd;
				}
				break;
			case 4: 
				fclose(fp);
				return;
		}
	}
		
}

/* Function For Closing Account*/
void close_account(long int a) {
	system("clear");
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
			printf("\nEnter Valid Date...\n");
			goto CLOSE;
		}
		
		p = search(l, a);
		if(p == NULL) {
			printf("Account Number is Invalid\n");
			return;
		}
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
						printf("..YOU ARE BREAKING YOUR FIXED ACCOUNT BEFORE MATURITY PENALTY OF 2 percent RATE WILL BE CONSIDERED..\n");
						printf("Do You Want To Continue\n1.YES\n2.NO\n");
						scanf("%d", &d);
						if(d == 2)
							return;
						else
							p->amount = simple_interest(p->amount, ratef1 - 2, days);
					}
					else					
						p->amount = compound_interest(p->amount, ratef1, 4 * 1);
					printf("NAME : %s\nACC_NO.: %ld\nAMOUNT :Rs. %lf\nINTEREST : %lf\n", p->name, p->acc_no, p->amount, p->amount - deposite);
					break;				
				case fixed2:
					if(days < (2 * 365)) {
						printf("..YOU ARE BREAKING YOUR FIXED ACCOUNT BEFORE MATURITY PENALTY OF 2 percent RATE WILL BE CONSIDERED..\n");
						printf("Do You Want To Continue\n1.YES\n2.NO\n");
						scanf("%d", &d);
						if(d == 2)
							return;
						else 
							p->amount = simple_interest(p->amount, ratef2 - 2, days);
					}	
					else							
						p->amount = compound_interest(p->amount, ratef2, 4 * 2);
					printf("NAME : %s\nACC_NO.: %ld\nAMOUNT :Rs. %lf\nINTEREST : %lf\n", p->name, p->acc_no, p->amount, p->amount - deposite);
					break;				
				case savings:
						p->amount = simple_interest(p->amount, rates, days);
						printf("NAME : %s\nACC_NO.: %ld\nAMOUNT :Rs. %lf\n", p->name, p->acc_no, p->amount);
					break;				
				case current:
					printf("YOU DIDN'T GET INTEREST AS ACCOUNT TYPE IS CURRENT\n");
					printf("NAME : %s\nACC_NO.: %ld\nAMOUNT :Rs. %lf\n", p->name, p->acc_no, p->amount);
					break;
				default:
					printf("INVALID ACCOUNT");
					break;
			}
			removelist(l, p);
			if(l->length == 0)
				remove("transaction_history.txt");
			printf("YOUR ACCOUNT IS SUCCESSFULLY CLOSED\n");
			save_info(l);
			
		}	
	}
	else
		printf("account number does not match\n");
	
}

/*Function For Printing Menu*/
void menu() {
	int choice, ch;
	long int a;
	char *npass, *opass, *tpass, *ntpass, str[40];
	FILE *fp;
	while(1) {
		fp = fopen("admin.txt", "r");
		fread(str, sizeof(opass), 1, fp);
		opass = (char *)malloc(sizeof(str));
		strcpy(opass, str);
		fclose(fp);
		printf("\n\tMENU :\n\t1.CREAT NEW ACCOUNT\n\t2.VIEW ACCOUNT HOLDER INFORMATION\n\t3.TRANSACTION\n\t4.BALENCE ENQUIRY\n\t5.MODIFY ACCOUNT\n\t6.CLOSE ACCOUNT\n\t7.TRANSACTION HISTORY\n\t8.CHANGE ADMIN PASSWORD\n\t9.STAFF INFORMATION\n\t10.EXIT\n");
		printf("Enter your choice : ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1:
				creat_acc();
				break;
			case 2:
				system("clear");
				vpass :
				printf("\nEnter Admin Password : ");
				scanf("%s", str);
				npass = (char *)malloc(sizeof(str));
				strcpy(npass, str);
				if(strcmp(npass, opass) == 0) {
					view_account();
				}
				else {
					printf("Password Doesn't Match...\n");
					goto vpass;				
				}
				break;
			case 3:	
				system("clear");
				printf("\nEnter your account number\n");
				scanf("%ld", &a);
				transaction(a);
				break;
			case 4:	
				system("clear");
				printf("\nEnter your account number\n");
				scanf("%ld", &a);
				balence(a);				
				break;
			case 5:
				system("clear");
				mpass :
				printf("\nEnter Admin Password : ");
				scanf("%s", str);
				npass = (char *)malloc(sizeof(str));
				strcpy(npass, str);
				if(strcmp(npass, opass) == 0) {
					system("clear");
					printf("Enter your account number\n");
					scanf("%ld", &a);
					modify_acc(a);
				}
				else {
					printf("Password Doesn't Match...\n");
					goto mpass;				
				}				
				break;
			case 6:
				system("clear");
				printf("\nEnter your account number\n");
				scanf("%ld", &a);				
				close_account(a);
				break;
			
			case 7:
				system("clear");
				printf("\nEnter your account number : ");
				scanf("%ld", &a);
				trans_history(a);
				break;
			case 8:
				system("clear");
				fp = fopen("admin.txt", "w");
				fread(opass, sizeof(opass), 1, fp);
				old:
				printf("\nEnter Old Pasword : ");
				scanf("%s", str);
				tpass = (char *)malloc(sizeof(str));
				strcpy(tpass, str);
				new:
				printf("Enter New Password : ");
				scanf("%s", str);
				npass = (char *)malloc(sizeof(str));
				strcpy(npass, str);
				printf("Re-enter New Password : ");
				scanf("%s", str);
				ntpass = (char *)malloc(sizeof(str));
				strcpy(ntpass, str);
				if(strcmp(tpass, opass) != 0) {
					printf("Incorrect old password\n");
					goto old;
				}
				else {
					if(strcmp(ntpass, npass) != 0) {
						printf("new password doesn't match\n");
						goto new;					
					}
					else {
						printf("password is successfully changed....\n");
						fwrite(npass, sizeof(npass), 1, fp);				
					}
				}
				fclose(fp);
				break;
			case 9:
				system("clear");
				staff_info(opass);
				system("clear");
				break;			
			case 10:
				return;
			default:
				printf("Enter valid choice\n");	
				break;
		}
	}	
}
