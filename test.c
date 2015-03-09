#include <stdlib.h>
#include <stdio.h> 
#include "dames.h"

struct game *game1;


void test_new_game()
{
	print_board(game1);
}

void test_load_game()
{

	struct move_seq seq1={NULL,(1,6),(2,5)};
	struct move_seq seq2={NULL,(4,3),(3,4)};
	struct move_seq seq3={NULL,(2,5),(4,3)};
	struct move move3={NULL,&seq3};
	struct move move2={&move3,&seq2};
	struct move move1={&move2,&seq1};
	apply_moves(game1,&move1);
	struct game *game2;
	game2=load_game(10,10,(const int **) game1->board,game1->cur_player);
	print_board(game1);
	print_board(game2);
	free_game(game2);
}

void test_apply_moves()
{
	struct move_seq seq4={NULL,(3,2),(5,4)};
	struct move move4={NULL,&seq4};
	print_board(game1);
	apply_moves(game1,&move4);
	print_board(game1);
}	

void test_is_move_seq_valid()
{
	struct move_seq seq5={NULL,(3,6),(4,5)};
	struct move move5={NULL,&seq5};
	apply_moves(game1,&move5);
	struct move_seq seq6={NULL,(5,4),(5,5)}; // mouvement invalide
	struct move_seq seq7={NULL,(5,4),(6,5)}; // déplacement uniquement
	struct move_seq seq8={NULL,(5,4),(3,6)}; // capture
	struct coord *taken;
	printf("%d, le mouvement est invalide", is_move_seq_valid(game1,&seq6,&seq5,taken));
	printf("%d, il y a seulement déplacement", is_move_seq_valid(game1,&seq7,&seq5,taken));
	printf("%d, il y a capture", is_move_seq_valid(game1,&seq8,&seq5,taken));
}

void test_undo_moves()
{
	print_board(game1);
	undo_moves(game1,1);
	print_board(game1);
	undo_moves(game1,7);
	print_board(game1);
}

int main(int argc, char *argv[])
{
	game1=new_game(10,10);
	test_new_game();
	test_load_game();
	test_apply_moves();
	test_is_move_seq_valid();
	test_undo_moves();
	free_game(game1);
	return 1;
}
