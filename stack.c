#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "function.h"

void push(stack *s, list *l) {
	s->l[s->i]= l;
	(s->i)++;
}

list *pop(stack *s) {
	list *t = (list *)malloc(sizeof(list));
	t = s->l[s->i - 1];
	(s->i)--;
	return t;
}
int empty(stack *s) {
	return s->i == 0;
}
int full(stack *s) {
	return s->i == MAX;
}

void sinit(stack *s) {
	s->i = 0;
}

void oparand_push(oparand_stack *s, list *l) {
	s->l[s->i]= l;
	(s->i)++;
}

list *oparand_pop(oparand_stack *s) {
	list *t = (list *)malloc(sizeof(list));
	t = s->l[s->i - 1];
	(s->i)--;
	return t;
}
int oparand_empty(oparand_stack *s) {
	return s->i == 0;
}
int oparand_full(oparand_stack *s) {
	return s->i == MAX;
}

void oparand_init(oparand_stack *s) {
	s->i = 0;
}


void oparator_push(oparator_stack *s, char num) {
	s->a[s->i]= num;
	(s->i)++;
}

char oparator_pop(oparator_stack *s) {
	char t = s->a[s->i - 1];
	(s->i)--;
	return t;
}
int oparator_empty(oparator_stack *s) {
	return s->i == 0;
}
void oparator_init(oparator_stack *s) {
	s->i = 0;
}
