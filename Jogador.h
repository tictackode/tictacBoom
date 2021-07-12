
#include "KrashBomb.h"

class Jogador
{
   public:
   int x;
   int y;
   BITMAP* imagem;
   KrashBomb bomb[5];
   int rangeOfExplosion;

   Jogador()
   {
        this->rangeOfExplosion=1;
   }
   ~Jogador()
   {
        destroy_bitmap(this->imagem);
        delete(this);
   }

   Jogador(int x,int y, int rangeOfExplosion)
   {
        this->x=x;
        this->y=y;
        this->rangeOfExplosion=rangeOfExplosion;

   }
   /*void checkPlayerGetItem()
   {
        if(checkColisionRight('1'))
        {
            this->x++;
            tela[this->x][this->y]='F';
            this->rangeOfExplosion++;                                   
        }
        if(checkColisionLeft('1'))
        {
            this->x--;
            tela[this->x][this->y]='F';
            this->rangeOfExplosion++;                                   
        }
        if(checkColisionUp('1'))
        {
            this->y--;
            tela[this->x][this->y]='F';
            this->rangeOfExplosion++;                                   
        } 
        if(checkColisionDown('1'))
        {
            this->y++;
            tela[this->x][this->y]='F';
            this->rangeOfExplosion++;                                   
        }         
   }*/

};

Jogador player1;
Jogador CPU1;
