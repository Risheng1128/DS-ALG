/**
 * @file chess.c
 * @author Ri-Sheng Chen
 * @date 2021.03.02
 * @brief 西洋棋悔棋 重播 及libev標頭檔
 * 
 */

#ifndef _STACK_H_
#define _STACK_H_

#include "function.h"
#include <unistd.h>
#include <ev.h>
#define STACKSIZE 1000
typedef struct stack{
    int top;                         /* 堆疊index */
    uint8_t position[STACKSIZE][5];  /* 座標資訊 */
}stack;
stack regret, replay; /* 宣告悔棋 重播結構 */
void timer_action(struct ev_loop *main_loop, ev_timer *time_w, int e);    /* 計時器函式 */
void io_action(struct ev_loop *main_loop, ev_io *w, int revent);          /* 輸入座標事件函式 */
void ev_Set();                                                            /* libev設定 */
void Choose_Mode(char mode, bool *state);                                 /* 選擇模式 */
bool Regret_Chess(bool *state);                                           /* 悔棋 */
bool Replay_Chess(stack regret, stack *replay_ptr);                       /* 重播 */
void push(stack *regret_ptr, coordinate *init_ptr, coordinate *dest_ptr); /* 加元素進堆疊 */
void replay_push(stack *replay_ptr, uint8_t *position);                   /* 加元素進Replay堆疊 */
uint8_t* pop(stack *regret_ptr);                                          /* 從堆疊取元素 */
bool isEmpty(stack* ptr);                                                 /* 判斷Stack是否為空 */
bool isFull(stack* ptr);                                                  /* 判斷Stack是否為滿 */
void Save_File(char **map_data, bool state);                              /* 存檔 */
bool Loading_Game(char **map_data, bool *state);                          /* 讀檔 */

#endif