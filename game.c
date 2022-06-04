#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include <unistd.h>

#include "log.h"
#include "screen.h"

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

void print_default_white_piece(){
    int i;
    for(i=0;i<8;i++){
        Pawn(7+i*12,40,240);
    }
    Rook(7,46,240);
    Rook(91,46,240);
    Knight(19,46,240);
    Knight(79,46,240);
    Bishop(31,46,240);
    Bishop(67,46,240);
    King(43,46,240);
    Queen(55,46,240);
}
void print_default_black_piece(){
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

void game()
{
    print_default_white_piece();
    print_default_black_piece();
    piece_move();
}