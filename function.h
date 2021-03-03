#define OPERAND 10
#define OPERATOR 20
#define	END	40
#define ERROR	50
#define PLUS 1
#define MINUS -1
#define PI 3.1415926535
#define MAX 1024
#include<math.h>

typedef struct node {
	int num;
	int flag;
	struct node *next, *prev;
}node;

typedef struct list {
	node *head, *tail;
	int len, dec, sign;
}list;

typedef struct token {
	char op;
	int dec;
	int type;
	list *l;
	int flag;
}token;


typedef struct stack{
	int i;
	list *l[MAX];

}stack;

typedef struct oparand_stack{
	int i;
	list *l[MAX];

}oparand_stack;

typedef struct oparator_stack{
	char a[MAX];
	int i;
}oparator_stack;


token *getnext(char *, int *);
enum states { SPC, DIG, OPR, STOP, ERR };

void init(list *l);
void insert(list *l, int pos, int num);
int remov(list *l, int pos);
void traverse(list *l, int arg);
void append(list *l, int num);
int length(list *l);
int dec(list *l);
int show(list *l, int pos);

void push(stack *s, list *l);
list *pop(stack *s);
int empty(stack *s);
void sinit(stack *s);

void oparand_push(oparand_stack *s, list *l);
list *oparand_pop(oparand_stack *s);
int oparand_empty(oparand_stack *s);
void oparand_init(oparand_stack *s);

void oparator_push(oparator_stack *s, char num);
char oparator_pop(oparator_stack *s);
int oparator_empty(oparator_stack *s);
void oparator_init(oparator_stack *s);

int precedence(char op);
int readline(char *arr, int len);
list *infix(char *str);

void copy(list *l1, list *l2);
int checkzero(list *l);
list *addition(list *l1, list *l2);
list *substraction(list *l1, list *l2);
list *multiplication(list *l1, list *l2);
list *division(list *l1, list *l2);
list *modulus(list *l1, list *l2);
int compare(list *l1, list *l2);
double radian(list *l1);
list *sine(list *l);
list *cosine(list *l);
list *tangent(list *l);
