int genorateEnemies(int *count, int *seed, int *seedDefault, int difficulty, int *type, int typeTotal, int backTotal, int *hits, int *hitsDefault, int *enemyX, int *enemyY, int *enemyW, int pos, int level);
int genorateDrops(int *drops, int *seed, int *seedDefault, int difficulty, int collisions, int *dropX, int *dropY, int *type ,int *enemyX, int *enemyY, int *collide, int *enemyHits );
int genorateEnemyBullets(int *count, int enemyCount, int *seed, int *seedDefault, int difficulty, int *enemyX, int *enemyY, int enemyW, int enemyH, struct coords *area);
