int gameMenu(struct container *screen, GLuint *menuTexture, int *menuW, int *menuH, int pos, int status);
int gameEvent(struct container *screen, int *screenshot, SDL_Event event, int *menu, int *keydown, int *clicked, int *status, int first, int *power, int *newlevel,int *back, struct coords *pBulletArea, int *pBulletStart, int *pBulletDist, int *pBulletType, int *bulletCount, struct spriteGroup *player, int *shipX, int *shipY, int *w, int *h, int *quit);
int gameMenuEvent(SDL_Event event, int *menu, int *status, int *pos,int *clicked, int *keydown, int *quit, int *newgame);
int optionMenu(struct container *screen, GLuint *optionsTexture, int *optionsW, int *optionsH, int optionsPos, int difficulty, int windowed, int soundVol, int musicVol, int status);
int optionMenuEvent(struct container *screen, SDL_Event event, int *windowed, int *menu, int *status, int *optPos, int *clicked, int *keydown, int *difficulty, int *soundVol, int *musicVol);


