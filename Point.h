/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

typedef struct {
  int x;
  int y;
} Point;

Point * newPoint (int x, int y); 
void freePoint (Point *p);
