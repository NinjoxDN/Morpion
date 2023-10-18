#include "graphics.h"

/*********************************************************************
 * définition de constantes :
 * Dans la suite du code :
 * - CASE est une valeur constante qui définit la largeur et la hauteur
 * des cases
 * - N est une valeur constante qui définit la taille du jeu (nombre de
 *   cases par lignes et colonnes pour un jeu N*N
 *********************************************************************/

#define CASE 200
#define N 3

#define JOUEUR_1 1
#define JOUEUR_2 -1
#define NON_JOUEE 0
#define JOUEE 3

/*********************************************************************
 * Variables globales
 * - a_qui_de_jouer : variable qui donne le joueur courant
 * - jeu : tableau dans lequel on stocke les coups joués
 ********************************************************************/

int a_qui_de_jouer; // variable qui donne le joueur courant JOUEUR_1 ou JOUEUR_2
int jeu[N][N]; // tableau dans lequel on stocke l'état du jeu

/* ----------------------------------------------------------------- */
/* 1) AFFICHAGE DE LA GRILLE ...                                     */
/* ----------------------------------------------------------------- */

void dessine_ligne_verticales(COULEUR C) /* dessine les lignes verticales du quadrillage */
{
    POINT P;
    POINT P1;
    int i;

    for (i=1; i<N; i=i+1)
    {
        P.x = i*CASE;
        P.y = 0;

        P1.x = i*CASE;
        P1.y = N*CASE;

        draw_line(P,P1,C);
    }
}

void dessine_ligne_horizontales(COULEUR C) /* dessine les lignes horizontales du quadrillage */
{
    POINT P;
    POINT P1;
    int i;

    for (i=1; i<N; i=i+1)
    {
        P.x = 0;
        P.y = i*CASE;

        P1.x = N*CASE;
        P1.y = i*CASE;

        draw_line(P,P1,C);
    }
}

void dessine_quadrillage(COULEUR C) /* dessine la grille de jeu de N*N Cases */
{
    dessine_ligne_verticales(C);
    dessine_ligne_horizontales(C);
}

/* ----------------------------------------------------------------- */
/* 2) AFFICHAGE DES CROIX ET CERCLES SELON LE JOUEUR ...             */
/* ----------------------------------------------------------------- */
POINT locale_centre(POINT P) /* calcule le centre de la case oû l'on a joué(à laquelle appartient le point P) */
{
    POINT centre;

    centre.x = (P.x / CASE) * CASE + CASE/2;
    centre.y = (P.y / CASE) * CASE + CASE/2;
    return centre;
}

void dessine_croix(POINT centre) /* dessine une croix centrée sur le point centre (oû l'on a cliqué) */
{
    POINT P1, P10;
    POINT P2, P20;
    int i;
    int Ep= 3; /* 1/2 Epaisseur de la croix */

    P1.x = centre.x - CASE/2 + CASE/10 - Ep; /* décallage des ligne pour fairre l'épaisseur */
    P1.y = centre.y - CASE/2 + CASE/10;

    P2.x = centre.x + CASE/2 - CASE/10 - Ep;
    P2.y = centre.y + CASE/2 - CASE/10;
    for (i=0;i<2*Ep+1;i=i+1)
    {
        P10.x=P1.x+i;P10.y=P1.y;
        P20.x=P2.x+i;P20.y=P2.y;
        draw_line(P10,P20,jaune);
    }

    P1.x = centre.x + CASE/2 - CASE/10 - Ep;
    P1.y = centre.y - CASE/2 + CASE/10;

    P2.x = centre.x - CASE/2 + CASE/10 - Ep;
    P2.y = centre.y + CASE/2 - CASE/10;

    for (i=0;i<2*Ep+1;i=i+1)
    {
        P10.x=P1.x+i;P10.y=P1.y;
        P20.x=P2.x+i;P20.y=P2.y;
        draw_line(P10,P20,jaune);
    }
}
void dessine_action(POINT P) /* dessine une croix centrée sur le point centre si a_qui_de_jouer vaut JOUEUR_1
                                ou dessine un cercle centrée sur le point centre si a_qui_de_jouer vaut JOUEUR_2 */
{
    POINT D;
    int Rayon=0;
    int Ep= 3; /* 1/2 Epaisseur du cercle */
    int i;

    D = locale_centre(P);
    if (a_qui_de_jouer == JOUEUR_1)
    {
        dessine_croix(D);
    }
    else if (a_qui_de_jouer == JOUEUR_2)
    {
        for (i=0;i<2*Ep+1;i=i+1)
        {
            Rayon=CASE/2 - CASE/20 - i;
            draw_circle(D,Rayon,vertclair);
        }
    }
}
/* ----------------------------------------------------------------- */
/* 3) VALIDATION ET SAUVEGARDE DES COUPS JOUES ...                   */
/* ----------------------------------------------------------------- */
void affiche_jeu_console() /* affiche le tableau du jeu dans la console */
{
    int i,j;

    for ( i=0; i<N; i=i+1)
    {
        for (j=0; j<N; j=j+1)
        {
            printf("%2d ",jeu[i][j]);
        }
        printf("\n");
    }
}

void init_jeu() /* mets le tableau de la console à 0 */
{
    int i,j;

    for ( i=0; i<N; i=i+1)
    {
        for (j=0; j<N; j=j+1)
        {
            jeu[i][j] =0;
        }
        printf("\n");
    }
}

int est_valide(POINT P) /* vérification de si la case a déja été jouée ou pas, si elle est valide ou pas */
{

    int valide = NON_JOUEE;
    int invalide = JOUEE;

    int i,j;

    j = P.x/CASE;
    i = N-1-P.y/CASE;

    if ( jeu[i][j] == 0)
    {
        return valide ;
    }
    else if (jeu[i][j]==1 || jeu[i][j]==-1)
    {
        return invalide ;
    }
    return 0;
}

void valider_coup(POINT P) /* validation du coup joué */
{
    int i,j;

    j = P.x/CASE;
    i = N-1-P.y/CASE;

    if ( a_qui_de_jouer == JOUEUR_1)
    {
        jeu[i][j] = JOUEUR_1;
    }
    else if ( a_qui_de_jouer == JOUEUR_2)
    {
        jeu[i][j] = JOUEUR_2;
    }
}

/* ----------------------------------------------------------------- */
/* 4) FIN DU JEU SI UN JOUEUR A GAGNE ...                            */
/* ----------------------------------------------------------------- */
int somme_ligne(int i) /* calcule la somme des cases d'une ligne du tableau */
{
    int j;
    int Res;
    Res = 0;

    for (j= 0;j< N; j= j+1)
    {
        Res = Res + jeu[i][j];
    }
    return Res;
}


int somme_colonne(int j) /* calcule la somme des cases d'une colonne du tableau */
{
    int i;
    int Res;
    Res = 0;

    for (i= 0;i< N; i= i+1)
    {
        Res = Res + jeu[i][j];
    }
    return Res;
}

int somme_diago() /* calcule la somme de la diagonale du tableau */
{
    int i;
    int Res;
    Res = 0;

    for (i= 0;i< N; i= i+1)
    {
        Res = Res + jeu[i][i];
    }
    return Res;
}

int somme_anti_diago() /* calcule la somme de l'anti-diagonale du tableau */
{
    int i,j;
    int Res;
    Res = 0;
    i = 0;

    for (j= 0;j< N; j= j+1)
    {
        i = N-1-j;
        Res = Res + jeu[i][j];
    }
    return Res;
}

int qui_a_gagne() /* arrête le jeu lors d'une victoire */
{
	int gagnant = 0;
	int x,z,y,r;

	for (x= 0; x< N; x= x+1) /* calcule toute les lignes de la grille de jeu et vérifie si il y a victoire ou non du JOUEUR_1 ou du JOUEUR_2 */
    {
        z= somme_ligne(x);
        if (z == N)
        {
            gagnant = JOUEUR_1;
            return gagnant;
        }
        else if (z == -N)
        {
            gagnant = JOUEUR_2;
            return gagnant;
        }
    }

	for (x= 0; x< N; x= x+1) /* calcule toute les colonnes de la grille de jeu et vérifie si il y a victoire ou non du JOUEUR_1 ou du JOUEUR_2 */
    {
        z= somme_colonne(x);
        if (z == N)
        {
            gagnant = JOUEUR_1;
            return gagnant;
        }
        else if (z == -N)
        {
            gagnant = JOUEUR_2;
            return gagnant;
        }
    }
    y= somme_diago(); /* calcule la diagonale de la grille de jeu et vérifie si il y a victoire ou non du JOUEUR_1 ou du JOUEUR_2 */
    if (y == N)
        {
            gagnant = JOUEUR_1;
            return gagnant;
        }
        else if (y == -N)
        {
            gagnant = JOUEUR_2;
            return gagnant;
        }

    r= somme_anti_diago(); /* calcule calcule l'anti-diagonale de la grille de jeu et vérifie si il y a victoire ou non du JOUEUR_1 ou du JOUEUR_2*/
    if (r == N)
        {
            gagnant = JOUEUR_1;
            return gagnant;
        }
        else if (r == -N)
        {
            gagnant = JOUEUR_2;
            return gagnant;
        }

	return gagnant;
}
/*********************************************************************
 * fonction principale
 *********************************************************************/
/* int  main(int argc, char ** argv) */
int  main()
{
	int i;
	POINT P;
	int gagnant;

    /* ces 3 lignes servent à faire des affichages
    dans la console ... en plus de la fenêtre graphique
	- à commenter sous ubuntu
	- à decommenter sous windows */
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

	/* création d'une fenètre graphique */
	init_graphics(N*CASE, N*CASE);

	/* affichage du quadrillage */
	dessine_quadrillage(magenta);

	/* initialisation du tableau de jeu */
	init_jeu();

	gagnant=0;
	/* moteur et affichage du jeu */
	a_qui_de_jouer = JOUEUR_1;
	for(i=0; i<N*N; i++)
	{
        /* test de validité du coup joué */
		P = wait_clic();
		while(est_valide(P) != NON_JOUEE)
		{
			P = wait_clic();
		}
		/* validation du coup joué */
		valider_coup(P);
		/* affichage du coup joué */
		dessine_action(P);

		affiche_jeu_console();

		/* test de fin de partie et arrêt du jeu le cas échéant */
		gagnant = qui_a_gagne();
		if (gagnant != 0)
		{
			wait_escape();
			break ;
		}

		/* changement de joueur */
		if (a_qui_de_jouer == JOUEUR_1)
		{
		    a_qui_de_jouer = JOUEUR_2;
		}
		else
        {
            a_qui_de_jouer = JOUEUR_1;
		}
    }

    if (gagnant == JOUEUR_1)/* Annonce du vainqueur dans la console ou match nul */
           {
               printf("\nJoueur 1 a gagne celui avec les croix\n\n");
           }
        else if (gagnant ==JOUEUR_2)
           {
                printf("\nJoueur 2 a gagne celui avec les cerles\n\n");
           }
        else
           {
               printf("\n\nMatch nul\n\n");
           }

	exit(0);
}
