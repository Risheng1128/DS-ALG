/**
 * @file chess.c
 * @author Ri-Sheng Chen
 * @date 2021.03.02
 * @brief 實做西洋棋悔棋 重播 存檔 讀檔 重頭及libev
 * 
 */
#include "stack.h"

void ev_Set(){
    ev_timer timer_w;
    ev_io io_w;
    struct ev_loop *main_loop;

    main_loop = ev_default_loop(0);
    ev_init(&timer_w, timer_action);
    ev_io_init(&io_w, io_action, STDIN_FILENO, EV_READ);
    ev_timer_set(&timer_w, 1, 1);
    ev_timer_start(main_loop, &timer_w);
    ev_io_start(main_loop, &io_w);
    ev_run(main_loop, 0);
}
void timer_action(struct ev_loop *main_loop, ev_timer *time_w, int e){
    static int time = 0;
    printf("time = %d sec\r", ++time);
}
void io_action(struct ev_loop *main_loop, ev_io *w, int revent){
    static bool state = false;              /* 判斷白動或黑動(false->白 | true->黑 */
    char mode;
    scanf(" %c",&mode);
    printf("\n");
    if(mode == 'N'){
        printf("Please input the coordinate(init,dest)\n");
        scanf(" %c%hhu%c%hhu",&init.column, &init.row, &dest.column, &dest.row);
        printf("\n");
        if(Move(state)){
            if(!state) state = true;
            else state = false;
        }
    }
    else Choose_Mode(mode, &state);
    Map_Set(map_pointer);
    printf("Choose mode : Regret chess(R) Replay chess(P) Save game(S) Loading gmae(L) Reset(E) Nothing(N)\n");
    if(Check_Win()) ev_break(main_loop, EVBREAK_ALL);   /* 跳出main loop */
}
void push(stack *regret_ptr, coordinate *init_ptr, coordinate *dest_ptr){
    if(isFull(&regret)) printf("\033[47;31mThe regret stack is full\033[0m\n");
    else{
        regret_ptr->position[++regret_ptr->top][0] = init_ptr->new_row;    /* 起點Row座標 */
        regret_ptr->position[regret_ptr->top][1]   = init_ptr->new_column; /* 起點Column座標 */
        regret_ptr->position[regret_ptr->top][2]   = dest_ptr->new_row;    /* 終點Row座標 */
        regret_ptr->position[regret_ptr->top][3]   = dest_ptr->new_column; /* 終點Column座標 */
        regret_ptr->position[regret_ptr->top][4]   = map[dest_ptr->new_row][dest_ptr->new_column]; /* 原本終點之棋子 */
    }
}
void replay_push(stack *replay_ptr, uint8_t *position){
    replay_ptr->position[++replay.top][0] = position[0]; /* 起點Row座標 */
    replay_ptr->position[replay.top][1] = position[1];   /* 起點Column座標 */
    replay_ptr->position[replay.top][2] = position[2];   /* 終點Row座標 */
    replay_ptr->position[replay.top][3] = position[3];   /* 終點Column座標 */
    replay_ptr->position[replay.top][4] = position[4];   /* 原本終點之棋子 */
}
uint8_t* pop(stack *regret_ptr){
    return regret_ptr->position[regret_ptr->top--];
}
void Choose_Mode(char mode, bool *state){
    switch (mode){
    case 'R': /* regret */
        if(!Regret_Chess(state)) printf("\033[47;31mThe regret stack is empty\033[0m\n");
        break;
    case 'P': /* replay */
        if(!Replay_Chess(regret, &replay)) printf("\033[47;31mThe replay stack is full\033[0m\n");
        break;
    case 'S': /* save */
        Save_File(map_pointer, *state);
        break;
    case 'L': /* load */
        if(!Loading_Game(map_pointer, state)) printf("\033[47;31mNot find the file\033[0m\n");
        break;
    case 'E':
        memcpy(map, init_map, ROW * COLUMN * sizeof(char));
        *state = false;
        break;
    case 'N': /* nothing */
        break;
    }
}
bool Regret_Chess(bool *state){
    if(isEmpty(&regret)) return false;
    uint8_t* position = pop(&regret);
    map[position[0]][position[1]] = map[position[2]][position[3]];
    map[position[2]][position[3]] = position[4];
    if(*state) *state = false;
    else *state = true;
    return true;
}
bool Replay_Chess(stack regret, stack *replay_ptr){
    uint8_t *position;
    int number = regret.top;
    if(number < 0) return false;
    for(uint8_t i = 0; i <= number; i++){
        replay_push(replay_ptr, pop(&regret));
    }
    printf("--------------------------Replay Start---------------------------\n");
    memcpy(map, init_map, ROW * COLUMN * sizeof(char));
    for(uint8_t i = 0; i <= number; i++){
        position = pop(&replay);
        map[position[2]][position[3]] = map[position[0]][position[1]];
        map[position[0]][position[1]] = ' ';
        if(i != number){
            Map_Set(map_pointer);
            printf("--------------------------------------------------------------------\n");
        }
    }
    return true;
}
bool isEmpty(stack* ptr){
    return (ptr->top == -1) ? true : false;
}
bool isFull(stack* ptr){
    return (ptr->top == STACKSIZE - 1) ? true : false;
}
void Save_File(char **map_data, bool state){
    FILE *fp_w = fopen("map.txt", "w");
    for(uint8_t i = 0; i < ROW; i++){
        for(uint8_t j = 0; j < COLUMN; j++){
            fprintf(fp_w,"%c", map_data[i][j]);
        }
    }
    if(!state) fprintf(fp_w, "%c", '0');  /* 該換白動 */
    else  fprintf(fp_w, "%c", '1');       /* 該換黑洞 */
    fclose(fp_w);
}
bool Loading_Game(char **map_data, bool *state){
    char check_state;
    FILE *fp_r = fopen("map.txt", "r");
    if(fp_r == NULL) return false;
    for(uint8_t i = 0; i < ROW; i++){
        for(uint8_t j = 0; j < COLUMN; j++){
            fscanf(fp_r, "%c",map_data[i] + j);
        }
    }
    fscanf(fp_r, "%c", &check_state);
    if(check_state == '0') *state = false;
    else *state = true;
    fclose(fp_r);
    regret.top = -1;
    replay.top = -1;
    return true;
}