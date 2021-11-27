#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int LCSS(char* str1, char* str2);
void plot(int** table, int row, int col);

int main(void){
    int group;
    char str1[1000], str2[1000];
    scanf("%d", &group);
    for(int i = 0; i < group; i++){
        scanf("%s%s",str1, str2);
        printf("%d\n", LCSS(str1, str2));
    }
    return 0;
}

int LCSS(char* str1, char* str2){
    int s1_len = strlen(str1), s2_len = strlen(str2);
    int** table = (int**)malloc((s1_len + 1) * sizeof(int*));
    for(int i = 0;  i < s1_len + 1; i++)
        *(table + i) = (int*)calloc(s2_len + 1, sizeof(int));

    for(int i = 1; i <= s1_len; i++){
        for(int j = 1; j <= s2_len; j++){
            if(*(str1 + i - 1) == *(str2 + j - 1)){
                *(*(table + i) + j) =  *(*(table + i - 1) + j - 1) + 1;
            }
	        else if(*(*(table + i - 1) + j) >= *(*(table + i) + j - 1)) 
                *(*(table + i) + j) = *(*(table + i - 1) + j);
	        else *(*(table + i) + j) = *(*(table + i) + j - 1);
        }
    }
    int res = *(*(table + s1_len) + s2_len);
    free(table);
    return res;
}

