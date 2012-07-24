/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

#define DEFAULT_TOWER_SCORE 50 
#define DEFAULT_TOWER_DISTANCE 5 

typedef struct {
  int tile;

  int level;
  int damage;

  int speed;
  int ticker;
} Tower;


Tower * newTower (int level, int tile,  int speed);
int placeTower (void *g, Point p);
int evolveTower (void *g, Point p);
void towerSell (void *g, Point p);

int towerDamage (Tower *t);

void towerTick (void *g, Tower *t);

int towerScore (Tower *t);
