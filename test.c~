#include "CUnit.h"
#include <stdlib.h>
#include <stdio.h> 
#include "dames.h"

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
	if ( NULL == game1 ) then return 42;
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
