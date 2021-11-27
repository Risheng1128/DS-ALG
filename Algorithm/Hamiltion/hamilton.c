#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define COLUMN 2

int* FindNode(int** edge, int edgenum, int* nodesize);
int* clearArr(int* arr, int size);
bool Hamilton(int** edge, int edgenum);
bool isInArr(int* arr, int size, int data);
bool canBack(int** edge, int edgenum, int origin, int destinate);

int main(){
    int group, edgenum;
    const char s[2] = ",";
    char str[10];
    scanf("%d", &group);
    for(int i = 0; i < group; i++){
        scanf("%d", &edgenum);
        int** edge = (int**)malloc(edgenum * sizeof(int*));
        for(int j = 0; j < edgenum; j++){
            *(edge + j) = (int*)malloc(COLUMN * sizeof(int));
            scanf("%s", str);
            char* tmp = strtok(str, s);
            **(edge + j) = atoi(tmp + 1);
            *(*(edge + j) + 1) = atoi(strtok(NULL, s));
        }
        if(Hamilton(edge, edgenum)) printf("True\n");
        else printf("False\n");
    }
    return 0;
}

bool Hamilton(int** edge, int edgenum){
    int nodesize = 0, *node = FindNode(edge, edgenum, &nodesize);
    int* path = (int*)malloc(nodesize * sizeof(int)); /* 紀錄路徑 */
    int* death = (int*)malloc(nodesize * sizeof(int)); /* 紀錄死路的node */
    int pathindex = 0, deathindex = 0; /* 路徑索引 死路索引*/
    bool isdeath = true; /* 判斷是否進死路 */

    if(nodesize < 3) return false;
    for(int i = 0; i < nodesize; i++){
        *(path + pathindex) = *(node + i);
        while(pathindex < nodesize - 1){
            for(int j = 0; j < edgenum; j++){
                if(isInArr(death, deathindex + 1, **(edge + j)) || isInArr(death, deathindex + 1, *(*(edge + j) + 1)) ) continue; /* 確定會進死路就跳過 */

                if(**(edge + j) == *(path + pathindex) && !isInArr(path, pathindex + 1, *(*(edge + j) + 1))){ 
                /* Stack頂端 = Edge的第一行 且 第二行不在 path */
                    *(path + ++pathindex) = *(*(edge + j) + 1);
                    isdeath = false;
                    break;
                }
                if(*(*(edge + j) + 1) == *(path + pathindex) && !isInArr(path, pathindex + 1, **(edge + j)) ){ 
                /* Stack頂端 = Edge的第二行 且 第一行不在 path */
                    *(path + ++pathindex) = **(edge + j);
                    isdeath = false;
                    break;
                }
            }
            if(isdeath){
                if(deathindex == nodesize) break;
                if(isInArr(death, deathindex, *(path + pathindex))) *(path + pathindex--) = 0; /* 已經在死路裡 */
                else{
                    *(death + deathindex++) = *(path + pathindex);
                    *(path + pathindex--) = 0;
                }
            }
            isdeath = true;
        }
        if(canBack(edge, edgenum, *path, *(path + pathindex))) return true;
        path = clearArr(path, pathindex + 1);
        death = clearArr(death, deathindex);
        pathindex = 0;
        deathindex = 0;
        isdeath = true;
    }
    return false;
}

int* clearArr(int* arr, int size){
    for(int i = 0; i < size; i++)
        *(arr + i) = 0;
    return arr;
}

int* FindNode(int** edge, int edgenum, int* nodesize){
    int* node = (int*)malloc(COLUMN * edgenum * sizeof(int));
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

bool canBack(int** edge, int edgenum, int origin, int destinate){
    for(int i = 0; i < edgenum; i++){
        if(**(edge + i) == origin && *(*(edge + i) + 1) == destinate) return true;
        else if(**(edge + i) == destinate && *(*(edge + i) + 1) == origin) return true;
    }
    return false;
}

bool isInArr(int* arr, int size, int data){
    for(int i = 0; i < size; i++)
        if(*(arr + i) == data) return true;
    return false;
}