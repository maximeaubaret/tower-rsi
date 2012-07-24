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
#include "Mob.h"
#include "Point.h"
#include "TowerMob.h"
#include "game.h"
#include "graphics.h"
#include "Fonts.h"

#define SIZE 32

SDL_Surface *screen=NULL;

SDL_Surface *tile[ALL_I];


const char *tilenames[]={
  NULL,
  "data/grass.bmp",
  "data/terre.bmp",
  "data/terre-eau.bmp",
  "data/ground_horizontal.bmp",
  "data/ground_vertical.bmp",
  "data/ground_sup_r.bmp",
  "data/ground_sup_l.bmp",
  "data/ground_inf_r.bmp",
  "data/ground_inf_l.bmp",
  "data/eau.bmp",
  "data/water1.bmp",
  "data/water2.bmp",
  "data/water3.bmp",
  "data/water4.bmp",
  "data/water5.bmp",
  "data/water6.bmp",
  "data/water7.bmp",
  "data/water8.bmp",
  "data/water1_horizontal.bmp",
  "data/water2_horizontal.bmp",
  "data/water3_horizontal.bmp",
  "data/water4_horizontal.bmp",
  "data/water5_horizontal.bmp",
  "data/water6_horizontal.bmp",
  "data/water7_horizontal.bmp",
  "data/water8_horizontal.bmp",
  "data/water1_vertical.bmp",
  "data/water2_vertical.bmp",
  "data/water3_vertical.bmp",
  "data/water4_vertical.bmp",
  "data/water5_vertical.bmp",
  "data/water6_vertical.bmp",
  "data/water7_vertical.bmp",
  "data/water8_vertical.bmp",
  "data/water1_sup_r.bmp",
  "data/water2_sup_r.bmp",
  "data/water3_sup_r.bmp",
  "data/water4_sup_r.bmp",
  "data/water5_sup_r.bmp",
  "data/water6_sup_r.bmp",
  "data/water7_sup_r.bmp",
  "data/water8_sup_r.bmp",
  "data/water1_sup_l.bmp",
  "data/water2_sup_l.bmp",
  "data/water3_sup_l.bmp",
  "data/water4_sup_l.bmp",
  "data/water5_sup_l.bmp",
  "data/water6_sup_l.bmp",
  "data/water7_sup_l.bmp",
  "data/water8_sup_l.bmp",
  "data/water1_inf_r.bmp",
  "data/water2_inf_r.bmp",
  "data/water3_inf_r.bmp",
  "data/water4_inf_r.bmp",
  "data/water5_inf_r.bmp",
  "data/water6_inf_r.bmp",
  "data/water7_inf_r.bmp",
  "data/water8_inf_r.bmp",
  "data/water1_inf_l.bmp",
  "data/water2_inf_l.bmp",
  "data/water3_inf_l.bmp",
  "data/water4_inf_l.bmp",
  "data/water5_inf_l.bmp",
  "data/water6_inf_l.bmp",
  "data/water7_inf_l.bmp",
  "data/water8_inf_l.bmp",
  "data/w1g_horizontal.bmp",
  "data/w2g_horizontal.bmp",
  "data/w3g_horizontal.bmp",
  "data/w4g_horizontal.bmp",
  "data/w5g_horizontal.bmp",
  "data/w6g_horizontal.bmp",
  "data/w7g_horizontal.bmp",
  "data/w8g_horizontal.bmp",
  "data/w1g_vertical.bmp",
  "data/w2g_vertical.bmp",
  "data/w3g_vertical.bmp",
  "data/w4g_vertical.bmp",
  "data/w5g_vertical.bmp",
  "data/w6g_vertical.bmp",
  "data/w7g_vertical.bmp",
  "data/w8g_vertical.bmp",
  "data/monster_1_r.bmp",
  "data/monster_2_r.bmp",
  "data/monster_3_r.bmp",
  "data/monster_4_r.bmp",
  "data/monster_5_r.bmp",
  "data/monster_1w_r.bmp",
  "data/monster_2w_r.bmp",
  "data/monster_3w_r.bmp",
  "data/monster_4w_r.bmp",
  "data/monster_5w_r.bmp",
  "data/tower1_black.bmp",
  "data/tower2_black.bmp",
  "data/tower3_black.bmp",
  "data/tower1_blue.bmp",
  "data/tower2_blue.bmp",
  "data/tower3_blue.bmp",
  "data/tree.bmp",
  "data/flower1.bmp",
  "data/flower2.bmp",
  "data/flower3.bmp",
  "data/flower4.bmp",
  "data/hover.bmp",
  "data/dot.bmp",
  "data/expl_1.bmp",
  "data/expl_2.bmp",
  "data/expl_3.bmp",
  "data/expl_4.bmp",
  "data/expl_5.bmp"
};

/**
  * loadTiles ()
  */
void 
loadTiles () 
{
  int i;

  for (i = 0; i < ALL_I; i++)  {
    tile[i] = SDL_LoadBMP (tilenames[i]);

    if (tile[i] == NULL) {
      fprintf (stderr, "file %s cannot be found\n", tilenames[i]);
    }
  }
}

void
waterAnimation (
    game_t *g,
    int i,
    int j)
{
  int start;
  int end;

  int *tile = &(g->board[j * g->width + i]);

  start = EAU_0;
  end = EAU_7;

  if (*tile >= start && *tile <= end) 
    *tile = start + (*tile - start + 1) % (end - start + 1);


  start = EAU_0_HORIZONTAL;
  end = EAU_7_HORIZONTAL;

  if (*tile >= start && *tile <= end)  {
    *tile = start + (*tile - start + 1) % (end - start + 1);
  }


  start = EAU_0_VERTICAL;
  end = EAU_7_VERTICAL;

  if (*tile >= start && *tile <= end)  {
    *tile = start + (*tile - start + 1) % (end - start + 1);
  }


  start = EAU_0_SUP_R;
  end = EAU_7_SUP_R;

  if (*tile >= start && *tile <= end)  {
    *tile = start + (*tile - start + 1) % (end - start + 1);
  }


  start = EAU_0_SUP_L;
  end = EAU_7_SUP_L;

  if (*tile >= start && *tile <= end)  {
    *tile = start + (*tile - start + 1) % (end - start + 1);
  }


  start = EAU_0_INF_R;
  end = EAU_7_INF_R;

  if (*tile >= start && *tile <= end)  {
    *tile = start + (*tile - start + 1) % (end - start + 1);
  }


  start = EAU_0_INF_L;
  end = EAU_7_INF_L;

  if (*tile >= start && *tile <= end)  {
    *tile = start + (*tile - start + 1) % (end - start + 1);
  }

  start = EAU_0_TERRE_HORIZONTAL;
  end = EAU_7_TERRE_HORIZONTAL;

  if (*tile >= start && *tile <= end)  {
    *tile = start + (*tile - start + 1) % (end - start + 1);
  }

  start = EAU_0_TERRE_VERTICAL;
  end = EAU_7_TERRE_VERTICAL;

  if (*tile >= start && *tile <= end)  {
    *tile = start + (*tile - start + 1) % (end - start + 1);
  }
}

void
flowerAnimation (
    game_t *g,
    int i,
    int j)
{
  int *tile = &(g->board[j * g->width + i]);

  *tile = (*tile) + 1;
  
  if (*tile > FLOWER_3)
    *tile = FLOWER_0;
}

void
explosion (
    game_t *g,
    Point *p)
{
  if (p != NULL)
    g->explosions[p->y * g->width + p->x] = 4;
}

/**
  * drawTile ()
  *
  * @param game_t *	g
  * @param int	x
  * @param int	y
  * @param int	tick
  */
void
drawTile (
    game_t *g,
    int x,
    int y,
    int tick)
{
  SDL_Rect rect;

  int type;
 
  type = g->board[y * g->width + x];

  rect.w = SIZE;
  rect.h = SIZE;
  rect.x = x * SIZE;
  rect.y = y * SIZE;

  if ((tick % 10) == 0) {
    if (isWater (type)) {
      waterAnimation (g, x, y);
    }
  }

  if ((tick % 15) == 0) {
    if (type >= FLOWER_0 && type <= FLOWER_3) {
      flowerAnimation (g, x, y);
    }
  }

  if (type == TREE)
    type = HERBE;

  SDL_SetColorKey (tile[type], SDL_SRCCOLORKEY, SDL_MapRGB (screen->format,0,0,0));
  SDL_BlitSurface (tile[type], NULL, screen, &rect);
}

/**
  * drawMob
  *
  * @param game_t *	g
  * @param Mob *	m
  */
void 
drawMob (
    game_t *g,
    Mob *m,
    int tick)
{
  SDL_Rect rect;

  if (m->active && m->position >= 0) {
    Point *p = g->route[m->position];

    rect.w = SIZE;
    rect.h = SIZE;

    rect.x = p->x * SIZE;
    rect.y = p->y * SIZE - 10;

    /* Draw in-water tile */
    if (isWater (g->board[p->y * g->width + p->x])) {
      SDL_SetColorKey (tile[m->tile + 5], SDL_SRCCOLORKEY , SDL_MapRGB (screen->format,0,0,0));
      SDL_BlitSurface (tile[m->tile + 5], NULL, screen, &rect);
    }

    /* Draw default tile */
    else {
      SDL_SetColorKey (tile[m->tile], SDL_SRCCOLORKEY , SDL_MapRGB (screen->format,0,0,0));
      SDL_BlitSurface (tile[m->tile], NULL, screen, &rect);
    }
  }
}

void
hoverMouse (
    game_t *g,
    int tick)
{
  SDL_Rect rect;

  /* Draw hover */
  int x, y;
  x = (g->mouse.x / SIZE);
  y = (g->mouse.y / SIZE);
  rect.w = SIZE;
  rect.h = SIZE;
  rect.x = x * SIZE;
  rect.y = y * SIZE;

  SDL_SetColorKey(tile[HOVER],SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0,0,0));
  SDL_BlitSurface(tile[HOVER],NULL,screen,&rect);


  /* Draw route reachability */
  int i, j;

  for (i = 0; i < g->width; i++) {
    for (j = 0; j < g->height; j++) {
      int d = (x - i) * (x - i) + (y - j) * (y - j);

      if (d <= DEFAULT_TOWER_DISTANCE) {
	if (isRoute (g->board[j * g->width + i])) {
	  rect.x = i * SIZE;
	  rect.y = j * SIZE;

	  SDL_SetColorKey (tile[DOT],SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0,0,0));
	  SDL_BlitSurface (tile[DOT],NULL,screen,&rect);
	}
      }
    }
  }

  /*
  for (i = -1; i < 2; i++) {
    for (j = -1; j < 2; j++) {
      if (isRoute (g->board[(y + j) * g->width + (i + x)])) {
	rect.x = (x + i) * SIZE;
	rect.y = (y + j) * SIZE;
	SDL_SetColorKey(tile[DOT],SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0,0,0));
	SDL_BlitSurface(tile[DOT],NULL,screen,&rect);
      }
    }
  }
  */


}

void
drawExplosion (
    game_t *g,
    int x,
    int y) 
{
  SDL_Rect rect;

  if (g->explosions[y * g->width + x] >= 0) {
    rect.w = SIZE;
    rect.h = SIZE;

    rect.x = x * SIZE;
    rect.y = y * SIZE - 10;

    SDL_SetColorKey (tile[EXPLOSION_0 + g->explosions[y * g->width + x]], SDL_SRCCOLORKEY , SDL_MapRGB (screen->format,0,0,0));
    SDL_BlitSurface (tile[EXPLOSION_0 + g->explosions[y * g->width + x]], NULL, screen, &rect);

    g->explosions[y * g->width + x]--;
  }
}

/**
  * paint ()
  *
  * @param game_t *	m
  * @param int	tick
  */
void 
paint (
    game_t *m, 
    int tick) 
{
  SDL_Rect rect;

  int i, j;
  
  /* Fill screen with black */
  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));

  /* Drawing tiles */
  for (i = 0; i < m->width; i++) {
    for (j = 0; j < m->height; j++) {
      drawTile (m, i, j, tick);
    }
  }

  /* Drawing Hover */
  hoverMouse (m, tick);

  /* Drawing mobs */
  for (i = 0; i < m->nMobs; i++) {
    drawMob (m, m->mobs[i], tick);
  }

  /* Drawing explosions */
  for (i = 0; i < m->height; i++) {
    for (j = 0; j < m->width; j++) {
      drawExplosion (m, j, i);
    }
  }

  for (i = 0; i < m->height; i++) {
    for (j = 0; j < m->width; j++) {
      int type = m->board[i * m->width + j];

      if (type == TREE) {
	rect.w = 42;
	rect.h = 48;

	rect.x = j * SIZE - 7;
	rect.y = i * SIZE - 25;

	SDL_SetColorKey(tile[TREE],SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0,0,0));
	SDL_BlitSurface(tile[TREE],NULL,screen,&rect);
      }

      /* Towers */
      Tower *t = m->towers[i * m->width + j];
      if (t != NULL) {
	rect.w = SIZE;
	rect.h = SIZE;

	rect.x = j * SIZE;
	rect.y = i * SIZE - 15;

	SDL_SetColorKey(tile[t->tile],SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0,0,0));
	SDL_BlitSurface(tile[t->tile],NULL,screen,&rect);
      }

    }
  }

  char levelString[100];
  sprintf (levelString, "Level: %i", m->level + 1);
  drawText (screen, levelString, 10, 10);


  char scoreString[100];
  sprintf(scoreString, "%i$", m->score);

  drawText (screen, scoreString, 10, screen->h - 18 - 10);


  /* Tower damage */
  char towerMsg[100];
  int towerX = m->mouse.x / SIZE;
  int towerY = m->mouse.y / SIZE;
  Tower *tower = m->towers[towerY * m->width + towerX];

  if (tower != NULL) {
    sprintf (towerMsg, "%i PA (%i) - Upgrade: %i$", towerDamage
	(tower), tower->level + 1, towerScore (tower));

    drawText (screen, towerMsg, m->mouse.x + 20, m->mouse.y + 20);
  }

  if (m->looserScreen) {
    drawText (screen, "You loooooose!", 0.2 * m->width * SIZE / 2, m->height * SIZE / 2); 
    drawText (screen, "Try Again?", 0.2 * m->width * SIZE / 2, m->height * SIZE
	/ 2 + 20); 
  }

  /* Update screen */
  SDL_Flip (screen);
}

/**
  * getEvent ()
  *
  * @param game_t*	m
  *
  * @return int
  */
int 
getEvent (
    game_t *m) 
{
  SDL_Event event;

  while (SDL_PollEvent (&event)) {
    switch (event.type) {
      case SDL_QUIT: 
	return 1;

      case SDL_KEYDOWN: 
	switch (event.key.keysym.sym) {
	  case SDLK_ESCAPE: 
	    return 1;
	  case SDLK_DOLLAR: 
	    m->score += 10000;
	    break;
	  default:;
	}
	break;

      case SDL_MOUSEBUTTONDOWN:
	{
	  Point p;
	  p.x = event.button.x / SIZE;
	  p.y = event.button.y / SIZE;
	  click (m, p, event.button.button);
	}
	break;
      case SDL_MOUSEMOTION: 
	{
	  m->mouse.x = event.motion.x;
	  m->mouse.y = event.motion.y;
	}
	break;
    }
  }

  return 0;
}

/**
  * click ()
  *
  * @param game_t *	g
  * @param Point	p
  */
void 
click (
    game_t *g, 
    Point p,
    int button) 
{
  if (g->looserScreen) {
    endGame (g);
    startGame (g);
  }
  else {
    if (button == SDL_BUTTON_LEFT) {
      if (placeTower (g, p)) {

      }
      else if (evolveTower (g, p)) {

      }
    }
    else if (button == SDL_BUTTON_RIGHT) {
      towerSell (g, p);
    }
  }
}
/**
  * initWIndow ()
  *
  * @param int	w
  * @param int	h
  */
void 
initWindow (
    int w,
    int h) 
{
  if ( SDL_Init (SDL_INIT_VIDEO) == -1) {
    fprintf (stderr, "error %s\n", SDL_GetError());
    exit (1);
  }

  atexit (SDL_Quit);

  fprintf (stderr, "size %d %d\n", w * SIZE, h * SIZE);
  screen = SDL_SetVideoMode (w * SIZE, h * SIZE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

  if (screen == NULL) {
    fprintf (stderr, "error video mode: %s\n", SDL_GetError()) ;
    exit (1);
  }
}
