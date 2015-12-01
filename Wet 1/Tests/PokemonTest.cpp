#include "../avlTree.h"
#include "../Pokemon.h"
#include "../testing.h"
#include <iostream>

using namespace std;

bool basicPokemonTest()
{
	Pokemon charmander(4, 1,1);
	ASSERT_EQUALS(4, charmander.getID());
	ASSERT_EQUALS(1, charmander.getLevel());
	return true;
}

bool basicPokemonTreeTestID()
{
	
	Pokemon bulbasaur(1, 1,1);
	Pokemon charmander(4, 1,1);
	Pokemon squirtle(7, 1,1);

	avlTree<Pokemon, pokemonCompareByID> tree= avlTree<Pokemon, pokemonCompareByID>();
	ASSERT_EQUALS(0, tree.getSize());
	tree.insert(bulbasaur);
	ASSERT_EQUALS(1, tree.getSize());
	tree.insert(charmander);
	ASSERT_EQUALS(2, tree.getSize());
	tree.insert(squirtle);
	ASSERT_EQUALS(3, tree.getSize());
	tree.insert(squirtle);
	ASSERT_EQUALS(3, tree.getSize());

	Pokemon* array = tree.inOrder();
	ASSERT_EQUALS(1, array[0].getID());
	ASSERT_EQUALS(1, array[0].getLevel());
	ASSERT_EQUALS(4, array[1].getID());
	ASSERT_EQUALS(1, array[1].getLevel());
	ASSERT_EQUALS(7, array[2].getID());
	ASSERT_EQUALS(1, array[2].getLevel());
	delete[] array;

	return true;
}

bool basicPokemonTreeTestLevel()
{

	Pokemon bulbasaur(1, 2,2);
	Pokemon charmander(4, 1,1);
	Pokemon squirtle(7, 1,1);

	avlTree<Pokemon, pokemonCompareByID> tree = avlTree<Pokemon, pokemonCompareByID>();
	ASSERT_EQUALS(0, tree.getSize());
	tree.insert(bulbasaur);
	ASSERT_EQUALS(1, tree.getSize());
	tree.insert(charmander);
	ASSERT_EQUALS(2, tree.getSize());
	tree.insert(squirtle);
	ASSERT_EQUALS(3, tree.getSize());
	tree.insert(squirtle);
	ASSERT_EQUALS(3, tree.getSize());

	Pokemon* array = tree.inOrder();
	ASSERT_EQUALS(1, array[0].getID());
	ASSERT_EQUALS(2, array[0].getLevel());
	ASSERT_EQUALS(4, array[1].getID());
	ASSERT_EQUALS(1, array[1].getLevel());
	ASSERT_EQUALS(7, array[2].getID());
	ASSERT_EQUALS(1, array[2].getLevel());
	delete[] array;

	return true;
}



int main()
{
	RUN_TEST(basicPokemonTest);
	RUN_TEST(basicPokemonTreeTestID);
	RUN_TEST(basicPokemonTreeTestLevel);

	return 0;
}
