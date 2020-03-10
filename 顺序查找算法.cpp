#include <stdio.h>
#include <stdlib.h>
#define keyType int
typedef struct {
    keyType key;//查找表中每个数据元素的值
}ElemType;
 
typedef struct{
    ElemType *elem;//数据元素的数组
    int length;//数据数量
}SSTable;

void Create(SSTable **st,int length){
    (*st)=(SSTable*)malloc(sizeof(SSTable));
    (*st)->length=length;
    (*st)->elem =(ElemType*)malloc((length+1)*sizeof(ElemType));
    printf("输入表中的数据元素：\n");
    //从数组下标为 1 的空间开始存储数据
    for (int i=1; i<=length; i++) {
        scanf("%d",&((*st)->elem[i].key));
    }
}

int Search_seq(SSTable *st,keyType key){
    st->elem[0].key=key;
    int i=st->length;
    while (st->elem[i].key!=key) {
        i--;
    }
    return i; //如果 i=0，说明查找失败
}
int main(int argc, const char * argv[]) {
    SSTable *st;
    Create(&st, 6);
    getchar();
    printf("请输入查找数据的关键字：\n");
    int key;
    scanf("%d",&key);
    int location=Search_seq(st, key);
    if (location==0) {
        printf("0");
    }else{
        printf("数据在查找表中的位置为：%d",location);
    }
    return 0;
}
