#include <time.h>

#include "Jogador.h"
#include "Audio.h"

#define tamBloco 64
#define numberOfBlocksX 18
#define numberOfBlocksY 11


char tela[numberOfBlocksX][numberOfBlocksY];

BITMAP* stageFloors[numberOfBlocksX][numberOfBlocksY];
BITMAP* stageBricks[numberOfBlocksX][numberOfBlocksY];

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
BITMAP* brick;

BITMAP* sprite1_front1;
BITMAP* sprite1_left1;
BITMAP* sprite1_right1;
BITMAP* sprite1_back1;

BITMAP* sprite2_front1;
BITMAP* sprite2_left1;
BITMAP* sprite2_right1;
BITMAP* sprite2_back1;

//FONT *letra;
/*FONT *fontCordia48;
FONT *fontCordia28;*/

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

void loadAll()
{   //function that loads all extern images and fonts

    set_window_title("TictacKrash - A TictacKode's Bomberman clone!");
    buffer=create_bitmap(numberOfBlocksX*tamBloco,numberOfBlocksY*tamBloco);

    /*fontCordia28=load_font("fonts/cordia28.pcx",NULL,NULL);
    if(!fontCordia28) { exit(1); }

    letra=load_font("fonts/cordia36.pcx",NULL,NULL);
    if(!letra) { exit(1); }

    fontCordia48=load_font("fonts/cordia48.pcx",NULL,NULL);
    if(!fontCordia48) { exit(1); }*/

    logo=create_bitmap(13*tamBloco,11*tamBloco);
    logo=load_bitmap("img/tictackode.bmp",0);
    if(!logo) { exit(1); }

    krashBombImage=create_bitmap(tamBloco,tamBloco);
    krashBombImage=load_bitmap("img/timebomb256colors.bmp",0);
    if(!logo) { exit(1); }


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



}
void freeAll()
{   //clear the game bitmaps from memory

   /* destroy_bitmap(blocoVerm);
    destroy_bitmap(blocoAzul);
    destroy_bitmap(blocoVerde);
    destroy_bitmap(blocoCinza);
    destroy_bitmap(blocoAmarelo);
    destroy_bitmap(blocoRoxo);
    destroy_bitmap(blocoLaranja);
    destroy_bitmap(blocoRosa);
    destroy_bitmap(krashBombImage);*/
    destroy_bitmap(buffer);

    //clear the fonts used in the game
    //destroy_font(letra);
    /*destroy_font(fontCordia48);
    destroy_font(fontCordia28);*/

}

void KrashBomb::checkExplosion()
{

       if((this->bombIsSet==true)&&(timer-this->activationTime)>3)
       {
           gameAudio.playSample(gameAudio.bomb1);
           
           for(int i=1;i<=this->rangeOfExplosion;i++)
           {
                if(tela[this->x_location+i][this->y_location]!='P')
                {
                    tela[this->x_location+i][this->y_location]='F';


                }
                if(tela[this->x_location-i][this->y_location]!='P')
                {
                    tela[this->x_location-i][this->y_location]='F';

                }

                if(tela[this->x_location][this->y_location+i]!='P')
                {
                    tela[this->x_location][this->y_location+i]='F';

                }

                if(tela[this->x_location][this->y_location-i]!='P')
                {
                    tela[this->x_location][this->y_location-i]='F';

                }

           }
            tela[this->x_location][this->y_location]='F'; // bomb becomes floor
            this->bombIsSet=false;

       }
       

}
void criaBloco(BITMAP* bmp, int red, int green, int blue)
{   //this function generates the color for the square bitmaps

	int escuroR = 30,escuroG=30,escuroB=30;

	if (red < 30) { escuroR = 0; }
	if (green < 30) { escuroG = 0; }
	if (blue < 30) { escuroB = 0; }

	rectfill(bmp, 0, 0, tamBloco - (tamBloco / 10), tamBloco - (tamBloco / 10), makecol(red, green, blue));
	rectfill(bmp, 0, tamBloco - (tamBloco / 10), tamBloco, tamBloco, makecol(red - escuroR, green - escuroG, blue - escuroB));
	rectfill(bmp, tamBloco - (tamBloco / 10), 0, tamBloco, tamBloco, makecol(red - escuroR, green - escuroG, blue - escuroB));

}
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
 void initMapMatrix()
{
    int aux;
    for(int i=0;i<numberOfBlocksX;i++)
    {

        for(int j=0;j<numberOfBlocksY;j++)
        {
            //generates a floor
            stageFloors[i][j]=returnsRandomGrayscaleFloor();

            if((i%2!=0)&&(j%2!=0))
            {
                tela[i][j]='P'; //Pillar
            }
            if((i%2==0)&&(j%2==0))
            {
                aux=rand()%3;
                if(aux==0)
                {
                    tela[i][j]='B'; // 33% of chance to set a Brick
                    stageBricks[i][j]=createBrickBitmap();
                }
                else
                {
                    tela[i][j]='F'; //Floor


                }
            }
        }
    }

}

void initGame()
{
    //do the game initializations

    srand(time(0));

    initMapMatrix();
    initBlockColor();
    createBrickBitmap();

    player1.x=0;
    player1.y=0;
    player1.imagem=sprite1_front1;
    tela[player1.x][player1.y]='@';

    CPU1.x=10;
    CPU1.y=10;
    CPU1.imagem=sprite2_front1;
    tela[CPU1.x][CPU1.y]='1';

}
void tela_inicial()
{   //initial screen


    int loop_count=0;
    
    while(loop_count<1000)
    {
       // draw_sprite(buffer, spiderman_intro, 0, 0);
        textprintf_ex(buffer, font, 50,250 ,makecol(glow.fontaux,0,0),-1,"tictacKode");
        textprintf_ex(buffer, font, 50,300 ,makecol(glow.fontaux,0,0),-1,"tictacKrash");
        textprintf_ex(buffer, font, 50,350 ,makecol(glow.fontaux,0,0),-1,"A Bomberman Style Game");
        loop_count++;
        glow.glowingColor();

        blit(buffer,screen,0,0,0,0,20*tamBloco,20*tamBloco);
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
BITMAP* returnsRandomGrayscaleFloor()
{
    BITMAP* temp;
    temp=create_bitmap(tamBloco,tamBloco);
    int aux=32+rand()%32;

    criaBloco(temp,aux,aux,aux);

    return temp;
}
BITMAP* createBrickBitmap()
{

    brick=create_bitmap(tamBloco,tamBloco);

    if(!brick) { freeAll(); deinit(); exit(0); }

    int aux=200+rand()%25;

    criaBloco(brick,aux,32,0);

    aux=230+rand()%25;

    //void hline(BITMAP *bmp, int x1, int y, int x2, int color);
    hline(brick,0,15,64,makecol(aux,aux,aux));
    rect(brick,0,0,0,31,makecol(aux,aux,aux));
    aux=230+rand()%25;

    hline(brick,0,31,64,makecol(aux,aux,aux));
   // rect(brick,31,31,0,31,makecol(aux,aux,aux));
    
    
    aux=230+rand()%25;

    hline(brick,0,46,64,makecol(aux,aux,aux));

    

    //void vline(BITMAP *bmp, int x, int y1, int y2, int color);
    //rect(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
    vline(brick,20,0 , 15, makecol(255,255,255));
    
   // int positionTemp=rand()%20;
   // rect(brick,positionTemp,0,positionTemp+15,15,makecol(255,255,255));
    
    //positionTemp=rand()%20;
    vline(brick,46,15 , 31, makecol(255,255,255));
   // rect(brick,positionTemp,,positionTemp+15,31,makecol(255,255,255));
    
   // positionTemp=rand()%20;
    vline(brick,36,31 , 46, makecol(255,255,255));
    //rect(brick,positionTemp,31,positionTemp+15,46,makecol(255,255,255));
    
   // positionTemp=rand()%20;
    vline(brick,50,46 , 63, makecol(255,255,255));
   // rect(brick,positionTemp,46,positionTemp+15,63,makecol(255,255,255));
      
    rect(brick,0,0,63,63,makecol(255,255,255));
    
    return brick;
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
void controle()
{   // handles the keys that controls the application

    if(key[KEY_UP]||key[KEY_W])
    {
        if(player1.y>0)
        {
            if((testColisionUP('P'))&&(testColisionUP('B'))&&(testColisionUP('K')))
            {
                if(tela[player1.x][player1.y]!='K') { tela[player1.x][player1.y]='F'; }
                player1.y-=1;
                tela[player1.x][player1.y]='@';
                player1.imagem=sprite1_back1;
                gameAudio.playSample(gameAudio.step2);
            }
        }
        
    }

    if(key[KEY_DOWN]||key[KEY_S])
    {
        if(player1.y<numberOfBlocksY-1)
        {
            if((testColisionDOWN('P'))&&(testColisionDOWN('B'))&&(testColisionDOWN('K')))
            {
                if(tela[player1.x][player1.y]!='K') { tela[player1.x][player1.y]='F'; }
                player1.y+=1;
                tela[player1.x][player1.y]='@';
                player1.imagem=sprite1_front1;
                gameAudio.playSample(gameAudio.step2);
            }
        }
        
    }

    if(key[KEY_LEFT]||key[KEY_A])
    {
        if(player1.x>0)
        {
            if((testColisionLEFT('P'))&&(testColisionLEFT('B'))&&(testColisionLEFT('K')))
            {
                if(tela[player1.x][player1.y]!='K') { tela[player1.x][player1.y]='F'; }
                player1.x-=1;
                tela[player1.x][player1.y]='@';
                player1.imagem=sprite1_left1;
                gameAudio.playSample(gameAudio.step2);
            }
        }
        

    }

    if(key[KEY_RIGHT]||key[KEY_D])
    {
        if(player1.x<numberOfBlocksX-1)
        {
            if((testColisionRIGHT('P'))&&(testColisionRIGHT('B'))&&(testColisionRIGHT('K')))
            {
                if(tela[player1.x][player1.y]!='K') { tela[player1.x][player1.y]='F'; }
                player1.x+=1;
                tela[player1.x][player1.y]='@';
                player1.imagem=sprite1_right1;
                gameAudio.playSample(gameAudio.step2);
            }
        }
        

    }

    if(key[KEY_SPACE])
    {   //set krash bomb

        if(player1.bomb[0].bombIsSet==false)
        {
            player1.bomb[0].setKrashBomb(timer,player1.x ,player1.y ,player1.rangeOfExplosion);
            tela[player1.x][player1.y]='K';
        }
        else if(player1.bomb[1].bombIsSet==false)
        {
            player1.bomb[1].setKrashBomb(timer,player1.x ,player1.y ,player1.rangeOfExplosion);
            tela[player1.x][player1.y]='K';
        }
        else if(player1.bomb[2].bombIsSet==false)
        {
            player1.bomb[2].setKrashBomb(timer,player1.x ,player1.y ,player1.rangeOfExplosion);
            tela[player1.x][player1.y]='K';
        }
        else if(player1.bomb[3].bombIsSet==false)
        {
            player1.bomb[3].setKrashBomb(timer,player1.x ,player1.y ,player1.rangeOfExplosion);
            tela[player1.x][player1.y]='K';
        }
        else if(player1.bomb[4].bombIsSet==false)
        {
            player1.bomb[4].setKrashBomb(timer,player1.x ,player1.y ,player1.rangeOfExplosion);
            tela[player1.x][player1.y]='K';
        }

        
    }


    key[KEY_UP]=false;
    key[KEY_DOWN]=false;
    key[KEY_LEFT]=false;
    key[KEY_RIGHT]=false;
    key[KEY_SPACE]=false;
    key[KEY_W]=false;
    key[KEY_S]=false;
    key[KEY_A]=false;
    key[KEY_D]=false;
    
}
