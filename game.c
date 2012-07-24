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
#include <time.h>
#include <string.h>
#include "Point.h"
#include "Mob.h"
#include "TowerMob.h"
#include "game.h"

/**
  * routeLength ()
  *
  * @param game_t *	m
  *
  * @return int
  */
int
routeLength (
    game_t *m)
{
  int i, length = 0;

  for (i = 0; i < m->width * m->height; i++) {
    if (isRoute (m->board[i]))
      length++;
  }

  return length;
}


/**
  * is_route_last_point ()
  *
  * @param game_t *	m
  * @param Point *	p
  *
  * @return int
  */
int
is_route_last_point (
    game_t *m,
    Point *p)
{
  return (p->x == m->width - 1) && isRoute (m->board[p->y * m->width + p->x]);
}


/**
  * route_next_point ()
  *
  * @param game_t *	m
  * @param Point *	c
  * @param Point *	p
  *
  * @return Point *
  */
Point *
route_next_point (
    game_t *m,
    Point *c,
    Point *p)
{
  int x, y;

  // NORTH
  x = c->x;
  y = c->y - 1;

  if (y >= 0 && !(p->x == x && p->y == y) && isRoute (m->board[y * m->width +
	x]))
    return newPoint (x, y);


  // EAST 
  x = c->x + 1;
  y = c->y;

  if (x < m->width && !(p->x == x && p->y == y) && isRoute (m->board[y * m->width +
	x]))
    return newPoint (x, y);

  // SOUTH
  x = c->x;
  y = c->y + 1;

  if (y < m->height && !(p->x == x && p->y == y) && isRoute (m->board[y * m->width +
	x]))
    return newPoint (x, y);

  // WEST 
  x = c->x - 1;
  y = c->y;

  if (x >= 0 && !(p->x == x && p->y == y) && isRoute (m->board[y * m->width +
	x]))
    return newPoint (x, y);


  return NULL;
}


/**
  * computeRoute ()
  *
  * @param game_t *	g
  */
void
computeRoute (
    game_t *m)
{
  int i;

  m->routeLength = routeLength (m);
  m->route = malloc (sizeof (Point *) * m->routeLength);

  // First point
  for (i = 0; i < m->height; i++) {
    if (isRoute (m->board[i * m->width]))
      m->route[0] = newPoint (0, i);
  }

  i = 1;
  while ((i < m->routeLength) && !is_route_last_point (m, m->route[i-1])) {
    if (i == 1)
      m->route[i] = route_next_point (m, m->route[0], m->route[0]);
    else
      m->route[i] = route_next_point (m, m->route[i-1], m->route[i-2]);

    i++;
  }
}


/**
  * loadBoard ()
  *
  * @param char *	filename
  */
game_t *
loadBoard (
    char *filename) 
{
  game_t *g = NULL;

  g = (game_t *) malloc (sizeof (game_t));

  FILE *file;

  file = fopen (filename, "r");
  fscanf (file, "%i %i\n", &(g->height), &(g->width));

  g->board = malloc (sizeof (int) * g->width * g->height);

  int i = 0;
  char c;
  while (fscanf (file, "%c", &c) != EOF) {
    if (c != '\n') { 
      switch (c) {
	case '=':
	  g->board[i] = EAU_0;
	  break;

	case 'q':
	  g->board[i] = EAU_0_HORIZONTAL;
	  break;

	case 's':
	  g->board[i] = EAU_0_VERTICAL;
	  break;

	case 'd':
	  g->board[i] = EAU_0_SUP_R;
	  break;

	case 'f':
	  g->board[i] = EAU_0_SUP_L;
	  break;

	case 'g':
	  g->board[i] = EAU_0_INF_R;
	  break;

	case 'b':
	  g->board[i] = EAU_0_INF_L;
	  break;

	case 'w':
	  g->board[i] = EAU_0_TERRE_HORIZONTAL;
	  break;

	case 'x':
	  g->board[i] = EAU_0_TERRE_VERTICAL;
	  break;

	case '#':
	  g->board[i] = ROUTE;
	  break;

	case '+':
	  g->board[i] = ROUTE_INNONDEE;
	  break;

	case 'h':
	  g->board[i] = TERRE_HORIZONTAL;
	  break;

	case 'v':
	  g->board[i] = TERRE_VERTICAL;
	  break;

	case 'j':
	  g->board[i] = TERRE_SUP_R;
	  break;

	case 'k':
	  g->board[i] = TERRE_SUP_L;
	  break;

	case 'l':
	  g->board[i] = TERRE_INF_R;
	  break;

	case 'm':
	  g->board[i] = TERRE_INF_L;
	  break;

	case '.':
	  g->board[i] = HERBE;
	  break;

	case 't':
	  g->board[i] = TREE;
	  break;

	case '$':
	  g->board[i] = FLOWER_0;
	  break;

	default:
	  g->board[i] = EMPTY;
	  break;
      }

      i++;
    }
  }

  fclose (file);

  g->explosions = (int *) malloc (sizeof (int) * g->width * g->height);
  memset (g->explosions, -1, sizeof (int) * g->width * g->height);

  computeRoute (g);

  return g;
}


/**
  * isRoute ()
  *
  * @param int	c
  *
  * @return int
  */
int
isRoute (
    int c)
{
  return (
      c == ROUTE || 
      c == ROUTE_INNONDEE || 
      c == TERRE_HORIZONTAL ||
      c == TERRE_VERTICAL ||
      c == TERRE_SUP_R ||
      c == TERRE_SUP_L ||
      c == TERRE_INF_R ||
      c == TERRE_INF_L ||
      c == EAU_0_TERRE_HORIZONTAL ||
      c == EAU_0_TERRE_VERTICAL
      );
}


/**
  * isWater ()
  *
  * @param int 	c
  *
  * @return int
  */
int
isWater (
    int c)
{
  return (c >= RIVIERE && c <= EAU_7_TERRE_VERTICAL);
}


/**
  * blocSpeed ()
  *
  * @param int	c
  *
  * @return int
  */
int
blocSpeed (
    int c)
{
  return (isWater (c)) ? 40:0;
}


/**
  * startGame ()
  *
  * @param game_t *	g
  */
void
startGame (
    game_t *g)
{
  g->mobs = NULL;
  g->nMobs = 0;

  g->towers = (Tower **) malloc (sizeof (Tower *) * g->width * g->height);
  memset (g->towers, 0, sizeof (Tower *) * g->width * g->height);

  g->looserScreen = 0;

  g->score = 150;
  g->level = 0;

  g->mouse.x = 0;
  g->mouse.y = 0;
}

void
endGame (
    game_t *g)
{
  int i, j;

  for (i = 0; i < g->nMobs; i++) {
    free (g->mobs[i]);
  }
  free (g->mobs);

  for (i = 0; i < g->width; i++) {
    for (j = 0; j < g->height; j++) {
      free (g->towers[j * g->width + i]);
    }
  }
  free (g->towers);

  g->towers = NULL;
}


/**
  * spawnMob ()
  *
  * @param game_t *	g
  */
void
spawnMob (
    game_t *g,
    int tick)
{
  g->mobs = (Mob **) realloc (g->mobs, sizeof (Mob *) * g->nMobs + 1);

  g->mobs[g->nMobs] = newMob (g->level, (MOB_0 + rand () % 5), 5 + rand () % 2);
  g->nMobs++;
}



Point *
towerPoint (
    game_t *g,
    Tower *t)
{
  int i, j;

  for (i = 0; i < g->width; i++) {
    for (j = 0; j < g->height; j++) {
      if (g->towers[j * g->width + i] == t) {
	return newPoint (i, j);
      }
    }
  }

  return NULL;
}

/**
  * update ()
  *
  * @param game_t *	g
  * @param int	tick
  */
void 
update (
    game_t *g, 
    int tick) 
{
  int i, j;

  if (tick != 0 && (tick % 500) == 0) {
    g->level++;
  }

  if (g->score >= 0) {
    /* Mob spawning */

    if (((tick + rand() % 10) % 50) == 0)
      spawnMob (g, tick);

    /* Mob tick */
    for (i = 0; i < g->nMobs; i++) {
      Mob *m = g->mobs[i];

      tickMob (g, m);
    }

    /* Tower tick */
    for (i = 0; i < g->width; i++) {
      for (j = 0; j < g->height; j++) {
	if (g->towers[j * g->width + i] != NULL)
	  towerTick (g, g->towers[j * g->width + i]);
      }
    }
  }
  else {
    g->looserScreen = 1;
  }
}
