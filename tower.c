/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Point.h"
#include "Mob.h"
#include "TowerMob.h"
#include "game.h"
#include "graphics.h"
#include "timer.h"

int 
main (
    int argc, 
    char *argv[]) 
{
  game_t *g;
  int finished = 0;
  static int tick = 0;

  if (argc < 2) {
    printf ("Usage: %s <file>\n", argv[0]);
    exit (1); 
  }

  srand (time (NULL)); // Random seed

  loadTiles();

  g = loadBoard(argv[1]);

  initWindow (g->width, g->height);

  timerInit();

  startGame (g);

  while (!finished) {
    finished = getEvent(g);

    paint (g, tick);
    update (g, tick);
    
    timerWait();
    tick++;
  }
  return EXIT_SUCCESS;
}
