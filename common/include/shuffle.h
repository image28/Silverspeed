int shuffleCollide(int *count, int *type, int *enemyX, int *enemyY, int *collide, int collisions);
int shuffleObj(int *count, int *type, int *objX, int *objY, int less, int amount);
int dupCollide(int *collide, int *collisions);
int shuffleEnemyScreen(int *count, int *type, int *hits, int *objX, int *objY, int eHold[][16], int eFramePos[][16], int eBulletHold[][16], int less, int amount);
int shuffleEnemyBulletCollide(int *count, int *type, int *dist, int *start,int *objX, int *objY, struct coords *area, int *collide, int collisions);
int shuffleEnemyBullet(int *count, int *type, int *dist, int *start, int *objX, int *objY, int *objW, int *objH, struct coords *area);
int shuffleEnemyHit(int *hits, int *collide, int *collisions);
int shuffleEnemy(int *count, int *type, int *hits, int *enemyX, int *enemyY, int *collide, int eHold[][16], int eFramePos[][16], int eBulletHold[][16], int collisions);
int shuffleDrop(int *count, int *type, int *enemyX, int *enemyY, int *collide, int dHold[][16], int dFramePos[][16], int collisions);
int shuffleDropScreen(int *count, int *type, int *objX, int *objY, int dHold[][16], int dFramePos[][16], int less, int amount);

