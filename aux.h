/*
 * Fonction allouant l'espace mémoire pour un "game"
 *
 * @xsize taille: du jeu pour les abscisses (i.e. nombre de colonnes)
 * @ysize taille: du jeu pour ordonnées (i.e. nombre de lignes)
 * @cur_player: joueur actuel (PLAYER_WHITE ou PLAYER_BLACK)
 */
#include <stdbool.h>
extern struct game create_game(int xsize,int ysize,int cur_player);

/*Fonction qui indique si la case est occupée par un pion ou une dame noire*/
extern bool is_Black(int x, int y, struct game *game);

/*Fonction qui indique si la case est occupée par un pion ou une dame blanche*/
extern bool is_White(int x, int y , struct game *game);

/*Fonction qui indique si la pièce est une dame ou pas*/
bool is_Dame (int x, int y, struct game *game);

