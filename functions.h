#include <time.h>
#include <allegro.h>

#include "Jogador.h"
#include "Audio.h"
#include "InitMapMatrix.h"

 
BITMAP* buffer;
BITMAP* blocoVerm;
BITMAP* blocoAzul;
BITMAP* blocoVerde;
BITMAP* blocoCinza;
BITMAP* blocoAmarelo;
BITMAP* blocoRoxo;
BITMAP* blocoLaranja;
BITMAP* blocoRosa;
BITMAP* logo;
BITMAP* krashBombImage;

BITMAP* explosionBitmap;
BITMAP* itemRaiseRangeOfExplosion;

BITMAP* sprite1_front1;
BITMAP* sprite1_left1;
BITMAP* sprite1_right1;
BITMAP* sprite1_back1;

BITMAP* sprite2_front1;
BITMAP* sprite2_left1;
BITMAP* sprite2_right1;
BITMAP* sprite2_back1;

BITMAP* enemy_right;
BITMAP* enemy_left;

BITMAP* door;

BITMAP* createBlueBrickBitmap();

// timer
volatile int timer;
volatile int timerMilisec;

int timeaux=0;
int timeAuxMilisec=0;
volatile int bombTime=3;

void incrementaTimer()
{ 
     timer++; 
}
void incrementaTimerMilisec()
{ 
     timerMilisec++; 
}
void decrementaTimer()
{ 
     bombTime--; 
}

END_OF_FUNCTION(decrementaTimer)
END_OF_FUNCTION(incrementaTimer)
END_OF_FUNCTION(incrementaTimerMilisec)

void gameOver();
void paint();
BITMAP* createBrickBitmap();
BITMAP* returnsRandomGrayscaleFloor();

class Objeto
{
   public:
   int x;
   int y;
   BITMAP* imagem;
   Objeto()
   {
           
   }
   ~Objeto()
   {
       destroy_bitmap(this->imagem);
       delete(this);
   }
   
   
};


inline void init()
{
    //allegro 4.2 initialization function
    allegro_init();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, numberOfBlocksX*tamBloco, numberOfBlocksY*tamBloco, 0, 0);

    install_timer();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT,NULL);

   /* screen-> vtable -> mask_color = makecol(255, 0, 255);*/
}

inline void deinit()
{   
    //allegro deinit function
    clear_keybuf();
    allegro_exit();
    
    
    
}
void highcolor_fade_out(int speed)
{
    BITMAP *bmp_orig, *bmp_buff;

    if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
        {
            int a;
            blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (speed <= 0) speed = 16;

            for (a = 255-speed; a > 0; a-=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
                vsync();
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(bmp_buff);
        }
        destroy_bitmap(bmp_orig);
    }

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));
}
void highcolor_fade_in(BITMAP *bmp_orig, int speed)
{
   BITMAP *bmp_buff;

    if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        int a;
        if (speed <= 0) speed = 16;

        for (a = 0; a < 256; a+=speed)
        {
            clear(bmp_buff);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
            vsync();
            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(bmp_buff);
    }

    blit(bmp_orig, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
}

/*void clearItemsMatrix()
{
     
     for(int i=0;i<numberOfBlocksX;i++)
     {
          for(int j=0;i<numberOfBlocksY;j++)
          {
               items[i][j]='0';
          }
     }   
     
}*/

void loadAll()
{   //function that loads all extern images and fonts

    set_window_title("TictacKrash - A TictacKode's Bomberman clone!");
    buffer=create_bitmap(numberOfBlocksX*tamBloco,numberOfBlocksY*tamBloco);

    /*letra = load_font("fonts/arial18.pcx",NULL,NULL);
    fontCordia48 = load_font("fonts/cordia28.pcx",NULL,NULL);
    fontCordia28 = load_font("fonts/cordia48.pcx",NULL,NULL);*/
          
    /*if(!fontCordia28) { exit(1); }
          
    if(!letra) { exit(1); }

    if(!fontCordia48) { exit(1); }  */

    logo=create_bitmap(numberOfBlocksX*tamBloco,numberOfBlocksY*tamBloco);
    logo=load_bitmap("img/tictackode.bmp",0);
    if(!logo) { exit(1); }

    krashBombImage=create_bitmap(tamBloco,tamBloco);
    krashBombImage=load_bitmap("img/timebomb256colors.bmp",0);
    if(!logo) { exit(1); }

    
    itemRaiseRangeOfExplosion=create_bitmap(tamBloco,tamBloco);
    itemRaiseRangeOfExplosion=load_bitmap("img/itemRaiseRangeOfExplosion.bmp",0);
    if(!itemRaiseRangeOfExplosion) { exit(1); }

    sprite1_front1=create_bitmap(tamBloco,tamBloco);
    sprite1_front1=load_bitmap("img/sprite1_front1.bmp",0);
    if(!sprite1_front1) { exit(1); }

    sprite1_left1=create_bitmap(tamBloco,tamBloco);
    sprite1_left1=load_bitmap("img/sprite1_left1.bmp",0);
    if(!sprite1_left1) { exit(1); }

    sprite1_right1=create_bitmap(tamBloco,tamBloco);
    sprite1_right1=load_bitmap("img/sprite1_right1.bmp",0);
    if(!sprite1_right1) { exit(1);  }

    sprite1_back1=create_bitmap(tamBloco,tamBloco);
    sprite1_back1=load_bitmap("img/sprite1_back1.bmp",0);
    if(!sprite1_back1) { exit(1); }
    
    explosionBitmap=create_bitmap(tamBloco,tamBloco);
    explosionBitmap=load_bitmap("img/explosionBitmap.bmp",0);
    if(!explosionBitmap) { exit(1); }


    sprite2_front1=create_bitmap(tamBloco,tamBloco);
    sprite2_front1=load_bitmap("img/sprite2_front1.bmp",0);
    if(!sprite2_front1) { exit(1); }

    sprite2_left1=create_bitmap(tamBloco,tamBloco);
    sprite2_left1=load_bitmap("img/sprite2_left1.bmp",0);
    if(!sprite2_left1) { exit(1); }

    sprite2_right1=create_bitmap(tamBloco,tamBloco);
    sprite2_right1=load_bitmap("img/sprite2_right1.bmp",0);
    if(!sprite2_right1) { exit(1);  }

    sprite2_back1=create_bitmap(tamBloco,tamBloco);
    sprite2_back1=load_bitmap("img/sprite2_back1.bmp",0);
    if(!sprite2_back1) { exit(1); }
    
    door=create_bitmap(tamBloco,tamBloco);
    door=load_bitmap("img/door.bmp",0);
    if(!door) { exit(1); }
    
    enemy_left=create_bitmap(64,64);
    enemy_right=create_bitmap(64,64);
            
    enemy_right=load_bitmap("img/skull_right.bmp",0);
    if(!enemy_right) 
    {
        exit(1);
    }
    
    enemy_left=load_bitmap("img/skull_left.bmp",0);
    if(!enemy_left) 
    {
        exit(1); 
    }



}
void freeAll()
{   //clear the game bitmaps from memory

    destroy_bitmap(blocoVerm);
    destroy_bitmap(blocoAzul);
    destroy_bitmap(blocoVerde);
    destroy_bitmap(blocoCinza);
    destroy_bitmap(blocoAmarelo);
    destroy_bitmap(blocoRoxo);
    destroy_bitmap(blocoLaranja);
    destroy_bitmap(blocoRosa);
    destroy_bitmap(krashBombImage);
    destroy_bitmap(buffer);
    destroy_bitmap(explosionBitmap);
    destroy_bitmap(itemRaiseRangeOfExplosion);
    
    destroy_bitmap(enemy_right);
    destroy_bitmap(enemy_left);
    

    //clear the fonts used in the game
    //destroy_font(letra);
    /*destroy_font(fontCordia48);
    destroy_font(fontCordia28);*/

}
BITMAP* randomExplosionBitmap()
{
    BITMAP* explosionBitmap;
    explosionBitmap=create_bitmap(tamBloco,tamBloco);
    int aux1=0;
    int aux2=0;
    
    for(int i=0;i<64;i++)
    {
        for(int j=0;j<64;j++)
        {
             aux1=rand()%70;
             aux2=rand()%70;
             putpixel(explosionBitmap, i, j, makecol(180+aux1,0,180+aux2));
        }
    }
   
    return explosionBitmap;
}

void checkSkeletonDestroyed(int x, int y)
{
    if(tela[x][y]=='S')
    {
        
        gameAudio.playSample(gameAudio.deadSkeleton);
        numberOfEnemies--;                
                     
    }  
    
    
    if(numberOfEnemies==0)
    {
        //stageClear   --- setting the door randomly
         int temp1,temp2;
         bool doorOK=false;
         while(!doorOK)
         {
             temp1=rand()%64;
             temp2=rand()%64;
         
             if(tela[temp1][temp2]=='F')
             {
                 tela[temp1][temp2]='D';                                                                                                        
                 doorOK=true;
             } 
             
         }
         
         numberOfEnemies=7;
         stageNumber=2;
         
        
                            
    }
      
     
     
     
} 

void KrashBomb::checkExplosion()
{

       if((this->bombIsSet==true)&&(timer-this->activationTime>3))
       {
           gameAudio.playSample(gameAudio.bomb1);
           
           for(int i=1;i<=player1.rangeOfExplosion;i++)
           {
                if(tela[this->x_location+i][this->y_location]!='P')/*&&(numberOfBlocksX>=(this->x_location+player1.rangeOfExplosion)))*/
                {
                                                                   
                                                                   
                    checkSkeletonDestroyed(this->x_location+i,this->y_location);
                    tela[this->x_location+i][this->y_location]='F';
                                                                                                      

                }
                if(tela[this->x_location-i][this->y_location]!='P')
                {
                    checkSkeletonDestroyed(this->x_location-i,this->y_location);
                    tela[this->x_location-i][this->y_location]='F';

                }

                if(tela[this->x_location][this->y_location+i]!='P')
                {
                    checkSkeletonDestroyed(this->x_location,this->y_location+i);
                    tela[this->x_location][this->y_location+i]='F';

                }

                if(tela[this->x_location][this->y_location-i]!='P')
                {
                    checkSkeletonDestroyed(this->x_location,this->y_location-i);
                    tela[this->x_location][this->y_location-i]='F';

                }
            }// for
                

            
           tela[this->x_location][this->y_location]='E';
           this->bombIsSet=false;
            
            // setting the explosion bitmap in the screen char matrix
           for(int i=1;i<=player1.rangeOfExplosion;i++)
           { 
               if((tela[this->x_location+i][this->y_location])!='P')
               {
                    tela[this->x_location+i][this->y_location]='E';   
               }
               else
               {
                   i=player1.rangeOfExplosion;
               }
           }
           
           for(int i=1;i<=player1.rangeOfExplosion;i++)
           {  
               if((tela[this->x_location+i][this->y_location])!='P')
               {
                    tela[this->x_location+i][this->y_location]='E';   
               }
               else
               {
                   i=player1.rangeOfExplosion;
               }
           }
              
           for(int i=1;i<=player1.rangeOfExplosion;i++)
           {   
               if((tela[this->x_location-i][this->y_location])!='P')
               {
                    tela[this->x_location-i][this->y_location]='E';   
               }
               else
               {
                   i=player1.rangeOfExplosion;
               }
           }
            
           for(int i=1;i<=player1.rangeOfExplosion;i++)
           { 
               if((tela[this->x_location][this->y_location+i])!='P')
               {
                    tela[this->x_location][this->y_location+i]='E';   
               }
               else
               {
                   i=player1.rangeOfExplosion;
               }
           }
           for(int i=1;i<=player1.rangeOfExplosion;i++)
           {  
               if((tela[this->x_location][this->y_location-i])!='P')
               {
                    tela[this->x_location][this->y_location-i]='E';   
               }
               else
               {
                   i=player1.rangeOfExplosion;
               }
           }

           
       }// if
       
       if((this->bombIsSet==false)&&((timer-this->activationTime)>4))
       {
           tela[this->x_location][this->y_location]='F';
           
           //randomly sets itemRaiseRangeOfExplosion   '1'
           for(int i=1;i<=player1.rangeOfExplosion;i++)
           {
               if((tela[this->x_location+i][this->y_location])=='E')
               {
                   if(items[this->x_location+i][this->y_location]=='1')
                   {
                        tela[this->x_location+i][this->y_location]='1';                                                   
                   }
                   else
                   {
                        tela[this->x_location+i][this->y_location]='F';       
                   }
                   
               }
               if((tela[this->x_location-i][this->y_location])=='E')
               {
                    if(items[this->x_location-i][this->y_location]=='1')
                   {
                        tela[this->x_location-i][this->y_location]='1';                                                   
                   }
                   else
                   {
                        tela[this->x_location-i][this->y_location]='F';       
                   }
                            
               }
               if((tela[this->x_location][this->y_location+i])=='E')
               {
                   if(items[this->x_location][this->y_location+i]=='1')
                   {
                        tela[this->x_location][this->y_location+i]='1';                                                   
                   }
                   else
                   {
                        tela[this->x_location][this->y_location+i]='F';       
                   }
                      
               }
               if((tela[this->x_location][this->y_location-i])=='E')
               {
                   if(items[this->x_location][this->y_location-i]=='1')
                   {
                        tela[this->x_location][this->y_location-i]='1';                                                   
                   }
                   else
                   {
                        tela[this->x_location][this->y_location-i]='F';       
                   }
                   
               }//if
                                                                         
           }//for
       }//if activationTime>4

} // end of function


void initBlockColor()
{
	// tamBloco é a variavel que guarda o tamanho dos blocos
	// tamBloco=size of the square in pixels
	blocoAzul=create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoAzul, 32, 32, 192);

	blocoVerde = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoVerde, 32, 192, 32);

	blocoVerm = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoVerm, 192, 32, 32);

	blocoAmarelo = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoAmarelo, 255,215,0);

	blocoRoxo = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoRoxo, 139, 0, 204);

	blocoCinza = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoCinza, 92, 92, 92);

	blocoLaranja = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoLaranja, 255, 153, 0);

	blocoRosa = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoRosa, 255, 0, 128);

}
 

void initGame()
{
    //do the game initializations

    srand(time(0));

    initMapMatrix();
    initBlockColor();
    createBrickBitmap();

    player1.x=10;
    player1.y=10;
    player1.imagem=sprite1_front1;
    tela[player1.x][player1.y]='@';

    //CPU1.x=10;
    //CPU1.y=10;
    //CPU1.imagem=sprite2_front1;
    //tela[CPU1.x][CPU1.y]='1';

}
void tela_inicial()
{   //initial screen

    int loop_count=0;
    
    while(loop_count<800)
    {
        clear_to_color(buffer, makecol(255, 255, 255));
        stretch_sprite(buffer, logo, 200, 0, 700, 700);
       // draw_sprite(buffer, spiderman_intro, 0, 0);
        textprintf_ex(buffer, font, 50,250 ,makecol(glow.fontaux,0,0),-1,"tictacKode");
        textprintf_ex(buffer, font, 50,300 ,makecol(glow.fontaux,0,0),-1,"tictacKrash");
        textprintf_ex(buffer, font, 50,350 ,makecol(glow.fontaux,0,0),-1,"A Bomberman Style Game");
        loop_count++;
        glow.glowingColor();

        blit(buffer,screen,0,0,0,0,numberOfBlocksX*tamBloco,numberOfBlocksY*tamBloco);
        if(key[KEY_ESC]) { freeAll(); deinit(); exit(0); }
    }
    gameAudio.playSample(gameAudio.intro);
}
void desenhaBlocoRandomico(int i, int j)
{   //draws grayscale squares with random color

    BITMAP* temp;
    temp=create_bitmap(tamBloco,tamBloco);
    int aux=64+rand()%191;

    criaBloco(temp,aux,aux,aux);
    blit(temp,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);


}

void paint()
{   //função que desenha o estado atual do jogo
    //draws the current game state
    set_alpha_blender();
    set_write_alpha_blender(); 
    
    int i, j;
    for(i=0; i<numberOfBlocksX; i++)
    {
        for(j=0; j<numberOfBlocksY; j++)
        {
            if((i%2!=0)&&(j%2!=0))
            {   //drawing the pillar, inacessible place
                blit(blocoVerde,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
            }
            else if(tela[i][j]=='B')
            {    // drawing a brick

                 blit(stageBricks[i][j],buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
            }
            else if(tela[i][j]=='K')
            {    // drawing a krash bomb
                 blit(krashBombImage,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
                 
            }
             else if(tela[i][j]=='1')
            {    // drawing a krash bomb
                 blit(itemRaiseRangeOfExplosion,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
                 
            }
            else if(tela[i][j]=='D')
            {    // drawing the exit door
                 blit(door,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
                 
            }
            else if(tela[i][j]=='S')
            {    // drawing a skeleton
                 blit(enemy_right,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
                 
            }
            else if(tela[i][j]=='E')
            {    // drawing a krash bomb
                 blit(explosionBitmap/*randomExplosionBitmap() */,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
                 
            }
            else if(tela[i][j]=='@')
            {    // drawing the player
                 draw_trans_sprite(player1.imagem, buffer, i*tamBloco, j*tamBloco);
                 
                 //blit(player1.imagem,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
            }
            else if(tela[i][j]=='1')
            {    // drawing a krash bomb
                 blit(CPU1.imagem,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
            }
            else
            {
                //draw floor
                blit(stageFloors[i][j],buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);

            }

        }
    }

    blit(player1.imagem,buffer,0,0,player1.x*tamBloco,player1.y*tamBloco,(player1.x*tamBloco)+tamBloco,(player1.y*tamBloco)+tamBloco);
    //blit(artefato.imagem,buffer,0,0,artefato.x*tamBloco,artefato.y*tamBloco,(artefato.x*tamBloco)+tamBloco,(artefato.y*tamBloco)+tamBloco);
    //blit(combustivel.imagem,buffer,0,0,combustivel.x*tamBloco,combustivel.y*tamBloco,(combustivel.x*tamBloco)+tamBloco,(combustivel.y*tamBloco)+tamBloco);

    //timer
    textprintf_ex(buffer, font, 10,tamBloco ,makecol(glow.fontaux,glow.fontaux,glow.fontaux), -1,"Timer %d ",timer);

//    textprintf_ex(buffer, fontCordia48, 10,tamBloco+50 ,makecol(0,glow.fontaux,0), -1,"Artefatos %d ",player1.artefatos);
    blit(buffer,screen,0,0,0,0,numberOfBlocksX*tamBloco,numberOfBlocksY*tamBloco);
}
void paint_to_buffer()
{   //função que desenha o estado atual do jogo
    //draws the current game state
    set_alpha_blender();
    set_write_alpha_blender(); 
    
    int i, j;
    for(i=0; i<numberOfBlocksX; i++)
    {
        for(j=0; j<numberOfBlocksY; j++)
        {
            if((i%2!=0)&&(j%2!=0))
            {   //drawing the pillar, inacessible place
                blit(blocoVerde,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
            }
            else if(tela[i][j]=='B')
            {    // drawing a brick

                 blit(stageBricks[i][j],buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
            }
            else if(tela[i][j]=='K')
            {    // drawing a krash bomb
                 blit(krashBombImage,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
                 
            }
             else if(tela[i][j]=='1')
            {    // drawing a krash bomb
                 blit(itemRaiseRangeOfExplosion,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
                 
            }
            else if(tela[i][j]=='S')
            {    // drawing a skeleton
                 blit(enemy_right,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
                 
            }
            else if(tela[i][j]=='E')
            {    // drawing a krash bomb
                 blit(explosionBitmap/*randomExplosionBitmap() */,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
                 
            }
            else if(tela[i][j]=='@')
            {    // drawing the player
                 draw_trans_sprite(player1.imagem, buffer, i*tamBloco, j*tamBloco);
                 
                 //blit(player1.imagem,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
                 
            }
            else if(tela[i][j]=='1')
            {    // drawing a krash bomb
                 blit(CPU1.imagem,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
            }
            else
            {
                //draw floor
                blit(stageFloors[i][j],buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);

            }

        }
    }

    blit(player1.imagem,buffer,0,0,player1.x*tamBloco,player1.y*tamBloco,(player1.x*tamBloco)+tamBloco,(player1.y*tamBloco)+tamBloco);
    //blit(artefato.imagem,buffer,0,0,artefato.x*tamBloco,artefato.y*tamBloco,(artefato.x*tamBloco)+tamBloco,(artefato.y*tamBloco)+tamBloco);
    //blit(combustivel.imagem,buffer,0,0,combustivel.x*tamBloco,combustivel.y*tamBloco,(combustivel.x*tamBloco)+tamBloco,(combustivel.y*tamBloco)+tamBloco);

    //timer
    textprintf_ex(buffer, font, 10,tamBloco ,makecol(glow.fontaux,glow.fontaux,glow.fontaux), -1,"Timer %d ",timer);

//    textprintf_ex(buffer, fontCordia48, 10,tamBloco+50 ,makecol(0,glow.fontaux,0), -1,"Artefatos %d ",player1.artefatos);
   // blit(buffer,screen,0,0,0,0,numberOfBlocksX*tamBloco,numberOfBlocksY*tamBloco);
}

/*void gameOver()
{   //Game over screen

    int loop_count=0;
    while(loop_count<1000)
    {
       // draw_sprite(buffer, spiderlost, 0, 0);
        //textprintf_ex(buffer, fontCordia48, 180,150 ,makecol(glow.fontaux,0,0),-1,"Game Over!",player1.artefatos);
//        textprintf_ex(buffer, fontCordia48, 50,200 ,makecol(0,glow.fontaux,0),-1,"Pegou %d vezes o escudo",player1.artefatos);
        textprintf_ex(buffer, fontCordia48, 180,250 ,makecol(0,glow.fontaux,0),-1,"Esc para sair");
        textprintf_ex(buffer, fontCordia28, 20,480 ,makecol(0,glow.fontaux,0),-1,"https://www.facebook.com/groups/ProgDesafios/");
        textprintf_ex(buffer, fontCordia28, 20,540 ,makecol(0,glow.fontaux,0),-1,"https://www.youtube.com/user/tictacKode/playlists");
        loop_count++;
        glow.glow();

        blit(buffer,screen,0,0,0,0,12*tamBloco,10*tamBloco);
        if(key[KEY_ESC]) { freeAll(); deinit(); exit(0); }
    }
    freeAll(); deinit(); exit(0);
}*/
bool testColisionUP(char tile)
{
    if((tela[player1.x][player1.y-1]!=tile))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool testColisionDOWN(char tile)
{
    if((tela[player1.x][player1.y+1]!=tile))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool testColisionLEFT(char tile)
{
    if((tela[player1.x-1][player1.y]!=tile))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool testColisionRIGHT(char tile)
{
    if((tela[player1.x+1][player1.y]!=tile))
    {
        return true;
    }
    else
    {
        return false;
    }
}

