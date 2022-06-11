#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include <unistd.h>

#include "log.h"
#include "screen.h"
#define TEAM_BLACK 0
#define TEAM_WHITE 1

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


void King(int x,int y,int color){
    setColor(color);
    gotoXY(x,y);
    printf("K");
}
void Queen(int x, int y, int color){
    setColor(color);
    gotoXY(x,y);
    printf("Q");
}
void Bishop(int x, int y, int color){
    setColor(color);
    gotoXY(x,y);
    printf("B");
}
void Knight(int x, int y, int color){
    setColor(color);
    gotoXY(x,y);
    printf("kn");
}
void Rook(int x, int y, int color){
    setColor(color);
    gotoXY(x,y);
    printf("R");
}
void Pawn(int x, int y, int color){
    setColor(color);
    gotoXY(x,y);
    printf("P");
}


void default_white(){
    int i;
    for(i=0;i<8;i++){
        Pawn(7+i*12,40,240);
    }
    Rook(7, 46,BF_LWHITE_BLACK);
    Rook(91,46,BF_LWHITE_BLACK);
    Knight(19,46,BF_LWHITE_BLACK);
    Knight(79,46,BF_LWHITE_BLACK);
    Bishop(31,46,BF_LWHITE_BLACK);
    Bishop(67,46,BF_LWHITE_BLACK);
    King(43,46,BF_LWHITE_BLACK);
    Queen(55,46,BF_LWHITE_BLACK);
}
void default_black(){
    int i;
    for(i=0;i<8;i++){
        Pawn(7+i*12,9,7);
    }
    Rook(7,3,7);
    Rook(91,3,7);
    Knight(19,3,7);
    Knight(79,3,7);
    Bishop(31,3,7);
    Bishop(67,3,7);
    King(43,3,7);
    Queen(55,3,7);
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
    int currentPosX=2;
    int currentPosY=1;

    eBOX(currentPosX,currentPosY,12,6,BF_GREEN_BLACK,' ');
    int ArrX=0;
    int ArrY=0;
    chessArr[ArrY][ArrX];
    while(1){
        if(kbhit()){
            int pressKey=getch();
                switch(pressKey){
                case 72:    //위
                    if(ArrY-1<0)
                        break;
                    if(chessArr[ArrY][ArrX]==1)
                        eBOX(currentPosX,currentPosY,12,6,BF_LWHITE_BLACK,' ');
                    else
                        eBOX(currentPosX,currentPosY,12,6,BF_BLACK_WHITE,' ');                   
                    ArrY -=1;

                    currentPosY -= 6;
                    eBOX(currentPosX,currentPosY,12,6,BF_GREEN_BLACK,' ');                 
                    break;
                case 80:    //아래
                    if(ArrY+1>7)
                        break;
                    if(chessArr[ArrY][ArrX]==1)
                        eBOX(currentPosX,currentPosY,12,6,BF_LWHITE_BLACK,' ');
                    else
                        eBOX(currentPosX,currentPosY,12,6,BF_BLACK_WHITE,' ');                     
                    ArrY +=1;

                    currentPosY += 6;
                    eBOX(currentPosX,currentPosY,12,6,BF_GREEN_BLACK,' ');               
                    break;
                case 75:    //왼쪽
                    if(ArrX-1<0)
                        break;
                    if(chessArr[ArrY][ArrX]==1)
                        eBOX(currentPosX,currentPosY,12,6,BF_LWHITE_BLACK,' ');
                    else
                        eBOX(currentPosX,currentPosY,12,6,BF_BLACK_WHITE,' ');                  
                    ArrX -=1;

                    currentPosX -= 12;
                    eBOX(currentPosX,currentPosY,12,6,BF_GREEN_BLACK,' ');                  
                    break;
                case 77:    //오른쪽
                    if(ArrX+1>7)
                        break;
                    if(chessArr[ArrY][ArrX]==1)
                        eBOX(currentPosX,currentPosY,12,6,BF_LWHITE_BLACK,' ');
                    else
                        eBOX(currentPosX,currentPosY,12,6,BF_BLACK_WHITE,' ');                    
                    ArrX +=1;

                    currentPosX += 12;
                    eBOX(currentPosX,currentPosY,12,6,BF_GREEN_BLACK,' ');                
                    break;
                case 13:
                    eBOX(currentPosX,currentPosY,12,6,BF_RED_BLACK,' ');
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

void set_default(Player *player){
    if (player->color == TEAM_BLACK){
        int i;
        player->King.x = 4;
        player->King.y = 0;
        player->King.isDead = 0;
        
        player->Queen.x = 5;
        player->Queen.y = 0;
        player->Queen.isDead = 0;

        player->Rook[0].x = 0;
        player->Rook[0].y = 0;
        player->Rook[0].isDead = 0;
        
        player->Rook[1].x = 7;
        player->Rook[1].y = 0;
        player->Rook[1].isDead = 0;

        player->Knight[0].x = 1;
        player->Knight[0].y = 0;
        player->Knight[0].isDead = 0;

        player->Knight[1].x = 6;
        player->Knight[1].y = 0;
        player->Knight[1].isDead = 0;  
        
        player->Bishop[0].x = 3;
        player->Bishop[0].y = 0;
        player->Bishop[0].isDead = 0;
        
        player->Bishop[1].x = 5;
        player->Bishop[1].y = 0;
        player->Bishop[1].isDead = 0;

        for(i = 0; i <= 7; i++){
            player->Pawn[i].x = i;
            player->Pawn[i].y = 1;
            player->Pawn[i].isDead = 0;
        }      
    }
    else if(player->color == TEAM_WHITE){
        int i;
        player->King.x = 4;
        player->King.y = 7;
        player->King.isDead = 0;
        
        player->Queen.x = 5;
        player->Queen.y = 7;
        player->Queen.isDead = 0;

        player->Rook[0].x = 0;
        player->Rook[0].y = 7;
        player->Rook[0].isDead = 0;
        
        player->Rook[1].x = 7;
        player->Rook[1].y = 7;
        player->Rook[1].isDead = 0;

        player->Knight[0].x = 1;
        player->Knight[0].y = 7;
        player->Knight[0].isDead = 0;

        player->Knight[1].x = 6;
        player->Knight[1].y = 7;
        player->Knight[1].isDead = 0;  
        
        player->Bishop[0].x = 3;
        player->Bishop[0].y = 7;
        player->Bishop[0].isDead = 0;
        
        player->Bishop[1].x = 5;
        player->Bishop[1].y = 7;
        player->Bishop[1].isDead = 0;

        for(i = 0; i <= 7; i++){
            player->Pawn[i].x = i;
            player->Pawn[i].y = 6;
            player->Pawn[i].isDead = 0;
        }      
    }
}

void game()
{
    Player black;
    Player white;
    black.color = TEAM_BLACK;
    white.color = TEAM_WHITE;
    // set_default(&black);
    // set_default(&white);
    // print_default(&black);
    // print_default(&white);
    default_black();
    default_white();
    piece_move();
    // game_rule();
}