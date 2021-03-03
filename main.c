#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "function.h"

#define COUNT 3000

int main(int argc, char *argv[]) {
    printf("NAME:- KULKARNI VALLABH VIVEK\nDIV:-2\tMIS:-111903118\tBATCH:-S2\nDSA1 MINI PROJECT:- BINARY PRECISION CALCULATOR\nENTER EXPRESSION\n ");
    /*FILE *fp1;*/
	int arg = 0;
	char str[COUNT];
	int x;
	list *ans;
	ans = (list *)malloc(sizeof(list));
	init(ans);

	/*fp1= fopen ("history.txt", "w");*/
	while((x = readline(str, COUNT))) {
    ans = infix(str);
		if(ans == NULL) {
			printf("Erorr in expression\n");
		}
		else {
				traverse(ans, arg);
			printf("\n");
		}
	}
	/*fclose(fp1);*/
	return 0;
}
