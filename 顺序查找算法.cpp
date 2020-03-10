#include <stdio.h>
#include <stdlib.h>
#define keyType int
typedef struct {
    keyType key;//���ұ���ÿ������Ԫ�ص�ֵ
}ElemType;
 
typedef struct{
    ElemType *elem;//����Ԫ�ص�����
    int length;//��������
}SSTable;

void Create(SSTable **st,int length){
    (*st)=(SSTable*)malloc(sizeof(SSTable));
    (*st)->length=length;
    (*st)->elem =(ElemType*)malloc((length+1)*sizeof(ElemType));
    printf("������е�����Ԫ�أ�\n");
    //�������±�Ϊ 1 �Ŀռ俪ʼ�洢����
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
    return i; //��� i=0��˵������ʧ��
}
int main(int argc, const char * argv[]) {
    SSTable *st;
    Create(&st, 6);
    getchar();
    printf("������������ݵĹؼ��֣�\n");
    int key;
    scanf("%d",&key);
    int location=Search_seq(st, key);
    if (location==0) {
        printf("0");
    }else{
        printf("�����ڲ��ұ��е�λ��Ϊ��%d",location);
    }
    return 0;
}
