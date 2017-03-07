#define LIST_INIT_SIZE  10
#define LISTINCREMENT 5

typedef int ElemType;

typedef struct {
    ElemType* elem;
    int length;
    int listsize;
}SqList;
