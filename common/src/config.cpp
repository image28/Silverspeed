#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"

void isValid(FILE *config, char *file, int len)
{
	if ( ( feof(config) ) || ( len > 127 ) )
	{
		printf("Config file %s invalid\n",file);
		exit(-28);
	}
}

int read(FILE *config, char *inbyte, int *len)
{
	char temp='\0';
	int stop=0;

	*(inbyte+*(len))='\0';
	temp='\0';
	fread(&temp,1,1,config);
	*(inbyte+*(len))=temp;

	while ( temp == '\n' )
	{
		temp='\0';
		fread(&temp,1,1,config);
		*(inbyte+*(len))=temp;
	}

	while ( ( temp != ',' ) && ( temp != '>' ) && ( temp != ';' ) && ( temp != '\n' ) && ( ! feof(config) ) && ( *(len) < 128 ) )
	{
		if ( stop == 0 )
		{
			*(len)=*(len)+1;
		}

		*(inbyte+*(len))='\0';
		temp='\0';
		fread(&temp,1,1,config);

		if ( temp == ';' )
		{
			stop=1;
		}

		*(inbyte+*(len))=temp;
	}

	if ( stop )
	{
		while ( temp != '\n' )
		{
			temp='\0';
			fread(&temp,1,1,config);
		}
	}

	return(0);

}

int loadGameConfig(char *file, int *levels,int *drops,int *dropSeed, int *parts, int *powerMax, struct spriteGroup *drop, int *playerParts, struct spriteGroup *player)
{
	FILE *config;
	int len=0;
	char inbyte[128];
	int d,e,l,f;
	int multi=0;
	int temp=0;
	int pos=0;
	
	for(d=0;d<128;d++)
		inbyte[d]='\0';

	if ( ( config=fopen(file,"rb") ) == NULL )
	{
		printf("config file \"%s\" not found\n",file);
		exit(-1);
	}

	// Read # of Levels
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(levels)=strtol(inbyte,NULL,10);
	len=0;

	// Read number part to player
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(playerParts)=strtol(inbyte,NULL,10);
	len=0;

	for(e=0;e<=*(playerParts);e++)
	{
		// read # of Frames
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		player->part[e].frames=strtol(inbyte,NULL,10);
		len=0;

		if ( player->part[e].frames > 0 )
		{
			// read hold
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[e].hold=strtol(inbyte,NULL,10);
			len=0;

			// read loop
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[e].loop=strtol(inbyte,NULL,10);
			len=0;

			// read reverse
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[e].reverse=strtol(inbyte,NULL,10);
			len=0;


			// read addresses
			for(l=0;l<=player->part[e].frames;l++)	
			{

				read(config,inbyte,&len);

				if ( inbyte[len] == '>' )
				{
					multi=1;
					inbyte[len]='\0';
					player->part[e].addr[l]=strtol(inbyte,NULL,10);
					l=player->part[e].frames-1;
				}else{
					inbyte[len]='\0';

					if ( ! multi )
					{
						player->part[e].addr[l]=strtol(inbyte,NULL,10);
					}else{
						temp=0;
						temp=strtol(inbyte,NULL,10);
						for(f=player->part[e].addr[0]+1; f<=temp;f++)
						{
							player->part[e].addr[f-player->part[e].addr[0]]=f;
						}
					}
				}
	
				len=0;
			}multi=0;

			if ( player->part[e].reverse == 1 )
			{
				for(f=0; f<=player->part[e].frames/2; f++)
				{
					temp=0;
					temp=player->part[e].addr[f];
					player->part[e].addr[f]=player->part[e].addr[player->part[e].frames-f];
					player->part[e].addr[player->part[e].frames-f]=temp;
				}
			}

			isValid(config,file,len);
		}else{
			// read address
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[e].addr[0]=strtol(inbyte,NULL,10);
			len=0;

		}
	}


	// Read number of firing points
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(powerMax)=strtol(inbyte,NULL,10);
	len=0;

	for(l=0;l<*(powerMax);l++)
	{

		// Read number of firing points
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		player->part[l].firing=strtol(inbyte,NULL,10);
		len=0;
	
		for(d=0;d<player->part[l].firing;d++)
		{
			// Read texture
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[l].firetex[d]=strtol(inbyte,NULL,10);
			len=0;	

			// Read bullet power
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[l].firestart[d]=strtol(inbyte,NULL,10);
			len=0;	

			// Read bullet rate of fire
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[l].fireinterval[d]=strtol(inbyte,NULL,10);
			len=0;	

			// Read x2
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[l].firex2[d]=strtol(inbyte,NULL,10);
			len=0;	

			// Read y2
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[l].firey2[d]=strtol(inbyte,NULL,10);
			len=0;	

			// Read x1
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[l].firex1[d]=strtol(inbyte,NULL,10);
			len=0;	

			// Read y1
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			player->part[l].firey1[d]=strtol(inbyte,NULL,10);
			len=0;
		}
	
	}

	// Read number of drops
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(drops)=strtol(inbyte,NULL,10);
	len=0;

	// Read drops easy
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(dropSeed)=strtol(inbyte,NULL,10);
	len=0;

	// Read drops normal
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(dropSeed+1)=strtol(inbyte,NULL,10);
	len=0;

	// Read drops hard
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(dropSeed+2)=strtol(inbyte,NULL,10);
	len=0;

	for(d=0;d<*(drops);d++)
	{
		e=0;

		// Read # of parts
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		*(parts+d)=strtol(inbyte,NULL,10);
		len=0;

		for(e=0;e<=*(parts);e++)
		{
			// read # of Frames
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			drop[d].part[e].frames=strtol(inbyte,NULL,10);
			len=0;

			if ( drop[d].part[e].frames > 0 )
			{
				// read hold
				read(config,inbyte,&len);
				inbyte[len]='\0';
				isValid(config,file,len);
				drop[d].part[e].hold=strtol(inbyte,NULL,10);
				len=0;

				// read loop
				read(config,inbyte,&len);
				inbyte[len]='\0';
				isValid(config,file,len);
				drop[d].part[e].loop=strtol(inbyte,NULL,10);
				len=0;

				// read reverse
				read(config,inbyte,&len);
				inbyte[len]='\0';
				isValid(config,file,len);
				drop[d].part[e].reverse=strtol(inbyte,NULL,10);
				len=0;


				// read addresses
				for(l=0;l<=drop[d].part[e].frames;l++)	
				{

					read(config,inbyte,&len);

					if ( inbyte[len] == '>' )
					{
						multi=1;
						inbyte[len]='\0';
						drop[d].part[e].addr[l]=strtol(inbyte,NULL,10);
						l=drop[d].part[e].frames-1;
					}else{
						inbyte[len]='\0';

						if ( ! multi )
						{
							drop[d].part[e].addr[l]=strtol(inbyte,NULL,10);
						}else{
							temp=0;
							temp=strtol(inbyte,NULL,10);
							for(f=drop[d].part[e].addr[0]+1; f<=temp;f++)
							{
								drop[d].part[e].addr[f-drop[d].part[e].addr[0]]=f;
							}
						}
					}
		
					len=0;
				}multi=0;

				if ( drop[d].part[e].reverse == 1 )
				{
					for(f=0; f<=drop[d].part[e].frames/2; f++)
					{
						temp=0;
						temp=drop[d].part[e].addr[f];
						drop[d].part[e].addr[f]=drop[d].part[e].addr[drop[d].part[e].frames-f];
						drop[d].part[e].addr[drop[d].part[e].frames-f]=temp;
					}
				}

				isValid(config,file,len);
			}else{
				// read address
				read(config,inbyte,&len);
				inbyte[len]='\0';
				isValid(config,file,len);
				drop[d].part[e].addr[0]=strtol(inbyte,NULL,10);
				len=0;

			}
	
		}	

	}

	//*(levels)=strtol(inbyte,NULL,10);

	fclose(config);

}



int loadBossConfig(char *file, int *parts, int *bossX, int *bossY, struct bossPart *piece, int *desGroups, int *hpNorm, int *hpHard, struct bossHit *hits)
{
	FILE *config;
	int len=0;
	char inbyte[128];
	int d=0;
	int stop=0;
	int e=0;
	int f=0;
	int multi=0;
	int temp=0;
	int pos=0;
	
	for(d=0;d<128;d++)
		inbyte[d]='\0';

	if ( ( config=fopen(file,"rb") ) == NULL )
	{
		printf("config file \"%s\" not found\n",file);
		exit(-1);
	}
	

	read(config,inbyte,&len);	// Read Number of Parts to boss
	inbyte[len]='\0';
	isValid(config,file,len);		// Check Config File is Valid
	*(parts)=strtol(inbyte,NULL,10);// Convert string to number
	len=0;

	read(config,inbyte,&len);	// Read X coord
	inbyte[len]='\0';
	isValid(config,file,len);
	*(bossX)=strtol(inbyte,NULL,10);
	len=0;

	read(config,inbyte,&len);	// Read Y coord
	inbyte[len]='\0';
	isValid(config,file,len);
	*(bossY)=strtol(inbyte,NULL,10);
	len=0;

	read(config,inbyte,&len);	// Read destroyable groups
	inbyte[len]='\0';
	isValid(config,file,len);
	*(desGroups)=strtol(inbyte,NULL,10);
	len=0;

	read(config,inbyte,&len);	// Read hp add normal
	inbyte[len]='\0';
	isValid(config,file,len);
	*(hpNorm)=strtol(inbyte,NULL,10);
	len=0;

	read(config,inbyte,&len);	// Read hp add hard
	inbyte[len]='\0';
	isValid(config,file,len);
	*(hpHard)=strtol(inbyte,NULL,10);
	len=0;


	inbyte[0]='\0';

	for(d=0;d<=*(desGroups);d++)
	{
		while ( ( inbyte[len] != '\n' ) && ( inbyte[len] != ';' ) )
		{
			len=0;
			read(config,inbyte,&len);
			if ( inbyte[len] == '\n' )
				temp=1;
			else if ( inbyte[len] == ';' )
				temp=2;

			inbyte[len]='\0';
			hits[d].parts[e]=strtol(inbyte,NULL,10);
			if ( temp == 1 )
				inbyte[len]='\n';
			else if ( temp == 2 )
				inbyte[len]=';';
				
			e++;
			
			
		}
		temp=0;
		len=0;
	
		

		read(config,inbyte,&len);	// grouped
		inbyte[len]='\0';
		isValid(config,file,len);
		hits[d].grouped=strtol(inbyte,NULL,10);
		len=0;

		if ( hits[d].grouped )
		{
			read(config,inbyte,&len);	// hp's
			inbyte[len]='\0';
			isValid(config,file,len);
			hits[d].hp[0]=strtol(inbyte,NULL,10);
			len=0;
			hits[d].count=e;
		}else{
			hits[d].count=e;
			for(f=0;f<e;f++)
			{
				read(config,inbyte,&len);	// hp's
				inbyte[len]='\0';
				isValid(config,file,len);
				hits[d].hp[f]=strtol(inbyte,NULL,10);
				len=0;
			}
		}

		read(config,inbyte,&len);	// read start movment count
		inbyte[len]='\0';
		isValid(config,file,len);
		hits[d].moveStartCount=strtol(inbyte,NULL,10);
		len=0;

		read(config,inbyte,&len);	// read loop movment count
		inbyte[len]='\0';
		isValid(config,file,len);
		hits[d].moveLoopCount=strtol(inbyte,NULL,10);
		len=0;

		
		for(f=0;f<hits[d].moveStartCount;f++)
		{
			read(config,inbyte,&len);	// read start movment x
			inbyte[len]='\0';
			isValid(config,file,len);
			hits[d].moveStartX[f]=strtol(inbyte,NULL,10);
			len=0;

			read(config,inbyte,&len);	// read start movment y
			inbyte[len]='\0';
			isValid(config,file,len);
			hits[d].moveStartY[f]=strtol(inbyte,NULL,10);
			len=0;

		}

		for(f=0;f<hits[d].moveLoopCount;f++)
		{
			read(config,inbyte,&len);	// read loop movment x
			inbyte[len]='\0';
			isValid(config,file,len);
			hits[d].moveLoopX[f]=strtol(inbyte,NULL,10);
			len=0;

			read(config,inbyte,&len);	// read loop movment y
			inbyte[len]='\0';
			isValid(config,file,len);
			hits[d].moveLoopY[f]=strtol(inbyte,NULL,10);
			len=0;

			
		}

		e=0;
	}
	
	for(d=0;d<*(parts);d++)
	{
		// Read # of frames
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		piece[d].frames=strtol(inbyte,NULL,10);
		len=0;

	
		if ( piece[d].frames > 0 )
		{
			// Read Hold Value
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			piece[d].hold=strtol(inbyte,NULL,10);
			len=0;

			// Read loop value
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			piece[d].loop=strtol(inbyte,NULL,10);
			len=0;

			// Read Play backwards value
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			piece[d].reverse=strtol(inbyte,NULL,10);
			len=0;

			// read addresses of frames
			for(e=0;e<=piece[d].frames;e++)	
			{

				read(config,inbyte,&len);

				if ( inbyte[len] == '>' )
				{
					multi=1;
					inbyte[len]='\0';
					piece[d].addr[e]=strtol(inbyte,NULL,10);
					e=piece[d].frames-1;
				}else{
					inbyte[len]='\0';

					if ( ! multi )
					{
						piece[d].addr[e]=strtol(inbyte,NULL,10);
					}else{
						temp=0;
						temp=strtol(inbyte,NULL,10);
						for(f=piece[d].addr[0]+1; f<=temp;f++)
						{
							piece[d].addr[f-piece[d].addr[0]]=f;
						}
					}
				}
		
				len=0;
			}multi=0;

			if ( piece[d].reverse == 1 )
			{
				for(f=0; f<=piece[d].frames/2; f++)
				{
					temp=0;
					temp=piece[d].addr[f];
					piece[d].addr[f]=piece[d].addr[piece[d].frames-f];
					piece[d].addr[piece[d].frames-f]=temp;
				}
			}

			isValid(config,file,len);

			// Read X coord of piece
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);\
			piece[d].xPos=strtol(inbyte,NULL,10);
			len=0;

			// Read Y coord of piece
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			piece[d].yPos=strtol(inbyte,NULL,10);
			len=0;

			// Read number of firing points
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			piece[d].firing=strtol(inbyte,NULL,10);
			len=0;
			
		}else{
			// Read address of frame
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			piece[d].addr[0]=strtol(inbyte,NULL,10);
			len=0;

			// Read X coord of piece
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			piece[d].xPos=strtol(inbyte,NULL,10);
			len=0;

			// Read Y coord of piece
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			piece[d].yPos=strtol(inbyte,NULL,10);
			len=0;

			// Read number of firing points
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			piece[d].firing=strtol(inbyte,NULL,10);
			len=0;

		
			if ( piece[d].firing > 0 )
			{
				for(e=0;e<piece[d].firing;e++)
				{
					// Read texture
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					piece[d].firetex[e]=strtol(inbyte,NULL,10);
					len=0;	

					// Read start
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					piece[d].firestart[e]=strtol(inbyte,NULL,10);
					len=0;	

					// Read interval
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					piece[d].fireinterval[e]=strtol(inbyte,NULL,10);
					len=0;	

					// Read pause movement while firing 
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					piece[d].firepause[e]=strtol(inbyte,NULL,10);
					len=0;	

					// Read x2
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					piece[d].firex2[e]=strtol(inbyte,NULL,10);
					len=0;	


					// Read y2
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					piece[d].firey2[e]=strtol(inbyte,NULL,10);
					len=0;	
					
					// Read x1
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					piece[d].firex1[e]=strtol(inbyte,NULL,10);
					len=0;	

					// Read y1
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					piece[d].firey1[e]=strtol(inbyte,NULL,10);
					len=0;	
				}
			
			}
		}

		
	}
printf("-----------------------\n");
}

int loadLevelConfig(char *file, int *backgrounds, int *bgLoop, int *enemies, int *enemySeed, int *bulletSeed, int *hitsEasy, int *hitsNorm, int *hitsHard,int *parts, struct spriteGroup *enemy)
{
	FILE *config;
	int len=0;
	char inbyte[128];
	int d,e,l,f;
	int multi=0;
	int temp=0;
	int pos=0;
	
	for(d=0;d<128;d++)
		inbyte[d]='\0';

	if ( ( config=fopen(file,"rb") ) == NULL )
	{
		printf("config file \"%s\" not found\n",file);
		exit(-1);
	}


	// Read number of backgrounds
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(backgrounds)=strtol(inbyte,NULL,10);
	len=0;

	// Read background loop position
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(bgLoop)=strtol(inbyte,NULL,10);
	len=0;

	// Read enemy count
	read(config,inbyte,&len);
	inbyte[len]='\0';
	isValid(config,file,len);
	*(enemies)=strtol(inbyte,NULL,10);
	len=0;

	for(d=0;d<3;d++)
	{
		// Read enemy seeds per diffficulty
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		*(enemySeed+d)=strtol(inbyte,NULL,10);
		len=0;
	}

	for(d=0;d<3;d++)
	{
		// Read bullet seed per difficulty
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		*(bulletSeed+d)=strtol(inbyte,NULL,10);
		len=0;
	}

	for(d=0;d<*(enemies);d++)
	{
		// Read hits per enemy on easy
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		*(hitsEasy+d)=strtol(inbyte,NULL,10);
		len=0;
	}

	for(d=0;d<*(enemies);d++)
	{
		// Read hits per enemy on normal
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		*(hitsNorm+d)=strtol(inbyte,NULL,10);
		len=0;
	}

	for(d=0;d<*(enemies);d++)
	{
		// Read hits per enemy on hard
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		*(hitsHard+d)=strtol(inbyte,NULL,10);
		len=0;
	}

	// for all enemies
	for(d=0;d<*(enemies);d++)
	{
		// read number of parts to enemies
		read(config,inbyte,&len);
		inbyte[len]='\0';
		isValid(config,file,len);
		*(parts+d)=strtol(inbyte,NULL,10);
		len=0;

		// for all parts
		for(e=0;e<=*(parts+d);e++)
		{
			// read number of frames
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			enemy[d].part[e].frames=strtol(inbyte,NULL,10);
			len=0;

			// if frames > 0
			if ( enemy[d].part[e].frames > 0 )
			{
				// read hold
				read(config,inbyte,&len);
				inbyte[len]='\0';
				isValid(config,file,len);
				enemy[d].part[e].hold=strtol(inbyte,NULL,10);
				len=0;

				// loop
				read(config,inbyte,&len);
				inbyte[len]='\0';
				isValid(config,file,len);
				enemy[d].part[e].loop=strtol(inbyte,NULL,10);
				len=0;

				// read reverse
				read(config,inbyte,&len);
				inbyte[len]='\0';
				isValid(config,file,len);
				enemy[d].part[e].reverse=strtol(inbyte,NULL,10);
				len=0;

				// read addresses
				for(l=0;l<=enemy[d].part[e].frames;l++)	
				{

					read(config,inbyte,&len);

					if ( inbyte[len] == '>' )
					{
						multi=1;
						inbyte[len]='\0';
						enemy[d].part[e].addr[l]=strtol(inbyte,NULL,10);
						l=enemy[d].part[e].frames-1;
					}else{
						inbyte[len]='\0';

						if ( ! multi )
						{
							enemy[d].part[e].addr[l]=strtol(inbyte,NULL,10);
						}else{
							temp=0;
							temp=strtol(inbyte,NULL,10);
							for(f=enemy[d].part[e].addr[0]+1; f<=temp;f++)
							{
								enemy[d].part[e].addr[f-enemy[d].part[e].addr[0]]=f;
							}
						}
					}
		
					len=0;
				}multi=0;

				if ( enemy[d].part[e].reverse == 1 )
				{
					
					for(f=0; f<=enemy[d].part[e].frames/2; f++)
					{
						temp=0;
						temp=enemy[d].part[e].addr[f];
						enemy[d].part[e].addr[f]=enemy[d].part[e].addr[enemy[d].part[e].frames-f];
						enemy[d].part[e].addr[enemy[d].part[e].frames-f]=temp;
						
					}
				}

				isValid(config,file,len);

			}else{
				// read address
				read(config,inbyte,&len);
				inbyte[len]='\0';
				isValid(config,file,len);
				enemy[d].part[e].addr[0]=strtol(inbyte,NULL,10);
				len=0;
				
			}

			// read does fire
			read(config,inbyte,&len);
			inbyte[len]='\0';
			isValid(config,file,len);
			enemy[d].part[e].firing=strtol(inbyte,NULL,10);
			len=0;

			// if fires
			if ( enemy[d].part[e].firing > 0 )
			{
				// for all firing points
				for(l=0;l<enemy[d].part[e].firing;l++)
				{
					// texture
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					enemy[d].part[e].firetex[l]=strtol(inbyte,NULL,10);
					len=0;

					// start
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					enemy[d].part[e].firestart[l]=strtol(inbyte,NULL,10);
					len=0;

					// interval
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					enemy[d].part[e].fireinterval[l]=strtol(inbyte,NULL,10);
					len=0;

					// firing line
					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					enemy[d].part[e].firex2[l]=strtol(inbyte,NULL,10);
					len=0;

					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					enemy[d].part[e].firey2[l]=strtol(inbyte,NULL,10);
					len=0;

					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					enemy[d].part[e].firex1[l]=strtol(inbyte,NULL,10);
					len=0;

					read(config,inbyte,&len);
					inbyte[len]='\0';
					isValid(config,file,len);
					enemy[d].part[e].firey1[l]=strtol(inbyte,NULL,10);
					len=0;
				}
			}
		}
	}

	fclose(config);
}

