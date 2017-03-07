#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERFLOW -2

//typedef int SElemType;
typedef char SElemType;
typedef int Status;

typedef struct {
    SElemType* base;
    SElemType* top;
    int stacksize;
}SqStack;