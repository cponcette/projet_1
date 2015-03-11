#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dames.h"
#include "aux.h"

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
		printf("Merci, au revoir :)");
		return 1;
		}

	else {printf("Erreur, relancez le jeu");
		return -1;}

	struct move move={NULL, NULL};
	struct move move0={NULL, NULL};

	while (apply_moves(game,&move)!=1) // est-ce que le mouvement est appliqué s'il est seulement dans la condition ??
		do {
			if (move0->next==NULL)  // initialisation du premier mouvement
				{
				print_board(game);
				printf("C'est au tour du joueur noir, de quelle case démarre le pion/dame que vous voulez bouger? ( (x,y) )");
				fread(buffer, 6, 1, stdin);
				char s[]="stop";
				printf("Quelles sont les coordonnées suivantes? ( (x,y) )");
				fread(buffer, 6, 1, stdin);
				struct coordc_new={(int)buffer[1],(int)buffer[3]};
				struct move_seq seq0[NULL, c_old, c_new};

				while (!strcmp(buffer, s))
					do {
					c_new.x=(int)buffer[1];
					c_new.y=(int)buffer[3];
					struct move_seq seq={NULL, c_old, c_new};
					struct move_seq temp=seq0;
					while (temp->next != NULL)
						do {
						temp=temp->next;
						}
					temp->next = seq;
					c_old=c_new;
					printf("Quelles sont les coordonnées suivantes? ( (x,y)/stop )");
					fread(buffer, 6, A, stdin);
					}
				move0.next=&move;
				move0.seq=&seq0;
				
				}
			if (game->cur_player == PLAYER_BLACK)
				{
				print_board(game);
				printf("C'est au tour du joueur noir, de quelle case démarre le pion/dame que vous voulez bouger? ( (x,y) )");
				fread(buffer, 6, 1, stdin);
				char s[]="stop";
				printf("Quelles sont les coordonnées suivantes? ( (x,y) )");
				fread(buffer, 6, 1, stdin);
				struct coord c_new={(int)buffer[1],(int)buffer[3]};
				struct move_seq seq0={NULL, c_old, c_new}; // initialisation du premier élément
				
				while ( !strcmp(buffer, s) )
					do {
					printf("Quelles sont les coordonnées suivantes? ( (x,y)/stop )");
					fread(buffer, 6, 1, stdin);
					if ( !strcmp(buffer, s) ) // si pas de if, on risque d'essayer de mettre des lettres dans les coordonnées
						{
						c_new.x=(int)buffer[1];
						c_new.y=(int)buffer[3];
						struct move_seq seq={NULL, c_old, c_new}; // creation nouvelle sequence
						struct move_seq temp=seq0; // pointeur temporaire pour ajouter en bout de liste
						while(temp->next != NULL)
							do {
								temp=temp->next;
							}
						temp->next = seq;
						c_old = c_new; // les coordonnées d'arrivée sont les nouvelles coordonnées de départ
						}
					else {}
					}
				move->next=&seq0;
				struct move tempo=move0;
				while (tempo->next != NULL)
					{
					tempo=tempo->next;					
					}
				tempo->next = move;
				game->cur_player= PLAYER_WHITE; 
				}

			else if (game->cur_player == PLAYER_WHITE)
				{
				print_board(game);
				printf("C'est au tour du joueur blanc, de quelle case démarre le pion/dame que vous voulez bouger? ( (x,y) )");
				fread(buffer, 6, 1, stdin);
				char s[]="stop";
				printf("Quelles sont les coordonnées suivantes? ( (x,y) )");
				fread(buffer, 6, 1, stdin);
				struct coord c_new={(int)buffer[1],(int)buffer[3]};
				struct move_seq seq0={NULL, c_old, c_new}; // initialisation du premier élément
				
				while ( !strcmp(buffer, s) )
					do {
					printf("Quelles sont les coordonnées suivantes? ( (x,y)/stop )");
					fread(buffer, 6, 1, stdin);
					if ( !strcmp(buffer, s) ) // si pas de if, on risque d'essayer de mettre des lettres dans les coordonnées
						{
						c_new.x=(int)buffer[1];
						c_new.y=(int)buffer[3];
						struct move_seq seq={NULL, c_old, c_new}; // creation nouvelle sequence
						struct move_seq temp=seq0; // pointeur temporaire pour ajouter en bout de liste
						while(temp->next != NULL)
							do {
								temp=temp->next;
							}
						temp->next = seq;
						c_old = c_new; // les coordonnées d'arrivée sont les nouvelles coordonnées de départ
						}
					else {}
					}
				move->next=&seq0;
				struct move tempo=move0;
				while (tempo->next != NULL)
					{
					tempo=tempo->next;					
					}
				tempo->next = move;
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
