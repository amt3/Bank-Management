#include<stdio.h>
#include<stdlib.h>
#include"list.h"
int main(){
	printf("\n\t\tWELCOME TO BANK MANAGEMENT SYSTEM\n");
	l = (list *)malloc(sizeof(list));	
	init(l);
	info i;
	FILE *fp;
	fp = fopen("data.txt", "a+");
	while((fscanf(fp, "%s %d/%d/%d %s %s %ld %d %lf %d/%d/%d %ld", i.name, &i.dob.date, &i.dob.month, &i.dob.year, i.addrs, i.aadhar, &i.cont_no, 			&i.acc_type, &i.amount, &i.dod.date, &i.dod.month, &i.dod.year, &i.acc_no)) != EOF)
		append(l, i);
	fclose(fp);
	menu();
	return 0;
}
