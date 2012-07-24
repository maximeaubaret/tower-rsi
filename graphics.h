/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

void loadTiles ();
void initWindow (int w,int h);

void paint (game_t *m, int tick);

int getEvent (game_t *m) ;
void click (game_t *g, Point p, int button);

