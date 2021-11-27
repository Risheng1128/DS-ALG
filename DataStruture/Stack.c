/**
 * @file stack.c
 * @author Ri-Sheng Chen
 * @date 2021.03.23
 * @brief 利用stack製作四則運算練習
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define number 20

typedef struct stack{
    int ptr;
    char data[number];
}stack;
stack operant = { .ptr = -1, .data = " "}, operator = { .ptr = -1, .data = " " };

void postfix(char *exp_ptr, char *post_ptr, int size);   //中置式轉為後置式
void push(char *exp_ptr, stack *oper);                   //放進stack中
char caculate(char *post_ptr, int size);                 //計算最後答案
char pop(stack *oper);                                   //從stack中拿出
bool priority(char operator);                            //判斷優先序
bool isEmpty();                                          //判斷stack是否為空


int main(){
    char exp[number] = " ", post[number] = " ";
    scanf("%s",&exp);
    postfix(exp, post, strlen(exp));
    printf("postfix = %s\n",post);
    printf("ANS = %d\n",caculate(post, strlen(post)));
    return 0;
}
void postfix(char *exp_ptr, char *post_ptr, int size){
    int j = 0;
    char temp;
    for(int i = 0; i < size; i++){
        switch ( *(exp_ptr + i) ){
        case '+':
        case '-':
        case '*':
        case '/':
            if( priority(*(exp_ptr + i)) ) push(exp_ptr + i, &operator);
            else{
                while(!isEmpty() && (temp = pop(&operator)) != '('){
                    *(post_ptr + j++) = temp;
                }
                if(temp == '(') push(&temp, &operator);
                push(exp_ptr + i, &operator);
            }
            break;
        case '(':
            push(exp_ptr + i, &operator);
            break;
        case ')':
            while(!isEmpty() && (temp = pop(&operator)) != '('){
                *(post_ptr + j++) = temp;
            }
            break;
        default:
            *(post_ptr + j++) = *(exp_ptr + i);
            break;
        }
    }
    while(!isEmpty()){
        *(post_ptr + j++) = pop(&operator); 
    }
}
void push(char *exp_ptr, stack *oper){
    oper -> data[++oper->ptr] = *exp_ptr;
}
char pop(stack *oper){
    return oper->data[oper->ptr--];
}
char caculate(char *post_ptr, int size){
    char temp,ans;
    for(int i = 0; i < size; i++){
        if( *(post_ptr + i) >= '0' && *(post_ptr + i) <= '9') push(post_ptr + i, &operant);
        else{
            char first = pop(&operant) - '0', sec = pop(&operant) - '0';
            switch (*(post_ptr + i)){
            case '+':
                temp = sec + first + '0';
                push(&temp, &operant);
                break;
            case '-':
                temp = sec - first + '0';
                push(&temp, &operant);
                break;
            case '*':
                temp = sec * first + '0';
                push(&temp, &operant);
                break;
            case '/':
                temp = sec / first + '0';
                push(&temp, &operant);
                break;
            }
        }
    }
    ans = pop(&operant) - '0';
    return ans;
}
bool priority(char element){
    switch (element){
    case '+':
    case '-':
        if( operator.data[operator.ptr] != ' ' || operator.data[operator.ptr] != '(') return false;
        break;
    case '*':
    case '/':
        if( operator.data[operator.ptr] == '*' || operator.data[operator.ptr] == '/') return false;
        break;
    }
    return true;
}
bool isEmpty(){
    return (operator.ptr < 0) ? true : false;
}
