
/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/
void nextLevel();

void controle()
{   // handles the keys that controls the application

    if(key[KEY_UP]||key[KEY_W])
    {
        
        if(player1.y>0)
        {
            if(tela[player1.x][player1.y-1]=='D')
            {
                 nextLevel();                                           
            }
            if((items[player1.x][player1.y-1]=='1')&&(tela[player1.x][player1.y-1]!='B'))
            {
                player1.rangeOfExplosion++;
                gameAudio.playSample(gameAudio.powerUp);
                tela[player1.x][player1.y-1]='1';
                items[player1.x][player1.y-1]='B';
            }
            if((testColisionUP('P'))&&(testColisionUP('B'))&&(testColisionUP('K'))&&(testColisionUP('S')))
            {
                
                if(tela[player1.x][player1.y]!='K') 
                { 
                    tela[player1.x][player1.y]='F'; 
                }
                player1.y-=1;
                tela[player1.x][player1.y]='@';
                player1.imagem=sprite1_back1;
                gameAudio.playSample(gameAudio.step2);
            }
           
        }
        
    }

    if(key[KEY_DOWN]||key[KEY_S])
    {
        if(tela[player1.x][player1.y+1]=='D')
        {
            nextLevel();                                           
        }
        if(player1.y<numberOfBlocksY-1)
        {
            if((items[player1.x][player1.y+1]=='1')&&(tela[player1.x][player1.y+1]!='B'))
            {
                player1.rangeOfExplosion++;
                gameAudio.playSample(gameAudio.powerUp);
                tela[player1.x][player1.y+1]='@';
                items[player1.x][player1.y+1]='B';
            }
            if((testColisionDOWN('P'))&&(testColisionDOWN('B'))&&(testColisionDOWN('K'))&&(testColisionDOWN('S')))
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
        if(tela[player1.x-1][player1.y]=='D')
        {
            nextLevel();                                           
        }
        if(player1.x>0)
        {
            if((items[player1.x-1][player1.y]=='1')&&(tela[player1.x-1][player1.y]!='B'))
            {
                player1.rangeOfExplosion++;
                gameAudio.playSample(gameAudio.powerUp);
                tela[player1.x-1][player1.y]='@';
                items[player1.x-1][player1.y]='B';
            }
            if((testColisionLEFT('P'))&&(testColisionLEFT('B'))&&(testColisionLEFT('K'))&&(testColisionLEFT('S')))
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
        if(tela[player1.x+1][player1.y]=='D')
        {
            nextLevel();                                           
        }
        if(player1.x<numberOfBlocksX-1)
        {
            if((items[player1.x+1][player1.y]=='1')&&(tela[player1.x+1][player1.y]!='B'))
            {
                player1.rangeOfExplosion++;
                gameAudio.playSample(gameAudio.powerUp);
                 tela[player1.x+1][player1.y]='@';
                 items[player1.x+1][player1.y]='B';
            }
            if((testColisionRIGHT('P'))&&(testColisionRIGHT('B'))&&(testColisionRIGHT('K'))&&(testColisionRIGHT('S')))
            {
               
                if(tela[player1.x][player1.y]!='K') 
                { 
                    tela[player1.x][player1.y]='F'; 
                }
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
            player1.bomb[0].setKrashBomb(timer,player1.x ,player1.y);
            tela[player1.x][player1.y]='K';
        }
        else if(player1.bomb[1].bombIsSet==false)
        {
            player1.bomb[1].setKrashBomb(timer,player1.x ,player1.y);
            tela[player1.x][player1.y]='K';
        }
        else if(player1.bomb[2].bombIsSet==false)
        {
            player1.bomb[2].setKrashBomb(timer,player1.x ,player1.y );
            tela[player1.x][player1.y]='K';
        }
        else if(player1.bomb[3].bombIsSet==false)
        {
            player1.bomb[3].setKrashBomb(timer,player1.x ,player1.y );
            tela[player1.x][player1.y]='K';
        }
        else if(player1.bomb[4].bombIsSet==false)
        {
            player1.bomb[4].setKrashBomb(timer,player1.x ,player1.y );
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

void nextLevel()
{
     highcolor_fade_out(2);
     initGame();                  
     paint_to_buffer();
     highcolor_fade_in(buffer, 2);     
     
}
