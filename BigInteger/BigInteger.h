#ifdef biginteger_h
#define biginteger_h
struct node{
    int data;
    struct node *next;

};

struct big_int{
    struct node *head;
    int size;
    int sign;  
};

struct node * createnode(int data);
struct big_int * initialize_bigint();
void push(struct big_int *n,int val);
void display(struct big_int *n);
void truncate(struct big_int * bigInt);
struct node *reverse(struct node *head);
int compare(struct big_int* num1,struct big_int* num2);
struct big_int * addition(struct big_int * num1,struct big_int *num2);
struct big_int * subtraction(struct big_int * num1,struct big_int * num2);
struct big_int *mul(struct big_int *num1,struct big_int *num2);
struct big_int *division(struct big_int *num1,struct big_int *num2);
#endif


