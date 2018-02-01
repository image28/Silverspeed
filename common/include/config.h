struct bossPart
{
	int frames;
	int xPos;
	int yPos;
	int hold;
	int reverse;
	int loop;
	int addr[32];
	int firing;
	int firetex[16];
	int firestart[16];
	int fireinterval[16];
	int firepause[16];
	int firex1[16];
	int firey1[16];
	int firex2[16];
	int firey2[16];
};

struct bossHit
{
	int count;
	int grouped;
	int parts[16];
	int hp[16];	
	int moveStartCount;
	int moveLoopCount;
	int moveStartX[16];
	int moveStartY[16];
	int moveLoopX[16];
	int moveLoopY[16];
};

struct spriteGroup
{
	struct bossPart part[16];
};

int loadGameConfig(char *file, int *levels,int *drops,int *dropSeed, int *parts, int *powerMax, struct spriteGroup *drop, int *playerParts, struct spriteGroup *player);
int loadBossConfig(char *file, int *parts, int *bossX, int *bossY, struct bossPart *pieces, int *desGroups, int *hpNorm, int *hpHard, struct bossHit *hits);
int loadLevelConfig(char *file, int *backgrounds, int *bgLoop, int *enemies, int *enemySeed, int *bulletSeed, int *hitsEasy, int *hitsNorm, int *hitsHard,int *parts, struct spriteGroup *enemy);
