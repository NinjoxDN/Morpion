#include "graphics.h"

int main(int argc, char** argv)
{
    /* ces 3 lignes servent à faire des affichages
    dans la console ... en plus de la fenêtre graphique */
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

	/* déclaration des variables */
	POINT P1;
	POINT P2;

	/* Initialisation de la fenètre graphique */
	init_graphics(900,600);

	/* Taper votre code ici */
	P1.x = 100;
	P1.y = 90;
	P2.x = 200;
	P2.y = 300;
	draw_fill_rectangle(P1, P2, vert);

	P1.x = 10;
	P1.y = 10;
	P2.x = 400;
	P2.y = 500;
	draw_line(P1,P2,rouge);

	P1.x = 300;
	P1.y = 350;
	draw_circle(P1,100, magenta);

	P1.x = 420;
	P1.y = 400;
	draw_fill_circle(P1,150, blanc);
	/* Fin de votre code */

	/* permet d'attendre un appui sur Echap avant de fermer la fenètre graphique */
	wait_escape();

	/* fin du programme */
	exit(0);
}
