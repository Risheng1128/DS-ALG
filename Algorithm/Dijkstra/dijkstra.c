#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define COLUMN 2         /* 表示起點及終點 */
#define MAXWEIGHT 100000 /* 最大weight */

int Dijkstra(char** edge, int* weight, int edgenum, char org, char dst); /* 找最短路徑 */
int FindIndex(char* node, int nodesize, char val);  /* 找val在node裡的索引 */
int NextNode(int* distance, char* node, int nodesize, char* path, int pathsize); /* 找下一個node的索引 */
char* FindNode(char** edge, int edgenum, int* nodesize); /* 找輸入有幾個節點 */
bool isInArr(char* arr, int size, char data); /* 判斷data是否再arr裡面 */
int cmp (const void * a, const void * b); /* 排列 */ 

int main(){
    int edgenum;   /* 邊數 */
    char org, dst; /* 起點 及 終點 */
    scanf(" %c %c",&org, &dst);
    scanf("%d", &edgenum);
    char** edge = (char**)malloc(edgenum * sizeof(char*)); /* 存邊的資訊 */
    int* weight = (int*)malloc(edgenum * sizeof(int)); /* 存每個邊的Weight */
    for(int i = 0; i < edgenum; i++){
        *(edge + i) = (char*)malloc(COLUMN * sizeof(char));
        scanf(" %c %c%d", *(edge + i), *(edge + i) + 1, weight + i);
    }
    printf("%d\n", Dijkstra(edge, weight, edgenum, org, dst));
    return 0;
}

int Dijkstra(char** edge, int* weight, int edgenum, char org, char dst){
    int nodesize = 0; /* 節點總數量 */
    char* node = FindNode(edge, edgenum, &nodesize); /* 儲存全部節點 */
    char* path = (char*)malloc(nodesize * sizeof(char)); /* 掃過每個點的路徑 */
    int* distance = (int*)calloc(nodesize, sizeof(int)); /* 起點到每個點的最短距離 */
    int pathsize = 0; /* 路徑的大小 */

    for(int i = 0; i < nodesize; i++) /* 將距離先設定為MAXWEIGHT */
        *(distance + i) = MAXWEIGHT;
    
    *(path + pathsize) = org; /* 一開始儲存節點 */
    *(distance + FindIndex(node, nodesize, *(path + pathsize))) = 0; /* 一開始將起點的weight變為0 */
    while(pathsize < nodesize){ /* 還沒有走過每個點時 */
        for(int i = 0; i < edgenum; i++){
            int pre_index = FindIndex(node, nodesize, *(*(edge + i))); /* 出發點index */
            int now_index = FindIndex(node, nodesize, *(*(edge + i) + 1)); /* 目標點index */
            if(*(distance + now_index) > *(distance + pre_index) + *(weight + i)) /* 舊路徑的Weight是否大於新路徑Weight */
                *(distance + now_index) = *(distance + pre_index) + *(weight + i);
        }
        *(path + pathsize) = *(node + NextNode(distance, node, nodesize, path, ++pathsize)); /* 新增新的節點到path */
    }
    return *(distance + FindIndex(node, nodesize, dst));
}

int FindIndex(char* node, int nodesize, char val){
    for(int i = 0; i < nodesize; i++)
        if(*(node + i) == val) return i;
}

int NextNode(int* distance, char* node, int nodesize, char* path, int pathsize){
    int* tmp = (int*)malloc(nodesize * sizeof(int)); /* 複製原本的distance資訊 */
    for(int i = 0; i < nodesize; i++) /* 複製原本的distance資訊 */
        *(tmp + i) = *(distance + i);
    
    qsort(tmp, nodesize, sizeof(int), cmp); /* tmp 由小排到大 */ 
    for(int i = 0; i < nodesize; i++){ /* 找下一個還沒走過且Weight最小的點的索引(index) */
        if(*(tmp + pathsize) == *(distance + i)){
            if(!isInArr(path, pathsize, *(node + i))) {
                free(tmp);  
                return i;   
            }
        }
    }
}

char* FindNode(char** edge, int edgenum, int* nodesize){
    char* node = (char*)malloc(edgenum * COLUMN * sizeof(char));
    for(int i = 0; i < edgenum; i++){
        for(int j = 0; j < COLUMN; j++){
            if( !isInArr(node, *nodesize, *(*(edge + i) + j)) ){
                *(node + *nodesize) = *(*(edge + i) + j);
                (*nodesize)++;
            }
        }
    }
    return node;
}

int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

bool isInArr(char* arr, int size, char data){
    for(int i = 0; i < size; i++)
        if(*(arr + i) == data) return true;
    return false;
}