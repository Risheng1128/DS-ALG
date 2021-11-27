#include <stdio.h>
#include <stdlib.h>
int insert_sort(int* data, int size);
int main(void){
    int len = 0;
    while(1){
        scanf("%d",&len);
        if(!len) return 0;
        int* data = (int*)malloc(len * sizeof(int));
        for(int i = 0; i < len; i++){
            scanf("%d",&data[i]);
        }
        printf("Optimal swapping takes %d swaps.\n",insert_sort(data, len));
        free(data);
    }
    return 0;
}
int insert_sort(int* data, int size){
    int swap = 0;
    for(int i = 0; i < size; i++){
        int j = i;
        while(j > 0){
            if(*(data + j - 1) > *(data + j)){
                int temp = *(data + j);
                *(data + j) = *(data + j - 1);
                *(data + j - 1) = temp;
                swap++;
            }
            j--;
        }
    }
    return swap;
}