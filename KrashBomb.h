


class KrashBomb
{
   public:
   int x_location;
   int y_location;
   //int rangeOfExplosion;
   volatile int activationTime;
   int bombTimeCount;
   bool bombIsSet;
   BITMAP* imagem;

   KrashBomb()
   {
       
        this->bombIsSet=false;
        
   }
   KrashBomb(volatile int timer,int x_location,int y_location)
   {
       this->x_location=x_location;
       this->y_location=y_location;
       this->activationTime=timer;
   }

   ~KrashBomb()
   {
   
        destroy_bitmap(this->imagem);
        //delete(this);
   }

    void setKrashBomb(volatile int timer,int x_location,int y_location)
   {
       this->x_location=x_location;
       this->y_location=y_location;
       this->activationTime=timer;
       this->bombIsSet=true;
       //this->bombTimeCount=bombTime;
   }
   void checkExplosion();
   void explosionAnimation();
   

};
