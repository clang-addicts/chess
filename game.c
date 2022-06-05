#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include <unistd.h>

#include "log.h"
#include "screen.h"

typedef struct Piece {
    const char *name;
    const char *team;
    int type;
    int isDead;
    int x;
    int y;
}Piece;

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
void game()
{
    while(1){
        print_default_white_piece();
        print_default_black_piece();
    }
}