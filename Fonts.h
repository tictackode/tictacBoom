/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/


class Fonts
{
      
      public:
      FONT* letra;
      FONT* fontCordia48;
      FONT* fontCordia28;
      
      Fonts()
      {
          
             
      }
      ~Fonts()
      {
          destroy_font(this->letra);
          destroy_font(this->fontCordia28);
          destroy_font(this->fontCordia48);
          /*destroy_sample(this->step1);
          destroy_sample(this->step2);
          destroy_sample(this->bomb1);*/
          delete(this);
      }
      void loadALLFonts()
      {
          this->letra = load_font("fonts/arial18.pcx",NULL,NULL);
          this->fontCordia48 = load_font("fonts/cordia28.pcx",NULL,NULL);
          this->fontCordia28 = load_font("fonts/cordia48.pcx",NULL,NULL);
          
          if(!fontCordia28) { exit(1); }
          
          if(!letra) { exit(1); }

          if(!fontCordia48) { exit(1); }     
           
           
      }
      
      /*void playSample(SAMPLE* sound)
      { 
          play_sample(sound, 255, 128, 1000, 0);
      }*/
    
};
