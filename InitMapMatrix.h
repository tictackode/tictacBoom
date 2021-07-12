

/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/

#define numberOfBlocksX 18
#define numberOfBlocksY 11
#define tamBloco 64

int stageNumber=1;
int numberOfEnemies=5;

char tela[numberOfBlocksX][numberOfBlocksY];
char items[numberOfBlocksX][numberOfBlocksY];
BITMAP* stageFloors[numberOfBlocksX][numberOfBlocksY];
BITMAP* stageBricks[numberOfBlocksX][numberOfBlocksY];

BITMAP* brick;
BITMAP* createBlueBrickBitmap();
BITMAP* createBrickBitmap();
BITMAP* returnsRandomGrayscaleFloor();
void criaBloco(BITMAP* bmp, int red, int green, int blue);

void initMapMatrix()
{
    int aux;
    
/*
B - brick -          tijolo
P - pillar -         coluna de concreto
1 - item to raise bomb explosion range
S - skeleton



*/
    for(int i=0;i<numberOfBlocksX;i++)
    {

        for(int j=0;j<numberOfBlocksY;j++)
        {
            //generates a floor
            stageFloors[i][j]=returnsRandomGrayscaleFloor();

            if((i%2!=0)&&(j%2!=0))
            {
                tela[i][j]='P'; //Pillar
                items[i][j]='P'; 
            }
            else
            {
                // 50% of chance to set a Brick
                aux=rand()%30;
                if(aux<14)
                {
                    tela[i][j]='B'; 
                    if(stageNumber==1)
                    {
                    
                        stageBricks[i][j]=createBrickBitmap();
                    }
                    else if(stageNumber==2)
                    {
                         stageBricks[i][j]=createBlueBrickBitmap();
                         
                    }
                    aux=rand()%100;
                    if(aux<15)
                    {
                        //sets item range of explosion
                        items[i][j]='1';
                    }
                    
                }
                else
                {
                     tela[i][j]='F'; //Floor
                

                }
             
                
               
            }//else
        }//for
    }//for
    
    //setting the enemies on stage randomly
     int temp1,temp2;
     while(numberOfEnemies>0)
     {
         temp1=rand()%64;
         temp2=rand()%64;
         
         if(tela[temp1][temp2]=='F')
         {
             tela[temp1][temp2]='S';                                                                                                        
             numberOfEnemies--;   
         } 
     }
     numberOfEnemies=5;
    

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

    //if(!brick) { freeAll(); deinit(); exit(0); }

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
    vline(brick,24,0 , 15, makecol(255,255,255));
    
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
    vline(brick,12,46 , 63, makecol(255,255,255));
   // rect(brick,positionTemp,46,positionTemp+15,63,makecol(255,255,255));
      
    rect(brick,0,0,63,63,makecol(255,255,255));
    
    return brick;
}
BITMAP* createBlueBrickBitmap()
{

    brick=create_bitmap(tamBloco,tamBloco);

    //if(!brick) { freeAll(); deinit(); exit(0); }

    int aux=200+rand()%25;

    criaBloco(brick,0,32,255);

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
    vline(brick,24,0 , 15, makecol(255,255,255));
    
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
    vline(brick,12,46 , 63, makecol(255,255,255));
   // rect(brick,positionTemp,46,positionTemp+15,63,makecol(255,255,255));
      
    rect(brick,0,0,63,63,makecol(255,255,255));
    
    return brick;
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
