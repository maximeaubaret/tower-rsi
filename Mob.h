/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

#define DEFAULT_MOB_LIFE 100

typedef struct {
  int active;

  int level;

  int tile;

  int position;
  
  int life;

  int speed;
  int ticker;
} Mob;

Mob * newMob (int level, int tile, int speed);
void tickMob (void *g, Mob *m);

int mobLife (Mob *m);
int mobScoreWin (Mob *m);
int mobScoreDead (Mob *m);

void fireMob (Mob *m, int damage);
