/**
 * @file chess.c
 * @author Ri-Sheng Chen
 * @date 2021.03.02
 * @brief 西洋棋遊戲函式庫
 * 
 */
#include "function.h"

void Map_Set(char **map_data){
    for(uint8_t i = 0; i < ROW; i++){
        map_data[i] = map[i];
    }
    for(uint8_t i = 0; i < ROW; i++){
        printf("%d\t",ROW - i);
        for(uint8_t j = 0; j < COLUMN; j++){
            printf("%c\t",map_data[i][j]);
        }
        printf("\n");
    }
    printf("\n\ta\tb\tc\td\te\tf\tg\th\n");
}
bool Move(bool state){
    if(init.column >= 'a' && init.column <= 'h') init.new_column = (int)init.column - 97;
    else{
        printf("\033[47;31mPlease input a~h in 'init' row\033[0m\n");
        return false;
    }
    if(dest.column >= 'a' && dest.column <= 'h') dest.new_column = (int)dest.column - 97;
    else{
        printf("\033[47;31mPlease input a~h in 'dest' row\033[0m\n");
        return false;
    }
    if(init.row >= 1 && init.row <= 8) init.new_row = ROW - init.row;
    else{
        printf("\033[47;31mPlease input 1~8 in 'init' column\033[0m\n");
        return false;
    }
    if(dest.row >= 1 && dest.row <= 8) dest.new_row = ROW - dest.row;
    else{
        printf("\033[47;31mPlease input 1~8 in 'dest' column\033[0m\n");
        return false;
    }
    
    if(    !state && (map[init.new_row][init.new_column] > 'R' || map[init.new_row][init.new_column] < 'B')){  //判斷目前要移動白棋
        printf("\033[47;31mIt is white now\033[0m\n");
        return false;
    }
    else if(state && (map[init.new_row][init.new_column] > 'r' || map[init.new_row][init.new_column] < 'b')){  //判斷目前要移動黑棋
        printf("\033[47;31mIt is Black now\033[0m\n");
        return false;
    }

    if(!Check_Rule(state)){
        printf("\033[47;31mPlease input correct rule\033[0m\n");
        return false;
    }
    else{
        if(isFull(&regret)) return false; /* Stack滿了 */
        push(&regret, &init, &dest);    /* 將位置參數儲存 */
        map[dest.new_row][dest.new_column] = map[init.new_row][init.new_column]; //起始位置移動到目標位置
        map[init.new_row][init.new_column] = ' ';                                //起始位置清空
    }
    return true;
}
bool Check_Rule(bool state){
    if(    !state && map[dest.new_row][dest.new_column] <= 'R' && map[dest.new_row][dest.new_column] >= 'B') return false;  //判斷終點為白棋
    else if(state && map[dest.new_row][dest.new_column] <= 'r' && map[dest.new_row][dest.new_column] >= 'b') return false;  //判斷終點為黑棋
    
    switch(map[init.new_row][init.new_column]){
        case 'r': //選擇城堡(Rook)時
        case 'R':
            if(Check_Straight_Line()) return true;
            break;
        case 'n': //選擇騎士(Knight)時
        case 'N':
            if(dest.new_row == init.new_row - 1 && dest.new_column == init.new_column + 2) return true;
            else if( dest.new_row == init.new_row - 2 && dest.new_column == init.new_column + 1) return true;
            else if( dest.new_row == init.new_row - 2 && dest.new_column == init.new_column - 1) return true;
            else if( dest.new_row == init.new_row - 1 && dest.new_column == init.new_column - 2) return true;
            else if( dest.new_row == init.new_row + 1 && dest.new_column == init.new_column - 2) return true;
            else if( dest.new_row == init.new_row + 2 && dest.new_column == init.new_column - 1) return true;
            else if( dest.new_row == init.new_row + 2 && dest.new_column == init.new_column + 1) return true;
            else if( dest.new_row == init.new_row + 1 && dest.new_column == init.new_column + 2) return true;
            break;
        case 'b': //選擇主教(Bishop)時
        case 'B':
            if(Check_Slant_Line()) return true;
            break;
        case 'q': //選擇皇后(Queen)時
        case 'Q':
            if(Check_Straight_Line() || Check_Slant_Line()) return true;
            break;
        case 'k': //選擇國王(King)時
        case 'K':
            if(dest.new_row == init.new_row && dest.new_column == init.new_column + 1) return true;
            else if( dest.new_row == init.new_row - 1 && dest.new_column == init.new_column + 1) return true;
            else if( dest.new_row == init.new_row - 1 && dest.new_column == init.new_column    ) return true;
            else if( dest.new_row == init.new_row - 1 && dest.new_column == init.new_column - 1) return true;
            else if( dest.new_row == init.new_row     && dest.new_column == init.new_column - 1) return true;
            else if( dest.new_row == init.new_row + 1 && dest.new_column == init.new_column - 1) return true;
            else if( dest.new_row == init.new_row + 1 && dest.new_column == init.new_column    ) return true;
            else if( dest.new_row == init.new_row + 1 && dest.new_column == init.new_column + 1) return true;
            break;
        case 'p': //選擇士兵(Pawn)時
        case 'P':
            if(dest.new_column == init.new_column){ //選擇士兵走法
                if(     !state && init.new_row == 6 && (dest.new_row == init.new_row - 1 || dest.new_row == init.new_row - 2)) return true; //白棋第一步
                else if(!state && dest.new_row == init.new_row - 1) return true;
                else if( state && init.new_row == 1 && (dest.new_row == init.new_row + 1 || dest.new_row == init.new_row + 2)) return true; //黑棋第一步
                else if( state && dest.new_row == init.new_row + 1) return true;
            }
            else if(dest.new_column == init.new_column + 1 || dest.new_column == init.new_column - 1){  //選擇士兵吃法
                if(    !state && dest.new_row == init.new_row - 1 && map[dest.new_row][dest.new_column] != ' ') return true; //白棋吃法
                else if(state && dest.new_row == init.new_row + 1 && map[dest.new_row][dest.new_column] != ' ') return true; //黑棋吃法
            }
    }
    return false;
}
bool Check_Straight_Line(void){
    uint8_t init_column = (dest.new_column > init.new_column) ? init.new_column : dest.new_column;   //選擇路徑Column起始位置
    uint8_t dest_column   = (dest.new_column < init.new_column) ? init.new_column : dest.new_column; //選擇路徑Column終點位置
    uint8_t init_row = (dest.new_row > init.new_row) ? init.new_row : dest.new_row;                  //選擇路徑Row起始位置
    uint8_t dest_row   = (dest.new_row < init.new_row) ? init.new_row : dest.new_row;                //選擇路徑Row終點位置
    if(dest_row == init_row || dest_column == init_column){                                          //起始位置和目標位置同列或同行
        for(uint8_t i = init_row; i <= dest_row; i++){
            for(uint8_t j = init_column; j <= dest_column; j++){
                if(((i != init_row && i != dest_row) || (j != init_column && j != dest_column)) && map[i][j] != ' ') return false;
            }
        }
    }
    else return false;
    return true;
}
bool Check_Slant_Line(void){
    uint8_t init_column = (dest.new_column > init.new_column) ? init.new_column : dest.new_column;     //選擇路徑Column起始位置
    uint8_t dest_column   = (dest.new_column < init.new_column) ? init.new_column : dest.new_column;   //選擇路徑Column終點位置
    if(init_column == dest_column) return false;                                                       //防止原點和終點相同
    if((init.new_row - dest.new_row) / (dest.new_column - init.new_column) == 1){                      //判斷起始和終點為一斜率為1直線
        for(uint8_t i = init_column; i < dest_column; i++){
            if( i != init_column && map[init.new_row - i + init.new_column][i] != ' ' ) return false;
        }
    }
    else if((init.new_row - dest.new_row) / (dest.new_column - init.new_column) == -1){                //判斷起始和終點為一斜率為-1直線
        for(uint8_t i = init_column; i < dest_column; i++){
            if( i != init_column && map[init.new_row + i - init.new_column][i] != ' ' ) return false;
        }
    }
    else return false;
    return true;
}
bool Check_Win(void){
    bool k = false, K = false; //判斷k K是否存在
    for(uint8_t i = 0; i < ROW; i++){
        for(uint8_t j = 0; j < COLUMN; j++){
            if(map[i][j] == 'k') k = true;
            else if(map[i][j] == 'K') K = true;
        }
    }
    if(K && !k) printf("White Win!\n");
    else if(!K && k) printf("Black Win!\n");
    else{
        k = false;
        K = false;
        return false;
    }
    return true;
}