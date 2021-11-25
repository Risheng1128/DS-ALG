/**
 * @file chess.c
 * @author Ri-Sheng Chen
 * @date 2021.03.02
 * @brief 西洋棋遊戲函式標頭檔
 * 
 */
#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#define ROW 8
#define COLUMN 8
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
typedef struct coordinate{
    char column;                       //西洋棋Column(a~h)
    uint8_t row;                       //西洋棋Row(1~8)
    uint8_t new_column;                //西洋棋Column轉換成矩陣Column(0~7)
    uint8_t new_row;                   //西洋棋Row轉換成矩陣Row(0~7)
}coordinate;
coordinate init, dest;

#include "stack.h"
void Map_Set(char **map_data);         //地圖設定
bool Move(bool state);                 //棋移動
bool Check_Rule(bool state);           //判斷每種棋的走法是否正確
bool Check_Straight_Line(void);        //判斷直線(上下左右)
bool Check_Slant_Line(void);           //判斷斜直線(slop = 1 or -1)
bool Check_Win(void);                  //判斷勝利
char *map_pointer[ROW];
char map[ROW][COLUMN];
char init_map[ROW][COLUMN];
#endif