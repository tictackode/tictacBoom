


class KrashBomb
{
   public:
   int x_location;
   int y_location;
   int rangeOfExplosion;
   volatile int activationTime;
   int bombTimeCount;
   bool bombIsSet;
   BITMAP* imagem;

   KrashBomb()
   {
        this->rangeOfExplosion=1;
        this->bombIsSet=false;
        
   }
   KrashBomb(volatile int timer,int x_location,int y_location,int rangeOfExplosion)
   {
       this->x_location=x_location;
       this->y_location=y_location;
       this->rangeOfExplosion=rangeOfExplosion;
       this->activationTime=timer;
   }

   ~KrashBomb()
   {
   
        destroy_bitmap(this->imagem);
        delete(this);
   }

    void setKrashBomb(volatile int timer,int x_location,int y_location,int rangeOfExplosion)
   {
       this->x_location=x_location;
       this->y_location=y_location;
       this->rangeOfExplosion=rangeOfExplosion;
       this->activationTime=timer;
       this->bombIsSet=true;
       //this->bombTimeCount=bombTime;
   }
   void checkExplosion();
   

};
