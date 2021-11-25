/**
 * @file chess.c
 * @author Ri-Sheng Chen
 * @date 2021.03.02
 * @brief 西洋棋遊戲實作 
 * 
 */
#include "function.h"
#include "stack.h"


char map[ROW][COLUMN] = {   {'r','n','b','q','k','b','n','r'},
                            {'p','p','p','p','p','p','p','p'},
                            {' ',' ',' ',' ',' ',' ',' ',' '},
                            {' ',' ',' ',' ',' ',' ',' ',' '},
                            {' ',' ',' ',' ',' ',' ',' ',' '},
                            {' ',' ',' ',' ',' ',' ',' ',' '},
                            {'P','P','P','P','P','P','P','P'},
                            {'R','N','B','Q','K','B','N','R'}  };

stack regret = { .top = -1 };      /* 初始化悔棋結構 */
stack replay = { .top = -1 };      /* 初始化重播結構 */

int main(void){
    memcpy(init_map, map, ROW * COLUMN * sizeof(char));
    printf("-------------------------Game Start-----------------------------\n");
    Map_Set(map_pointer);
    printf("Choose mode : Regret chess(R) Replay chess(P) Save game(S) Loading gmae(L) Nothing(N)\n");
    ev_Set();
    return 0;
}