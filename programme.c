#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dames.h"

int main(int argc, char *argv[])
{
	struct game *game;
	printf("Bonjour, voulez-vous commencer une nouvelle partie ? (oui/non)");
	char buffer[20];
	char o[]="oui";
	char n[]="non";
	fread(buffer, 4, 1, stdin);
	if (strcmp(buffer,o)) 
		{
		game=new_game(10,10);
		}
	else if (strcmp(buffer,n))
		{
		printf("Voulez-vous recharger la dernière partie? (oui/non)");
		fread(buffer, 4, 1, stdin);
		if (strcmp(buffer,o))
			{
			game=load_game(10,10,game->board,game->cur_player); // game != game
			}
		else if (strcmp(buffer,n))
			{
			printf("Merci, au revoir :)");
			return 1;
			}
		}
	struct move move;
	while (apply_moves(game,&move)!=1)
		do {
			if (game->cur_player == PLAYER_BLACK)
				{
				print_board(game);
				printf("C'est au tour du joueur noir, de quelle case démarre le pion/dame que vous voulez bouger? ((x,y))");
				fread(buffer, 6, 1, stdin);
				struct coord c_old={buffer[1],buffer[3]};
				char s[]="stop";
				printf("Quelles sont les coordonnées suivantes? ((x,y))");
				fread(buffer, 6, 1, stdin);
				struct coord c_new;
				int i=0;					
				while (!strcmp(buffer,s))
					do {
					c_new.x=(int)buffer[1];
					c_new.y=(int)buffer[3];
					struct move_seq seq_i={&seq_(i+1),c_old,c_new}; // comment initialiser seq_(i+1) ???
					c_old=c_new;
					i++;
					printf("Quelles sont les coordonnées suivantes? ((x,y)/stop)");
					fread(buffer, 6, 1, stdin);
					}
				struct move move1={NULL,&seq_0};
				game->cur_player= PLAYER_WHITE;
				}
			else if (game->cur_player == PLAYER_WHITE)
				{
				print_board(game);
				printf("C'est au tour du joueur blanc, de quelle case démarre le pion/dame que vous voulez bouger? ((x,y))");
				fread(buffer, 6, 1, stdin);
				struct coord c_old={buffer[1],buffer[3]};
				char s[]="stop";
				printf("Quelles sont les coordonnées suivantes? ((x,y))");
				fread(buffer, 6, 1, stdin);
				struct coord c_new;
				int i=0;					
				while (!strcmp(buffer,s))
					do {
					c_new.x=(int)buffer[1];
					c_new.y=(int)buffer[3];
					struct move_seq seq_i={&seq_(i+1),c_old,c_new}; // comment initialiser seq_(i+1) ???
					c_old=c_new;
					i++;
					printf("Quelles sont les coordonnées suivantes? ((x,y)/stop)");
					fread(buffer, 6, 1, stdin);
					}
				struct move move1={NULL,&seq_0};
				game->cur_player= PLAYER_BLACK;
				}
		}
	if (game->cur_player == PLAYER_WHITE) {printf("Bravo, le joueur blanc a gagné la partie !");}
	else if (game->cur_player == PLAYER_BLACK) {printf("Bravo, le joueur noir a gagné la partie !");}
	else 
		{
		printf("Erreur, relancer le jeu");
		return -1;
		}
	return 1;
}