/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

#include <stdlib.h>
#include "Point.h"

Point *
newPoint (
    int x,
    int y)
{
  Point *p = malloc (sizeof (Point));
  p->x = x;
  p->y = y;
  return p;
}

void
freePoint (
    Point *p)
{
  free (p);
}

