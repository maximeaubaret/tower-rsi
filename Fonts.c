/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "Fonts.h"

#define FONT_TILE "data/font.bmp"

static char *charset[] = { 
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?\"'/\\<>()[]{}", 
  "abcdefghijklmnopqrstuvwxyz_$",
  "0123456789+=-x:;"
};

int
charAt (
    char *string,
    char c)
{
  int i = 0;

  while (string[i] != '\0') {
    if (string[i] == c)
      return i;

    i++;
  }

  return -1;
}

void 
drawText (
    SDL_Surface *screen, 
    char *string,
    int x,
    int y) 
{
  int i;
  SDL_Rect rect, clip;

  static SDL_Surface *surface = NULL;

  clip.w = 12;
  clip.h = 18;

  rect.w = 12;
  rect.h = 18;

  if (surface == NULL) {
    surface = SDL_LoadBMP (FONT_TILE);

    if (surface == NULL) {
      printf ("Could not open font\n");
      exit (1);
    }
  }


  for (i = 0; i < strlen (string); i++) {
    int posCharX, posCharY;

    posCharY = 0;
    posCharX = charAt (charset[0], string[i]);

    if (posCharX == -1) {
      posCharY = 1;
      posCharX = charAt (charset[1], string[i]);
    }
    if (posCharX == -1) {
      posCharY = 2;
      posCharX = charAt (charset[2], string[i]);
    }

    if (posCharX >= 0) {
      clip.x = posCharX * 12;
      clip.y = posCharY * 18;

      rect.x = x + i * 12;
      rect.y = y;

      SDL_SetColorKey (surface, SDL_SRCCOLORKEY, SDL_MapRGB (screen->format,0,0,0));
      SDL_BlitSurface (surface, &clip, screen, &rect);
    }
  }
}
