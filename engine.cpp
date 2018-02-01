#include "common/include/defines.h"
#ifdef _WIN32 
	#include <windows.h>
#endif
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include "common/include/gui.h"

#define MAXTEX 128
#define MAXWH 256
#define TURRETMAX MAXTEX
#define WIDTH 1024
#define HEIGHT 768
#define BPP 32
#define EN(x) printf("Entering %s\n",x);
#define EX(x) printf("Exiting %s\n",x);
#define MAXARRAY 256
#define EMAX 128
#define BOSSAT 9
#define PI 3.14159265

const int FRAMES_PER_SECOND = 100;

int main(int argc, char *argv[])
{

// PROGRAM VARABLES : REQUIRED VARABLES
	SDL_Event event; 
	SDL_keysym keysym;
	int quit=0;
	GLubyte *vendor;
	GLubyte *renderer;
	GLubyte *version;
	GLubyte *extensions;
	int modechange=0;

// PROGRAM VARABLES
	struct container screen;
	struct colour colour;
	colour.R=255;
	colour.G=0;
	colour.B=0;
	struct colour fontColour;
	fontColour.R=200;
	fontColour.G=0;
	fontColour.B=0;
	int len=0;
	int key=0;
	int d,e,l,f;
	int mousex,mousey,x,y;
	int screenshot=0;
// Time Varables
	long startTicks=0;
	long startTime=0;
	long startClock=0;
	long deltaClock=0;
	long currentFPS=0;
	long invStart=0;
	long invCurrent=0;
	long trackStart=0;
	long trackCurrent=0;
	long trackUp=0;
// Text Varables
	char fpsText[MAXARRAY];
	char cashText[MAXARRAY];
	char enemyText[MAXARRAY];
	char powerText[MAXARRAY];
	char dropsText[MAXARRAY];
	char livesText[MAXARRAY];
	char bulletText[MAXARRAY];

	int power=0;
	int cash=0;
	int update=1;
	int clicked=0;
	int shipX=50;
	int shipY=0;
	int dropX[EMAX];
	int dropY[EMAX];
	int drops=0;
	int genoratedDrops=0;
	int dropsCollected=0;
	int tempDrops=0;
	int enemyX[EMAX];
	int enemyY[EMAX];
	int enemyType[EMAX];
	int enemyHits[EMAX];
	int bulletType[MAXARRAY];
	int dropType[EMAX];
	int count=0;
	int tempEnemies=0;
	int genoratedEnemies=0;
	int enemiesKilled=0;
	int prevcount=0;
	int shuffle=0;
	int random=0;
	int seed[3];
	int tempSeed[3];
	int dropSeed[3];
	int tempDropSeed[3];
	for(d=0;d<3;d++)
	{
		seed[d]=0;
		tempSeed[d]=0;
		tempDropSeed[d]=0;
		dropSeed[d]=0;
	}
	GLuint texcount=0;
	double angle=0;
	GLfloat texcoord[4];

	int bulletsX[MAXARRAY];
	int bulletsY[MAXARRAY];
	int bulletCount=0;
	int eBulletCount=0;
	int eBulletSeed[3];
	int tempBulletSeed[3];
	int eTypeTotal=0;
	int eHitsEasy[EMAX];
	int eHitsNorm[EMAX];
	int eHitsHard[EMAX];
	int dTypeTotal=0;
	int dParts[16];
	struct spriteGroup dData[16];
	int eParts[16];
	struct spriteGroup eData[16];
	int eTemp=0;
	int eHold[MAXARRAY][16];
	int eFramePos[MAXARRAY][16];
	int dHold[MAXARRAY][16];
	int dFramePos[MAXARRAY][16];
	int eBulletHold[MAXARRAY][16];

	for(d=0;d<MAXARRAY;d++)
	{
		for(e=0;e<16;e++)
		{
			eHold[d][e]=0;
			dHold[d][e]=0;
			eBulletHold[d][e]=0;
			dFramePos[d][e]=0;
			eFramePos[d][e]=0;
		}
	}

	for(d=0;d<16;d++)
	{
		eParts[d]=0;
	}

	for(d=0;d<EMAX;d++)
	{
		eHitsEasy[d]=0;
		eHitsNorm[d]=0;
		eHitsHard[d]=0;
	}

	int bgLoop=0;
	int bgTotal=0;

	int eBulletX[MAXARRAY];
	int eBulletY[MAXARRAY];
	int eBulletCollide[MAXARRAY];
	int eBulletCollisions=0;

	int bossX=1024+340;
	int bossY=0;
	int bossType=0;
	int bossHits=80;

	int bullet_w[1];
	int bullet_h[1];
	int backX[MAXTEX];
	backX[0]=0;
	int curBack=0;
// path Varables
	struct coords eBulletArea[MAXARRAY];
	int eBulletDist[MAXARRAY];
	int eBulletType[MAXARRAY];
	int temp=0;
// Collision Varables
	int playLeft[MAXWH];
	int playRight[MAXWH];
	int playTop[MAXWH];
	int playBottom[MAXWH];
	int bulletLeft[EMAX][MAXWH];
	int bulletRight[EMAX][MAXWH];
	int bulletTop[EMAX][MAXWH];
	int bulletBottom[EMAX][MAXWH];
	int eBulletLeft[EMAX][MAXWH];
	int eBulletRight[EMAX][MAXWH];
	int eBulletTop[EMAX][MAXWH];
	int eBulletBottom[EMAX][MAXWH];
	int collide[MAXARRAY];
	int collisions=0;
	int dropCollide[MAXARRAY];
	int dropCollisions=0;
	int bulletCollide[MAXARRAY];
	int bulletCollisions=0;
	long delay=0;
	int odd=0;
	int first=1;
	int result=0;
	int lives=3;
// Menu Varables
	int status=0;
	int menu=1;
	int pos=0;
	int keydown=0;
	int newgame=0;
	int showMouse=0;
	int difficulty=1;
	int newDifficulty=1;
	int optPos=0;
	int soundVol=100;
	int musicVol=100;
	int newlevel=0;
	long levelStart=0;
	long levelCurrent=0;
	int level=0;
	int levelsTotal=0;
	int bc=12;
	int prevBack=0;
	int bossfire=0;
	struct goals complete[9];

// Boss Varables
	int parts=0;
	struct bossPart piece[16];
	int holdCount[MAXTEX];
	int pieceCount[MAXTEX];
	int fireCount[MAXTEX][MAXTEX];
	int eBulletStart[MAXTEX];
	int desGroups=0;
	int hpNorm=0;
	int hpHard=0;
	int bossDestX=0;
	int bossDestY=0;
	struct bossHit bossHp[MAXTEX];
	int destruct=0;
	int bossStart=0;
	int bossStatUp=-35;
	int bossPos=0;
	int bossDist=0;
	int bossMoveLoop=0;
	struct coords bossArea;
	int bossStartX=0;
	int bossStartY=0;
	int bossPause=0;


// Player
	struct spriteGroup pData;
	int pHold[16];
	int pFramePos[16];
	int pParts=0;
	int powerMax=0;
	struct coords pBulletArea[MAXARRAY];
	int pBulletStart[MAXARRAY];
	int pBulletDist[MAXARRAY];
	int pBulletType[MAXARRAY];

// TEXTURE VARABLES
	struct textures menuList[MAXTEX];
	GLuint menuCount=0;
	GLuint menuTextures[MAXTEX];
	int menuW[MAXTEX];
	int menuH[MAXTEX];
	GLuint scoreFontCount;
	GLuint scoreFontTexture[128];
	int scoreFontW[128];
	int scoreFontH[128];
	GLuint fontCount;
	GLuint fontTexture[128];
	int fontW[128];
	int fontH[128];
	char tempText[2];
	struct textures l1BackList[MAXTEX];
	GLuint l1BackCount=0;
	GLuint l1BackTextures[MAXTEX];
	int l1BackW[MAXTEX];
	int l1BackH[MAXTEX];
	struct textures l1InfoList[MAXTEX];
	GLuint l1InfoCount=0;
	GLuint l1InfoTextures[MAXTEX];
	int l1InfoW[MAXTEX];
	int l1InfoH[MAXTEX];
	struct textures optList[MAXTEX];
	GLuint optCount=0;
	GLuint optionsTexture[MAXTEX];
	int optionsW[MAXTEX];
	int optionsH[MAXTEX];
	struct textures dropsList[MAXTEX];
	GLuint dropCount=0;
	GLuint dropTextures[MAXTEX];
	int dropW[MAXTEX];
	int dropH[MAXTEX];
	struct textures playerList[MAXTEX];
	GLuint playerCount=0;
	GLuint playerTextures[MAXTEX];
	int playerW[MAXTEX];
	int playerH[MAXTEX];
	struct textures musicList[MAXTEX];
	GLuint musicCount=0;
	int currentTrack=0;
	int musicSeed=0;
	int notPlayed[MAXTEX];
	int notPlayedTotal=0;
	int completePos=0;
	int completeCounter=0;
	int completeWait=0;

	for(d=0;d<MAXTEX;d++)
	{
		playerW[d]=0;
		playerH[d]=0;
		notPlayed[d]=1;
	}
	struct textures enemyList[MAXTEX];
	GLuint enemyCount=0;
	GLuint enemyTextures[MAXTEX];
	int enemyW[MAXTEX];
	int enemyH[MAXTEX];
	struct textures weaponList[MAXTEX];
	GLuint weaponCount=0;
	GLuint weaponTextures[MAXTEX];
	int weaponW[MAXTEX];
	int weaponH[MAXTEX];
	struct textures bossList[MAXTEX];
	GLuint bossCount=0;
	GLuint bossTextures[MAXTEX];
	int bossW[MAXTEX];
	int bossH[MAXTEX];

	for(d=0;d<MAXTEX;d++)
	{
		bossW[d]=0;
		bossH[d]=0;
	}
	struct textures completeList[MAXTEX];
	GLuint completeCount=0;
	GLuint completeTextures[MAXTEX];
	int completeW[MAXTEX];
	int completeH[MAXTEX];
	struct textures eBulletList[MAXTEX];
	GLuint eBulletTypeTotal=0;
	GLuint eBulletTextures[MAXTEX];
	int eBulletW[MAXTEX];
	int eBulletH[MAXTEX];

	char loading[128];
	char levelBackFile[128];
	char levelEnemiesFile[128];
	char levelBossFile[128];
	char levelWeaponsFile[128];
	char levelConfig[128];
	char levelBossConfig[128];
	strcpy(loading,"LOADING ");

	for(d=0;d<MAXTEX;d++)
	{
		eBulletW[d]=0;
		eBulletH[d]=0;
	}

	for(d=0;d<16;d++)
	{
		pHold[d]=0;
		pFramePos[d]=0;
	}

	for(d=0;d<MAXTEX;d++)
	{
		bossHp[d].count=0;
		bossHp[d].grouped=0;
		bossHp[d].moveStartCount=0;
		bossHp[d].moveLoopCount=0;
		for(e=0;e<16;e++)
		{
			bossHp[d].parts[e]=0;	
			bossHp[d].hp[e]=0;
			bossHp[d].moveStartX[e]=0;
			bossHp[d].moveStartY[e]=0;
			bossHp[d].moveLoopX[e]=0;
			bossHp[d].moveLoopY[e]=0;
		}

	}

	for(d=0;d<9;d++)
	{
		complete[d].drops=0;
		complete[d].enemies=0;
		complete[d].lives=0;
		complete[d].perfect=0;
	}

	for(d=0;d<EMAX;d++)
	{
		enemyX[d]=0;
		enemyY[d]=0;
		enemyHits[d]=0;
		enemyType[d]=0;
		dropX[d]=0;
		dropY[d]=0;
		dropType[d]=0;
	}

	for(d=0;d<MAXARRAY;d++)
	{
		collide[d]=0;
		bulletType[d]=0;
		
		bulletsX[d]=0;
		bulletsY[d]=0;
		eBulletCollide[d]=0;
		eBulletX[d]=0;
		eBulletY[d]=0;
		eBulletDist[d]=0;
		pBulletStart[d]=0;
		pBulletType[d]=0;
		pBulletDist[d]=0;
	}

	// Set screen resolution
	screen.area.x=0;
	screen.area.y=0;
	screen.area.w=WIDTH;
	screen.area.h=HEIGHT;
	int windowed=1;
	
	// Load Game Config
	loadGameConfig("config/game.config", &levelsTotal, &dTypeTotal, dropSeed, dParts, &powerMax, dData, &pParts, &pData );

	// Run OGL/SDL Startup code
	startup(&screen,vendor,renderer,version,extensions);

	// Load Menu Textures
	loadList("graphics/menu.list", menuList, &menuCount);
	SDL_GL_LoadTexture(menuList,menuTextures,&menuCount, texcoord,menuW,menuH);

	// Draw Title While loading
	SDL_GL_Enter2DMode();

	// Initialize the TTF library 
	if ( TTF_Init() < 0 ) {
		printf("Couldn't initialize TTF: %s\n",SDL_GetError());
		fprintf(stderr, "Couldn't initialize TTF: %s\n",SDL_GetError());
		SDL_Quit();
		return(2);
	}

	TTF_Font *font;
	TTF_Font *scoreFont;

	font = TTF_OpenFont("graphics/font/Elements.ttf",14);
	if ( font == NULL ) {
		printf("Failed to load font file\n");
		SDL_Quit();
		return(2);
	}else{
		TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	}

	scoreFont = TTF_OpenFont("graphics/font/Elements.ttf",24);
	if ( scoreFont == NULL ) {
		printf("Failed to load font file\n");
		SDL_Quit();
		return(2);
	}else{
		TTF_SetFontStyle(scoreFont, TTF_STYLE_NORMAL);
	}

	// Genorate font textures
	genTextTexture(fontTexture, tempText,&fontCount, font, fontColour, fontW, fontH);
	genTextTexture(scoreFontTexture, tempText, &scoreFontCount, scoreFont, fontColour, scoreFontW, scoreFontH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	loadList("graphics/level1-info.list", l1InfoList, &l1InfoCount);
	SDL_GL_LoadTexture(l1InfoList,l1InfoTextures,&l1InfoCount, texcoord,l1InfoW,l1InfoH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	loadList("graphics/options.list", optList, &optCount);
	SDL_GL_LoadTexture(optList,optionsTexture,&optCount, texcoord,optionsW,optionsH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	loadList("graphics/drops.list", dropsList, &dropCount);
	SDL_GL_LoadTexture(dropsList,dropTextures,&dropCount, texcoord,dropW,dropH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	loadList("graphics/player.list", playerList, &playerCount);
	SDL_GL_LoadTexture(playerList,playerTextures,&playerCount, texcoord,playerW,playerH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	loadList("graphics/bullet.list", weaponList, &weaponCount);
	SDL_GL_LoadTexture(weaponList,weaponTextures,&weaponCount, texcoord,weaponW,weaponH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	loadList("graphics/score.list", completeList, &completeCount);
	SDL_GL_LoadTexture(completeList,completeTextures,&completeCount, texcoord,completeW,completeH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	// Load textures and genorate collision coords
	loadList("graphics/level1.list", l1BackList, &l1BackCount);
	SDL_GL_LoadTexture(l1BackList,l1BackTextures,&l1BackCount, texcoord,l1BackW,l1BackH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	loadList("graphics/level1-enemies.list", enemyList, &enemyCount);
	SDL_GL_LoadTexture(enemyList,enemyTextures,&enemyCount, texcoord,enemyW,enemyH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	loadList("graphics/level1-boss.list", bossList, &bossCount);
	SDL_GL_LoadTexture(bossList,bossTextures,&bossCount, texcoord,bossW,bossH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();

	loadList("graphics/level1-weapons.list", eBulletList, &eBulletTypeTotal);
	SDL_GL_LoadTexture(eBulletList,eBulletTextures,&eBulletTypeTotal, texcoord,eBulletW,eBulletH);

	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();


	genCollisionCoords("graphics/ships/player/player body.png",playLeft,playRight,playTop,playBottom);
	
	// Generate Collision Coords for Player Bullets
	for(d=0;d<weaponCount;d++)
	{
		genCollisionCoords(weaponList[d].name,bulletLeft[d],bulletRight[d],bulletTop[d],bulletBottom[d]);
	}

	// Generate Collision Coords for Enemy Bullets
	for(d=0;d<eBulletTypeTotal;d++)
	{
		genCollisionCoords(eBulletList[d].name,eBulletLeft[d],eBulletRight[d],eBulletTop[d],eBulletBottom[d]);
	}
	


	SDL_Surface *enemy_surface[MAXTEX];
	SDL_Surface *boss_surface[MAXTEX];
	SDL_Surface *player_surface;
	SDL_Surface *drop_surface[MAXTEX];


	loadLevelConfig("config/level1.config", &bgTotal, &bgLoop, &eTypeTotal, seed, eBulletSeed, eHitsEasy, eHitsNorm, eHitsHard, eParts, eData);

	// Get Max Boss Hp
	int bossMaxHits=0;

	int dColW[EMAX];
	int dColH[EMAX];

	int dropCount2=0;
	for(d=0;d<dTypeTotal;d++)
	{

		for(l=0;l<=dParts[d];l++)
		{
			if ( dData[d].part[l].frames == 0 )
			{
				drop_surface[d]=loadSurface(dropsList[dData[d].part[l].addr[0]].name);
				dColW[d]=drop_surface[d]->w;
				dColH[d]=drop_surface[d]->h;
				dropCount2++;
			}
		}
		
	}

	int eColW[EMAX];
	int eColH[EMAX];

	int enemyCount2=0;
	for(d=0;d<eTypeTotal;d++)
	{

		for(l=0;l<=eParts[d];l++)
		{
			if ( eData[d].part[l].frames == 0 )
			{
				enemy_surface[d]=loadSurface(enemyList[eData[d].part[l].addr[0]].name);
				eColW[d]=enemy_surface[d]->w;
				eColH[d]=enemy_surface[d]->h;
				enemyCount2++;
			}
		}
		
	}


	for(d=0;d<bossCount;d++)
	{
		boss_surface[d]=loadSurface(bossList[d].name);
	}
	int bossCountOld=bossCount;
	player_surface=loadSurface("graphics/ships/player/player body.png");

	sprintf(levelBossConfig,"config/level%d-boss.config",level+1);
	loadBossConfig(levelBossConfig,&parts,&bossStartX,&bossStartY,piece, &desGroups, &hpNorm, &hpHard, bossHp);



	// Draw Loading Progress
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
	strcat(loading,"#");
	putText(&screen, loading,fontTexture,10,744,fontW,fontH);
	SDL_GL_SwapBuffers();


	// Get The Starting Time
	startTime = SDL_GetTicks();
	startClock = SDL_GetTicks();
	

	//power=3;
	shipY=(screen.area.h/2)-(playerH[0]/2);

	Mix_Init(MIX_INIT_OGG);

	if(Mix_OpenAudio(22050, AUDIO_S16SYS , 2, 2048)) {
	  printf("Unable to open audio!\n");
	  exit(1);
	}

	Mix_Music *music;

	loadList("music/track.list", musicList, &musicCount);
	notPlayedTotal=musicCount;

	int channels=16;
	int randExp=0;

	// allocate 16 mixing channels
	Mix_AllocateChannels(channels);

	// Load all sound effects
/*	struct textures sfxList[MAXTEX];
	unsigned int sfxCount=0;

	loadList("sfx/sfx.list", sfxList, &sfxCount);
	Mix_Chunk *sfx[MAXTEX];
								

	for(d=0;d<sfxCount;d++)
	{
		sfx[d]=Mix_LoadWAV(sfxList[d].name);

		if( ! sfx[d] )
		{
			printf("Sound File %s Failed to Load\n",sfxList[d].name);
			printf("Mix_LoadWAV: %s\n", Mix_GetError());
			exit(-1);
		}
	}*/

	

	// Main Loop
	while ( ! quit )
	{
		// Get the current clock time
		startTicks = SDL_GetTicks();

		if ( menu == 0 )
		{
			if ( showMouse == 1 )
			{
				SDL_ShowCursor(SDL_DISABLE);
				showMouse=0;
			}
		}else{
			if ( showMouse == 0 )
			{
				SDL_ShowCursor(SDL_ENABLE);
				showMouse=1;
			}
		}

		if ( newgame )
		{
			// Load level config
			
			prevBack=bgLoop;
			

			if ( level != 0 )
			{
				level=0;

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glLoadIdentity();
				draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
				strcpy(loading,"LOADING ");
				putText(&screen, loading,fontTexture,10,744,fontW,fontH);
				SDL_GL_SwapBuffers();

				glDeleteTextures(eBulletTypeTotal, eBulletTextures);
				glDeleteTextures(bossCount,bossTextures);
				glDeleteTextures(enemyCount,enemyTextures);
				glDeleteTextures(l1BackCount,l1BackTextures);

				sprintf(levelBackFile,"graphics/level%d.list",level+1);
				sprintf(levelEnemiesFile,"graphics/level%d-enemies.list",level+1);
				sprintf(levelBossFile,"graphics/level%d-boss.list",level+1);
				sprintf(levelWeaponsFile,"graphics/level%d-weapons.list",level+1);
				sprintf(levelConfig,"config/level%d.config",level+1);
				sprintf(levelBossConfig,"config/level%d-boss.config",level+1);
				loadList(levelBackFile, l1BackList, &l1BackCount);
				loadList(levelEnemiesFile, enemyList, &enemyCount);
				loadList(levelBossFile, bossList, &bossCount);
				loadList(levelWeaponsFile, eBulletList, &eBulletTypeTotal);

				loadLevelConfig(levelConfig, &bgTotal, &bgLoop, &eTypeTotal, seed, eBulletSeed, eHitsEasy, eHitsNorm, eHitsHard, eParts, eData);
				loadBossConfig(levelBossConfig,&parts,&bossStartX,&bossStartY,piece, &desGroups, &hpNorm, &hpHard, bossHp);



				SDL_GL_LoadTexture(l1BackList,l1BackTextures,&l1BackCount, texcoord,l1BackW,l1BackH);
				// Draw Loading Progress
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glLoadIdentity();
				draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
				strcat(loading,"#");
				putText(&screen, loading,fontTexture,10,744,fontW,fontH);
				SDL_GL_SwapBuffers();

				SDL_GL_LoadTexture(enemyList,enemyTextures,&enemyCount, texcoord,enemyW,enemyH);
				// Draw Loading Progress
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glLoadIdentity();
				draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
				strcat(loading,"#");
				putText(&screen, loading,fontTexture,10,744,fontW,fontH);
				SDL_GL_SwapBuffers();

				SDL_GL_LoadTexture(bossList,bossTextures,&bossCount, texcoord,bossW,bossH);
				// Draw Loading Progress
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glLoadIdentity();
				draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
				strcat(loading,"#");
				putText(&screen, loading,fontTexture,10,744,fontW,fontH);
				SDL_GL_SwapBuffers();

				SDL_GL_LoadTexture(eBulletList,eBulletTextures,&eBulletTypeTotal, texcoord,eBulletW,eBulletH);
				// Draw Loading Progress
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glLoadIdentity();
				draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
				strcat(loading,"#");
				putText(&screen, loading,fontTexture,10,744,fontW,fontH);
				SDL_GL_SwapBuffers();

				// Generate Collision Coords for Enemy Bullets
				for(d=0;d<eBulletTypeTotal;d++)
				{
					genCollisionCoords(eBulletList[d].name,eBulletLeft[d],eBulletRight[d],eBulletTop[d],eBulletBottom[d]);
				}

				for(d=enemyCount2-1;d>-1;d--)
					SDL_FreeSurface(enemy_surface[d]);

				for(d=bossCountOld-1;d>-1;d--)
					SDL_FreeSurface(boss_surface[d]);

				enemyCount2=0;
				for(d=0;d<eTypeTotal;d++)
				{

					for(l=0;l<=eParts[d];l++)
					{
						if ( eData[d].part[l].frames == 0 )
						{
							enemy_surface[d]=loadSurface(enemyList[eData[d].part[l].addr[0]].name);
							eColW[d]=enemy_surface[d]->w;
							eColH[d]=enemy_surface[d]->h;
							enemyCount2++;
						}
					}
		
				}


				for(d=0;d<bossCount;d++)
				{
					boss_surface[d]=loadSurface(bossList[d].name);
				}
				bossCountOld=bossCount;

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glLoadIdentity();
				draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
				strcat(loading,"#");
				putText(&screen, loading,fontTexture,10,744,fontW,fontH);
				SDL_GL_SwapBuffers();
			}else{
				loadBossConfig(levelBossConfig,&parts,&bossStartX,&bossStartY,piece, &desGroups, &hpNorm, &hpHard, bossHp);
			}

			// Get Max Boss Hp
			bossMaxHits=0;
			for(d=0;d<bossHp[0].count;d++)
			{
				bossMaxHits=bossMaxHits+bossHp[destruct].hp[d];
			}

			for(d=0;d<parts;d++)
			{
				if ( piece[d].firing > 0 )
				{
					for(e=0;e<piece[d].firing;e++)
					{
						fireCount[d][e]=piece[d].firestart[e];
					}
				}
			}

			
			tempDropSeed[0]=dropSeed[0];
			tempDropSeed[1]=dropSeed[1];
			tempDropSeed[2]=dropSeed[2];
			tempSeed[0]=seed[0];
			tempSeed[1]=seed[1];
			tempSeed[2]=seed[2];
			tempBulletSeed[0]=eBulletSeed[0];
			tempBulletSeed[1]=eBulletSeed[1];
			tempBulletSeed[2]=eBulletSeed[2];

			
			power=0;
			cash=0;
			clicked=0;
			shipX=50;
			shipY=(screen.area.h/2)-(playerH[0]/2);
			SDL_WarpMouse(shipX+playerW[0]/2,shipY+playerH[0]/2);
			drops=0;
			count=0;
			genoratedEnemies=0;
			genoratedDrops=0;
			enemiesKilled=0;
			dropsCollected=0;
			prevcount=0;
			shuffle=0;
			random=0;
			bulletCount=0;
			eBulletCount=0;
			eBulletCollisions=0;
			backX[0]=0;
			curBack=0;
			bc=0;
			temp=0;
			bulletCollisions=0;
			odd=0;
			first=1;
			result=0;
			lives=9;
			collisions=0;
			dropCollisions=0;
			newgame=0;
			difficulty=newDifficulty;

			// BOSS VARABLES
			bossX=bossStartX;
			bossY=bossStartY;
			bossType=0;
			bossPos=0;
			bossMoveLoop=0;
			bossStatUp=-35;
			destruct=0;
			bossDist=0;

			invStart=SDL_GetTicks();
			completeWait=0;

			// Music 
			srand(time(0));
			currentTrack=0;

			if ( notPlayedTotal == 0 )
			{
				for(d=0;d<musicCount;d++)
				{
					notPlayed[d]=1;
				}	
				notPlayedTotal=musicCount;
			}

			musicSeed=rand()%notPlayedTotal;

			for(d=0;d<musicCount;d++)
			{
				if ( notPlayed[d] )
				{
					if ( currentTrack == musicSeed )
					{
						notPlayed[d]=0;
						currentTrack=d;
						notPlayedTotal--;
						d=musicCount;
					}else{
						currentTrack++;
					}
				}
			}

			if ( music != NULL )
			{
				Mix_HaltMusic();
				Mix_FreeMusic(music);
			}

			music=Mix_LoadMUS(musicList[currentTrack].name);
			trackStart=SDL_GetTicks();
			trackUp=768;
			

			for (d=0;d<EMAX;d++)
			{
				dropX[d]=0;
				dropY[d]=0;
				enemyX[d]=0;
				enemyY[d]=0;
				enemyHits[d]=0;
				enemyType[d]=0;
				bulletType[d]=0;
				dropType[d]=0;
			}

			for (d=0;d<MAXARRAY;d++)
			{
				bulletCollide[d]=0;
				collide[d]=0;
				dropCollide[d]=0;
				eBulletDist[d]=0;
				eBulletX[d]=0;
				eBulletY[d]=0;
				bulletsX[d]=0;
				bulletsY[d]=0;
				eBulletCollide[d]=0;
				bulletType[d]=0;
			}

		}

	#ifdef _RELEASE
		if ( newlevel )
		{

			//draw(&screen,level,completeTextures,(screen.area.w/2)-(completeW[level]/2),(screen.area.h/2)-(completeH[level]/2),completeW[level],completeH[level]);
			
			if ( completeWait )
			{
			
			levelCurrent=SDL_GetTicks();
			
			if ( level < levelsTotal-1 )
			{

				if ( levelCurrent/1000 - levelStart/1000 >= 3 )
				{

					if ( genoratedEnemies == enemiesKilled )
					{
						complete[level].enemies=1;
						enemiesKilled=0;
					}

					if ( genoratedDrops == dropsCollected )
					{	
						complete[level].drops=1;
						dropsCollected=0;
					}

					completePos=0;
					completeCounter=0;
					completeWait=0;

					level++;
				
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcpy(loading,"LOADING ");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					// (un)Load new level textures
					glDeleteTextures(eBulletTypeTotal, eBulletTextures);
					glDeleteTextures(bossCount,bossTextures);
					glDeleteTextures(enemyCount,enemyTextures);
					glDeleteTextures(l1BackCount,l1BackTextures);

					sprintf(levelBackFile,"graphics/level%d.list",level+1);
					sprintf(levelEnemiesFile,"graphics/level%d-enemies.list",level+1);
					sprintf(levelBossFile,"graphics/level%d-boss.list",level+1);
					sprintf(levelWeaponsFile,"graphics/level%d-weapons.list",level+1);
					sprintf(levelConfig,"config/level%d.config",level+1);
					sprintf(levelBossConfig,"config/level%d-boss.config",level+1);
			
					loadList(levelBackFile, l1BackList, &l1BackCount);
					loadList(levelEnemiesFile, enemyList, &enemyCount);
					loadList(levelBossFile, bossList, &bossCount);
					loadList(levelWeaponsFile, eBulletList, &eBulletTypeTotal);
					loadLevelConfig(levelConfig, &bgTotal, &bgLoop, &eTypeTotal, seed, eBulletSeed, eHitsEasy, eHitsNorm, eHitsHard, eParts, eData);
					loadBossConfig(levelBossConfig,&parts,&bossStartX,&bossStartY,piece, &desGroups, &hpNorm, &hpHard, bossHp);

					SDL_GL_LoadTexture(l1BackList,l1BackTextures,&l1BackCount, texcoord,l1BackW,l1BackH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(enemyList,enemyTextures,&enemyCount, texcoord,enemyW,enemyH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(bossList,bossTextures,&bossCount, texcoord,bossW,bossH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(eBulletList,eBulletTextures,&eBulletTypeTotal, texcoord,eBulletW,eBulletH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					// Generate Collision Coords for Enemy Bullets
					for(d=0;d<eBulletTypeTotal;d++)
					{
						genCollisionCoords(eBulletList[d].name,eBulletLeft[d],eBulletRight[d],eBulletTop[d],eBulletBottom[d]);
					}

					for(d=enemyCount2-1;d>-1;d--)
						SDL_FreeSurface(enemy_surface[d]);

					for(d=bossCountOld-1;d>-1;d--)
						SDL_FreeSurface(boss_surface[d]);

					enemyCount2=0;
					for(d=0;d<eTypeTotal;d++)
					{

						for(l=0;l<=eParts[d];l++)
						{
							if ( eData[d].part[l].frames == 0 )
							{
								enemy_surface[d]=loadSurface(enemyList[eData[d].part[l].addr[0]].name);
								eColW[d]=enemy_surface[d]->w;
								eColH[d]=enemy_surface[d]->h;
								enemyCount2++;
							}
						}
		
					}


					for(d=0;d<bossCount;d++)
					{
						boss_surface[d]=loadSurface(bossList[d].name);
					}
					bossCountOld=bossCount;

					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					
					clicked=0;
					drops=0;
					count=0;
					genoratedEnemies=0;
					genoratedDrops=0;
					enemiesKilled=0;
					dropsCollected=0;
					prevcount=0;
					shuffle=0;
					random=0;
					bulletCount=0;
					eBulletCount=0;
					eBulletCollisions=0;
					backX[0]=0;
					curBack=0;
					bc=0;
					temp=0;
					bulletCollisions=0;
					odd=0;
					result=0;
					collisions=0;
					dropCollisions=0;
					newlevel=0;
		
					// BOSS VARABLES
					bossPos=0;
					bossStatUp=-35;
					destruct=0;
					bossMoveLoop=0;
					bossDist=0;
					bossX=bossStartX;
					bossY=bossStartY;
					bossType=0;
					
					invStart=SDL_GetTicks();
					trackStart=SDL_GetTicks();

					// Get Max Boss Hp
					bossMaxHits=0;
					for(d=0;d<bossHp[0].count;d++)
					{
						bossMaxHits=bossMaxHits+bossHp[destruct].hp[d];
					}

					for(d=0;d<parts;d++)
					{
						if ( piece[d].firing > 0 )
						{
							for(e=0;e<piece[d].firing;e++)
							{
								fireCount[d][e]=piece[d].firestart[e];
							}
						}
					}

					// Music 
					srand(time(0));
					currentTrack=0;

					if ( notPlayedTotal == 0 )
					{
						for(d=0;d<musicCount;d++)
						{
							notPlayed[d]=1;
						}	
						notPlayedTotal=musicCount;
					}

					musicSeed=rand()%notPlayedTotal;

					for(d=0;d<musicCount;d++)
					{
						if ( notPlayed[d] )
						{
							if ( currentTrack == musicSeed )
							{
								notPlayed[d]=0;
								currentTrack=d;
								notPlayedTotal--;
								d=musicCount;
							}else{
								currentTrack++;
							}
						}
					}

					if ( music != NULL )
					{
						Mix_HaltMusic();
						Mix_FreeMusic(music);
					}

					music=Mix_LoadMUS(musicList[currentTrack].name);
					trackUp=768;

					for (d=0;d<EMAX;d++)
					{
						dropX[d]=0;
						dropY[d]=0;
						enemyX[d]=0;
						enemyY[d]=0;
						enemyHits[d]=0;
						enemyType[d]=0;
						bulletType[d]=0;
						dropType[d]=0;
					}

					for (d=0;d<MAXARRAY;d++)
					{
						bulletCollide[d]=0;
						collide[d]=0;
						dropCollide[d]=0;
						eBulletDist[d]=0;
						eBulletX[d]=0;
						eBulletY[d]=0;
						bulletsX[d]=0;
						bulletsY[d]=0;
						eBulletCollide[d]=0;
						bulletType[d]=0;
					}
				}
			}}

		}
	#endif

		// Event Handling
		
		while ( SDL_PollEvent( &event ) )
		{
			if ( menu == 0 )
			{
				if ( ! Mix_PlayingMusic() )
				{
					Mix_PlayMusic(music, -1);
				}

				if ( Mix_PausedMusic() )
				{
					Mix_ResumeMusic();
				}

				gameEvent(&screen,&screenshot,event, &menu, &keydown, &clicked, &status, first, &power, &newlevel,&bc, pBulletArea, pBulletStart, pBulletDist, pBulletType, &bulletCount, &pData, &shipX, &shipY, playerW, playerH, &quit);			
			}else if ( menu == 1 ){
				gameMenuEvent(event, &menu,&status,&pos,&clicked,&keydown,&quit,&newgame);

			}else{
				optionMenuEvent(&screen, event, &modechange, &menu, &status, &optPos, &clicked, &keydown, &newDifficulty, &soundVol, &musicVol);
				if ( modechange )
				{
					modechange=0;

				//#ifdef _WIN32
					reload(&screen,&windowed,1);

					// unload and reload all textures
					glDeleteTextures(eBulletTypeTotal, eBulletTextures);
					glDeleteTextures(bossCount,bossTextures);
					glDeleteTextures(enemyCount,enemyTextures);
					glDeleteTextures(l1BackCount,l1BackTextures);
					glDeleteTextures(completeCount,completeTextures);
					glDeleteTextures(weaponCount,weaponTextures);
					glDeleteTextures(playerCount,playerTextures);
					glDeleteTextures(dropCount,dropTextures);
					glDeleteTextures(optCount,optionsTexture);
					glDeleteTextures(l1InfoCount,l1InfoTextures);
					glDeleteTextures(scoreFontCount, scoreFontTexture);
					glDeleteTextures(fontCount,fontTexture);
					glDeleteTextures(menuCount,menuTextures);

					for(d=0;d<MAXTEX;d++)
					{
						eBulletTextures[d]=0;
						bossTextures[d]=0;
						enemyTextures[d]=0;
						l1BackTextures[d]=0;
						completeTextures[d]=0;
						weaponTextures[d]=0;
						playerTextures[d]=0;
						dropTextures[d]=0;
						optionsTexture[d]=0;
						l1InfoTextures[d]=0;
						fontTexture[d]=0;
						menuTextures[d]=0;
					}

					// Reload all textures
					SDL_GL_LoadTexture(menuList,menuTextures,&menuCount, texcoord,menuW,menuH);
					SDL_GL_Enter2DMode();

					// Genorate font textures
					genTextTexture(fontTexture, tempText,&fontCount, font, fontColour, fontW, fontH);
					genTextTexture(scoreFontTexture, tempText, &scoreFontCount, scoreFont, fontColour, scoreFontW, scoreFontH);

					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcpy(loading,"LOADING ");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(l1InfoList,l1InfoTextures,&l1InfoCount, texcoord,l1InfoW,l1InfoH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(optList,optionsTexture,&optCount, texcoord,optionsW,optionsH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(dropsList,dropTextures,&dropCount, texcoord,dropW,dropH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(playerList,playerTextures,&playerCount, texcoord,playerW,playerH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(weaponList,weaponTextures,&weaponCount, texcoord,weaponW,weaponH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(completeList,completeTextures,&completeCount, texcoord,completeW,completeH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(l1BackList,l1BackTextures,&l1BackCount, texcoord,l1BackW,l1BackH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(enemyList,enemyTextures,&enemyCount, texcoord,enemyW,enemyH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(bossList,bossTextures,&bossCount, texcoord,bossW,bossH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();

					SDL_GL_LoadTexture(eBulletList,eBulletTextures,&eBulletTypeTotal, texcoord,eBulletW,eBulletH);
					// Draw Loading Progress
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glLoadIdentity();
					draw(&screen,8,menuTextures,0,0,menuW[8],menuH[8]);
					strcat(loading,"#");
					putText(&screen, loading,fontTexture,10,744,fontW,fontH);
					SDL_GL_SwapBuffers();



				/*#else
					reload(&screen,&windowed,0);
					modechange=0;
				#endif*/
					
				}
			}

		}

		
		
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		if ( menu > 0 )
		{
			if ( status )
			{
				if ( Mix_PlayingMusic() )
				{
					Mix_PauseMusic();
				}

				// In Game Menu
				// draw the background
				if ( backX[0] == 0 )
				{
					draw(&screen,curBack,l1BackTextures,backX[0],0,1024,768);
					backX[1]=1023;
					curBack=1;
					prevBack=0;
					bc=1;
				}else{
					draw(&screen,prevBack,l1BackTextures,backX[prevBack],0,1024,768);
					draw(&screen,curBack,l1BackTextures,backX[bc],0,1024,768);
				}

				// Draw Drops and Powerups
				for(d=0;d<drops;d++)
				{
					for(l=0;l<=dParts[dropType[d]];l++)
					{
						if ( dData[dropType[d]].part[l].frames > 0 )
						{
							draw(&screen,dData[dropType[d]].part[l].addr[dFramePos[d][l]],dropTextures,dropX[d],dropY[d],dropW[dData[dropType[d]].part[l].addr[dFramePos[d][l]]],dropH[dData[dropType[d]].part[l].addr[dFramePos[d][l]]]);
						}else{
							draw(&screen,dData[dropType[d]].part[l].addr[0],dropTextures,dropX[d],dropY[d],dropW[dData[dropType[d]].part[l].addr[0]],dropH[dData[dropType[d]].part[l].addr[0]]);
						}
					}
				}

				// Draw Bullets
				if ( bulletCount > 0 )
				{
					for(d=0;d<bulletCount;d++)
					{
						draw(&screen,pBulletType[d],weaponTextures,bulletsX[d],bulletsY[d],weaponW[pBulletType[d]],weaponH[pBulletType[d]]);
					}
				}

				

				// Draw Enemies
				for(d=0;d<count;d++)
				{
					for(l=0;l<=eParts[enemyType[d]];l++)
					{
						if ( eData[enemyType[d]].part[l].frames > 0 )
						{
							draw(&screen,eData[enemyType[d]].part[l].addr[eFramePos[d][l]],enemyTextures,enemyX[d],enemyY[d],enemyW[eData[enemyType[d]].part[l].addr[eFramePos[d][l]]],enemyH[eData[enemyType[d]].part[l].addr[eFramePos[d][l]]]);
						}else{
							draw(&screen,eData[enemyType[d]].part[l].addr[0],enemyTextures,enemyX[d],enemyY[d],enemyW[eData[enemyType[d]].part[l].addr[0]],enemyH[eData[enemyType[d]].part[l].addr[0]]);
						}
					}
				}

				// Draw Ship
				for(l=0;l<=pParts;l++)
				{
					if ( pData.part[l].frames > 0 )
					{
						draw(&screen,pData.part[l].addr[pFramePos[l]],playerTextures,shipX,shipY,playerW[0],playerH[0]);
					}else{
						draw(&screen,pData.part[l].addr[0],playerTextures,shipX,shipY,playerW[0],playerH[0]);
					}
				}

				// Draw Boss
				if ( bc > BOSSAT )
				{
					if ( bossHits > 0 )
					{
						for(d=0;d<parts;d++)
						{
							if ( piece[d].frames == 0 )
							{
								draw(&screen,piece[d].addr[0], bossTextures, bossX+piece[d].xPos,bossY+piece[d].yPos,bossW[piece[d].addr[0]],bossH[piece[d].addr[0]]);
							}else{
								draw(&screen,piece[d].addr[pieceCount[d]], bossTextures, bossX+piece[d].xPos,bossY+piece[d].yPos,bossW[piece[d].addr[pieceCount[d]]],bossH[piece[d].addr[pieceCount[d]]]);
							}
						}
					

						
					}

					for(e=0;e<eBulletCount;e++)
					{
	
						drawpart(&screen,eBulletType[e], eBulletTextures, eBulletStart[e],eBulletX[e], eBulletY[e], eBulletW[eBulletType[e]],eBulletH[eBulletType[e]]);
					}
						
				}else{
					for(d=0;d<eBulletCount;d++)
					{
						drawpart(&screen,eBulletType[d], eBulletTextures, eBulletStart[d],eBulletX[d], eBulletY[d], eBulletW[eBulletType[d]],eBulletH[eBulletType[d]]);
					}
				}

				// Draw In Game Menu


				if ( menu == 1 )
				{
					gameMenu(&screen, menuTextures, menuW, menuH , pos, status);
				}else{
					optionMenu(&screen, optionsTexture, optionsW, optionsH, optPos, newDifficulty,windowed, soundVol, musicVol,status);
				}
			}else{
				
				// Title Menu
				if ( menu == 1 )
				{
					gameMenu(&screen, menuTextures, menuW, menuH , pos, status);
				}else{
					optionMenu(&screen, optionsTexture, optionsW, optionsH, optPos, newDifficulty,windowed, soundVol, musicVol,status);
				}
			
			}
	
		}else{

		if ( ! newgame )
		{

			if ( backX[0] == 0 )
			{
				draw(&screen,curBack,l1BackTextures,backX[0],0,1024,768);
				backX[0]--;
				backX[1]=1023;
				curBack=1;
				prevBack=0;
				bc=1;
			}else{

				
				if ( backX[prevBack] > -1024 )
				{
					draw(&screen,prevBack,l1BackTextures,backX[prevBack],0,1024,768);
					backX[prevBack]--;

				}

				if ( backX[bc] > -1024 )
				{
					draw(&screen,curBack,l1BackTextures,backX[bc],0,1024,768);
					backX[bc]--;
				}

				if ( backX[bc] == -1 )
				{
					bc++;
					prevBack=bc-1;
					if ( bc == bgTotal )
					{
						bc=bgLoop;
					}
					
					curBack=bc;
					backX[bc]=1023;
				}

			}

			// Reset Varables
			collisions=0;
			dropCollisions=0;
			bulletCollisions=0;
			eBulletCollisions=0;



			// genorate random enemy ships
			if ( bc < BOSSAT )
			{
				tempEnemies=count;
				if ( difficulty == 0 )
				{
					genorateEnemies(&count,tempSeed,seed,difficulty,enemyType,eTypeTotal,bgLoop,enemyHits,eHitsEasy,enemyX,enemyY,eColW,bc,level);
				}
				else if ( difficulty == 1 )
				{
					genorateEnemies(&count,tempSeed,seed,difficulty,enemyType,eTypeTotal,bgLoop,enemyHits,eHitsNorm,enemyX,enemyY,eColW,bc,level);
				}
				else 
				{
					genorateEnemies(&count,tempSeed,seed,difficulty,enemyType,eTypeTotal,bgLoop,enemyHits,eHitsHard,enemyX,enemyY,eColW,bc,level);
				}

				for(e=tempEnemies;e<count;e++)
				{
					for(l=0;l<=eParts[enemyType[e]];l++)
					{
						
						for(d=0;d<eData[enemyType[e]].part[l].firing;d++)
						{
							eBulletHold[e][d]=eData[enemyType[e]].part[l].firestart[d];
						}

					}
				}
				genoratedEnemies=genoratedEnemies+(count-tempEnemies);
			}
			
			// Test for player enemy collision
			if ( count > 0 )
			{
		
				result=enemyCollision(enemy_surface,enemyType,shipX, playerW[0], shipY, playerH[0], count, enemyX, enemyY, eColW, eColH, collide, &collisions,playTop,playBottom,playLeft,playRight);

				if ( ! first )
				{
					if ( result )
					{
						first=1;
						//shipX=50;
						//shipY=(screen.area.h/2)-(playerH[0]/2);
						//SDL_WarpMouse(shipX+playerW[0]/2,shipY+playerH[0]/2);

						if ( lives > 0 )
						{
							lives--;
						}else{
							status=0;
							menu=1;
							newgame=1;
						}

						invStart= SDL_GetTicks();
					}
				}

			}

			// If at boss
			if ( bc > BOSSAT )
			{

				bossHits=0;

				if ( bossHp[destruct].grouped == 0 )
				{
					for(d=0;d<bossHp[destruct].count;d++)
					{
						bossHits=bossHits+bossHp[destruct].hp[d];
					}

					if ( bossHits == 0 )
					{
						if ( destruct < desGroups )
						{
							destruct++;
							bossHits=0;
							for(d=0;d<bossHp[destruct].count;d++)
							{
								bossHits=bossHits+bossHp[destruct].hp[d];
							}
						}
					}
				}else{
					bossHits=bossHp[destruct].hp[0];

					if ( bossHits == 0 )
					{
						if ( destruct < desGroups )
						{
							destruct++;
							bossHits=bossHp[destruct].hp[0];
						}
					}
				}

				// draw boss hitpoint bar
				bossStart=(float)l1InfoW[5]/(float)bossMaxHits*bossHits;
				if ( bossStatUp < 0 )
				{
					bossStatUp++;
				}
				draw(&screen,4,l1InfoTextures,1000-l1InfoW[4],bossStatUp,l1InfoW[4],l1InfoH[4]);
				drawpart(&screen,5,l1InfoTextures,bossStart,(1000-(l1InfoW[4]/2))-l1InfoW[5]/2,bossStatUp+((l1InfoH[4]/2)-l1InfoH[5]/2),l1InfoW[5],l1InfoH[5]);

				if ( bulletCount > 0 )
				{		
					for(d=0;d<bulletCount;d++)
					{
					
						// Move and draw current bullet
						bulletsX[d]=pathPos(pBulletArea[d],pBulletDist[d],0);
						bulletsY[d]=pathPos(pBulletArea[d],pBulletDist[d],1);	
						pBulletDist[d]=pBulletDist[d]+10;
						//if ( pBulletStart[d] <= weaponW[pBulletType[d]] )
						//	pBulletStart[d]++;

						draw(&screen,pBulletType[d],weaponTextures,bulletsX[d],bulletsY[d],weaponW[pBulletType[d]],weaponH[pBulletType[d]]);
					}
	
					shuffleEnemyBullet(&bulletCount,pBulletType,pBulletDist,pBulletStart,bulletsX,bulletsY,weaponW,weaponH,pBulletArea);
				}

				
				if ( ( ( bossHits == 0 ) && ( destruct == desGroups ) ) || ( newlevel ) )
				{
					#ifdef _RELEASE
						if ( ! newlevel )
						{
								newlevel=1;
						}

						if ( completePos < 3 )
						{

							levelComplete(&screen, &completePos, &completeCounter, cash, lives, enemiesKilled, 9, genoratedEnemies, completeTextures, completeW, completeH, scoreFontTexture,scoreFontW, scoreFontH);

						}else{	
							levelComplete(&screen, &completePos, &completeCounter, cash, lives, enemiesKilled, 9, genoratedEnemies, completeTextures, completeW, completeH, scoreFontTexture,scoreFontW, scoreFontH);	
							if ( completeWait == 0 )
							{
								levelStart=SDL_GetTicks();
								completeWait=1;
							}
						}
					#else
						draw(&screen,level,completeTextures,(screen.area.w/2)-(completeW[level]/2),(screen.area.h/2)-(completeH[level]/2),completeW[level],completeH[level]);

					#endif

					for(d=0;d<parts;d++)
					{
						for(e=0;e<eBulletCount;e++)
						{
	
		
							eBulletX[e]=pathPos(eBulletArea[e],eBulletDist[e],0);
							eBulletY[e]=pathPos(eBulletArea[e],eBulletDist[e],1);	
							eBulletDist[e]=eBulletDist[e]+1;

							

							if ( eBulletStart[e] < eBulletW[eBulletType[e]] )
							{
								eBulletStart[e]++;
							}
				

							drawpart(&screen,eBulletType[e], eBulletTextures, eBulletStart[e],eBulletX[e], eBulletY[e], eBulletW[eBulletType[e]],eBulletH[eBulletType[e]]);
						}
					}

				}else{

					if ( bulletCount > 0 )
					{
					
						for(d=0;d<bulletCount;d++)
						{
						
							for(e=0;e<bossHp[destruct].count;e++)
							{
								if ( piece[bossHp[destruct].parts[e]].frames == 0 )
								{
									
									// collision detection for each bullet 
									if ( collision(boss_surface[piece[bossHp[destruct].parts[e]].addr[0]],bulletsX[d],weaponW[pBulletType[d]],bulletsY[d],weaponH[pBulletType[d]],piece[bossHp[destruct].parts[e]].xPos+bossX,piece[bossHp[destruct].parts[e]].yPos+bossY,bossW[piece[bossHp[destruct].parts[e]].addr[0]],bossH[piece[bossHp[destruct].parts[e]].addr[0]],bulletTop[pBulletType[d]],bulletBottom[pBulletType[d]],bulletLeft[pBulletType[d]],bulletRight[pBulletType[d]]) )
									{

										bulletCollide[bulletCollisions]=d;
										bulletCollisions++;
										// minus hit from destruct group or part of group
										if ( bossHp[destruct].grouped == 0 )
										{
											if ( bossHp[destruct].hp[e] > 0 )
												bossHp[destruct].hp[e]--;
										}else{
											if ( bossHp[destruct].hp[0] > 0 )
												bossHp[destruct].hp[0]--;
										}
										
									}
							
									if ( bulletCollisions > 0 )
										shuffleEnemyBulletCollide(&bulletCount,pBulletType, pBulletDist,pBulletStart, bulletsX,bulletsY,pBulletArea,bulletCollide,bulletCollisions);

									bulletCollisions=0;
								}	
							}
				
						}
		
					}

					for(e=0;e<bossHp[destruct].count;e++)
					{
						if ( piece[bossHp[destruct].parts[e]].frames == 0 )
						{
							
					

							if ( collision(boss_surface[piece[bossHp[destruct].parts[e]].addr[0]],shipX-playerW[0]/2,playerW[0],shipY-playerH[0]/2,playerH[0],piece[bossHp[destruct].parts[e]].xPos+bossX,piece[bossHp[destruct].parts[e]].yPos+bossY,bossW[piece[bossHp[destruct].parts[e]].addr[0]],bossH[piece[bossHp[destruct].parts[e]].addr[0]],playTop,playBottom,playLeft,playRight) )
							{	
								if ( ! first )
								{
									first=1;
	
									if ( lives > 0 )

									{
										lives--;

									}else{
										status=0;
										menu=1;
										newgame=0;
									}


									invStart=SDL_GetTicks();
								}
							}

					
						}	
					}
				
					if ( ! bossPause )
					{
						if ( ! bossMoveLoop )
						{
							if ( bossPos < bossHp[destruct].moveStartCount )
							{
								if ( bossPos == 0 )
								{
									bossArea.x=bossStartX;
									bossArea.y=bossStartY;
									bossArea.w=bossHp[destruct].moveStartX[bossPos];
									bossArea.h=bossHp[destruct].moveStartY[bossPos];
								}else{
									bossArea.x=bossHp[destruct].moveStartX[bossPos-1];
									bossArea.y=bossHp[destruct].moveStartY[bossPos-1];
									bossArea.w=bossHp[destruct].moveStartX[bossPos];
									bossArea.h=bossHp[destruct].moveStartY[bossPos];
								}

								if ( ( bossX/4 == bossHp[destruct].moveStartX[bossPos]/4 ) && ( bossY/4 == bossHp[destruct].moveStartY[bossPos]/4 ) )
								{
									bossPos++;
									bossDist=0;
								}else{
									bossX=pathPos(bossArea,bossDist,0);
									bossY=pathPos(bossArea,bossDist,1);
									bossDist=bossDist+4;
								}
							}else{
								bossMoveLoop=1;
								bossPos=0;
								bossStartX=bossX;
								bossStartY=bossY;
							}

						}else{
							if ( bossHp[destruct].moveLoopCount > 0 )
							{

								if ( bossPos == 0 )
								{
									bossArea.x=bossStartX;
									bossArea.y=bossStartY;
									bossArea.w=bossHp[destruct].moveLoopX[bossPos];
									bossArea.h=bossHp[destruct].moveLoopY[bossPos];
								}else{
									bossArea.x=bossHp[destruct].moveLoopX[bossPos-1];
									bossArea.y=bossHp[destruct].moveLoopY[bossPos-1];
									bossArea.w=bossHp[destruct].moveLoopX[bossPos];
									bossArea.h=bossHp[destruct].moveLoopY[bossPos];
								}

								if ( ( bossX/2 == bossHp[destruct].moveLoopX[bossPos]/2 ) && ( bossY/2 == bossHp[destruct].moveLoopY[bossPos]/2 ) )
								{
									if ( bossPos < bossHp[destruct].moveLoopCount )
									{
										bossPos++;
										bossDist=0;
									}

									if ( bossPos == bossHp[destruct].moveLoopCount )
									{
										bossStartX=bossHp[destruct].moveLoopX[bossPos-1];
										bossStartY=bossHp[destruct].moveLoopY[bossPos-1];
										bossPos=0;
									}
								}else{
									bossX=pathPos(bossArea,bossDist,0);
									bossY=pathPos(bossArea,bossDist,1);
									bossDist=bossDist+2;
								}
							}
						}
					}

					bossPause=0;

					for(d=0;d<parts;d++)
					{
						if ( piece[d].firing > 0 )
						{
							for(e=0;e<piece[d].firing;e++)
							{	
								if ( fireCount[d][e] > 0 )
								{
									fireCount[d][e]--;
								}else{
									fireCount[d][e]=piece[d].fireinterval[e];
									eBulletArea[eBulletCount].x=piece[d].firex2[e]+bossX;
									eBulletArea[eBulletCount].y=piece[d].firey2[e]+bossY;
									eBulletArea[eBulletCount].w=piece[d].firex1[e]+bossX;
									eBulletArea[eBulletCount].h=piece[d].firey1[e]+bossY;
								
									eBulletStart[eBulletCount]=0;//piece[d].firex2[e];
									eBulletType[eBulletCount]=piece[d].firetex[e];
									eBulletDist[eBulletCount]=0;
									multiplyPath(&screen,&eBulletArea[eBulletCount]);
									eBulletCount++;

								} 
							}
						}
		
						// collision detection for boss
						for(e=0;e<eBulletCount;e++)
						{
	
		
							eBulletX[e]=pathPos(eBulletArea[e],eBulletDist[e],0);
							eBulletY[e]=pathPos(eBulletArea[e],eBulletDist[e],1);	
							eBulletDist[e]=eBulletDist[e]+1;

							

							if ( eBulletStart[e] < eBulletW[eBulletType[e]] )
							{
								eBulletStart[e]++;
								for(f=0;f<piece[d].firing;f++)
								{
									if ( piece[d].firepause[f] == 1 )
									{
										bossPause=1;
									}
								}
							}
				

							drawpart(&screen,eBulletType[e], eBulletTextures, eBulletStart[e],eBulletX[e], eBulletY[e], eBulletW[eBulletType[e]],eBulletH[eBulletType[e]]);
						}

						if ( piece[d].frames == 0 )
						{
							draw(&screen,piece[d].addr[0], bossTextures, bossX+piece[d].xPos,bossY+piece[d].yPos,bossW[piece[d].addr[0]],bossH[piece[d].addr[0]]);

							
						}else{

							if ( holdCount[d] < piece[d].hold )
							{
								holdCount[d]++;
							}else{
								holdCount[d]=0;
								pieceCount[d]++;
								if ( pieceCount[d] > piece[d].frames )
								{
									pieceCount[d]=0;
								}
							}
							draw(&screen,piece[d].addr[pieceCount[d]], bossTextures, bossX+piece[d].xPos,bossY+piece[d].yPos,bossW[piece[d].addr[pieceCount[d]]],bossH[piece[d].addr[pieceCount[d]]]);
						}

					}

					if ( eBulletCount > 0 )
						shuffleEnemyBullet(&eBulletCount,eBulletType,eBulletDist,eBulletStart,eBulletX,eBulletY,eBulletW,eBulletH,eBulletArea);


					if ( eBulletCount > 0 )
					{
						for(d=0;d<eBulletCount;d++)
						{
							// collision detection for each bullet 
							if ( collision(player_surface,eBulletX[d],eBulletW[eBulletType[d]],eBulletY[d],eBulletH[eBulletType[d]],shipX,shipY,playerW[0],playerH[0],eBulletTop[eBulletType[d]],eBulletBottom[eBulletType[d]],eBulletLeft[eBulletType[d]],eBulletRight[eBulletType[d]]) )
							{

								eBulletCollide[eBulletCollisions]=d;
								eBulletCollisions++;

								if ( ! first )
								{
									first=1;
			
									if ( lives > 0 )

									{
										lives--;

									}else{
										status=0;
										menu=1;
										newgame=0;
									}


									invStart=SDL_GetTicks();
								}
					
							}

						}

						// shuffle enemy bullet collisions
						if ( eBulletCollisions > 0 )
							shuffleEnemyBulletCollide(&eBulletCount,eBulletType, eBulletDist,eBulletStart, eBulletX,eBulletY,eBulletArea, eBulletCollide,eBulletCollisions); 

						eBulletCollisions=0;
					}
				}

				
			}else{

			// MUSIC TRACK INFO DRAWING //
				if ( (trackCurrent-trackStart)/1000 < 10 )
				{
					if ( trackUp > 768-l1InfoH[6] )
					{
						trackUp--;
					}
					draw(&screen,6,l1InfoTextures,20,trackUp,l1InfoW[6],l1InfoH[6]);
					draw(&screen,7+currentTrack,l1InfoTextures,20,trackUp,l1InfoW[7+currentTrack],l1InfoH[7+currentTrack]);
					trackCurrent=SDL_GetTicks();
				}else{
					if ( trackUp < 768 )
					{
						draw(&screen,6,l1InfoTextures,20,trackUp,l1InfoW[6],l1InfoH[6]);
						draw(&screen,7+currentTrack,l1InfoTextures,20,trackUp,l1InfoW[7+currentTrack],l1InfoH[7+currentTrack]);
						trackUp++;
					}
				}
					

			// BULLET ENEMY COLLISION AND DRAWING //
	
				if ( bulletCount > 0 )
				{			
					for(d=0;d<bulletCount;d++)
					{
					
						// Move and draw current bullet
						bulletsX[d]=pathPos(pBulletArea[d],pBulletDist[d],0);
						bulletsY[d]=pathPos(pBulletArea[d],pBulletDist[d],1);	
						pBulletDist[d]=pBulletDist[d]+10;
						if ( pBulletStart[d] <= weaponW[pBulletType[d]] )
							pBulletStart[d]++;

						draw(&screen,pBulletType[d],weaponTextures,bulletsX[d],bulletsY[d],weaponW[pBulletType[d]],weaponH[pBulletType[d]]);
					}
	
					shuffleEnemyBullet(&bulletCount,pBulletType,pBulletDist,pBulletStart,bulletsX,bulletsY,weaponW,weaponH,pBulletArea);

					if ( count > 0 )
					{
						for(d=0;d<bulletCount;d++)
						{

			

							// collision detection for each bullet 
							if ( enemyCollision(enemy_surface,enemyType,bulletsX[d],weaponW[0],bulletsY[d],weaponH[0],count,enemyX,enemyY,eColW,eColH,collide,&collisions,bulletTop[pBulletType[d]],bulletBottom[pBulletType[d]],bulletLeft[pBulletType[d]],bulletRight[pBulletType[d]]) )
							{

								bulletCollide[bulletCollisions]=d;
								bulletCollisions++;
								// shuffleBullets 
						
							}

						}

						if ( bulletCollisions > 0 )
							shuffleEnemyBulletCollide(&bulletCount,pBulletType, pBulletDist,pBulletStart, bulletsX,bulletsY,pBulletArea,bulletCollide,bulletCollisions); 
					}

					
				}

			// DRAW ENEMY BULLETS //
			
				temp=eBulletCount;
				//genorateEnemyBullets(&eBulletCount, count, &eBulletSeed[difficulty],difficulty, enemyX, enemyY, enemyW[0], enemyH[0], eBulletArea); // remove this line
				// decrement eBulletHold
				for(d=0;d<count;d++)
				{
					for(l=0;l<=eParts[enemyType[d]];l++)
					{
						
						for(f=0;f<eData[enemyType[d]].part[l].firing;f++)
						{
							
							eBulletHold[d][f]--;
							if ( eBulletHold[d][f] == 0 )
							{
								
								eBulletHold[d][f]=eData[enemyType[d]].part[l].fireinterval[f];
								if ( eData[enemyType[d]].part[l].firex1[f] == 1025 )
								{
									eBulletArea[eBulletCount].w=shipX;
								}else{
									eBulletArea[eBulletCount].w=enemyX[d]+eData[enemyType[d]].part[l].firex1[f];
								}

								if ( eData[enemyType[d]].part[l].firey1[f] == 1025 )
								{
									eBulletArea[eBulletCount].h=shipY;
								}else{
									eBulletArea[eBulletCount].h=enemyY[d]+eData[enemyType[d]].part[l].firey1[f];
								}
								eBulletArea[eBulletCount].x=enemyX[d]+eData[enemyType[d]].part[l].firex2[f];
								eBulletArea[eBulletCount].y=enemyY[d]+eData[enemyType[d]].part[l].firey2[f];
								eBulletType[eBulletCount]=eData[enemyType[d]].part[l].firetex[f];
								eBulletStart[eBulletCount]=0;
								eBulletDist[eBulletCount]=0;
								multiplyPath(&screen,&eBulletArea[eBulletCount]);
								eBulletCount++;
							}
						}
					}
				}

				for(d=0;d<eBulletCount;d++)
				{
					eBulletX[d]=pathPos(eBulletArea[d],eBulletDist[d],0);
					eBulletY[d]=pathPos(eBulletArea[d],eBulletDist[d],1);	
					eBulletDist[d]=eBulletDist[d]+6;
					eBulletStart[d]++;

					drawpart(&screen,eBulletType[d], eBulletTextures, eBulletStart[d],eBulletX[d], eBulletY[d], eBulletW[eBulletType[d]],eBulletH[eBulletType[d]]);
				}

				if ( eBulletCount > 0 )
					shuffleEnemyBullet(&eBulletCount,eBulletType,eBulletDist,eBulletStart, eBulletX,eBulletY,eBulletW,eBulletH,eBulletArea);

			}
			

		// PICKUPS DRAWING AND COLLISION //
	
			if ( drops > 0 )
			{
				shuffleDropScreen(&drops, dropType, dropX, dropY, dHold, dFramePos,1, -80);
		
		// need to modify collision algorithm to support multiple object types for different drop types
				enemyCollision(drop_surface,dropType,shipX, playerW[0], shipY, playerH[0], drops, dropX, dropY, dColW, dColH, dropCollide, &dropCollisions,playTop,playBottom,playLeft,playRight);


				for(d=0;d<dropCollisions;d++)
				{
					if ( dropType[dropCollide[d]] == 0 )
					{
						if ( power < powerMax-1 )
						{
							power++;
						}
					}else{
						cash=cash+100;
					}
				}

				// Detect if drop picked up
				if ( dropCollisions > 0 )
				{
					tempDrops=drops;
					shuffleDrop(&drops, dropType, dropX, dropY, dropCollide, dHold, dFramePos, dropCollisions);
					dropsCollected=dropsCollected+(drops-tempDrops);
				}

				for(d=0;d<drops;d++)
				{
					dropX[d]--;
					// 2-6 powerup shield cash-small cash-med cash-large
					for(l=0;l<=dParts[dropType[d]];l++)
					{
						if ( dData[dropType[d]].part[l].frames > 0 )
						{
							if ( dHold[d][l] < dData[dropType[d]].part[l].hold )
							{
								dHold[d][l]++;
							}else{
								dHold[d][l]=0;
								dFramePos[d][l]++;
								if ( dFramePos[d][l] > dData[dropType[d]].part[l].frames )
								{
									dFramePos[d][l]=0;
								}
							}

							draw(&screen,dData[dropType[d]].part[l].addr[dFramePos[d][l]],dropTextures,dropX[d],dropY[d],dropW[dData[dropType[d]].part[l].addr[dFramePos[d][l]]],dropH[dData[dropType[d]].part[l].addr[dFramePos[d][l]]]);
						}else{
							draw(&screen,dData[dropType[d]].part[l].addr[0],dropTextures,dropX[d],dropY[d],dropW[dData[dropType[d]].part[l].addr[0]],dropH[dData[dropType[d]].part[l].addr[0]]);
						}
					}
				}
		
			}


		// ENEMY BULLET/PLAYER COLLISION //
			
			if ( eBulletCount > 0 )
			{
				for(d=0;d<eBulletCount;d++)
				{
					// collision detection for each bullet 
					if ( collision(player_surface,eBulletX[d],eBulletW[eBulletType[d]],eBulletY[d],eBulletH[eBulletType[d]],shipX,shipY,playerW[0],playerH[0],eBulletTop[eBulletType[d]],eBulletBottom[eBulletType[d]],eBulletLeft[eBulletType[d]],eBulletRight[eBulletType[d]]) )
					{

						eBulletCollide[eBulletCollisions]=d;
						eBulletCollisions++;

						if ( ! first )
						{
							first=1;
					
							if ( lives > 0 )

							{
								lives--;
							}else{
								status=0;
								menu=1;
								newgame=0;
							}

							invStart=SDL_GetTicks();
						}
				
					}
				}

				// shuffle enemy bullet collisions
				if ( eBulletCollisions > 0 )
					shuffleEnemyBulletCollide(&eBulletCount,eBulletType, eBulletDist,eBulletStart, eBulletX,eBulletY,eBulletArea, eBulletCollide,eBulletCollisions); 

				eBulletCollisions=0;
			}
			


		// ENEMEY/PLAYER BULLET COLLISION AND HITS //

			if ( count > 0 )
			{
				
				if ( collisions > 0 )
				{
					shuffleEnemyHit(enemyHits,collide,&collisions);
					dupCollide(collide,&collisions);	
				}

				if ( collisions > 0 )
				{
					tempDrops=drops;
					genorateDrops(&drops, &tempDropSeed[difficulty],dropSeed,difficulty, collisions, dropX, dropY, dropType,enemyX, enemyY, collide, enemyHits );
					genoratedDrops=genoratedDrops+(drops-tempDrops);
				}

				prevcount=count;
				shuffleEnemyScreen(&count,enemyType,enemyHits,enemyX,enemyY,eHold, eFramePos,eBulletHold,1,-120);

				if ( ! first )
				{
					if ( count < prevcount )
					{

						if ( lives > 0 )
						{
							lives--;
						}else{
							status=0;
							menu=1;
							newgame=1;
						}

						invStart=SDL_GetTicks();
					}
				}


				if ( collisions > 0 )
				{
					
					prevcount=count;					
					shuffleEnemy(&count,enemyType,enemyHits, enemyX, enemyY,collide,eHold,eFramePos,eBulletHold,collisions);

					if ( prevcount > count )
					{
						
						/*srand(time(0));
						randExp=rand()%2;
						playSFX(sfx[randExp],&channels);*/
						enemiesKilled=enemiesKilled+(prevcount-count);
					}
				}

			// ENEMY DRAWING //

				for(d=0;d<count;d++)
				{
					enemyX[d]=enemyX[d]-4;
					// for parts in enemy type at address enemyType
					
					for(l=0;l<=eParts[enemyType[d]];l++)
					{
						if ( eData[enemyType[d]].part[l].frames > 0 )
						{
							if ( eHold[d][l] < eData[enemyType[d]].part[l].hold )
							{
								eHold[d][l]++;
							}else{
								eHold[d][l]=0;
								eFramePos[d][l]++;
								if ( eFramePos[d][l] > eData[enemyType[d]].part[l].frames )
								{
									eFramePos[d][l]=0;
								}
							}

							draw(&screen,eData[enemyType[d]].part[l].addr[eFramePos[d][l]],enemyTextures,enemyX[d],enemyY[d],enemyW[eData[enemyType[d]].part[l].addr[eFramePos[d][l]]],enemyH[eData[enemyType[d]].part[l].addr[eFramePos[d][l]]]);
						}else{
							draw(&screen,eData[enemyType[d]].part[l].addr[0],enemyTextures,enemyX[d],enemyY[d],enemyW[eData[enemyType[d]].part[l].addr[0]],enemyH[eData[enemyType[d]].part[l].addr[0]]);
						}
					}
								
				}
			}

		// PLAYER SHIP DRAWING //

			if ( first )
			{
				if ( odd == 5 )
				{
					odd=0;
					for(l=0;l<=pParts;l++)
					{
						if ( pData.part[l].frames > 0 )
						{
							if ( pHold[l] < pData.part[l].hold )
							{
								pHold[l]++;
							}else{
								pHold[l]=0;
								pFramePos[l]++;
								if ( pFramePos[l] > pData.part[l].frames )
								{
									pFramePos[l]=0;
								}
							}

							draw(&screen,pData.part[l].addr[pFramePos[l]],playerTextures,shipX,shipY,playerW[0],playerH[0]);
						}else{
							draw(&screen,pData.part[l].addr[0],playerTextures,shipX,shipY,playerW[0],playerH[0]);
						}
					}
				}else{

					odd++;
				}
				invCurrent=SDL_GetTicks();

				if ( invCurrent/1000 - invStart/1000 >= 3 )
				{
					first=0;
				}

				invCurrent=0;

			}else{
				for(l=0;l<=pParts;l++)
				{
					if ( pData.part[l].frames > 0 )
					{
						if ( pHold[l] < pData.part[l].hold )
						{
							pHold[l]++;
						}else{
							pHold[l]=0;
							pFramePos[l]++;
							if ( pFramePos[l] > pData.part[l].frames )
							{
								pFramePos[l]=0;
							}
						}

						draw(&screen,pData.part[l].addr[pFramePos[l]],playerTextures,shipX,shipY,playerW[0],playerH[0]);
					}else{
						draw(&screen,pData.part[l].addr[0],playerTextures,shipX,shipY,playerW[0],playerH[0]);
					}
				}
				//draw(&screen,0, playerTextures, shipX,shipY,playerW[0],playerH[0]);
			}

		// PLAYER INFO/STATS DRAWING //

			draw(&screen,0,l1InfoTextures,20,0,l1InfoW[0],l1InfoH[0]);
			draw(&screen,1,l1InfoTextures,22,0,l1InfoW[1],l1InfoH[1]);
			draw(&screen,2,l1InfoTextures,22,0,l1InfoW[2],l1InfoH[2]);
			sprintf(cashText,"%d",cash);
			putText(&screen, cashText,fontTexture,250,9,fontW,fontH);
			sprintf(livesText, "%d", lives);
			putText(&screen, livesText,fontTexture,120,9,fontW,fontH);
			sprintf(fpsText, "FPS: %d", currentFPS);
			putText(&screen, fpsText,fontTexture,20,80,fontW,fontH);
		
		}
		}
		// Update the screen
		SDL_GL_SwapBuffers();

		// Get Framerate
		deltaClock = SDL_GetTicks() - startClock;
		startClock = SDL_GetTicks();

		if ( deltaClock != 0 )
			currentFPS = 1000 / deltaClock;

		//If we want to cap the frame rate
		if( ( get_ticks(startTicks) < 1000 / FRAMES_PER_SECOND ) )
		{
		    delay=( 1000 / FRAMES_PER_SECOND ) - get_ticks(startTicks);
		    //Sleep the remaining frame time
		    if ( delay > 0 )
		    	SDL_Delay(delay);
		}
		

	}	

	// unload level specific textures
	glDeleteTextures(eBulletTypeTotal, eBulletTextures);
	glDeleteTextures(bossCount,bossTextures);
	glDeleteTextures(enemyCount,enemyTextures);
	glDeleteTextures(l1BackCount,l1BackTextures);

	// unload remaining textures
	glDeleteTextures(completeCount,completeTextures);
	glDeleteTextures(weaponCount,weaponTextures);
	glDeleteTextures(playerCount,playerTextures);
	glDeleteTextures(dropCount,dropTextures);
	glDeleteTextures(optCount,optionsTexture);
	glDeleteTextures(l1InfoCount,l1InfoTextures);
	glDeleteTextures(scoreFontCount,scoreFontTexture);
	glDeleteTextures(fontCount,fontTexture);
	glDeleteTextures(menuCount,menuTextures);

#ifdef _WIN32 
	if ( ! windowed )
		reload(&screen,&windowed,1);
#endif

	// Exit
	Mix_HaltMusic();
	Mix_FreeMusic(music);

	// Halt and free sound effects
	Mix_HaltChannel(-1);
	/*for(d=sfxCount-1;d>-1;d--)
	{
		Mix_FreeChunk(sfx[d]);
	}*/

	TTF_CloseFont(font);

	for(d=enemyCount2-1;d>-1;d--)
		SDL_FreeSurface(enemy_surface[d]);

	for(d=dropCount2-1;d>-1;d--)
		SDL_FreeSurface(drop_surface[d]);

	SDL_FreeSurface(player_surface);
	for(d=bossCount-1;d>-1;d--)
		SDL_FreeSurface(boss_surface[d]);
	

	Mix_CloseAudio();

	SDL_Quit();
	//exit(0);
	return(0);
}

