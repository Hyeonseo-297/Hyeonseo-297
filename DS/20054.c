#include<stdio.h>
#include<stdlib.h>
//#define NULL ((void *)0)

//트리 가짓수 세기-높이가 k개 이하인 bst생성 경우의 수
//가지수 구하려면 숫자마다 insert순서를 부여해야 함
typedef struct node{
    int data;
    struct node *left, *right;
    int ht;
}node;

int BF(node *n);
int insert(int k, int x, node *n);

int main(){
    node* root = NULL;
    int n, k;

    scanf("%d %d\n",&n, &k);
    for (int i = 0; i < n; i++){
        insert(k, i, root);
        }
}

//left에 노드가 있으면 ht값 +1 = a, right도 마찬가지 =b, bf = a-b 
int BF(node *n){
    int lh,rh;
    if(n==NULL)
    return(0);
 
    if(n->left==NULL)
        lh=0;
    else
        lh=1+n->left->ht;
 
    if(n->right==NULL)
        rh=0;
    else
        rh=1+n->right->ht;
        
        return(lh-rh);
        }

int insert(int k, int x, node *n){
    int cnt = 0;
    if(x < n->data){
        if(!n->left){
            n=(node*)malloc(sizeof(node));
            n->left=x;
            }
        else{ insert(k, x,n->left);}
    }
    else{
        if(!n->right){
            n=(node*)malloc(sizeof(node));
            n->right=x;
            }
        else{ insert(k, x,n->right);}
    }
}


//int count_tree(int range, int height, node*node){
    //높이 구하는 함수

    //인서트 함수 
        //중복 검사


    //count     


//}

