/**
  * Tower-Defense
  *
  * @date 06/12
  *
  * @author <maxime.aubaret@enseirb-matmeca.fr>
  * @author <steve.libaros@enseirb-matmeca.fr>
  */

enum {
  EMPTY=0,
  HERBE,
  ROUTE,
  ROUTE_INNONDEE,
  TERRE_HORIZONTAL,
  TERRE_VERTICAL,
  TERRE_SUP_R,
  TERRE_SUP_L,
  TERRE_INF_R,
  TERRE_INF_L,
  RIVIERE,
  EAU_0,
  EAU_1,
  EAU_2,
  EAU_3,
  EAU_4,
  EAU_5,
  EAU_6,
  EAU_7,
  EAU_0_HORIZONTAL,
  EAU_1_HORIZONTAL,
  EAU_2_HORIZONTAL,
  EAU_3_HORIZONTAL,
  EAU_4_HORIZONTAL,
  EAU_5_HORIZONTAL,
  EAU_6_HORIZONTAL,
  EAU_7_HORIZONTAL,
  EAU_0_VERTICAL,
  EAU_1_VERTICAL,
  EAU_2_VERTICAL,
  EAU_3_VERTICAL,
  EAU_4_VERTICAL,
  EAU_5_VERTICAL,
  EAU_6_VERTICAL,
  EAU_7_VERTICAL,
  EAU_0_SUP_R,
  EAU_1_SUP_R,
  EAU_2_SUP_R,
  EAU_3_SUP_R,
  EAU_4_SUP_R,
  EAU_5_SUP_R,
  EAU_6_SUP_R,
  EAU_7_SUP_R,
  EAU_0_SUP_L,
  EAU_1_SUP_L,
  EAU_2_SUP_L,
  EAU_3_SUP_L,
  EAU_4_SUP_L,
  EAU_5_SUP_L,
  EAU_6_SUP_L,
  EAU_7_SUP_L,
  EAU_0_INF_R,
  EAU_1_INF_R,
  EAU_2_INF_R,
  EAU_3_INF_R,
  EAU_4_INF_R,
  EAU_5_INF_R,
  EAU_6_INF_R,
  EAU_7_INF_R,
  EAU_0_INF_L,
  EAU_1_INF_L,
  EAU_2_INF_L,
  EAU_3_INF_L,
  EAU_4_INF_L,
  EAU_5_INF_L,
  EAU_6_INF_L,
  EAU_7_INF_L,
  EAU_0_TERRE_HORIZONTAL,
  EAU_1_TERRE_HORIZONTAL,
  EAU_2_TERRE_HORIZONTAL,
  EAU_3_TERRE_HORIZONTAL,
  EAU_4_TERRE_HORIZONTAL,
  EAU_5_TERRE_HORIZONTAL,
  EAU_6_TERRE_HORIZONTAL,
  EAU_7_TERRE_HORIZONTAL,
  EAU_0_TERRE_VERTICAL,
  EAU_1_TERRE_VERTICAL,
  EAU_2_TERRE_VERTICAL,
  EAU_3_TERRE_VERTICAL,
  EAU_4_TERRE_VERTICAL,
  EAU_5_TERRE_VERTICAL,
  EAU_6_TERRE_VERTICAL,
  EAU_7_TERRE_VERTICAL,
  MOB_0,
  MOB_1,
  MOB_2,
  MOB_4,
  MOB_5,
  MOB_0_WATER,
  MOB_1_WATER,
  MOB_2_WATER,
  MOB_4_WATER,
  MOB_5_WATER,
  TOUR_0,
  TOUR_1,
  TOUR_2,
  TOUR_0_1,
  TOUR_1_1,
  TOUR_2_1,
  TREE,
  FLOWER_0,
  FLOWER_1,
  FLOWER_2,
  FLOWER_3,
  HOVER,
  DOT,
  EXPLOSION_0,
  EXPLOSION_1,
  EXPLOSION_2,
  EXPLOSION_3,
  EXPLOSION_4,
  ALL_I
};


typedef struct {
  int width;
  int height;

  int *board;

  Point **route;
  int routeLength;

  Mob ** mobs;
  int nMobs;

  Tower **towers;

  int score;
  int level;

  int looserScreen;

  Point mouse;

  int *explosions;
} game_t;

game_t *loadBoard(char *filename);

void startGame (game_t *g);
void endGame (game_t *g);

void update(game_t *m, int tick);


int isRoute (int c);
int isWater (int c);
int blocSpeed (int c);

Point * towerPoint (game_t *g, Tower *t);
