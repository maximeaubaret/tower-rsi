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
#include "Mob.h"
#include "Point.h"
#include "TowerMob.h"
#include "game.h"

Mob *
newMob (
    int level,
    int tile,
    int speed)
{
  Mob *m;

  m = (Mob *) malloc (sizeof (Mob));

  m->active = 1;

  m->level = level;

  m->position = -1;
  m->tile = tile;

  m->life = 0;

  m->speed = speed;
  m->ticker = 1;

  return m;
}

int 
mobLife (
    Mob *m)
{
  return DEFAULT_MOB_LIFE + (m->level * 0.5 * DEFAULT_MOB_LIFE);
}

int
mobScoreWin (
    Mob *m)
{
  return mobLife (m) / 2;
}

int
mobScoreDead (
    Mob *m)
{
  return mobLife (m);
}

void
fireMob (
    Mob *m,
    int damage)
{
  printf ("Mob Hit (%i)(%i)\n", m->life, m->life + damage);

  m->life += damage;
}


void
tickMob (
    void *v,
    Mob *m)
{
  game_t *g = (game_t *)v;

  if (m->ticker -- == 0 && m->active) {
    Point *p;

    /* Life */
    if (m->life >= mobLife (m)) {
      m->active = 0;

      g->score += mobScoreWin (m);
    }

    /* Mob arrives border */
    if (m->position >= g->routeLength -1) {
      m->active = 0;

      g->score -= mobScoreDead (m);
    }
    else {
      /* Move mob */
      m->position++;

      /* Calculating mob speed */
      p = g->route[m->position];
      m->ticker = m->speed + blocSpeed (g->board[p->y * g->width + p->x]);
    }
  }
}

