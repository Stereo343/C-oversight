#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAPSIZE 10
#define PORTEAVION 5
#define NB_PORTEAVION 1
#define CUIRASSIER 4
#define NB_CUIRASSIER 1
#define CROISEUR 3
#define NB_CROISEUR 1
#define FREGATE 2
#define NB_FREGATE 2
#define SOUSMARIN 1
#define NB_SOUSMARIN 3
#define SEA 0

void FillCPU();
void FillHuman();
void PrintMaps();
void PlacementCPU(int NB, int Size);
void PlacementHuman(int bateau);
void StartGame();

unsigned int MapHuman[MAPSIZE][MAPSIZE] = {SEA};
unsigned int MapCPU[MAPSIZE][MAPSIZE] = {SEA};

int main()
{
	int test = 0;

	FillCPU();
	FillHuman();
	StartGame();

	scanf("%d", &test);
	return 0;
}

void PrintMaps()
{
	unsigned int x = 0;
	unsigned int y = 0;


	printf("Map CPU: \n\n");

	//Lettres CPU
	printf("   ");
	for(x = 0; x < MAPSIZE; x++) printf(" %c", x+65);
	printf("\n");

	//Borders Up CPU
	printf("   %c", 218);
	for(x = 0; x < MAPSIZE-1; x++) printf("%c%c", 196, 196);
	printf("%c%c%c \n", 196, 196, 191);

	//Print MapCPU
	for(y = 0; y < MAPSIZE; y++)
	{
		printf("%2d %c", y+1, 179);
		for(x = 0; x < MAPSIZE; x++)
		{
			if(MapCPU[y][x] == SEA) printf("~ ");
			else if(MapCPU[y][x] == PORTEAVION) printf("%d ", PORTEAVION);
			else if(MapCPU[y][x] == CUIRASSIER) printf("%d ", CUIRASSIER);
			else if(MapCPU[y][x] == CROISEUR) printf("%d ", CROISEUR);
			else if(MapCPU[y][x] == FREGATE) printf("%d ", FREGATE);
			else if(MapCPU[y][x] == SOUSMARIN) printf("%d ", SOUSMARIN);
			else printf("E ", MapCPU[y][x]);
		}
		printf("%c\n", 179);
	}

	//Border Down CPU
	printf("   %c%c%c", 192, 196, 196);
	for(x = 0; x < MAPSIZE-2; x++) printf("%c%c", 196, 196);
	printf("%c%c%c \n\n", 196, 196, 217);

	printf("Map Player: \n\n");
	//Lettres Human
	printf("   ");
	for(x = 0; x < MAPSIZE; x++) printf(" %c", x+65);
	printf("\n");

	//Borders Up Human
	printf("   %c", 218);
	for(x = 0; x < MAPSIZE-1; x++) printf("%c%c", 196, 196);
	printf("%c%c%c \n", 196, 196, 191);

	//Print MapHuman
	for(y = 0; y < MAPSIZE; y++)
	{
		printf("%2d %c", y+1, 179);
		for(x = 0; x < MAPSIZE; x++)
		{
			if(MapHuman[y][x] == SEA) printf("~ ");
			else if(MapHuman[y][x] == PORTEAVION) printf("%d ", PORTEAVION);
			else if(MapHuman[y][x] == CUIRASSIER) printf("%d ", CUIRASSIER);
			else if(MapHuman[y][x] == CROISEUR) printf("%d ", CROISEUR);
			else if(MapHuman[y][x] == FREGATE) printf("%d ", FREGATE);
			else if(MapHuman[y][x] == SOUSMARIN) printf("%d ", SOUSMARIN);
			else if(MapHuman[y][x] == 6) 
			{
				color(15,0);
				printf("T");
				color(0,15);
			}
			else printf("E ", MapHuman[y][x]);
		}
		printf("%c\n", 179);
	}

	//Border Down Human
	printf("   %c%c%c", 192, 196, 196);
	for(x = 0; x < MAPSIZE-2; x++) printf("%c%c", 196, 196);
	printf("%c%c%c \n\n", 196, 196, 217);
}

void FillCPU()
{
	PlacementCPU(NB_PORTEAVION, PORTEAVION);
	PlacementCPU(NB_CUIRASSIER, CUIRASSIER);
	PlacementCPU(NB_CROISEUR, CROISEUR);
	PlacementCPU(NB_FREGATE, FREGATE);
	PlacementCPU(NB_SOUSMARIN, SOUSMARIN);
}

void PlacementCPU(int NB, int Size)
{
	unsigned short int i;
	unsigned short int j;
	unsigned short int x;
	unsigned short int y;
	unsigned short int OnSea;
	srand(time(NULL));

	for(i=0;i<NB;i++)
	{
		OnSea = 0;
		while(!OnSea)
		{
			OnSea = 1;
			if(rand()%2 == 0) //= Placement Vertical
			{
				do
				{
					x = rand()%(MAPSIZE-2)+1;
					y = rand()%(MAPSIZE-Size);
				}while(y==0);

				for(j = 0; j < Size+2; j++)
				{
					if(MapCPU[y+j-1][x] != SEA || MapCPU[y+j-1][x-1] != SEA || MapCPU[y+j-1][x+1] != SEA)
					{
						OnSea = 0;
						break;
					}
				}

				if(OnSea)
				{
					for(j = 0; j < Size; j++)
						MapCPU[y+j][x] = Size;

				printf("Position Verticale. Taille: %d ", Size);
				printf("H: %d ", x+1);
				printf("V: %d \n", y+1);
				}
			}//End Vertical

			else //= Placement Horizontal
			{
				do
				{
					x = rand()%(MAPSIZE-Size);
					y = rand()%(MAPSIZE-2)+1;
				}while(x==0);

				for(j = 0; j < Size+2; j++)
				{
					if(MapCPU[y][x+j-1] != SEA || MapCPU[y+1][x+j-1] != SEA || MapCPU[y-1][x+j-1] != SEA)
						OnSea = 0;
				}

				if(OnSea)
				{
					for(j = 0; j < Size; j++)
						MapCPU[y][x+j] = Size;

				printf("Position Horizontale. Taille: %d ", Size);
				printf("H: %d ", x+1);
				printf("V: %d \n", y+1);
				}
			}//End Horizontal
		}
	}
}

void FillHuman()
{
	short int i;
	printf("Placement de vos bateaux.\n");

	printf("Placement du Porte-Avion\n");
	for(i=0;i<NB_PORTEAVION;i++)
		PlacementHuman(PORTEAVION);
	printf("Placement du Cuirassier\n");
	for(i=0;i<NB_CUIRASSIER;i++)
		PlacementHuman(CUIRASSIER);
	printf("Placement du Croiseur\n");
	for(i=0;i<NB_CROISEUR;i++)
		PlacementHuman(CROISEUR);
	printf("Placement des Frégates\n");
	for(i=0;i<NB_FREGATE;i++)
		PlacementHuman(FREGATE);
	printf("Placement des Sous-marins\n");
	for(i=0;i<NB_SOUSMARIN;i++)
		PlacementHuman(SOUSMARIN);
}

void PlacementHuman(int bateau)
{
	char answer[4], *ptr = answer, sense, x;
	unsigned int y, i;
	unsigned int Place_Available = 0;

	while(!Place_Available)
	{
		PrintMaps();
		Place_Available = 1;
		do
		{
			printf("V/H ? ");
			fgets(answer, 3, stdin);
			sscanf(answer, "%c", &sense);
		}while(!(sense =='H' || sense == 'V'));

		do
		{
			printf("Position en x (%c-%c) ? ", 65+1, 65+MAPSIZE-2);
			fgets(answer, 4, stdin);
			sscanf(answer, "%c", &x);
		}while(!((x >= 66) && (x <= 73)));
		x-=65;

		do
		{
			printf("Position en y (%d-%d) ? ", 1, MAPSIZE);
			fgets(answer, 4, stdin);
			sscanf(answer, "%u", &y);
		}while(!((y >= 2) && (y <= 9)));
		y-=1;

		if(x > MAPSIZE-1 || x < 1 || y > MAPSIZE-1 || y < 1 || sense == 'H' && x > MAPSIZE-1 - bateau || sense == 'V' && y > MAPSIZE-1 - bateau)
		{
            system("cls");
			printf("Zone hors de la carte\n");
			Place_Available = 0;
		}


		if((sense == 'V') && Place_Available)
		{
			for(i = 0; i<bateau+2; i++)
			{
				if(MapHuman[y+i-1][x] != SEA || MapHuman[y+i-1][x-1] != SEA || MapHuman[y+i-1][x+1] != SEA)
				{
                    system("cls");
                    Place_Available = 0;
					printf("Impossible de placer le bateau à cet endroit.\n");
					break;
				}

			}
		}//end of if vertical condition

		else if((sense == 'H') && Place_Available)
		{
			for(i = 0; i<bateau+2; i++)
			{
				if(MapHuman[y][x+i-1] != SEA || MapHuman[y-1][x+i-1] != SEA || MapHuman[y+1][x+i-1] != SEA)
				{
                    system("cls");
                    Place_Available = 0;
					printf("Impossible de placer le bateau à cet endroit.\n");
					break;
				}

			}
		}//end of else if horizontal condition

		else
		{
            system("cls");
            printf("Veuillez indiquer un sens vertical ou horizontal ainsi qu’une zone suffisamment grande pour le bateau, ainsi qu’un endroit qui ne soit pas aux bords.\n");
		}

	}//end of while loop

	if(sense == 'V')
	{
		for(i=0;i<bateau;i++)
			MapHuman[y+i][x] = bateau;
            system("cls");
	}
	else
	{
		for(i=0;i<bateau;i++)
            MapHuman[y][x+i] = bateau;
        system("cls");
    }
}//end of function


void StartGame()
{
	char answer[4], *ptr = answer, sense, x;
	unsigned int y, i;

	do
	{
		PrintMaps();
		printf("Ou voulez-vous tirer?\n");

		do
		{
			printf("Position en x (%c-%c) ? ", 65+1, 65+MAPSIZE-2);
			fgets(answer, 3, stdin);
			sscanf(answer, "%c", &x);
		}while(!((x >= 66) && (x <= 73)));
		x-=65;

		do
		{
			printf("Position en y (%d-%d) ? ", 1, MAPSIZE);
			fgets(answer, 4, stdin);
			sscanf(answer, "%u", &y);
		}while(!((y >= 2) && (y <= 9)));
		y-=1;

		If(MapCPU[y][x] == PORTEAVION || MapCPU[y][x] == CUIRASSIER || MapCPU[y][x] == CROISEUR || MapCPU[y][x] == FREGATE || MapCPU[y][x] == SOUSMARIN)
		{
			MapCPU[y][x] = 6;
		}
		system("cls");
	}while(y != 11);
	printf("cc");
}