#include <stdio.h>

typedef int TreeNode;

typedef struct LineListRec
{
    int lineno;
    struct LineListRec *next;
} * LineList;

typedef struct BucketListRec
{
    char* name;
    LineList lines;
    int memloc; // memory location for variable
    struct BucketListRec* next;
    
    TreeNode* node;// 타입 체크를 위한 노드 정보
} * BucketList;

typedef struct HashTableRec
{
    struct HashTableRec* next;
    BucketList node;
} * HashTableList;

int main( int argv, char **argc )
{
    printf("test");
}
