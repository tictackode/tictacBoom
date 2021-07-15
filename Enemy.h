/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/


class Enemy
{
   public:
   int x;
   int y;
   BITMAP* enemy_right;
   BITMAP* enemy_left;
   

   Enemy()
   {
            this->enemy_left=create_bitmap(64,64);
            this->enemy_right=create_bitmap(64,64);
            
            this->enemy_right=load_bitmap("img/skull_right.bmp",0);
            if(!this->enemy_right) 
            {
                exit(1);
            } 
            this->enemy_left=load_bitmap("img/skull_left.bmp",0);
            if(!this->enemy_left) 
            {
                exit(1); 
            }
        
   }
   ~Enemy()
   {
        destroy_bitmap(this->enemy_right);
        destroy_bitmap(this->enemy_left);
        //delete(this);
   }
   

 

}skeleton;

