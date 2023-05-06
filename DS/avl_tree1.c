// - 준비
// 리스트는 15, 50 포함
// 198개의 랜덤 integer(1~100) 뽑고 리스트에 추가하기 (중복가능), 총 200개의 정수리스트 (키)
// list[50] 15, 50포함의 유니크 키로 AVL트리 만들기(참고)
// *중복된 수 들어오면 insert에서 컷해줘야 함
// *유니크 키가 50개보다 작으면 그 상태로 끝내야 함

// - 실행
// 인오더, 포스트오더, 프리오더 함수 먼저 실행
// 15, 20, 50, 70, 90 서치, 결과 프린트
// max key 서치 프린트
// 15보다 작은 키 "
// 50보다 큰 키 "
// 15<x<50인 키 " (50이 있는 키의 left node들은 다 50보다 작음)

// file: avl_tree.c
// subject: Data Structures
// Date: 23.04.04
// writer: Lee Hyeonseo
// Description: PWH3, implementaton of AVLtree 
//(insert, delete & traversal & compare specific key values and print(smaller, larger, between)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define RMAX 100

typedef struct node {
    int data;
    struct node* left, * right;
    int ht;
}node;

node* insert(node*, int);
node* Delete(node*, int);
void preorder(node*);
void inorder(node*);
void postorder(node*);
int height(node*);
node* rotateright(node*);
node* rotateleft(node*);
node* RR(node*);
node* LL(node*);
node* LR(node*);
node* RL(node*);
int BF(node*);
int search(node*, int);
int s_max(node*);
int smaller(node*, int);
int larger(node*, int);
int between(node*, int, int);

int main() {
    node* root = NULL; //initiallize the node(tree)
    int x, op;

    //#0 implement key list
    int k_list[200] = {15, 50};
    srand(time(NULL));
    for (int i = 2; i < 200; i++) {
        int random_no = 1 + (int)rand() % RMAX;
        k_list[i] = random_no;
    }
    //#0 insert the keys to AVLtree 
    for (int i = 0; i < 200; i++) {
        root = insert(root, k_list[i]);
    }
    //#1 Traverse and print keys in inorder, preorder, and postorder.
    printf("\n\nInorder sequence:\n");
    inorder(root);
    printf("\n");
    printf("\nPreorder sequence:\n");
    preorder(root);
    printf("\n");
    printf("\n\npostorder sequence:\n");
    postorder(root);
    printf("\n");
    //#2 Search the tree for keys 15, 20, 50, 70, 90
    search(root, 15);
    search(root, 20);
    search(root, 50);
    search(root, 70);
    search(root, 90);
    //#3 Search and print the MAX key
    s_max(root);
    //#4 Search and print all keys < 15
    printf("\nsmaller values than key is\n");
    smaller(root, 15);
    printf("\n");
    //#5 Search and print all keys > 50
    printf("\nlarger values than key is\n");
    larger(root, 50);
    printf("\n");
    //#6 Search and print 15 < all keys < 50
    printf("\nbetween values than key is\n");
    between(root, 15, 30);
}

// function to insert data in AVLtree
// argument: node* T, int x
// return: T
node* insert(node* T, int x) {
    if (T == NULL) { //if tree is empty(even no root), node -> data = x (root is X) and node ->left, right is empty.
        T = (node*)malloc(sizeof(node));
        T->data = x;
        T->left = NULL;
        T->right = NULL;
    }
    else
        if (x > T->data) {// insert in right subtree
            T->right = insert(T->right, x);
            if (BF(T) == -2)
                if (x > T->right->data)
                    T = RR(T);
                else
                    T = RL(T);
        }
        else
            if (x < T->data) {
                T->left = insert(T->left, x);
                if (BF(T) == 2)
                    if (x < T->left->data)
                        T = LL(T);
                    else
                        T = LR(T);
            }
    T->ht = height(T);
    return(T);
}

// function to delete data in AVLtree
// argument: node* T, int x
// return: T
 node* Delete(node* T, int x) {
     node* p;
     if (T == NULL) {
         return NULL;
     }
     else
         if (x > T->data) {// insert in right subtree
             T->right = Delete(T->right, x);
             if (BF(T) == 2)
                 if (BF(T->left) >= 0)
                     T = LL(T);
                 else
                     T = LR(T);
         }
         else
             if (x < T->data) {
                 T->left = Delete(T->left, x);
                 if (BF(T) == -2) //Rebalance during windup
                     if (BF(T->right) <= 0)
                         T = RR(T);
                     else
                         T = RL(T);
             }
             else {
                 //data to be deleted is found
                 if (T->right != NULL) { //delete its inorder succesor
                     p = T->right;
                     while (p->left != NULL)
                         p = p->left;
                     T->data = p->data;
                     T->right = Delete(T->right, p->data);
                     if (BF(T) == 2)//Rebalance during windup
                         if (BF(T->left) >= 0)
                             T = LL(T);
                         else
                             T = LR(T);
                 }
                 else
                     return(T->left);
             }
     T->ht = height(T);
     return(T);
 }

// function to measure the height of tree. It used in insert & delete functions and help to get BF. 
// argument: node* T
// return: rh
 int height(node* T) {
     int lh, rh;
     if (T == NULL)
         return(0);
     if (T->left == NULL)
         lh = 0;
     else
         lh = 1 + T->left->ht;

     if (T->right == NULL)
         rh = 0;
     else
         rh = 1 + T->right->ht;

     if (lh > rh)
         return(lh);
     return(rh);
 }

// function to Rotateright, it used in LL, RL function.
// argument: node* x
// return: y
 node* rotateright(node* x) {
     node* y;
     y = x->left;
     x->left = y->right;
     y->right = x;
     x->ht = height(x);
     y->ht = height(y);
     return(y);
 }

// function to rotaterleft, it used in RR, LR function
// argument: node* x
// return: y
 node* rotateleft(node* x) {
     node* y;
     y = x->right;
     x->right = y->left;
     y->left = x;
     x->ht = height(x);
     y->ht = height(y);
     return(y);
 }

// function to single rotation(left)
// argument: node* T
// return: T
 node* RR(node* T) {
     T = rotateleft(T);
     return(T);
 }

// function to single rotation(right)
// argument: node* T
// return: T
 node* LL(node* T) {
     T = rotateright(T);
     return(T);
 }

// function to double rotation(right&left)
// argument: node* T
// return: T
 node* LR(node* T) {
     T->left = rotateleft(T->left);
     T = rotateright(T);
     return(T);
 }

// function to double rotation(left&right)
// argument: node* T
// return: T
 node* RL(node* T) {
     T->right = rotateright(T->right);
     T = rotateleft(T);
     return(T);
 }
// function to get balance factor
// argument: node* T
// return: T
 int BF(node* T) {
     int lh, rh;
     if (T == NULL)
         return(0);

     if (T->left == NULL)
         lh = 0;
     else
         lh = 1 + T->left->ht;

     if (T->right == NULL)
         rh = 0;
     else
         rh = 1 + T->right->ht;

     return(lh - rh);
 }

// function to preorder traversal
// argument: node* T
// return: 
 void preorder(node* T) {
     if (T != NULL) {
         printf("%d(Bf=%d)  ", T->data, BF(T));
         preorder(T->left);
         preorder(T->right);
     }
 }

// function to inorder traversal
// argument: node* T
// return: 
 void inorder(node* T) {
     if (T != NULL) {
         inorder(T->left);
         printf("%d (Bf=%d)  ", T->data, BF(T));
         inorder(T->right);
     }
 }

 // function to postorder traversal
// argument: node* T
// return: 
 void postorder(node* T) {
     if (T != NULL) {
         postorder(T->left);
         postorder(T->right);
         printf("%d (Bf=%d)  ", T->data, BF(T));
     }
 }
 //follow the tree to find the specific key value. If key is smaller than T->data, go left and otherwise go right recursive.
// function to search the key location
// argument: node* T, int key
// return: NULL
 int search(node* T, int key){ 
     if (T == NULL) {
         return 0;
     }
     if (key == T->data) {
         printf("Find key %d (Bf=%d)\n", T->data, BF(T));
     }
     else if (key < T->data) {
         search(T->left, key);
     }
     else if (key > T->data) {
         search(T->right, key);
     }
     else {
         printf("No exist key %d", key);
     }
 }

// function to find max key value (recursive go right node)
// argument: node* T
// return: NULL
 int s_max(node* T) {
     if (T) {
         while (T && T->right != NULL) {
             T = T->right;
         }
         printf("max = %d\n", T->data);
     }
     return 0;
 }

//key보다 작은 값 출력 = key 위치의 root를 찾아서 올라가서 걔의 left node들 출력(재귀)
// function to values that smaller than key value
// argument: node* T, int key
// return: NULL
 int smaller(node* T, int key) {
     for (int i = 0; i < sizeof(T); i++) {
         if (key == T->data) {
             smaller(T->left, key);
         }
         else if (key < T->data) {
             smaller(T->left, key);
         }
         else if (key > T->data) {
             printf("%d ", T->data);
             smaller(T->right, key);
         }
         else {
             printf("no smaller value..");
         }
     }
     return 0;
 }

//key보다 큰 값 출력 = key 위치의 root로 올라가서 걔의 right node들 출력(재귀)
// function to values that larger than key value
// argument: node* T, int key
// return: NULL 
int larger(node* T, int key) {
     for (int i = 0; i < sizeof(T); i++) {
         if (key == T->data) {
             larger(T->right, key);
         }
         else if (key < T->data) {
             printf("%d ", T->data);
             larger(T->left, key);
         }
         else if (key > T->data) {
             larger(T->right, key);
         }
         else {
             printf("no larger value..");
         }
     }
}

//두 key사이 값 =  15와 50 사이 15키의 right node들 출력하다가 50되기 전에 스탑
// function to between values of key value
// argument: node* T, int key1, key2
// return: NULL 
int between(node* T, int key1, int key2) {
    for (int i = 0; i < sizeof(T); i++) {
        if (key1 == T->data) {
            if (key2 <= T->data) {
                break;
            }
            between(T->right, key1, key2);
        }
        else if (key1 < T->data) {
            printf("%d ", T->data);
            between(T->left, key1, key2);
        }
        else if (key1 > T->data) {
            if (key2 <= T->data) {
                break;
            }
            between(T->right, key1, key2);
        }
        else {
            printf("no between value..");
        }
    }
}

