#ifndef _DAMES_C
#include <stdlib.h>
#include <stdio.h>
#include "dames.h"
#include <stdbool.h>

 
#define PION_NOIR "O"
#define PION_BLANC "X"
#define DAME_NOIRE "@"
#define DAME_BLANCHE "Q" 

struct game create_game(int xsize,int ysize,int cur_player){/*Fonction allouant l'espace mémoire pour un "game"*/
 struct game *g1 = malloc(sizeof(struct game))
 g1->xsize = xsize;
 g1->ysize = ysize;
 g1->move = NULL;
 g1->cur_player = cur_player;
 g1->board = (**int) malloc(xsize * ysize * sizeof(int));
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
 int i, j;
 for(i=0; i<10 ;i++){
  for(j=0; j<10; j++){
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
 struct game g1 = malloc(sizeof(struct game));
  g1->xsize = xsize;
  g1->ysize = ysize;
  g1->move = NULL;
  g1->cur_player = cur_player;
  g1->board = **board;
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

int is_move_seq_valid(const struct game *game, const struct move_seq *seq, const struct move_seq *prev, struct coord *taken){/*On vérifie d'abord que la séquence précédente a c_new.x,y les même que la séquence actuelle c_old.x,y. On vérifie ensuite que les pions ne sortent pas du plateau. Pour un déplacement de pion on peut avoir
x qui augmente ou diminue au choix mais y peut seulement augmenter pour un pion noir et diminuer pour un blanc. Même chose pour une prise de pion (+2 ou -2 à la place de +1/-1) sauf que cette fois-ci on peut aussi prendre en arrière donc y peut augmenter et diminuer pour les deux couleurs. Si la séquence implique un mouvement de dame, il faut vérifier que la différence des coordonnées en x et en y soit égale. Si il se trouve un pion/dame sur la trajectoire de la dame, la pièce est prise si et seulement si la case adjacente à celle-ci et dans la trajectoire de la dame est vide.*/
 struct game exemple = create_game(game->xsize, game->ysize, game->cur_player);
  if(!((prev->c_new.x == seq->c_old.x) && (prev->c_new.y == seq->c_old.y))){/*On vérifie que la séquence précédente et actuelle sont bien cohérentes*/
   return 0;
  }
  else{
   if(((seq->c_new.x <= 9) && (seq->c_new.y <= 9)) && ((game->board[seq->c_new.x][seq->c_new.y]) == 00000000)){ /*Erreur si on sort du damier*/
    if(is_Black(seq->c_old.x, seq->c_old.y, game)){
     if(((seq->c_new.x == (seq->c_old.x) +1) && (seq->c_new.y == seq->c_old.y +1)) || ((seq->c_new.x == seq->c_old.x -1) && (seq->c_new.y == seq->c_new.y +1))){/*Mouvement du pion*/
      return 1;
     }
     else if(((seq->c_new.x == (seq->c_old.x) -2) && (seq->c_new.y == seq->c_new.y +2)) || ((seq->c_new.x == (seq->c_old.x) +2) && (seq->c_new.y == seq->c_old.y +2))){
      /*Prise par un pion*/
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
      else if(seq->c_new.x-seq->c_old.x > 2 || seq->c_old.y-seq->c_new.y > 2){/*Mouvement d'une dame*/
      if(((seq->c_new.x)-(seq->c_old.x) == (seq->c_old.y)-(seq->c_new.y)) || ((seq->c_old.x)-(seq->c_new.x) == (seq->c_old.y)-(seq->c_new.y))){/*Différence des oronnées doit valloir la différence des abscisses*/
       if(((seq->c_old.x) > (seq->c_new.x)) && ((seq->c_old.y) > (seq->c_new.y))){
        int i;
        for (i=0; i<((seq->c_old.x)-(seq->c_new.x)) ; i++){
         if(is_White(seq->c_new.x +i, seq->c_new.y +i, game) && (game->board[(seq->c_new.x+i)+1][(seq->c_new.y+i)+1] == 00000000)){
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
        int i;
        for (i=0; i<((seq->c_new.x)-(seq->c_old.x)) ; i++){
         if(is_White(seq->c_old.x +i, seq->c_new.y +i, game) && (game->board[(seq->c_old.x+i)+1][(seq->c_new.y+i)+1] == 00000000)){
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
        int i;
        for(i=0; i<((seq->c_old.x)-(seq->c_new.x)); i++){
         if(is_White(seq->c_new.x +i, (seq->c_old.y)+i , game) && (game->board[(seq->c_new.x+i)+1][(seq->c_old.y+i)+1] == 00000000)){ /*On vérifie qu'il n'y a pas 2 pions qui se suivent dans la trajectoire de la dame, sans quoi pas de prise*/
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
        int i;
        for (i=0; i<((seq->c_new.x)-(seq->c_old.x)); i++){
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
    else if(is_White(seq->c_old.x,seq->c_old.y, game)){/*Même chose si le pion ou la dame est blanche*/
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
     else if(seq->c_new.x-seq->c_old.x > 2 || seq->c_old.y-seq->c_new.y > 2){
      if(((seq->c_new.x)-(seq->c_old.x) == (seq->c_old.y)-(seq->c_new.y)) || ((seq->c_old.x)-(seq->c_new.x) == (seq->c_old.y)-(seq->c_new.y))){
       if(((seq->c_old.x) > (seq->c_new.x)) && ((seq->c_old.y) > (seq->c_new.y))){
        int i;
        for (i=0; i<((seq->c_old.x)-(seq->c_new.x)) ; i++){
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
        int i;
        for (i=0; i<((seq->c_new.x)-(seq->c_old.x)) ; i++){
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
        int i;
        for(i=0; i<((seq->c_old.x)-(seq->c_new.x)); i++){
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
        int i;
        for (i=0; i<((seq->c_new.x)-(seq->c_old.x)); i++){
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
}

int is_Black(int x, int y, struct game *game){/*Fonction qui indique si la case est occupée par un pion ou une dame noire*/
 int x1= x;
 int y1 = y;
 if((game->board[x1][y1] == 00000001) || (game->board[x][y] == 00000011)){
  return 1;
 }
 else {
  return 0;
 }
}

int is_White(int x, int y , struct game *game){/*Fonction qui indique si la case est occupée par un pion ou une dame blanche*/
 int x1 = x;
 int y1 = y;
 if((game->board[x1][y1] == 00000101) || (game->board[x][y] == 00000111)){
  return 1;
 }
 else{
  return 0;
 }
}


int is_Dame (int x, int y, struct game *game){/*Fonction qui indique si la pièce est une dame ou pas*/
  int x1 = x;
  int y1 = y;
  if((game->board[x1][y1] == 00000011) || (game->board[x][y] == 00000111)){
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
int apply_moves(struct game *game, const struct move *moves){/*On parcours la structure chainée, si is_move_seq_valid a identifié un déplacement on vide la case de départ et on rempli la case destination. Si elle a identifié une prise on vide la case de départ et la case de prise, on rempli la case de destination. Dans les deux cas, si l'un des joueurs avance un pion sur la dernière ligne en coordonées y, il devient une dame. Après avoir effectué le mouvement on vérifie que le joueur qui n'a pas joué possède encore des pions, sinon fin de partie!*/
struct move *this_move = game->moves;
struct  move_seq *this_seq = game->moves->seq;
  while(this_move != NULL)do{
   while(this_seq != NULL)do{
    if(is_move_seq_valid(game, this_move->seq, NULL, NULL) == 1){/*Si le mouvement n'implique pas une prise*/
     if(is_Black(this_move->seq->c_old.x,this_move->seq->c_old.y, game)){/*Si pièce noire*/
      if(is_Dame(this_move->seq->c_old.x, this_move->seq->c_old.y, game)){
       this_seq->old_orig = 00000011;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][this_move->seq->c_new.y] = 00000011;
       this_seq = game->moves->seq->next;
      }
      else if(!(is_Dame(this_move->seq->c_old.x, this_move->seq->c_old.y, game)) && (this_move->seq->c_new.y == 9)){/*Si un pion arrive à la fin du damier, il devient une dame*/
       this_seq->old_orig = 00000001;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][9] = 00000011;
       this_seq = game->moves->seq->next;
      }
      else{
       this_seq->old_orig = 00000001;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][this_move->seq->c_new.y] = 00000001;
       this_seq = game->moves->seq->next;
      }
     }
     else if(is_White(this_move->seq->c_old.x,this_move->seq->c_old.y, game)){/*Si pièce blanche*/
      if(is_Dame(this_move->seq->c_old.x,this_move->seq->c_old.y, game)){
       this_seq->old_orig = 00000111;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][this_move->seq->c_new.y] = 00000111;
       this_seq = game->moves->seq->next;
      }
       else if(!(is_Dame(this_move->seq->c_old.x, this_move->seq->c_old.y, game)) && (this_move->seq->c_new.y == 0)){
       this_seq->old_orig = 00000101;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][0] = 00000111;
       this_seq = game->moves->seq->next;
      }
      else{
       this_seq->old_orig = 00000101;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][this_move->seq->c_new.y] = 00000101;
       this_seq = game->moves->seq->next;
      }
     } 
     else{
      return -1;
     }
    }
    else if(is_move_seq_valid(game, this_move->seq, NULL, NULL) == 2){/*Si le mouvement implique une prise*/
     if(is_Black(this_move->seq->c_old.x, this_move->seq->c_old.y, game)){/*Si le pion est noir*/
      if(is_Dame(this_move->seq->c_old.x, this_move->seq->c_old.y, game)){/*Une dame*/
       this_seq->old_orig = 00000011;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][this_move->seq->c_new.y] = 00000011;
       if(is_Dame(this_move->seq->piece_taken.x,this_move->seq->piece_taken.y, game)){
        this_seq->piece_value = 00000111;
       }
       else{
        this_seq->piece_value = 00000011;
       }
       game->board[this_move->seq->piece_taken.x][this_move->seq->piece_taken.y] = 00000000;
       this_seq = game->moves->seq->next;
      }
      else if(!(is_Dame(this_move->seq->c_old.x, this_move->seq->c_old.y, game)) && (this_move->seq->c_new.y == 9)){/*Si un pion noir prend un blanc et arrive aux abords du plateau, il devient une dame*/
       this_seq->old_orig = 00000001;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][9] = 00000111;
       game->board[this_move->seq->piece_taken.x][this_move->seq->piece_taken.y] = 00000000;
       if(is_Dame(this_move->seq->piece_taken.x,this_move->seq->piece_taken.x, game)){
        this_seq->piece_value = 00000111;
       }
       else{
        this_seq->piece_value = 00000011;
       }
       this_seq = game->moves->seq->next;
      }
      else{
       this_seq->old_orig = 00000001;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][this_move->seq->c_new.y] = 00000001;
       game->board[this_move->seq->piece_taken.x][this_move->seq->piece_taken.y] = 00000000;
       if(is_Dame(this_move->seq->piece_taken.x,this_move->seq->piece_taken.y, game)){
        this_seq->piece_value = 00000111;
       }
       else{
        this_seq->piece_value = 00000011;
       }
       this_seq = game->moves->seq->next;
      }
     }
     else if(is_White(this_move->seq->c_old.x,this_move->seq->c_old.y, game)){/*Même chose pour une pièce blanche*/
      if(is_Dame(this_move->seq->c_old.x, this_move->seq->c_old.y, game)){
       this_seq->old_orig = 00000111;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][this_move->seq->c_new.y] = 00000011;
       game->board[this_move->seq->piece_taken.x][this_move->seq->piece_taken.y] = 00000000;
       if(is_Dame(this_move->seq->piece_taken.x,this_move->seq->piece_taken.y, game)){
        this_seq->piece_value = 00000011;
       }
       else{
        this_seq->piece_value = 00000001;
       }
       this_seq = game->moves->seq->next;
      }
      else if(!(is_Dame(this_move->seq->c_old.x, this_move->seq->c_old.y, game)) && (this_seq->c_new.y == 0)){
       this_seq->old_orig = 00000101;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][0] = 00000111;
       game->board[this_move->seq->piece_taken.x][this_move->seq->piece_taken.y] = 00000000;
       if(is_Dame(this_move->seq->piece_taken.x,this_move->seq->piece_taken.y, game)){
        this_seq->piece_value = 00000011;
       }
       else{
        this_seq->piece_value = 00000001;
       }
       this_seq = game->moves->seq->next;
      }
      else{
       this_seq->old_orig = 00000101;
       game->board[this_move->seq->c_old.x][this_move->seq->c_old.y] = 00000000;
       game->board[this_move->seq->c_new.x][this_move->seq->c_new.y] = 00000101;
       game->board[this_move->seq->piece_taken.x][this_move->seq->piece_taken.y] = 00000000;
       if(is_Dame(this_move->seq->piece_taken.x,this_move->seq->piece_taken.y, game)){
        this_seq->piece_value = 00000011;
       }
       else{
        this_seq->piece_value = 00000001;
       }
       this_seq = game->moves->seq->next;
       }
     }
     else{
      return -1;
     }
    }
    else{
     return -1;
    }
   }
   this_move = game->moves->next;
   game->moves->next = this_move;
  }
 if(game->cur_player == 0){
  int i, j;
  for(i=0; i<game->xsize; i++){/*On vérifie que le joueur qui n'a pas joué possède encore des pièces, sinon fin de partie*/
   for(j=0; j<game->ysize; j++){
    if(is_White( i, j, game)){
     return 0;
     game->cur_player = !(game->cur_player);
    }
    else{
    }
   } 
  }
  return 1;
 else if(game->cur_player == 1){
  int k, l;
  for(k=0; k<game->xsize; k++){
   for(l=0; l<game->ysize; l++){
    if(is_Black(k, l, game){
     return 0;
     game->cur_player = !(game->cur_player);
    }
    else{
    }
   }
  }
  return 1;    
}  

/*
 * undo_moves
 * Annule des mouvements et remet l'état du jeu correspondant
 *
 * @game: pointeur vers la structure du jeu
 * @n: nombre de coups à annuler. Si n > nombre total de mouvements, alors ignorer le surplus.
 * @return: 0 si OK, -1 si erreur
 */
int undo_moves(struct game *game, int n) {/*On parcours la liste chainée au niveau des séquences, on vide les coordonnées c_new et on rempli les c_old grâce à la valeur old_orig de move_seq. Si une pièce a été prise, on la replace sur le damier grâce à la valeur piece_value. On passe ensuite au move précédent et on fait un appel récursif afin d'appliquer la fonction n fois.*/
 if(game->moves == NULL) {
  return 0;
 }
struct move_seq *my_seq = game->moves->seq;
struct move_seq *prev_seq = NULL;
 while(my_seq != NULL){
  game->board[seq->c_new.x][seq->c_new.y] = 00000000;/*On vide la case occupée auparavant*/
  game->board[seq->c_old.x][seq->c_old.y] = seq->old_orig;
 if(seq->piece_value != 00000000){
  game->board[piece_taken.x][piece_taken.y] = seq->piece_value;/* On rempli la case où une prise a été effectuée*/
 }
 prev_seq = my_seq;/*On passe à la séquence suivante*/
 my_seq = my_seq->next;
 free(prev_seq);
 } 
 struct move *my_move = game->moves;
 game->moves = my_move->next;
 free(my_move);
 game->cur_player = !(game->cur_player); 
 if(n>1){/*Appel récursif*/
  return undo_moves(game, n-1);
 }
 else{
  return 0;
 }
}

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

#endif
