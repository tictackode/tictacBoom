
#include <allegro.h>
#include <time.h>
#include "Glow.h"

#include "functions.h"
#include "Controle.h"


int main()
{
    //initializations
    init();
    loadAll();
    initGame();
    //clearItemsMatrix();

	LOCK_FUNCTION(incrementaTimer);
	LOCK_VARIABLE(timer);

	LOCK_FUNCTION(incrementaTimerMilisec);
	LOCK_VARIABLE(timerMilisec);

	timer = 0;
    clear_to_color(buffer, makecol(255, 255, 255));
    stretch_sprite(buffer, logo, 200, 0, 700, 700);
    highcolor_fade_in(buffer, 6);
    tela_inicial();
    
    paint_to_buffer();
    highcolor_fade_in(buffer, 4);

    install_int_ex(incrementaTimer, MSEC_TO_TIMER(1000));

    install_int_ex(incrementaTimerMilisec, MSEC_TO_TIMER(1));
    
    
    while(!key[KEY_ESC])
    {
        
        paint();
        glow.glowingColor();
        controle();

        player1.bomb[0].checkExplosion();
        player1.bomb[1].checkExplosion();
        player1.bomb[2].checkExplosion();
        player1.bomb[3].checkExplosion();
        player1.bomb[4].checkExplosion();


    }

    freeAll();
    deinit();
    
    return 0;
    
    
}
END_OF_MAIN()
