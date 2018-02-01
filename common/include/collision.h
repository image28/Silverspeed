int pixelCollide(SDL_Surface *graphic, int comp, int objX,int objW, int objY, int objH, int enemyX, int enemyY, int *side);
int collision(SDL_Surface *graphic, int objX, int objW, int objY, int objH, int enemyX, int enemyY, int enemyW, int enemyH, int *top, int *bottom, int *left, int *right);
int genCollisionCoords(char *infile, int *left, int *right, int *top, int *bottom);
int enemyCollision(SDL_Surface *graphic[10], int *enemyType, int objX, int objW, int objY, int objH, int enemies, int *enemyX, int *enemyY, int *enemyW, int *enemyH, int *collide, int *collisions, int *top, int *bottom, int *left, int *right);
