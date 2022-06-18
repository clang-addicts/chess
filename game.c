#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include <unistd.h>

#include "log.h"
#include "screen.h"

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

typedef struct _piece {
    int type;
    int isDead;
    int x;
    int y;
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

char board[MAX_BOARD_Y][MAX_BOARD_X]={0};

//////////////////////////////////////////////////
// definition
//////////////////////////////////////////////////
void print_path(Piece *pi,int team){
    int i,j;
    int cnt=0;
    switch(pi->type)
    {
        case TYPE_KING :
        {
            for(i=-1;i<=1;i++){
                for(j=-1;j<=1;j++){
                    if(i==0&&j==0){
                        continue;
                    }
                    if(pi->x+j<0&&pi->x+j>=MAX_BOARD_X){
                        continue;
                    }
                     if(pi->y+i<0&&pi->y+i>=MAX_BOARD_Y){
                        continue;
                    }
                    if(board[pi->y+i][pi->x+j]==team){
                        continue;
                    }
    
                    cnt++;
                
                }
            }
            //pi->x-1 pi->y-1
            //pi->x+0 pi->y-1
            //pi->x+1 pi->y-1
            //pi->x-1 pi->y+0
            //pi->x+1 pi->y+0
            //pi->x-1 pi->y+0
            //pi->x+0 pi->y+1
            //pi->x+1 pi->y+1
            
            
            break;
        }
    }
    if(cnt>0){
        return 1;
    }
    else{
        return 0;
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
                    if(board[ArrY][ArrX]==TEAM_BLACK){
                        print_path()
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
    if (player->color == TEAM_BLACK){
        int i;
        player->King.x = 4;
        player->King.y = 0;
        player->King.isDead = 0;
        player->King.type = TYPE_KING;
        board[player->King.y][player->King.x] = TEAM_BLACK;
        
        player->Queen.x = 5;
        player->Queen.y = 0;
        player->Queen.isDead = 0;
        player->Queen.type = TYPE_QUEEN;
        board[player->Queen.y][player->Queen.x] = TEAM_BLACK;

        player->Rook[0].x = 0;
        player->Rook[0].y = 0;
        player->Rook[0].isDead = 0;
        player->Rook[0].type = TYPE_ROOK;
        board[player->Rook[0].y][player->Rook[0].x] = TEAM_BLACK;
        
        player->Rook[1].x = 7;
        player->Rook[1].y = 0;
        player->Rook[1].isDead = 0;
        player->Rook[1].type = TYPE_ROOK;
        board[player->Rook[1].y][player->Rook[1].x] = TEAM_BLACK;

        player->Knight[0].x = 1;
        player->Knight[0].y = 0;
        player->Knight[0].isDead = 0;
        player->Knight[0].type = TYPE_KNIGHT;
        board[player->Knight[0].y][player->Knight[0].x] = TEAM_BLACK;

        player->Knight[1].x = 6;
        player->Knight[1].y = 0;
        player->Knight[1].isDead = 0;  
        player->Knight[1].type = TYPE_KNIGHT;
        board[player->Knight[1].y][player->Knight[1].x] = TEAM_BLACK;
        

        player->Bishop[0].x = 3;
        player->Bishop[0].y = 0;
        player->Bishop[0].isDead = 0;
        player->Bishop[0].type = TYPE_BISHOP;
        board[player->Bishop[0].y][player->Bishop[0].x] = TEAM_BLACK;

        
        player->Bishop[1].x = 5;
        player->Bishop[1].y = 0;
        player->Bishop[1].isDead = 0;
        player->Bishop[1].type = TYPE_BISHOP;
        board[player->Bishop[1].y][player->Bishop[1].x] = TEAM_BLACK;


        for(i = 0; i <= 7; i++){
            player->Pawn[i].x = i;
            player->Pawn[i].y = 1;
            player->Pawn[i].isDead = 0;
            player->Pawn[i].type = TYPE_PAWN;
            board[player->Pawn[i].y][player->Pawn[i].x] = TEAM_BLACK;
        }      
    }
    else if(player->color == TEAM_WHITE){
        int i;
        player->King.x = 4;
        player->King.y = 7;
        player->King.isDead = 0;
        player->King.type = TYPE_KING;
        board[player->King.y][player->King.x] = TEAM_WHITE;

        
        player->Queen.x = 5;
        player->Queen.y = 7;
        player->Queen.isDead = 0;
        player->Queen.type = TYPE_QUEEN;
        board[player->Queen.y][player->Queen.x] = TEAM_WHITE;


        player->Rook[0].x = 0;
        player->Rook[0].y = 7;
        player->Rook[0].isDead = 0;
        player->Rook[0].type = TYPE_ROOK;
        board[player->Rook[0].y][player->Rook[0].x] = TEAM_WHITE;

        
        player->Rook[1].x = 7;
        player->Rook[1].y = 7;
        player->Rook[1].isDead = 0;
        player->Rook[1].type = TYPE_ROOK;
        board[player->Rook[1].y][player->Rook[1].x] = TEAM_WHITE;


        player->Knight[0].x = 1;
        player->Knight[0].y = 7;
        player->Knight[0].isDead = 0;
        player->Knight[0].type = TYPE_KNIGHT;
        board[player->Knight[0].y][player->Knight[0].x] = TEAM_WHITE;



        player->Knight[1].x = 6;
        player->Knight[1].y = 7;
        player->Knight[1].isDead = 0;  
        player->Knight[1].type = TYPE_KNIGHT;
        board[player->Knight[1].y][player->Knight[1].x] = TEAM_WHITE;


        
        player->Bishop[0].x = 3;
        player->Bishop[0].y = 7;
        player->Bishop[0].isDead = 0;
        player->Bishop[0].type = TYPE_BISHOP;
        board[player->Bishop[0].y][player->Bishop[0].x] = TEAM_WHITE;


        
        player->Bishop[1].x = 5;
        player->Bishop[1].y = 7;
        player->Bishop[1].isDead = 0;
        player->Bishop[1].type = TYPE_BISHOP;
        board[player->Bishop[1].y][player->Bishop[1].x] = TEAM_WHITE;



        for(i = 0; i <= 7; i++){
            player->Pawn[i].x = i;
            player->Pawn[i].y = 6;
            player->Pawn[i].isDead = 0;
            player->Pawn[i].type = TYPE_PAWN;
            board[player->Pawn[i].y][player->Pawn[i].x] = TEAM_WHITE;


        }      
    }
}

void game()
{
    Player black;
    Player white;
    black.color = TEAM_BLACK;
    white.color = TEAM_WHITE;
    set_default(&black);
    set_default(&white);
    print_default(&black);
    print_default(&white);
    piece_move();

    // game_rule();
}