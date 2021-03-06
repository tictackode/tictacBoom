/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/

class Audio
{
      
      public:
      SAMPLE* hit;
      SAMPLE* intro;
      SAMPLE* step1;
      SAMPLE* step2;
      SAMPLE* bomb1;
      SAMPLE* powerUp;
      SAMPLE* deadSkeleton;
      
      Audio()
      {
          this->hit = load_sample("sound/phase2.wav");
          this->intro = load_sample("sound/chime2.wav");
          this->step1 = load_sample("sound/step1.wav");
          this->step2 = load_sample("sound/step2.wav");
          this->bomb1 = load_sample("sound/bomb1.wav");
          this->powerUp = load_sample("sound/powerUp.wav");
          this->deadSkeleton = load_sample("sound/deadSkeleton.wav");
             
      }
      ~Audio()
      {
          destroy_sample(this->hit);
          destroy_sample(this->intro);
          destroy_sample(this->step1);
          destroy_sample(this->step2);
          destroy_sample(this->bomb1);
          destroy_sample(this->deadSkeleton);
          delete(this);
      }
      // method to play sound effect
      void playSample(SAMPLE* sound)
      { 
          play_sample(sound, 255, 128, 1000, 0);
      }
    
}gameAudio;


