#include <stdio.h>
#include <stdlib.h>

//typedef struct MyLinkedList MyLinkedList;
typedef struct MyLinkedList{
    int val;
    struct MyLinkedList* next;
}MyLinkedList;

/** Initialize your data structure here. */
MyLinkedList* myLinkedListCreate();                                  /* 創立新串列 */
int myLinkedListGet(MyLinkedList* obj, int index);                   /* 取指定index資料 */
void myLinkedListAddAtHead(MyLinkedList* obj, int val);              /* 從頭部加入資料 */
void myLinkedListAddAtTail(MyLinkedList* obj, int val);              /* 從尾部加入資料 */
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val);  /* 加入指定index資料 */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index);        /* 刪除指定index資料 */
void myLinkedListFree(MyLinkedList* obj);
void print_LinkedList(MyLinkedList* obj);                            /* 印出所有LinkedList資料 */

int main(){
    MyLinkedList* node = myLinkedListCreate();
    myLinkedListAddAtHead(node, 2);
    print_LinkedList(node);
    myLinkedListDeleteAtIndex(node, 1);
    print_LinkedList(node);
    myLinkedListAddAtHead(node, 7);
    print_LinkedList(node);
    myLinkedListAddAtHead(node, 3);
    print_LinkedList(node);
    myLinkedListAddAtHead(node, 2);
    print_LinkedList(node);
    myLinkedListAddAtHead(node, 5);
    print_LinkedList(node);
    myLinkedListAddAtTail(node, 5);
    print_LinkedList(node);
    printf("get = %d\n",myLinkedListGet(node, 1));
    myLinkedListDeleteAtIndex(node, 6);
    print_LinkedList(node);
    myLinkedListDeleteAtIndex(node, 4);
    print_LinkedList(node);
    
    //print_LinkedList(node);
    
    return 0;
}


MyLinkedList* myLinkedListCreate() {
    MyLinkedList* head = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    if (head == NULL) printf("申請內存空間失敗\n");
    head->next = NULL;
    return head;
}

/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) {
    MyLinkedList* obj_cpy = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    obj_cpy = obj;
    int i = 0;
    while(i < index){
        i++;
        obj_cpy = obj_cpy->next;
    }
    if(obj_cpy->next != NULL) return obj_cpy->next->val;
    return -1;
}

/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    MyLinkedList* node = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    node->val = val;
    node->next = obj->next;
    obj->next = node;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList* findtail = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    MyLinkedList* node = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    findtail = obj;
    while(findtail->next != NULL){ findtail = findtail->next; }
    node->val = val;
    node->next = findtail->next;
    findtail->next = node;
}

/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    MyLinkedList* obj_cpy = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    MyLinkedList* node = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    obj_cpy = obj;
    int i = 0;
    while(i < index){
        i++;
        obj_cpy = obj_cpy->next;
    }
    node->val = val;
    node->next = obj_cpy->next;
    obj_cpy->next = node;
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList* obj_cpy = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    obj_cpy = obj;
    int i = 0;
    while(i < index){
        i++;
        obj_cpy = obj_cpy->next;
    }
    if(obj_cpy->next != NULL) obj_cpy->next = obj_cpy->next->next;
}

void myLinkedListFree(MyLinkedList* obj) {
    free(obj);
}

void print_LinkedList(MyLinkedList* obj){
    while(obj != NULL){
        printf("%d\t",obj->val);
        obj = obj->next;
    }
    printf("\n");
}
