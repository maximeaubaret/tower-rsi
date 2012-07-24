/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

#include <SDL.h>
#define TICK_INTERVAL 50

Uint32 next;

/**
  * timerInit ()
  */
void 
timerInit () 
{
  next = SDL_GetTicks() + TICK_INTERVAL;
}


/**
  * timerWait ()
  */
void 
timerWait () 
{
  Uint32 now;
  now = SDL_GetTicks ();

  if (next > now) 
    SDL_Delay (next-now);

  next+=TICK_INTERVAL;
}
