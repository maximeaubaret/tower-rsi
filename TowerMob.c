/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

#include <stdio.h>
#include <stdlib.h>
#include "Point.h"
#include "TowerMob.h"
#include "Mob.h"
#include "game.h"

void explosion (game_t *g, Point *p);

Tower *
newTower (
    int level,
    int tile,
    int speed)
{
  Tower *t = (Tower *) malloc (sizeof (Tower));

  t->tile = tile;

  t->level = 0;

  t->speed = speed;
  t->ticker = 0;

  return t;
}


int
towerScore (
    Tower *t)
{
  return DEFAULT_TOWER_SCORE + (t->level + 1) * DEFAULT_TOWER_SCORE * 0.75;
}

/**
  * placeTower ()
  *
  * @param game_t *	g
  * @param Point	p
  *
  * @return int
  */
int
placeTower (
    void *v,
    Point p)
{
  game_t *g = (game_t *)v;

  if (g->towers[p.y * g->width + p.x] == NULL &&
      g->board[p.y * g->width + p.x] != TREE &&
      !isRoute (g->board[p.y * g->width + p.x]) &&
      !isWater (g->board[p.y * g->width + p.x]) 
     ) {

    if (g->score >= DEFAULT_TOWER_SCORE) {
      Tower *t = newTower (0, TOUR_0 + rand() % 3, 15);
      g->towers[p.y * g->width + p.x] = t;

      g->score -= DEFAULT_TOWER_SCORE;
    }
    else {
      printf ("Not enough to buy a tower (%i)\n", DEFAULT_TOWER_SCORE);
    }
    return 1;
  }

  return 0;
}


/**
  * evolveTower ()
  *
  * @param game_t *	g
  * @param Point	p
  *
  * @return int	
  */
int
evolveTower (
    void *v,
    Point p)
{
  game_t *g = (game_t *)v;

  if (g->towers[p.y * g->width + p.x] != NULL) {
    Tower *t = g->towers[p.y * g->width + p.x];

    if (g->score >= towerScore (t)) {
      g->score = g->score - towerScore (t);
      t->level++;

      return 1;
    }
    else {
      printf ("Not enough score! (%i)\n", towerScore (t));
    }
  }

  return 0;
}

void
towerSell (
    void *v,
    Point p)
{
  game_t *g = (game_t *)v;

  Tower *t = g->towers[p.y * g->width + p.x];

  if (t != NULL) {
    if (t->level == 0) {
      g->score += 10;
    }
    else {
      g->score += 30;
    }

    g->towers[p.y * g->width + p.x] = NULL;
    free (t);
  }

}

int 
towerDamage (
    Tower *t)
{
  return towerScore (t) * 0.5;
}

int
mobReachable (
    game_t *g,
    Tower *t,
    Mob *m)
{
  int r = 0;

  Point *t_p = towerPoint (g, t);
  Point *m_p = g->route[m->position];

  if (t_p != NULL && m_p != NULL) {
    int d = (t_p->x - m_p->x) * (t_p->x - m_p->x) +
      (t_p->y - m_p->y) * (t_p->y - m_p->y);

    return (d <= DEFAULT_TOWER_DISTANCE);
  }

  return 10000000;

  /*
  if (m->position >=  0) {

    int i, j;
    for (i = -1; i < 2; i++) {
      for (j = -1; j < 2; j++) {

	if (t_p->x + i >= 0 && t_p->x + j < g->width &&
	    t_p->y + j >= 0 && t_p->y + j < g->height) {

	  if (m_p->x == (t_p->x + i) && m_p->y == (t_p->y + j)) {
	    r = 1;
	    break;
	  }
	}
      }
    }

  }

  freePoint (t_p);
  */

  return r;
}

void
towerFire (
    game_t *g,
    Tower *t)
{
  int i;

  for (i = 0; i < g->nMobs; i++) {
    Mob *m = g->mobs[i];

    if (m->active && mobReachable (g, t, m)) {
      explosion (g, g->route[m->position]);

      fireMob (m, towerDamage (t));

      g->score = g->score + mobScoreWin (m);

      return;
    }
  }
}

void
towerTick (
    void *v,
    Tower *t)
{
  game_t *g = (game_t *)v;


  if (t->ticker-- == 0) {
    towerFire (g, t);

    t->ticker = t->speed;
  }
}
