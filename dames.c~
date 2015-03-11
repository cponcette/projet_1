#include <stdlib.h>
#include <stdio.h>
#include "dames.h"
 
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
 
















