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
int main(){
	system("clear");
	printf("\n\t\tWELCOME TO BANK MANAGEMENT SYSTEM\n");
	l = (list *)malloc(sizeof(list));	
	init(l);
	info i;
	FILE *fp;
	fp = fopen("data.txt", "a+");
	if(fp == NULL) {
		printf("Error\n");
		return 1;
	}
	while((fscanf(fp, "%s %d/%d/%d %s %s %s %d %lf %d/%d/%d %ld %d/%d/%d", i.name, &i.dob.date, &i.dob.month, &i.dob.year, i.addrs, i.aadhar, i.cont_no, &i.acc_type, &i.amount, &i.dod.date, &i.dod.month, &i.dod.year, &i.acc_no, &i.doc.date, &i.doc.month, &i.doc.year)) != EOF)
		append(l, i);
	fclose(fp);
	menu();
	return 0;
}
