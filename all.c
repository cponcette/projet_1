#ifndef _DAMES_H
#define _DAMES_H

#define PLAYER_BLACK    0
#define PLAYER_WHITE    1

/*
 * Structure du jeu.
 * @board représente le plateau de jeu. Chaque case est représentée par
 *         une valeur entière dont la signification est la suivante:
 *         [...|C|T|P] sont les 3 bits de poid faible de chaque valeur
 *         entière. Le bit C est le bit de couleur: 0 = noir, 1 = blanc.
 *         Le bit T est le bit de type de pièce: 0 = pion, 1 = dame.
 *         Le bit P est le bit de présence: 0 = case vide, 1 = case remplie.
 *         board[i][j] représente donc l'état de la case aux coordonnées (i,j).
 * @xsize et @ysize stockent la taille du jeu
 * @moves enregistre la liste des mouvements effectués
 * @cur_player enregistre le joueur actuel (i.e. qui doit effectuer le prochain mouvement)
 *             (PLAYER_BLACK ou PLAYER_WHITE)
 */
struct game {
    int **board;
    int xsize, ysize;

    struct move *moves;
    int cur_player;
};

/* Coordonnées */
struct coord {
    int x, y;
};

/*
 * Liste de la séquence d'un mouvement
 */
struct move_seq {
    struct move_seq *next;
    struct coord c_old;     /* coordonnées de départ */
    struct coord c_new;     /* coordonnées de destination */

    /*
     * Les champs suivants ne sont utilisés que lorsque l'élément fait partie
     * des mouvements effectués dans game->moves.
     *
     * @piece_value est la valeur entière d'une pièce capturée lors du mouvement.
     *              0 si pas de pièce capturée.
     * @piece_taken contient les coordonnées de la pièce capturée
     * @old_orig contient la valeur entière de la pièce se situant en @c_old avant
     *           l'exécution du mouvement.
     */
    int piece_value;
    struct coord piece_taken;
    int old_orig;
};

/*
 * Liste de mouvements
 */
struct move {
    struct move *next;
    struct move_seq *seq;
};

/*
 * new_game
 * Créer un nouveau jeu avec la position initiale
 *
 * @xsize: taille du jeu pour les abscisses (i.e. nombre de colonnes)
 * @ysize: taille du jeu pour les ordonnées (i.e. nombre de lignes)
 * @return: Pointeur vers la structure du jeu ou NULL si erreur
 */
extern struct game *new_game(int xsize, int ysize);

/*
 * load_game
 * Charger un jeu depuis une position donnée
 *
 * @xsize: taille du jeu pour les abscisses (i.e. nombre de colonnes)
 * @ysize: taille du jeu pour les ordonnées (i.e. nombre de lignes)
 * @board: tableau à deux dimensions représentant l'état du jeu
 * @cur_player: joueur actuel (PLAYER_WHITE ou PLAYER_BLACK)
 * @return Pointeur vers la structure du jeu ou NULL si erreur
 */
extern struct game *load_game(int xsize, int ysize, const int **board, int cur_player);

/*
 * free_game
 * Libérer les ressources allouées à un jeu
 *
 * @game: pointeur vers la structure du jeu
 */
extern void free_game(struct game *game);

/*
 * apply_moves
 * Effectuer des mouvements
 *
 * @game: pointeur vers la structure du jeu
 * @moves: liste chainée de mouvements à effectuer
 * @return: -1 si erreur (e.g. mouvement invalide), 0 si mouvements valides, 1 si jeu terminé (game->cur_player est le gagnant)
 */
extern int apply_moves(struct game *game, const struct move *moves);

/*
 * is_move_seq_valid
 * Vérifier si une séquence d'un mouvement est valide. La fonction ne MODIFIE PAS l'état du jeu !
 * 
 * @game: pointeur vers la structure du jeu
 * @seq: séquence du mouvement à vérifier
 * @prev: séquence précédent immédiatement la séquence à vérifier, NULL s'il @seq est la première séquence du mouvement
 * @taken: pointeur vers des coordonnées qui seront définies aux coordonnées de la pièce prise s'il en existe une
 * @return: 0 si mouvement invalide, 1 si déplacement uniquement, 2 si capture
 */
extern int is_move_seq_valid(const struct game *game, const struct move_seq *seq, const struct move_seq *prev, struct coord *taken);

/*
 * undo_moves
 * Annule des mouvements et remet l'état du jeu correspondant
 *
 * @game: pointeur vers la structure du jeu
 * @n: nombre de coups à annuler. Si n > nombre total de mouvements, alors ignorer le surplus.
 * @return: 0 si OK, -1 si erreur
 */
extern int undo_moves(struct game *game, int n);

/*
 * print_board
 * Affiche l'état du jeu sur le terminal
 *
 * @game: pointeur vers la structure du jeu
 */
extern void print_board(const struct game *game);

#endif

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

#include <stdlib.h>
#include <stdio.h>
 
#define PION_NOIR "O"
#define PION_BLANC "X"
#define DAME_NOIRE "@"
#define DAME_BLANCHE "Q"

struct game create_game(int xsize,int ysize,int cur_player){/*Fonction allouant l'espace mémoire pour un "game"*/
 struct game g1 = malloc(sizeof(struct game)){
 g1->xsize = xsize;
 g1->ysize = ysize;
 g1->move = NULL;
 g1->cur_player = cur_player;
 g1->board = (**int) board(xsize * ysize * sizeof(int))
 }
}
/*
 * new_game
 * Créer un nouveau jeu avec la position initiale
 *
 * @xsize: taille du jeu pour les abscisses (i.e. nombre de colonnes)
 * @ysize: taille du jeu pour les ordonnées (i.e. nombre de lignes)
 * @return: Pointeur vers la structure du jeu ou NULL si erreur
 */
struct game *new_game(int xsize, int ysize)/*Cette fonction n'est définie que pour un damier classique, de dimension 10x10. On dispose des pions noirs sur les cases dont
l'indice i est impair et l'indice j pair ainsi que sur les cases ou c'est l'inverse (indice i pair et j impair). On laisse les lignes d'indice 4 et 5 vides et puis on réitère la première méthode sur les lignes restantes avec les pions blancs.*/
{
struct game *g = create_game(xsize, ysize, PLAYER_WHITE);  
 for(int i=0; i<10 ;i++){
  for(int j=0; j<10; j++){
   if(!((i%2)== 0) && (j%2) == 0){
    if(j<4){
     g->board[i][j] = 00000001;
    } 
    else if (j>5){
     g->board[i][j] = 00000101;
    }
    else {
     g->board[i][j] = 00000000;
    }
   }
   else if ((i%2)==0 && !((j%2)==0))){
    if(j<4){
     g->board[i][j] = 00000001;
    }
    else if (j>5){
     g->board[i][j] = 00000101;
    }
    else {
     g->board[i][j] = 00000000;
    }
   }
   else { 
    g->board[i][j] = 00000000;
   }
  }
 }
return *g; 
}

/*
 * load_game
 * Charger un jeu depuis une position donnée
 *
 * @xsize: taille du jeu pour les abscisses (i.e. nombre de colonnes)
 * @ysize: taille du jeu pour les ordonnées (i.e. nombre de lignes)
 * @board: tableau à deux dimensions représentant l'état du jeu
 * @cur_player: joueur actuel (PLAYER_WHITE ou PLAYER_BLACK)
 * @return Pointeur vers la structure du jeu ou NULL si erreur
 */
struct game *load_game(int xsize, int ysize, const int **board, int cur_player){
 struct game g1 = malloc(sizeof(struct game)){
  g1->xsize = xsize;
  g1->ysize = ysize;
  g1->move = NULL;
  g1->cur_player = cur_player;
  g1->board = **board;
 }
return *g1;
} 

/*
 * free_game
 * Libérer les ressources allouées à un jeu
 *
 * @game: pointeur vers la structure du jeu
 */
void free_game(struct game *game){
 free(game->board);
 free(game->move);
 free(game->xsize);
 free(game->ysize);
 free(game->cur_player);
 free(game);
}

bool is_move_seq_valid(const struct game *game, const struct move_seq *seq, const struct move_seq *prev, struct coord *taken){
 struct game exemple = create_game(game->xsize, game->ysize, game->cur_player);
  if(!((prev->c_new.x == seq->c_old.x) && (prev->c_new.y == seq->c_old.y))){
   return 0;
  }
  else{
   if(((seq->c_new.x <= 9) && (seq->c_new.y <= 9)) && ((game->board[seq->c_new.x][seq->c_new.y]) == 00000000)){ 
    if(is_Black(seq->c_old.x, seq->c_old.y, game)){
     if(((seq->c_new.x == (seq->c_old.x) +1) && (seq->c_new.y == seq->c_old +1)) || ((seq->c_new.x == seq->c_old.x -1) && (seq->c_new.y == seq->c_new.y +1))){
      return 1;
     }
     else if(((seq->c_new.x == (seq->c_old.x) -2) && (seq->c_new.y == seq->c_new.y +2)) || ((seq->c_new.x == (seq->c_old.x) +2) && (seq->c_new.y == seq->c_old +2))){
      if(is_White(seq->c_old.x -1, seq->c_old.y +1, game) || is_White(seq->c_old.x -1, seq->c_old.y -1, game)){
       taken->x = seq->c_old.x -1;
       taken->y = seq->c_old.y +1;
       return 2;
      }
      else if(is_White(seq->c_old.x +1, seq->c_old.y +1, game)|| is_White(seq->c_old.x +1, seq->c_old.y -1, game)){
       taken->x = seq->c_old.x +1;
       taken->y = seq->c_old.y +1;
       return 2;
      }
      else if((((seq->c_new.x)-(seq->c_old.x) > 2) || ((seq->c_old.y)-(seq->c_new.y) > 2)))){
      if(((seq->c_new.x)-(seq->c_old.x) == (seq->c_old.y)-(seq->c_new.y)) || ((seq->c_old.x)-(seq->c_new.x) == (seq->c_old.y)-(seq->c_new.y))){
       if(((seq->c_old.x) > (seq->c_new.x)) && ((seq->c_old.y) > (seq->c_new.y))){
        for (int i=0; i<((seq->c_old.x)-(seq->c_new.x)) ; i++){
         if(is_White(seq->c_new.x +i, seq->c_new.y +i, game) && (game->board[(seq->c_new.x+i)+1][(seq->c_new.y+i)+1] == 00000000)){
          taken->x = (seq->c_new.x)+i;
          taken->y = (seq->c_new.y)+i;
          return 2;
         }
         else{/*Ajouter si 2 pièces sont l'une derrière l'autre*/
          return 1;
         }
        }
       }
       else if(((seq->c_old.x) < (seq->c_new.x)) && ((seq->c_old.y) > (seq->c_new.y))){
        for (int i=0; i<((seq->c_new.x)-(seq->c_old.x)) ; i++){
         if(is_White(seq->c_old.x +i, seq->c_new.y +i, game) && (game->board[(seq->c_old.x+i)+1][(seq->c_new.y+i)+1] == 00000000)){/*A modifier*/
          taken->x = (seq->c_old.x)+i;
          taken->y = (seq->c_new.y)+i;
          return 2;
         }
         else{
          return 1;
         }
        }
       }
      }
      else if(((seq->c_new.x)-(seq->c_old.x) == (seq->c_new.y)-(seq->c_old.y)) || ((seq->c_old.x)-(seq->c_new.x) == (seq->c_new.y)-(seq->c_old.y))){
       if(((seq->c_old.x) > (seq->c_new.x)) && ((seq->c_old.y) < (seq->c_new.y))){
        for(int i=0; i<((seq->c_old.x)-(seq->c_new.x)); i++){
         if(is_White(seq->c_new.x +i, (seq->c_old.y)+i , game) && (game->board[(seq->c_new.x+i)+1][(seq->c_old.y+i)+1] == 00000000)){
          taken->x = (seq->c_new.x)+i;
          taken->y = (seq->c_old.y)+i;
          return 2;
         }
         else{
          return 1;
         }
        }
       }
       else if(((seq->c_old.x) < (seq->c_new.x)) && ((seq->c_old.y) < (seq->c_new.y))){
        for (int i=0; i<((seq->c_new.x)-(seq->c_old.x)); i++){
         if(is_White(seq->c_new.x +i, seq->c_new.y +i, game) && (game->board[(seq->c_old.x+i)+1][(seq->c_old.y+i)+1] == 00000000)){
          taken->x = seq->c_old.x+i;
          taken->y = seq->c_old.y+i;
          return 2;
         }
         else{
          return 1;
         }
        }
       }
      } 
      else{
       return 0;
      }
     }  
     
    }       
  
    else if(is_White(seq->c_old.x,seq->c_old.y, game)){
     if((seq->c_new.x == (seq->c_old.x) +1) && (seq->c_new.y == (seq->c_old.y) -1) || ((seq->c_new.x == (seq->c_old.x) -1) && (seq->c_new.y == (seq->c_old.y) -1))){
      return 1;
     }
     else if(((seq->c_new.x == (seq->c_old.x) -2) && (seq->c_new.y == seq->c_new.y -2)) || ((seq->c_new.x == (seq->c_old.x) +2) && (seq->c_new.y == seq->c_new.y -2))){
      if(is_Black(seq->c_old.x -1, seq->c_old.y -1, game)|| is_Black(seq->c_old.x -1, seq->c_old.y +1, game)){
       taken->x = seq->c_old.x +1;
       taken->y = seq->c_old.y -1;
       return 2;
      } 
      else if(is_Black(seq->c_old.x +1, seq->c_old.y -1, game)|| is_Black(seq->c_old.x +1, seq->c_old.y +1, game)){
       taken->x = seq->c_old.x +1;
       taken->y = seq->c_old.y -1;
       return 2;
      }
     else if((((seq->c_new.x)-(seq->c_old.x) > 2) || ((seq->c_old.y)-(seq->c_new.y) > 2)))){
      if(((seq->c_new.x)-(seq->c_old.x) == (seq->c_old.y)-(seq->c_new.y)) || ((seq->c_old.x)-(seq->c_new.x) == (seq->c_old.y)-(seq->c_new.y))){
       if(((seq->c_old.x) > (seq->c_new.x)) && ((seq->c_old.y) > (seq->c_new.y))){
        for (int i=0; i<((seq->c_old.x)-(seq->c_new.x)) ; i++){
         if(is_Black(seq->c_new.x +i, seq->c_new.y +i, game) && (game->board[(seq->c_new.x+i)+1][(seq->c_new.y+i)+1] == 00000000)){/* A modifier*/
          taken->x = (seq->c_new.x)+i;
          taken->y = (seq->c_new.y)+i;
          return 2;
         }
         else{
          return 1;
         }
        }
       }
       else if(((seq->c_old.x) < (seq->c_new.x)) && ((seq->c_old.y) > (seq->c_new.y))){
        for (int i=0; i<((seq->c_new.x)-(seq->c_old.x)) ; i++){
         if(is_Black(seq->c_old.x +i, seq->c_new.y +i, game) && (game->board[(seq->c_old.x+i)+1][(seq->c_new.y+i)+1] == 00000000)){/*A modifier*/
          taken->x = (seq->c_old.x)+i;
          taken->y = (seq->c_new.y)+i;
          return 2;
         }
         else{
          return 1;
         }
        }
       }
      }
      else if(((seq->c_new.x)-(seq->c_old.x) == (seq->c_new.y)-(seq->c_old.y)) || ((seq->c_old.x)-(seq->c_new.x) == (seq->c_new.y)-(seq->c_old.y))){
       if(((seq->c_old.x) > (seq->c_new.x)) && ((seq->c_old.y) < (seq->c_new.y))){
        for(int i=0; i<((seq->c_old.x)-(seq->c_new.x)); i++){
         if(is_Black(seq->c_new.x +i, (seq->c_old.y)+i , game) && (game->board[(seq->c_new.x+i)+1][(seq->c_old.y+i)+1] == 00000000)){
          taken->x = (seq->c_new.x)+i;
          taken->y = (seq->c_old.y)-i;
          return 2;
         }
         else{
          return 1;
         }
        }
       }
       else if(((seq->c_old.x) < (seq->c_new.x)) && ((seq->c_old.y) < (seq->c_new.y))){
        for (int i=0; i<((seq->c_new.x)-(seq->c_old.x)); i++){
         if(is_Black(seq->c_old.x +i, seq->c_old.y +i, game) && (game->board[(seq->c_old.x+i)+1][(seq->c_old.y+i)+1] == 00000000)){
          taken->x = seq->c_old.x+i;
          taken->y = seq->c_old.y+i;
          return 2;
         }
         else{
          return 1;
         }
        }
       }
      } 
      else{
       return 0;
      }
     }   
     else{
       return 0;
     }
    }
   }
   else{
    return 0;
   }
  }  
}  


bool is_Black(int x, int y, struct game *game){/*Fonction qui indique si la case est occupée par un pion ou une dame noire*/
 if((game->board[x][y] == 00000001) || (game->board[x][y] == 00000011){
  return 1;
 }
 else {
  return 0;
 }
}

bool is_White(int x, int y , struct game *game){/*Fonction qui indique si la case est occupée par un pion ou une dame blanche*/
 if((game->board[x][y] == 00000101) || (game->board[x][y] == 00000111)){
  return 1;
 }
 else{
  return 0;
 }
}


bool is_Dame (int x, int y, struct game *game);{/*Fonction qui indique si la pièce est une dame ou pas*/
  if((game->board[x][y] == 00000011) || (game->board[x][y] == 00000111)){
   return 1;
  }
  else{
   return 0;
  }
}


/*
 * apply_moves
 * Effectuer des mouvements
 *
 * @game: pointeur vers la structure du jeu
 * @moves: liste chainée de mouvements à effectuer
 * @return: -1 si erreur (e.g. mouvement invalide), 0 si mouvements valides, 1 si jeu terminé (game->cur_player est le gagnant)
 */
int apply_moves(struct game *game, const struct move *moves){
  while(moves->next != NULL)do{
   while(moves->seq != NULL)do{
    if(is_move_seq_valid() == 1){
     if(is_Black(move->seq->c_old.x,move->seq->c_old.y, game)){
      if(is_Dame(move->seq->c_old.x, move->seq->c_old.y, game)){
       game->board[move->seq->c_old.x][move->seq->c_old.y] = 00000000;
       game->board[move->seq->c_new.x][move->seq->c_new.y] = 00000011;
      }
      else{
       game->board[move->seq->c_old.x][move->seq->c_old.y] = 00000000;
       game->board[move->seq->c_new.x][move->seq->c_new.y] = 00000001;
      }
     }
     else if(is_White(move->seq->c_old.x,move->seq->c_old.y, game)){
      if(is_Dame(move->seq->c_old.x, move->seq->c_old.y, game)){
       game->board[move->seq->c_old.x][move->seq->c_old.y] = 00000000;
       game->board[move->seq->c_new.x][move->seq->c_new.y] = 00000111;
      }
      else{
       game->board[move->seq->c_old.x][move->seq->c_old.y] = 00000000;
       game->board[move->seq->c_new.x][move->seq->c_new.y] = 00000101;
      }
     else{
      return -1;
     }
    }
    else if(is_move_seq_valid() == 2){
     if(is_Black(move->seq->c_old.x, move->seq->c_old.y, game)){
      if(is_Dame(move->seq->c_old.x, move->seq->c_old.y, game)){
       game->board[move->seq->c_old.x][move->seq->c_old.y] = 00000000;
       game->board[move-<seq->c_new.x][move->seq->c_new.y] = 00000011;
       game->board[taken->x][taken->y] = 00000000;
      }
      else{
       game->board[move->seq->c_old.x][move->seq->c_old.y] = 00000000;
       game->board[move->seq->c_new.x][move->seq->c_new.y] = 00000001;
       game->board[taken->x][taken->y] = 00000000;
      }
     }
     else if(is_White(move->seq->c_old.x, move->seq->c_old.y, game)){
      if(is_Dame(move->seq->c_old.x, move->seq->c_old.y, game)){
       game->board[move->seq->c_old.x][move->seq->c_old.y] = 00000000;
       game->board[move->seq->c_new.x][move->seq->c_new.y] = 00000111;
       game->board[taken->x][taken->y] = 00000000;
      }
      else{
       game->board[move->seq->c_old.x][move->seq->c_old.y] = 00000000;
       game->board[move->seq->c_new.x][move->seq->c_new.y] = 00000101;
       game->board[taken->x][taken->y] = 00000000;
      }
     else{
      return -1;
     }
    }
    else{
     return 0;
    }
   }
  }
}  

/*
 * undo_moves
 * Annule des mouvements et remet l'état du jeu correspondant
 *
 * @game: pointeur vers la structure du jeu
 * @n: nombre de coups à annuler. Si n > nombre total de mouvements, alors ignorer le surplus.
 * @return: 0 si OK, -1 si erreur
 */
int undo_moves(struct game *game, int n){
 

/*
 * print_board
 * Affiche l'état du jeu sur le terminal
 *
 * @game: pointeur vers la structure du jeu
 */
void print_board(const struct game *game){
int i, j;
 for(i=0;i<(game->xsize);i++) {
  for(j=0;j<(game->ysize);j++) {
       printf("|");
        if(game->board[i][j] == 00000000){
         printf("%s", " ");
        }
        else if(game->board[i][j] == 00000101){
         printf("%s", "X");
        }
        else if(game->board[i][j] == 00000001){
         printf("%s", "O");
        }
        else if(game->board[i][j] == 00000101){
         printf("%s", "@");
        }
        else if(game->board[i][j] == 00000111){
         printf("%s", "Q");
        }
        printf("|");
  }
  printf("\n");
 } 
}
 



#include "CUnit.h"

struct game *game1;


void test_new_game(void)
{
	print_board(game1);
	CU_ASSERT_PTR_NOT_NULL(game1);
}

void test_load_game(void)
{
	struct coord c1={1,6};
	struct coord c2={2,5};
	struct coord c3={4,3};
	struct coord c4={3,4};
	struct coord c5={2,5};
	struct coord c6={4,3};
	struct move_seq seq1={NULL,c1,c2};
	struct move_seq seq2={NULL,c3,c4};
	struct move_seq seq3={NULL,c5,c6};
	struct move move3={NULL,&seq3};
	struct move move2={&move3,&seq2};
	struct move move1={&move2,&seq1};
	apply_moves(game1,&move1);
	struct game *game2;
	game2=load_game(10,10,(const int **) game1->board,game1->cur_player);
	CU_ASSERT_PTR_NOT_NULL(game2);
	print_board(game1);
	print_board(game2);
	free_game(game2);
}

void test_apply_moves(void) // a complèter !!!
{	
	struct coord c1={3,2};
	struct coord c2={5,4};
	struct move_seq seq4={NULL, c1, c2};
	struct move move4={NULL, &seq4};
	print_board(game1);
	CU_ASSERT_FALSE(apply_moves(game1, &move4));
	print_board(game1);
}	

void test_is_move_seq_valid(void)
{
	struct move_seq seq5={NULL,(3,6),(4,5)};
	struct move move5={NULL,&seq5};
	apply_moves(game1,&move5);
	struct move_seq seq6={NULL,(5,4),(5,5)}; // mouvement invalide
	struct move_seq seq7={NULL,(5,4),(6,5)}; // déplacement uniquement
	struct move_seq seq8={NULL,(5,4),(3,6)}; // capture
	struct coord *taken;
	CU_ASSERT(is_move_seq_valid(game1, &seq6, &seq5, taken));
	CU_ASSERT_EQUAL(is_move_seq_valid(game1,&seq7,&seq5,taken), 1);
	CU_ASSERT_EQUAL(is_move_seq_valid(game1,&seq8,&seq5,taken), 2);
}

void test_undo_moves(void)
{
	print_board(game1);
	CU_ASSERT_FALSE(undo_moves(game1,1));
	print_board(game1);
	CU_ASSERT_FALSE(undo_moves(game1,7));
	print_board(game1);
}

int setup(void)
{
	game1=new_game(10,10);
	if ( NULL == game1 ) return 42;
	return 0;
}

int teardown(void)
{
	free_game(game1);
	
	return 0;
}



int main(int argc, char *argv[])
{
	CU_initialize_registry();
	if (CUE_SUCCESS != CU_initialize_registry()); // initialisation du catalogue
		{return CU_get_error();}
	
	CU_pSuite pSuite = NULL ;

	pSuite = CU_add_suite("ma_suite", setup, teardown); // ajout d'une suite de tests au catalogue
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Test new game", test_new_game)) ||  // ajout des tests à la suite de tests
	    (NULL == CU_add_test(pSuite, "Test load game", test_load_game)) ||
	    (NULL == CU_add_test(pSuite, "Test apply moves", test_apply_moves)) ||
	    (NULL == CU_add_test(pSuite, "Test is move seq valid", test_is_move_seq_valid)) ||
	    (NULL == CU_add_test(pSuite, "Test undo moves", test_undo_moves)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests(); // fait tourner les tests
	CU_basic_show_failures(CU_get_failure_list()); // affiche le rapport

	CU_cleanup_registry(); // libération des ressources

	return 0;
}













