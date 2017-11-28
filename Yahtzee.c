/* Cornet Bruno
   6 TTr I*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char tableau[16][16] = {" 1. As         ",
							 " 2. Deux       ",
							 " 3. Trois      ",
							 " 4. Quatre     ",
							 " 5. Cinq       ",
							 " 6. Six        ",
							 "    BONUS      ",
							 "    TOTAL      ",
							 " 7. Brelan     ",
							 " 8. Carre      ",
							 " 9. Full       ",
							 "10. Peti. Suite",
							 "11. Gran. Suite",
							 "12. Yahtzee    ",
							 "13. Chance     ",
							 " TOTAL GLOBAL  "};
struct yams {
	char figure[16];
	int pointjoueur;
}tabscore[16];

int i, Nbr_Lance=0;
int de[5];

char NdFComplet[75];
char Pseudo[26];
char Extension[5]=".6ti";
char Cunite[4]="C:\\"; /*mettre 2 \ pour qu'il en ecrive 1*/
char Zunite[4]="Z:\\";
char Sunite[4]="S:\\";
char Eunite[4]="E:\\";
char Uunite[4]="U:\\";
char Funite[4]="F:\\";
//char Chemin[52]="E:\\C\\Save";
char Chemin[6]="Save\\";

FILE *AdrOuv; // C'est un pointeur sur un fichier de mémoire de masse
FILE *AdrCharge;

void Initialisation(void);
void Affichage(int);
void De(int);
void Change_de(void);
void ChoixEtRelance(void);
void Calcul(int);

void NomDeFichier(void);
void CreationdeFichier(void);
void ChargerPartie(void);

int main()
{
	srand(time(NULL));
	if(!Nbr_Lance) Initialisation();// Si c'est le premier lancé, on initialise tout
	De(0);
	Affichage(1);
	if(Nbr_Lance < 13)
	{
		Change_de();
		ChoixEtRelance();
	}
	return 0;
}
void Initialisation()
{
	char reponse;

	printf("Bienvenu(e) au jeu du Yahtzee !!!\n");
	printf("Voulez-vous charger une partie precedente ? (Y ou N)\n");
	fflush(stdin);scanf("%c",&reponse);
	reponse=toupper(reponse);
	if(reponse != 'Y')
	{
		for(i=0;i<17;i++)
		{
			strcpy(tabscore[i].figure,tableau[i]);
			tabscore[i].pointjoueur=-1;
		}
	}
	else
		ChargerPartie();
}
void Affichage(d)
{
	system("cls");

	printf("%c-     SCORE     Vous%c",218,191);
	for(i=0;i<16;i++) {
		printf("\n%c%s%c",179,tabscore[i].figure,179);
		if(tabscore[i].pointjoueur == -1)
			printf(" -- %c",179);
		else if(tabscore[i].pointjoueur > 99)
			printf(" %2d%c",tabscore[i].pointjoueur,179);
		else
			printf(" %2d %c",tabscore[i].pointjoueur,179);
		if(i==7)
			printf("\n%c---------------%c----%c",195,197,180);
	}
	printf("\n%c---------------%c----%c\n",192,193,217);
	if(d && Nbr_Lance < 13)
	{
		for(i=0;i<5;i++) printf("  D%d ",i+1);
		printf("\n");
		for(i=0;i<5;i++) printf("%c---%c",218,191);
		printf("\n");
		for(i=0;i<5;i++) printf("| %d |", de[i]);
		printf("\n");
		for(i=0;i<5;i++) printf("%c---%c",192,217);
	}
}

void De(numero)
{
	if(numero != 0) /* Relance un dé spécifique */
	{
		de[numero-1] = rand()%6+1;
	}
	else /* Relance tout les dés */
	{
		for(i=0;i<5;i++)
		{
			de[i] = rand()%6+1;
		}
	}
}

void Change_de()
{
	char des[6];
	int lance=0,erreur,longueur;
	do{
		do{  /*-------------------------- TRAITEMENT D'ERREUR --------------------------- */
			int j;
			erreur=0;

			printf("\nQuels d%cs voulez vous rejouer ? (Lanc%c restant : %d) : ",130,130,2-lance);
			fflush(stdin);gets(des);

			longueur=strlen(des);

/* ------- PREMIER TEST D'ERREUR --------- */

			if(!longueur) {printf("Erreur : Il n'y a rien propos%c !",130);erreur=1;}
			else if(longueur > 5) {printf("Erreur : Il n'y a pas plus de 5 d%cs !",130);erreur=1;}

/* ------- SECOND TEST D'ERREUR --------- */

			if(!erreur) // Si le premier test d'erreur est nul
			{
				for(i=0;i<longueur;i++)
				{
					if(des[i] != 84 && des[i] != 116 && des[i] != 65 && des[i] != 97 && !(des[i] >= 49 && des[i] <= 54))
					{
						printf("Erreur : Vous ne pouvez taper que : A,a,T,t et 1,2,3,4,5 !");
						erreur=1;
						i=5;
					}
				}
				if(longueur > 1 && !erreur) // S'il y a qu'un caractère inutile de faire ces vérifications
				{
					for(i=0;i<longueur;i++) // Vérifie si on n'a pas A ou T
					{
						if(des[i] == 84 || des[i] == 116 || des[i] == 65 || des[i] == 97)
						{
							printf("Erreur : '%s' n'est pas correct, mais 'A', 'a', 'T' ou 't' tout seul sont correct !", des);
							i=5;
							erreur=1;
						}
					}
					for(i=0;i<longueur;i++)
					{
						for(j=i+1;j<longueur;j++)
						{
							if(des[i] == des[j])
							{
								i=5;
								j=5;
								printf("Erreur : On lance le meme d%c qu'une seule fois !",130);
								erreur=1;
							}
						}
					}
				}
			}
		}while(erreur == 1); /*-------------------------- FIN TRAITEMENT D'ERREUR --------------------------- */

		if(des[0] == 84 || des[0] == 116)
		{
			lance++;
			De(0);
		}
		else if(des[0] == 65 || des[0] == 97) lance=2;
		else
		{
			for(i=0;i<longueur;i++)
			{
				De(des[i]-48); // Pourquoi - 48 ? Code ascii de 1 est 49 et donc 49-48 = 1
			}
			lance++;
		}
		Affichage(1);
	}while(lance != 2);
}
void ChoixEtRelance()
{
	int choix;
	char reponse;
	Nbr_Lance++;
	do{
		printf("\nOu voulez-vous plac%c votre serie de d%cs (1-13) ? ",130,130);
		scanf("%d",&choix);
		if(choix < 1 || choix > 13)
			printf("Numero de 1 a 13 sont uniquement accepte !");
		else if(choix < 7 && tabscore[choix-1].pointjoueur != -1 || choix > 6 && choix < 14 && tabscore[choix+1].pointjoueur != -1)
		{printf("Ce choix a deja ete utilise !");choix=0;}
	}while(choix < 1 || choix > 13);
	Calcul(choix);
	printf("Voulez-vous continuer a jouer ? (Y ou N)\n"); // Le joueur peut taper autre chose que 'N' pour arrêter le jeu
	fflush(stdin);scanf("%c",&reponse);
	reponse=toupper(reponse);
	if(reponse == 'Y' && Nbr_Lance < 13) main();
	else if(reponse != 'Y' || Nbr_Lance == 13)
	{
		if(Nbr_Lance == 13) {
			printf("Vous avez termine le jeu avec un score de %d. \n\n", tabscore[15].pointjoueur);
			CreationdeFichier();
		}
		else {
			printf("Une sauvegarde est prevue, voulez-vous la faire ? (Y ou N)\n");
			fflush(stdin);scanf("%c",&reponse);
			reponse=toupper(reponse);
			if(reponse == 'Y') CreationdeFichier();
			else printf("Merci d'avoir joue ! A bientot !");
		}
	}
}
void Calcul(choix)
{
	int mem=0,j;

	if(choix == 13) tabscore[14].pointjoueur=de[0]+de[1]+de[2]+de[3]+de[4];
	else if(choix > 0 && choix < 7) // SOMME DES DéS EGAUX
	{
		for(i=0;i<5;i++)
		{
			if(de[i] == choix)
				mem+=choix;
		}
		tabscore[choix-1].pointjoueur=mem;
	}
	else if(choix == 7 || choix == 8 || choix == 12) // SOMME LORQU'IL Y A X DéS IDENTIQUES : BRELAN, CARRE et YATHZEE
	{
		tabscore[choix+1].pointjoueur=0; // On prévoit le coup en mettant 0 au score
		for(i=0;i<5;i++)
		{
			for(j=i+1;j<5;j++)
			{
				if(de[i] == de[j]) // On vérifie un dé à la fois par rapport aux autres
					mem++;
			}
			// Si le dé vérifié est égal à minimum 2 autres dés ou plus (en fonction du choix), on a la condition complètée
			if(choix == 7 && mem >= 2) {tabscore[8].pointjoueur=de[0]+de[1]+de[2]+de[3]+de[4];i=5;}
			else if(choix == 8 && mem >= 3) {tabscore[9].pointjoueur=de[0]+de[1]+de[2]+de[3]+de[4];i=5;}
			else if(choix == 12 && mem == 4) {tabscore[13].pointjoueur=50;i=5;}
			else mem=0; // Sinon on le met de côté et on recommence avec le dé suivant
		}
	}
	else // PETITE/GRANDE SUITE et FULL avec triage des dés
	{
		tabscore[choix+1].pointjoueur=0; // On prévoit le coup en mettant 0 au score
		for(i=0;i<5;i++)
		{
			for(j=i+1;j<5;j++)
			{
				if(de[i] > de[j])
				{
					mem=de[i];
					de[i]=de[j];
					de[j]=mem;
				}
			}
		}
		if(choix == 9)
		{
			if(de[0] == de[1] && de[1] == de[2] && de[3] == de[4] || de[0] == de[1] && de[2] == de[3] && de[3] == de[4])
				tabscore[10].pointjoueur=25;
		}
		if(choix == 10 || choix == 11)// PETITE et GRANDE SUITE
		{
			mem=0;
			for(i=0;i<5;i++)
			{
				if(de[i] == de[i+1]-1)
					mem++;
				printf("%d,%d\n",de[i],mem);
			}
			if(choix == 10 && mem >= 3) tabscore[11].pointjoueur=30;
			else if(choix == 11 && mem == 4) tabscore[12].pointjoueur=40;
		}
	}
	tabscore[7].pointjoueur=0;
	tabscore[15].pointjoueur=0;
	for(i=0;i<7;i++) if(tabscore[i].pointjoueur > -1) tabscore[7].pointjoueur+=tabscore[i].pointjoueur;
	if(tabscore[7].pointjoueur >= 63) tabscore[6].pointjoueur = 35;
	for(i=8;i<15;i++) if(tabscore[i].pointjoueur > -1) tabscore[15].pointjoueur+=tabscore[i].pointjoueur;
	tabscore[15].pointjoueur+=tabscore[7].pointjoueur;
	Affichage(0);
}

/************* MODULE TRAITEMENT DE FICHIER ***************/
void NomDeFichier()
{
	char unite;
	do {
		printf("Choisissez votre unite (C - E - F - S - U - Z) !\n");
		fflush(stdin); scanf("%c",&unite);
		unite=toupper(unite);
		printf("Votre choix : %c\n",unite);
		if ((unite!='C'&& unite!='E' && unite!='S'&& unite!='U' && unite!='Z' && unite!='F')) printf("Choix incorrect (C - E - F - S - U - Z) !\n");
	}while ((unite!='C'&& unite!='E' && unite!='S'&& unite!='U' && unite!='Z' && unite!='F'));

	do {printf("Introduisez votre pseudo (au plus 25 caracteres)\n");
	fflush(stdin); scanf("%s",Pseudo);
	if(strlen(Pseudo)>25)printf("Erreur d'encodage votre pseudo est trop long!\n");
	}while(strlen(Pseudo)>20);

	switch(unite)
	{
		case 'C': strcpy(NdFComplet,Cunite); break;
		case 'E': strcpy(NdFComplet,Cunite); break;
		case 'S': strcpy(NdFComplet,Sunite); break;
		case 'U': strcpy(NdFComplet,Uunite); break;
		case 'Z': strcpy(NdFComplet,Zunite); break;
		case 'F': strcpy(NdFComplet,Funite); break;
	}

	strcat(NdFComplet,Chemin);
	strcat(NdFComplet,Pseudo);
	strcat(NdFComplet,Extension);
	printf("Voici votre fichier:\n");
	puts(NdFComplet);
}
void CreationdeFichier()
{
	int i,x,point;
	char reponse;
	x=sizeof(point);

	NomDeFichier();

	AdrOuv = fopen(NdFComplet,"r");
	if(AdrOuv)
	{
		printf("Attention ce fichier existe deja, voulez-vous l'ecraser ? (Y ou N)\n");
		fflush(stdin);scanf("%c",&reponse);
		reponse=toupper(reponse);
		if(reponse != 'Y')
			NomDeFichier();
	}
	fclose(AdrOuv);

	AdrOuv = fopen(NdFComplet,"w");
	for(i=0;i<16;i++)
	{
		point = tabscore[i].pointjoueur;
		fwrite(&point,x,1,AdrOuv);
	}
	fwrite(&Nbr_Lance,x,1,AdrOuv);
	printf("Fichier sauvegarde !\nMerci d'avoir joue ! A bientot !");
	fclose(AdrOuv);
}
void ChargerPartie()
{
	int x,point,cpt=0;
	x=sizeof(point);

	NomDeFichier();

	AdrCharge=fopen(NdFComplet,"r");
	if(AdrCharge)
	{
		while(fread(&point,x,1,AdrCharge),!feof(AdrCharge))
		{
			if(cpt < 16)
			{
				strcpy(tabscore[cpt].figure,tableau[cpt]);
				tabscore[cpt].pointjoueur = point;
			}
			else Nbr_Lance=point;
			cpt++;
		}
		printf("%d",Nbr_Lance);
		fclose(AdrCharge);
	}
	else
	{
		fclose(AdrCharge);
		printf("Le fichier n'existe pas !");
		ChargerPartie();
	}
}
