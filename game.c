#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include <unistd.h>

#include "screen.h"
#include "log.h"


//////////////////////////////////////////////////
// definition
//////////////////////////////////////////////////
#define TEAM_NONE 0
#define TEAM_BLACK 1
#define TEAM_WHITE 2
#define TYPE_KING 0
#define TYPE_QUEEN 1
#define TYPE_ROOK 2
#define TYPE_BISHOP 3
#define TYPE_KNIGHT 4
#define TYPE_PAWN 5
#define MAX_BOARD_X 8
#define MAX_BOARD_Y 8

int curTeam = TEAM_BLACK;

typedef struct _piece {
    int type;
    int isDead;
    int x;
    int y;
    int team;
    int moved;
    int path;
}Piece;

typedef struct _player{
    Piece King;//1
    Piece Queen;//1
    Piece Rook[2];//2
    Piece Bishop[2];//2
    Piece Knight[2];//2
    Piece Pawn[8];//8
    char color;
}Player;

typedef struct _rule{
    int kingDead;
    int timeOver;
}Rule;

typedef struct _path{
    int x;
    int y;
}Path;

Piece* board[MAX_BOARD_Y][MAX_BOARD_X] = {0};
Path path[MAX_BOARD_Y * MAX_BOARD_X] = {0};
int path_count = 0;

//////////////////////////////////////////////////
// definition
//////////////////////////////////////////////////
int calcx(int calcx){
    int x;
    if(calcx==0)
        x=2;
    else
        x=2+calcx*12;
    return x;
}

int calcy(int calcy){
    int y;
    if(calcy==0)
        y=1;
    else
        y=1+calcy*6;
    return y;
}

void movable_space(int x, int y, int color, int cnt) {
    path[cnt].x = x;
    path[cnt].y = y;
    setColor(color);
    gotoXY(calcx(x)+6,calcy(y)+1);

    if(board[y][x] != NULL) {
        board[y][x]->path = 1;
    }

    printf(" ");
}

int print_path(Piece *pi, int team, int color){
    int i,j;
    int cnt=0;

    if(pi == NULL) {
        return 0;
    }

    switch(pi->type) {
        case TYPE_KING: {
            for(i=-1;i<=1;i++){
                for(j=-1;j<=1;j++){
                    if(i==0||j==0){
                        continue;
                    }
                    if(pi->x+j<0||pi->x+j>=MAX_BOARD_X){
                        continue;
                    }
                     if(pi->y+i<0||pi->y+i>=MAX_BOARD_Y){
                        continue;
                    }
                    if(board[pi->y+i][pi->x+j] != NULL){
                        if(!board[pi->y+i][pi->x+j]->isDead && board[pi->y+i][pi->x+j]->team == team) {
                            continue;
                        }
                    }
                    movable_space(pi->y+i,pi->x+j, color, cnt);      
                    cnt++;
                }
            }
            break;
        }

        case TYPE_QUEEN: {
            //DOWN
            for(i=1;i<MAX_BOARD_Y;i++){
                if(pi->y+i>=MAX_BOARD_Y){
                    continue;
                }
                if(board[pi->y+i][pi->x]!=NULL){
                    if(board[pi->y+i][pi->x]->isDead){
                        movable_space(pi->x, pi->y+i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y+i][pi->x]->team!=team){
                        movable_space(pi->x, pi->y+i-1, color, cnt);
                        cnt++;
                    }
                    break;
                }
                else{
                    movable_space(pi->x, pi->y+i, color, cnt);
                    cnt++;
                }
            }
            //UP
            for(i=1;i<MAX_BOARD_Y;i++){
                if(pi->y-i<0){
                    continue;
                }
                if(board[pi->y-i][pi->x]!=NULL){
                    if(board[pi->y-i][pi->x]->isDead){
                        movable_space(pi->x, pi->y-i,color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y-i][pi->x]->team!=team){
                        movable_space(pi->x, pi->y-i+1, color, cnt);
                        cnt++;
                    }
                    break;
                }
                else{
                    movable_space(pi->x, pi->y-i, color, cnt);
                    cnt++;
                }
            }   
            //LEFT
            for(i=1;i<MAX_BOARD_X;i++){
                if(pi->x-i<0){
                    continue;
                }
                if(board[pi->y][pi->x-i]!=NULL){
                    if(board[pi->y][pi->x-i]->isDead){
                        movable_space(pi->x-i, pi->y,color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y][pi->x-i]->team!=team){
                        movable_space(pi->x-i+1, pi->y, color, cnt);
                        cnt++;
                    }
                    break;
                }
                else{
                    movable_space(pi->x-i, pi->y, color, cnt);
                    cnt++;
                }
            }
            //RIGHT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x+i>=MAX_BOARD_X){
                    continue;
                }
                if(board[pi->y][pi->x+i]!=NULL){
                    if(board[pi->y][pi->x+i]->isDead){
                        movable_space(pi->x+i, pi->y,color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y][pi->x+i]->team!=team){
                        movable_space(pi->x+i-1, pi->y, color, cnt);
                        cnt++;
                    }
                    break;
                }
                else{
                    movable_space(pi->x+i, pi->y, color, cnt);
                    cnt++;
                }
            }            
            //DOWN_RIGHT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x+i>=MAX_BOARD_X||pi->y+i>=MAX_BOARD_Y){
                    continue;
                }
                if(board[pi->y+i][pi->x+i]!=NULL){
                    if(board[pi->y+i][pi->x+i]->isDead){
                        movable_space(pi->x+i, pi->y+i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y+i][pi->x+i]->team!=team){
                            movable_space(pi->x+i-1, pi->y+i-1, color, cnt);
                            cnt++;
                        }
                        break;
                }
                else{
                    movable_space(pi->x+i, pi->y+i, color, cnt);
                    cnt++;
                }
            }
            //DOWN_LEFT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x-i<0||pi->y+i>=MAX_BOARD_Y){
                    continue;
                }
                if(board[pi->y+i][pi->x-i]!=NULL){
                    if(board[pi->y+i][pi->x-i]->isDead){
                        movable_space(pi->x-i, pi->y+i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y+i][pi->x-i]->team!=team){
                            movable_space(pi->x-i+1, pi->y+i-1, color, cnt);
                            cnt++;
                        }
                        break;
                }
                else{
                    movable_space(pi->x-i, pi->y+i, color, cnt);
                    cnt++;
                }
            }
             //UP_RIGHT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x+i>=MAX_BOARD_X||pi->y-i<0){
                    continue;
                }
                if(board[pi->y-i][pi->x+i]!=NULL){
                    if(board[pi->y-i][pi->x+i]->isDead){
                        movable_space(pi->x+i, pi->y-i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y-i][pi->x+i]->team!=team){
                            movable_space(pi->x+i-1, pi->y-i+1, color, cnt);
                            cnt++;
                        }
                        break;
                }
                else{
                    movable_space(pi->x+i, pi->y-i, color, cnt);
                    cnt++;
                }
            }
             //UP_LEFT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x-i<0||pi->y-i<0){
                    continue;
                }
                if(board[pi->y-i][pi->x-i]!=NULL){
                    if(board[pi->y-i][pi->x-i]->isDead){
                        movable_space(pi->x-i, pi->y-i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y-i][pi->x-i]->team!=team){
                            movable_space(pi->x-i+1, pi->y-i+1, color, cnt);
                            cnt++;
                        }
                        break;
                }
                else{
                    movable_space(pi->x-i, pi->y-i, color, cnt);
                    cnt++;
                }
            }
        break;
        }
        case TYPE_ROOK: {
            //DOWN
            for(i=1;i<MAX_BOARD_Y;i++){
                if(pi->y+i>=MAX_BOARD_Y){
                    continue;
                }
                if(board[pi->y+i][pi->x]!=NULL){
                    if(board[pi->y+i][pi->x]->isDead){
                        movable_space(pi->x, pi->y+i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y+i][pi->x]->team!=team){
                        movable_space(pi->x, pi->y+i-1, color, cnt);
                        cnt++;
                    }
                    break;
                }
                else{
                    movable_space(pi->x, pi->y+i, color, cnt);
                    cnt++;
                }
            }
            //UP
            for(i=1;i<MAX_BOARD_Y;i++){
                if(pi->y-i<0){
                    continue;
                }
                if(board[pi->y-i][pi->x]!=NULL){
                    if(board[pi->y-i][pi->x]->isDead){
                        movable_space(pi->x, pi->y-i,color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y-i][pi->x]->team!=team){
                        movable_space(pi->x, pi->y-i+1, color, cnt);
                        cnt++;
                    }
                    break;
                }
                else{
                    movable_space(pi->x, pi->y-i, color, cnt);
                    cnt++;
                }
            }   
            //LEFT
            for(i=1;i<MAX_BOARD_X;i++){
                if(pi->x-i<0){
                    continue;
                }
                if(board[pi->y][pi->x-i]!=NULL){
                    if(board[pi->y][pi->x-i]->isDead){
                        movable_space(pi->x-i, pi->y,color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y][pi->x-i]->team!=team){
                        movable_space(pi->x-i+1, pi->y, color, cnt);
                        cnt++;
                    }
                    break;
                }
                else{
                    movable_space(pi->x-i, pi->y, color, cnt);
                    cnt++;
                }
            }
            //RIGHT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x+i>=MAX_BOARD_X){
                    continue;
                }
                if(board[pi->y][pi->x+i]!=NULL){
                    if(board[pi->y][pi->x+i]->isDead){
                        movable_space(pi->x+i, pi->y,color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y][pi->x+i]->team!=team){
                        movable_space(pi->x+i-1, pi->y, color, cnt);
                        cnt++;
                    }
                    break;
                }
                else{
                    movable_space(pi->x+i, pi->y, color, cnt);
                    cnt++;
                }
            }
        break;             
        }

        case TYPE_BISHOP: {
            //DOWN_RIGHT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x+i>=MAX_BOARD_X||pi->y+i>=MAX_BOARD_Y){
                    continue;
                }
                if(board[pi->y+i][pi->x+i]!=NULL){
                    if(board[pi->y+i][pi->x+i]->isDead){
                        movable_space(pi->x+i, pi->y+i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y+i][pi->x+i]->team!=team){
                            movable_space(pi->x+i-1, pi->y+i-1, color, cnt);
                            cnt++;
                        }
                        break;
                }
                else{
                    movable_space(pi->x+i, pi->y+i, color, cnt);
                    cnt++;
                }
            }
            //DOWN_LEFT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x-i<0||pi->y+i>=MAX_BOARD_Y){
                    continue;
                }
                if(board[pi->y+i][pi->x-i]!=NULL){
                    if(board[pi->y+i][pi->x-i]->isDead){
                        movable_space(pi->x-i, pi->y+i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y+i][pi->x-i]->team!=team){
                            movable_space(pi->x-i+1, pi->y+i-1, color, cnt);
                            cnt++;
                        }
                        break;
                }
                else{
                    movable_space(pi->x-i, pi->y+i, color, cnt);
                    cnt++;
                }
            }
             //UP_RIGHT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x+i>=MAX_BOARD_X||pi->y-i<0){
                    continue;
                }
                if(board[pi->y-i][pi->x+i]!=NULL){
                    if(board[pi->y-i][pi->x+i]->isDead){
                        movable_space(pi->x+i, pi->y-i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y-i][pi->x+i]->team!=team){
                            movable_space(pi->x+i-1, pi->y-i+1, color, cnt);
                            cnt++;
                        }
                        break;
                }
                else{
                    movable_space(pi->x+i, pi->y-i, color, cnt);
                    cnt++;
                }
            }
            //UP_LEFT
            for(i=1;i>MAX_BOARD_X;i++){
                if(pi->x-i<0||pi->y-i<0){
                    continue;
                }
                if(board[pi->y-i][pi->x-i]!=NULL){
                    if(board[pi->y-i][pi->x-i]->isDead){
                        movable_space(pi->x-i, pi->y-i, color, cnt);
                        cnt++;
                        continue;
                    }
                    if(board[pi->y-i][pi->x-i]->team!=team){
                            movable_space(pi->x-i+1, pi->y-i+1, color, cnt);
                            cnt++;
                        }
                        break;
                }
                else{
                    movable_space(pi->x-i, pi->y-i, color, cnt);
                    cnt++;
                }
            }
        break;
        }

        case TYPE_PAWN: {
            if(team == TEAM_BLACK) {
                if(pi->y+1 >= MAX_BOARD_Y){
                    break;
                }

                // check front space 
                if (board[pi->y+1][pi->x] == NULL) {
                    movable_space(pi->x, pi->y+1, color, cnt);
                    cnt++;
                } else {
                    if (board[pi->y+1][pi->x]->isDead) {
                        movable_space(pi->x, pi->y+1, color, cnt);
                        cnt++;
                    }
                }

                // check 2 front space
                if(!pi->moved) {
                    if (board[pi->y+2][pi->x] == NULL) {
                        movable_space(pi->x, pi->y+2, color, cnt);
                        cnt++;
                    } else {
                        if (board[pi->y+2][pi->x]->isDead) {
                            movable_space(pi->x, pi->y+2, color, cnt);
                            cnt++;
                        }
                    }
                }

                // check diagonal (left)
                if(pi->y+1 < MAX_BOARD_Y && pi->x+(-1) >= 0){
                    if (board[pi->y+1][pi->x+(-1)] != NULL) {
                        if (!board[pi->y+1][pi->x+(-1)]->isDead && board[pi->y+1][pi->x+(-1)]->team != team) {
                            movable_space(pi->x+(-1), pi->y+1, color, cnt);
                            cnt++;
                        }
                    }
                }
                
                // check diagonal (right)
                if(pi->y+1 < MAX_BOARD_Y && pi->x+(+1) < MAX_BOARD_X){    
                    if(board[pi->y+1][pi->x+(+1)] != NULL) {
                        if (!board[pi->y+1][pi->x+(+1)]->isDead && board[pi->y+1][pi->x+(+1)]->team != team) {
                            movable_space(pi->x+(+1), pi->y+1, color, cnt);
                            cnt++;
                        }
                    }
                }
            }

            else if(team == TEAM_WHITE) {
                if(pi->y-1 <0){
                    break;
                }
                // check front space 
                if (board[pi->y-1][pi->x] == NULL) {
                    movable_space(pi->x, pi->y-1, color, cnt);
                    cnt++;
                } else {
                    if (board[pi->y-1][pi->x]->isDead) {
                        movable_space(pi->x, pi->y-1, color, cnt);
                        cnt++;
                    }
                }

                // check 2 front space
                if(!pi->moved) {
                    if (board[pi->y-2][pi->x] == NULL) {
                        movable_space(pi->x, pi->y-2, color, cnt);
                        cnt++;
                    } else {
                        if (board[pi->y-2][pi->x]->isDead) {
                            movable_space(pi->x, pi->y-2, color, cnt);
                            cnt++;
                        }
                    }
                }

                // check diagonal (left)
                if(pi->y-1 >= 0 && pi->x+(-1) >= 0){
                    if (board[pi->y-1][pi->x+(-1)] != NULL) {
                        if (!board[pi->y-1][pi->x+(-1)]->isDead && board[pi->y-1][pi->x+(-1)]->team != team) {
                            movable_space(pi->x+(-1), pi->y-1, color, cnt);
                            cnt++;
                        }
                    }
                }
                
                // check diagonal (right)
                if(pi->y-1 >= 0 && pi->x+(+1) < MAX_BOARD_X){    
                    if(board[pi->y-1][pi->x+(+1)] != NULL) {
                        if (!board[pi->y-1][pi->x+(+1)]->isDead && board[pi->y-1][pi->x+(+1)]->team != team) {
                            movable_space(pi->x+(+1), pi->y-1, color, cnt);
                            cnt++;
                        }
                    }
                }
            }
            break;
        }
        case TYPE_KNIGHT:{
            //check down
            if(pi->y+2 < MAX_BOARD_Y){
                if(pi->x-1 > -1){
                    if(board[pi->y+2][pi->x-1] == NULL){
                        movable_space(pi->x-1, pi->y+2, color, cnt);
                        cnt++;
                    }
                    else if(board[pi->y+2][pi->x-1]->isDead){
                        movable_space(pi->x-1, pi->y+2, color, cnt);
                        cnt++;
                    }
                }
                if(pi->x+1 < MAX_BOARD_X){
                    if(board[pi->y+2][pi->x+1] == NULL){
                        movable_space(pi->x+1, pi->y+2, color, cnt);
                        cnt++;
                    }
                    else if(board[pi->y+2][pi->x+1]->isDead){
                        movable_space(pi->x+1, pi->y+2, color, cnt);
                        cnt++;
                    }
                }
            }

            //check up
            if(pi->y-2 > -1){
                if(pi->x-1 > -1){
                    if(board[pi->y-2][pi->x-1] == NULL){
                        movable_space(pi->x-1, pi->y-2, color, cnt);
                        cnt++;
                    }
                    else if(board[pi->y-2][pi->x-1]->isDead){
                        movable_space(pi->x-1, pi->y-2, color, cnt);
                        cnt++;
                    }
                }
                if(pi->x+1 < MAX_BOARD_X){
                    if(board[pi->y-2][pi->x+1] == NULL){
                        movable_space(pi->x+1, pi->y-2, color, cnt);
                        cnt++;
                    }
                    else if(board[pi->y-2][pi->x+1]->isDead){
                        movable_space(pi->x+1, pi->y-2, color, cnt);
                        cnt++;
                    }
                }
            }

            //check right
            if(pi->x+2 < MAX_BOARD_X){
                if(pi->y-1 > -1){
                    if(board[pi->y-1][pi->x+2] == NULL){
                        movable_space(pi->x+2, pi->y-1, color, cnt);
                        cnt++;
                    }
                    else if(board[pi->y-1][pi->x+2]->isDead){
                        movable_space(pi->x+2, pi->y-1, color, cnt);
                        cnt++;
                    }
                }
                if(pi->y+1 < MAX_BOARD_Y){
                    if(board[pi->y+1][pi->x+2] == NULL){
                        movable_space(pi->x+2, pi->y+1, color, cnt);
                        cnt++;
                    }
                    else if(board[pi->y+1][pi->x+2]->isDead){
                        movable_space(pi->x+2, pi->y+1, color, cnt);
                        cnt++;
                    }
                }
            }

            //check left
            if(pi->x-2 > -1){
                if(pi->y-1 > -1){
                    if(board[pi->y-1][pi->x-2] == NULL){
                        movable_space(pi->x-2, pi->y-1, color, cnt);
                        cnt++;
                    }
                    else if(board[pi->y-1][pi->x-2]->isDead){
                        movable_space(pi->x-2, pi->y-1, color, cnt);
                        cnt++;
                    }
                }
                if(pi->y+1 < MAX_BOARD_Y){
                    if(board[pi->y+1][pi->x-2] == NULL){
                        movable_space(pi->x-2, pi->y+1, color, cnt);
                        cnt++;
                    }
                    else if(board[pi->y+1][pi->x-2]->isDead){
                        movable_space(pi->x-2, pi->y+1, color, cnt);
                        cnt++;
                    }
                }
            }
            break;
        }
    }

    path_count = cnt;

    if(path_count>0){
        return 1;
    } else{
        return 0;
    }
}

void print_move(Piece *pi){
    if(kbhit()){
            int pressKey=getch();
            int i;
            if(pressKey == 13) {
                for(i = 0; i <path_count; i++){
                    if(pi->x == path[i].x && pi->y == path[i].y){
                        
                    }
                }
            }
    }
}

void King(int x,int y,int color){
    setColor(color);
    gotoXY(x+2,y+1);
    printf("K");
}
void Queen(int x, int y, int color){
    setColor(color);
    gotoXY(x+2,y+1);
    printf("Q");
}
void Bishop(int x, int y, int color){
    setColor(color);
    gotoXY(x+2,y+1);
    printf("B");
}
void Knight(int x, int y, int color){
    setColor(color);
    gotoXY(x+2,y+1);
    printf("kn");
}
void Rook(int x, int y, int color){
    setColor(color);
    gotoXY(x+2,y+1);
    printf("R");
}
void Pawn(int x, int y, int color){
    setColor(color);
    gotoXY(x+2,y+1);
    printf("P");
}

int chessArr[8][8]={{1,0,1,0,1,0,1,0},  // 0 = BF_BLACK_WHITE, 1 = BF_LWHITE_BLACK
                    {0,1,0,1,0,1,0,1},
                    {1,0,1,0,1,0,1,0},
                    {0,1,0,1,0,1,0,1},
                    {1,0,1,0,1,0,1,0},
                    {0,1,0,1,0,1,0,1},
                    {1,0,1,0,1,0,1,0},
                    {0,1,0,1,0,1,0,1}
};

void piece_move(){

    eBOX(calcx(0),calcy(0),12,6,BF_GREEN_BLACK,' ');
    int ArrX=0;
    int ArrY=0;
    
    while(1){
        if(kbhit()){
            int pressKey=getch();
                switch(pressKey){
                case 72:    //위
                    if(ArrY-1<0)
                        break;
                    if(chessArr[ArrY][ArrX]==1)
                        eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_LWHITE_BLACK,' ');
                    else
                        eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_BLACK_WHITE,' ');                   
                    ArrY -=1;

                    eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_GREEN_BLACK,' ');                 
                    break;
                case 80:    //아래
                    if(ArrY+1>7)
                        break;
                    if(chessArr[ArrY][ArrX]==1)
                        eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_LWHITE_BLACK,' ');
                    else
                        eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_BLACK_WHITE,' ');                     
                    ArrY +=1;

                    eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_GREEN_BLACK,' ');               
                    break;
                case 75:    //왼쪽
                    if(ArrX-1<0)
                        break;
                    if(chessArr[ArrY][ArrX]==1)
                        eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_LWHITE_BLACK,' ');
                    else
                        eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_BLACK_WHITE,' ');                  
                    ArrX -=1;

                    eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_GREEN_BLACK,' ');                  
                    break;
                case 77:    //오른쪽
                    if(ArrX+1>7)
                        break;
                    if(chessArr[ArrY][ArrX]==1)
                        eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_LWHITE_BLACK,' ');
                    else
                        eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_BLACK_WHITE,' ');                    
                    ArrX +=1;

                    eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_GREEN_BLACK,' ');                
                    break;
                case 13:
                    eBOX(calcx(ArrX),calcy(ArrY),12,6,BF_RED_BLACK,' ');

                    if(board[ArrY][ArrX] != NULL) {
                        if(board[ArrY][ArrX]->team == curTeam) {
                            if(print_path(board[ArrY][ArrX], curTeam, BF_RED_BLACK) > 0) {
                                // team change
                                // update score
                                // kill malr
                                
                                if(curTeam == TEAM_BLACK){
                                    curTeam = TEAM_WHITE;
                                }
                                else if(curTeam == TEAM_WHITE){
                                    curTeam = TEAM_BLACK;
                                }
                            }
                            //좀이따 지움

                            // if(path_count == 0){
                            //     print_path(board[ArrY][ArrX], curTeam, BF_RED_BLACK);
                            // }
                            // else
                            // if(path_count > 0){
                            //     print_move(board[ArrY][ArrX]);

                            //     if(curTeam == TEAM_BLACK){
                            //         curTeam = TEAM_WHITE;
                            //     }
                            //     else if(curTeam == TEAM_WHITE){
                            //         curTeam = TEAM_BLACK;
                            //     }
                            // }
                        }
                        // else if (path_count > 0 && board[ArrY][ArrX]->path == 1){
                            
                        //     int i;
                        //     int j;
                        //     path_count = 0;
                        //     for(i = 0; i < MAX_BOARD_Y; i++){
                        //         for(j = 0; j < MAX_BOARD_X; j++){
                        //             board[i][j]->path = 0;
                        //         }
                        //     }
                        // }
                    }
                    break;
            }
        }
    }
    
}

void black_win(){
    
}

void white_win(){
    
}

// void game_rule(){
//     if(black.kingDead){
//         black_win();
//     }
//     else if(white.kingDead){
//         white_win();
//     }

//     if(black.TimeOver){
//         white_win();
//     }
//     else if(white.timeOver){
//         black_win();
//     }
// }

void print_default(Player *p){
    King(calcx(p->King.x),calcy(p->King.y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Queen(calcx(p->Queen.x),calcy(p->Queen.y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Bishop(calcx(p->Bishop[0].x),calcy(p->Bishop[0].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Bishop(calcx(p->Bishop[1].x),calcy(p->Bishop[1].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Rook(calcx(p->Rook[0].x),calcy(p->Rook[0].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Rook(calcx(p->Rook[1].x),calcy(p->Rook[1].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Knight(calcx(p->Knight[0].x),calcy(p->Knight[0].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Knight(calcx(p->Knight[1].x),calcy(p->Knight[1].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Pawn(calcx(p->Pawn[0].x),calcy(p->Pawn[0].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Pawn(calcx(p->Pawn[1].x),calcy(p->Pawn[1].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Pawn(calcx(p->Pawn[2].x),calcy(p->Pawn[2].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Pawn(calcx(p->Pawn[3].x),calcy(p->Pawn[3].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Pawn(calcx(p->Pawn[4].x),calcy(p->Pawn[4].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Pawn(calcx(p->Pawn[5].x),calcy(p->Pawn[5].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Pawn(calcx(p->Pawn[6].x),calcy(p->Pawn[6].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
    Pawn(calcx(p->Pawn[7].x),calcy(p->Pawn[7].y),p->color == TEAM_BLACK? BF_BLACK_WHITE : BF_LWHITE_BLACK);
}

void set_default(Player *player){
    int i;
    if (player->color == TEAM_BLACK){
        player->King.x = 4;
        player->King.y = 0;
        player->King.type = TYPE_KING;
        player->King.team = TEAM_BLACK;
        board[player->King.y][player->King.x] = &(player->King);
        
        player->Queen.x = 3;
        player->Queen.y = 0;
        player->Queen.type = TYPE_QUEEN;
        player->Queen.team = TEAM_BLACK;
        board[player->Queen.y][player->Queen.x] = &(player->Queen);

        player->Rook[0].x = 0;
        player->Rook[0].y = 0;
        player->Rook[0].type = TYPE_ROOK;
        player->Rook[0].team = TEAM_BLACK;
        board[player->Rook[0].y][player->Rook[0].x] = &(player->Rook[0]);
        
        player->Rook[1].x = 7;
        player->Rook[1].y = 0;
        player->Rook[1].type = TYPE_ROOK;
        player->Rook[1].team = TEAM_BLACK;
        board[player->Rook[1].y][player->Rook[1].x] = &(player->Rook[1]);

        player->Knight[0].x = 1;
        player->Knight[0].y = 0;
        player->Knight[0].type = TYPE_KNIGHT;
        player->Knight[0].team = TEAM_BLACK;
        board[player->Knight[0].y][player->Knight[0].x] = &(player->Knight[0]);

        player->Knight[1].x = 6;
        player->Knight[1].y = 0;
        player->Knight[1].type = TYPE_KNIGHT;
        player->Knight[1].team = TEAM_BLACK;
        board[player->Knight[1].y][player->Knight[1].x] = &(player->Knight[1]);

        player->Bishop[0].x = 2;
        player->Bishop[0].y = 0;
        player->Bishop[0].type = TYPE_BISHOP;
        player->Bishop[0].team = TEAM_BLACK;
        board[player->Bishop[0].y][player->Bishop[0].x] = &(player->Bishop[0]);

        player->Bishop[1].x = 5;
        player->Bishop[1].y = 0;
        player->Bishop[1].type = TYPE_BISHOP;
        player->Bishop[1].team = TEAM_BLACK;
        board[player->Bishop[1].y][player->Bishop[1].x] = &(player->Bishop[1]);

        for(i = 0; i <= 7; i++){
            player->Pawn[i].x = i;
            player->Pawn[i].y = 1;
            player->Pawn[i].type = TYPE_PAWN;
            player->Pawn[i].team = TEAM_BLACK;
            board[player->Pawn[i].y][player->Pawn[i].x] = &(player->Pawn[i]);
        }      
    } else if(player->color == TEAM_WHITE) {
        player->King.x = 4;
        player->King.y = 7;
        player->King.type = TYPE_KING;
        player->King.team = TEAM_WHITE;
        board[player->King.y][player->King.x] = &(player->King);
        
        player->Queen.x = 3;
        player->Queen.y = 7;
        player->Queen.type = TYPE_QUEEN;
        player->Queen.team = TEAM_WHITE;
        board[player->Queen.y][player->Queen.x] = &(player->Queen);

        player->Rook[0].x = 0;
        player->Rook[0].y = 7;
        player->Rook[0].type = TYPE_ROOK;
        player->Rook[0].team = TEAM_WHITE;
        board[player->Rook[0].y][player->Rook[0].x] = &(player->Rook[0]);
        
        player->Rook[1].x = 7;
        player->Rook[1].y = 7;
        player->Rook[1].type = TYPE_ROOK;
        player->Rook[1].team = TEAM_WHITE;
        board[player->Rook[1].y][player->Rook[1].x] = &(player->Rook[1]);

        player->Knight[0].x = 1;
        player->Knight[0].y = 7;
        player->Knight[0].type = TYPE_KNIGHT;
        player->Knight[0].team = TEAM_WHITE;
        board[player->Knight[0].y][player->Knight[0].x] = &(player->Knight[0]);

        player->Knight[1].x = 6;
        player->Knight[1].y = 7;
        player->Knight[1].type = TYPE_KNIGHT;
        player->Knight[1].team = TEAM_WHITE;
        board[player->Knight[1].y][player->Knight[1].x] = &(player->Knight[1]);
        
        player->Bishop[0].x = 2;
        player->Bishop[0].y = 7;
        player->Bishop[0].type = TYPE_BISHOP;
        player->Bishop[0].team = TEAM_WHITE;
        board[player->Bishop[0].y][player->Bishop[0].x] = &(player->Bishop[0]);

        player->Bishop[1].x = 5;
        player->Bishop[1].y = 7;
        player->Bishop[1].type = TYPE_BISHOP;
        player->Bishop[1].team = TEAM_WHITE;
        board[player->Bishop[1].y][player->Bishop[1].x] = &(player->Bishop[1]);

        for(i = 0; i <= 7; i++){
            player->Pawn[i].x = i;
            player->Pawn[i].y = 6;
            player->Pawn[i].type = TYPE_PAWN;
            player->Pawn[i].team = TEAM_WHITE;
            board[player->Pawn[i].y][player->Pawn[i].x] = &(player->Pawn[i]);
        }      
    }
}

void game()
{
    Player black;
    Player white;

    memset(&black, 0, sizeof(Player));
    memset(&white, 0, sizeof(Player));

    black.color = TEAM_BLACK;
    white.color = TEAM_WHITE;

    set_default(&black);
    set_default(&white);

    print_default(&black);
    print_default(&white);

    piece_move();

    // game_rule();
}