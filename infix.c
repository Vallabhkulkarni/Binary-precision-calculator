#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "function.h"

int precedence(char op) {
	if(op == '*' || op == '/' || op == '%')
		return 3;
	if(op == '+' || op == '-')
		return 2;
	if(op == '(')
		return 1;
	return 0;
}

int readline(char *arr, int len) {
	int k = 0;
	int ch;
	while((ch = getchar()) != '\n' && k < len - 1) {
		arr[k] = ch;
		k++;
	}
	arr[k] = '\0';
	return k;
}
list *infix(char *str) {
	list *x, *y, *z, *w;
	x = (list *)malloc(sizeof(list));
	y = (list *)malloc(sizeof(list));
	z = (list *)malloc(sizeof(list));
	w = (list *)malloc(sizeof(list));
	init(x);
	init(y);
	init(z);
	init(w);
	int reset = 1, c, b;
	char op1, op2;
	token *t;
	t = (token *)malloc(sizeof(token));
	oparator_stack cs;
	stack a;
	oparand_stack e;
	sinit(&a);
	oparator_init(&cs);
	oparand_init(&e);
	int flag = 0,settrigo = 0;
	int i = 0;
	while(1) {
		t = getnext(str, &reset);
		if(t->type == OPERAND){
				push(&a, t->l);

		}
		else if(t->type == OPERATOR) {
			switch(t->op) {
				case '+': case '/': case '*': case '-': case '%':
					oparator_push(&cs, t->op);
					break;
				case '(':
					oparator_push(&cs, t->op);
					flag++;
					break;
				case 'S':
					settrigo = 1;
					break;
				case 'C':
					settrigo = 2;
					break;
				case 'T':
					settrigo = 3;
					break;
				case ')':
					if(settrigo != 0) {
						switch(settrigo) {
							case 1:
								x = pop(&a);
								y = sine(x);
								push(&a, y);
								break;
							case 2:
								x = pop(&a);
								y = cosine(x);
								push(&a, y);
								break;
							case 3:
								x = pop(&a);
								y = tangent(x);
								push(&a, y);
								break;
						}
						settrigo = 0;
					}
					flag--;
					if(flag < 0)
						return NULL;
					while(1) {
						if(!oparator_empty(&cs)) {
							op1 = oparator_pop(&cs);
							if(op1 == '(') {
								break;
							}
						}
						else
							break;
						if(!oparator_empty(&cs))
							op2 = oparator_pop(&cs);
						c = precedence(op1);
						b = precedence(op2);
						if(c > b) {
							if(!empty(&a))
								z = pop(&a);
							else
								return NULL;
							if(!empty(&a))
								y = pop(&a);
							else
								return NULL;
							switch(op1) {
								case '+':
									push(&a, addition(y, z));
									break;
								case '-':
									push(&a, substraction(y, z));
									break;
								case '/':
									push(&a, division(y, z));
									break;
								case '*':
									push(&a, multiplication(y, z));
									break;
								case '%':
									push(&a, modulus(y,z));
									break;
							}
							if(op2 != '(') {
								if(!empty(&a))
									z = pop(&a);
								else
									return NULL;
								if(!empty(&a))
									y = pop(&a);
								else
									return NULL;
								switch(op2) {
									case '+':
										push(&a, addition(y, z));
										break;
									case '-':
										push(&a, substraction(y, z));
										break;
									case '/':
										push(&a, division(y, z));
										break;
									case '*':
										push(&a, multiplication(y, z));
										break;
									case '%':
										push(&a, modulus(y,z));
										break;
								}
							}
						}
						else if(c <= b) {
							if(!empty(&a))
								z = pop(&a);
							else
								return NULL;
							if(!empty(&a))
								y = pop(&a);
							else
								return NULL;
							if(!empty(&a))
								x = pop(&a);
							else
								return NULL;
							switch(op2) {
								case '+':
									x = addition(x, y);
									break;
								case '-':
									x = substraction(x, y);
									break;
								case '/':
									x = division(x, y);
									break;
								case '*':
									x = multiplication(x, y);
									break;
								case '%':
									x = modulus(x, y);
									break;
							}
							switch(op1) {
								case '+':
									push(&a, addition(x, z));
									break;
								case '-':
									push(&a, substraction(x, z));
									break;
								case '/':
									push(&a, division(x, z));
									break;
								case '*':
									push(&a, multiplication(x, z));
									break;
								case '%':
									push(&a, modulus(x,z));
									break;
							}
						}
					}
					break;
				default:
					printf("Default");
					return NULL;
					break;
			}
		}
		else if(t->type == END) {
			while(!empty(&a)) {
				x = pop(&a);
				oparand_push(&e, x);
			}
			char op[100];
			i = 0;
			while(!oparator_empty(&cs)) {
				op[i] = oparator_pop(&cs);
				i++;
			}
			int j = 0;
			while(j < i) {
				oparator_push(&cs, op[j]);
				j++;
			}

			while(1) {
				if(flag != 0)
					return NULL;
				if(!oparator_empty(&cs)) {
					op1 = oparator_pop(&cs);
				}
				else {
					break;
				}
				if(!oparator_empty(&cs))
					op2 = oparator_pop(&cs);
				else {
					if(!oparand_empty(&e)) {
						z = oparand_pop(&e);
					}
					else
						return NULL;
					if(!oparand_empty(&e)) {
						y = oparand_pop(&e);
					}
					else
						return NULL;
					switch(op1) {
						case '+':
							oparand_push(&e, addition(z, y));
							break;
						case '-':
							oparand_push(&e, substraction(z, y));
							break;
						case '/':
							oparand_push(&e, division(z, y));
							break;
						case '*':
							oparand_push(&e, multiplication(z, y));
							break;
						case '%':
							oparand_push(&e, modulus(z,y));
							break;
					}
					break;
				}
				c = precedence(op1);
				b = precedence(op2);
				if(c >= b) {
					if(!oparand_empty(&e)) {
						z = oparand_pop(&e);
					}
					else
						return NULL;
					if(!oparand_empty(&e)) {
						y = oparand_pop(&e);
					}
					else
						return NULL;
					switch(op1) {
						case '+':
							oparand_push(&e, addition(z, y));
							break;
						case '-':
							oparand_push(&e, substraction(z, y));
							break;
						case '/':
							oparand_push(&e, division(z, y));
							break;
						case '*':
							oparand_push(&e, multiplication(z, y));
							break;
						case '%':
							oparand_push(&e, modulus(z, y));
							break;
					}
					oparator_push(&cs, op2);
				}
				else if(c < b) {
					if(!oparand_empty(&e)) {
						z = oparand_pop(&e);
					}
					else
						return NULL;
					if(!oparand_empty(&e)) {
						y = oparand_pop(&e);
					}
					else
						return NULL;
					if(!oparand_empty(&e))
						x = oparand_pop(&e);
					else
						return NULL;
					switch(op2) {
						case '+':
							oparand_push(&e, addition(y, x));
							break;
						case '-':
							oparand_push(&e, substraction(y, x));
							break;
						case '/':
							oparand_push(&e, division(y, x));
							break;
						case '*':
							oparand_push(&e, multiplication(y, x));
							break;
						case '%':
							oparand_push(&e, modulus(y, x));
							break;
					}
					oparand_push(&e, z);
					oparator_push(&cs, op1);
				}
			}
			if(!oparand_empty(&e) && oparator_empty(&cs)) {

				y = (oparand_pop(&e));

				if(oparand_empty(&e) && oparator_empty(&cs)) {
					x = NULL;
					z = NULL;
					w = NULL;
					free(x);
					free(z);
					free(w);
					return (y);

				}
			}
		}
		else if(t->type == ERROR) {
			printf("Error");
			x = NULL;
			y = NULL;
			z = NULL;
			w = NULL;
			free(x);
			free(y);
			free(z);
			free(w);
			return NULL;
		}
  }
}
