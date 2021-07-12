
#include <allegro.h>
#include <time.h>
#include "Glow.h"

#include "functions.h"

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

    tela_inicial();

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
