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
#include"list_stack.h"
void stackinit() {
	s->i = 0;
}

void push(info a) {
	s->b[s->i] = a;
	s->i++;
}

info *pop() {
	info *a;
	a = &s->b[s->i - 1];
	s->i--;
	return a;
}

int stackempty() {
	if(s->i == 0)
		return 1;
	else
		return 0;
}

int stackfull() {
	if(s->i == MAX - 1)
		return 1;
	else
		return 0;
}
