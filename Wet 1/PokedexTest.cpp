#include "Pokedex.h"
#include "testing.h"
#include <iostream>

using namespace std;

bool basicTrainerTest()
{
	Pokedex DS = Pokedex();

		ASSERT_THROW(Pokedex::InvalidInput, DS.addTrainer(-1));
		ASSERT_NO_THROW(DS.addTrainer(1));
		ASSERT_THROW(Pokedex::Failure, DS.addTrainer(1));

	return true;
}

bool basicCatchFreeTest()
{
	Pokedex DS=Pokedex();
	ASSERT_NO_THROW(DS.addTrainer(1));
	ASSERT_NO_THROW(DS.catchPokemon(1, 1, 1));
	ASSERT_THROW(Pokedex::Failure, DS.catchPokemon(1, 1, 1));
	ASSERT_THROW(Pokedex::Failure, DS.catchPokemon(1, 2, 1));
	ASSERT_THROW(Pokedex::InvalidInput, DS.catchPokemon(-1, 1, 1));
	ASSERT_THROW(Pokedex::InvalidInput, DS.catchPokemon(1, -1, 1));
	ASSERT_THROW(Pokedex::InvalidInput, DS.catchPokemon(1, 1, -1));
	int poke= DS.getMaxPokemonId();
	ASSERT_EQUALS(1, poke);
	ASSERT_NO_THROW(DS.freePokemon(1));
	ASSERT_THROW(Pokedex::Failure, DS.freePokemon(1));
	ASSERT_THROW(Pokedex::InvalidInput, DS.freePokemon(-1));
	poke = DS.getMaxPokemonId();
	ASSERT_EQUALS(-1, poke);
	return true;
}

bool basicLevelUpTest()
{
	Pokedex DS = Pokedex();
	ASSERT_NO_THROW(DS.addTrainer(1));
	ASSERT_NO_THROW(DS.catchPokemon(1, 1, 1));
	ASSERT_NO_THROW(DS.catchPokemon(2, 1, 3));
	int poke = DS.getMaxPokemonId();
	ASSERT_EQUALS(2, poke);
	ASSERT_NO_THROW(DS.levelUp(1, 5));
	ASSERT_THROW(Pokedex::InvalidInput, DS.levelUp(-1, 5));
	ASSERT_THROW(Pokedex::InvalidInput, DS.levelUp(1, -5));
	ASSERT_THROW(Pokedex::Failure, DS.levelUp(3, 5));
	poke = DS.getMaxPokemonId();
	ASSERT_EQUALS(1, poke);
	return true;
}

bool basicGetTopTest()
{
	Pokedex DS = Pokedex();
	ASSERT_NO_THROW(DS.addTrainer(1));
	ASSERT_NO_THROW(DS.addTrainer(2));
	ASSERT_NO_THROW(DS.catchPokemon(1, 1, 1));
	ASSERT_NO_THROW(DS.catchPokemon(2, 1, 3));
	ASSERT_NO_THROW(DS.catchPokemon(3, 2, 5));
	int poke;
	ASSERT_NO_THROW(DS.getTopPokemon(-1, &poke));
	ASSERT_EQUALS(3, poke);
	ASSERT_NO_THROW(DS.getTopPokemon(1, &poke));
	ASSERT_EQUALS(2, poke);
	ASSERT_THROW(Pokedex::InvalidInput, DS.getTopPokemon(0, &poke));
	ASSERT_THROW(Pokedex::InvalidInput, DS.getTopPokemon(1, NULL));
	ASSERT_THROW(Pokedex::Failure, DS.getTopPokemon(3, &poke));
	return true;
}

bool basicGetAllTest()
{
	Pokedex DS = Pokedex();
	ASSERT_NO_THROW(DS.addTrainer(1));
	ASSERT_NO_THROW(DS.addTrainer(2));
	ASSERT_NO_THROW(DS.catchPokemon(1, 1, 1));
	ASSERT_NO_THROW(DS.catchPokemon(2, 1, 3));
	ASSERT_NO_THROW(DS.catchPokemon(3, 2, 5));
	ASSERT_NO_THROW(DS.catchPokemon(4, 2, 4));
	ASSERT_NO_THROW(DS.catchPokemon(5, 2, 1));
	int *pokeArray=NULL, num=0;
	ASSERT_NO_THROW(DS.GetAllPokemonsByLevel(-1, &pokeArray,&num));
	ASSERT_EQUALS(5, num);
	int currentArray[5] = { 3,4,2,1,5 };
	for (int i = 0; i < 5; i++)
	{
		ASSERT_EQUALS(currentArray[i], pokeArray[i]);
	}
	free(pokeArray);
	int *pokeArray2 = NULL;
	ASSERT_NO_THROW(DS.GetAllPokemonsByLevel(1, &pokeArray2, &num));
	ASSERT_EQUALS(2, num);
	int currentArray2[2] = { 2,1 };
	for (int i = 0; i < 2; i++)
	{
		ASSERT_EQUALS(currentArray2[i], pokeArray2[i]);
	}
	free(pokeArray2);

	ASSERT_THROW(Pokedex::InvalidInput, DS.GetAllPokemonsByLevel(0, &pokeArray, &num));
	ASSERT_THROW(Pokedex::InvalidInput, DS.GetAllPokemonsByLevel(-1, NULL, &num));
	ASSERT_THROW(Pokedex::InvalidInput, DS.GetAllPokemonsByLevel(-1, &pokeArray, NULL));
	ASSERT_THROW(Pokedex::Failure, DS.GetAllPokemonsByLevel(3, &pokeArray, &num));

	
	return true;
}

bool basicEvolveTest()
{
	Pokedex DS = Pokedex();
	ASSERT_NO_THROW(DS.addTrainer(1));
	ASSERT_NO_THROW(DS.catchPokemon(1, 1, 1));
	int poke = DS.getMaxPokemonId();
	ASSERT_EQUALS(1, poke);
	ASSERT_NO_THROW(DS.EvolvePokemon(1, 2));
	poke = DS.getMaxPokemonId();
	ASSERT_EQUALS(2, poke);
	ASSERT_THROW(Pokedex::InvalidInput, DS.EvolvePokemon(-1, 5));
	ASSERT_THROW(Pokedex::InvalidInput, DS.EvolvePokemon(1, -5));
	ASSERT_THROW(Pokedex::Failure, DS.EvolvePokemon(3, 5));
	ASSERT_THROW(Pokedex::Failure, DS.EvolvePokemon(2, 2));
	return true;
}

bool basicStonesTest()
{
	Pokedex DS = Pokedex();
	ASSERT_NO_THROW(DS.addTrainer(1));
	ASSERT_NO_THROW(DS.addTrainer(2));
	ASSERT_NO_THROW(DS.catchPokemon(1, 1, 1));
	ASSERT_NO_THROW(DS.catchPokemon(2, 1, 3));
	ASSERT_NO_THROW(DS.catchPokemon(3, 2, 5));
	ASSERT_NO_THROW(DS.catchPokemon(4, 2, 4));
	ASSERT_NO_THROW(DS.catchPokemon(5, 2, 1));
	
	int *pokeArray = NULL, num = 0;
	ASSERT_NO_THROW(DS.GetAllPokemonsByLevel(-1, &pokeArray, &num));
	ASSERT_EQUALS(5, num);
	int currentArray[5] = { 3,4,2,1,5 };
	for (int i = 0; i < 5; i++)
	{
		ASSERT_EQUALS(currentArray[i], pokeArray[i]);
	}
	free(pokeArray);
	int *pokeArray2 = NULL;
	ASSERT_NO_THROW(DS.GetAllPokemonsByLevel(1, &pokeArray2, &num));
	ASSERT_EQUALS(2, num);
	int currentArray2[2] = { 2,1 };
	for (int i = 0; i < 2; i++)
	{
		ASSERT_EQUALS(currentArray2[i], pokeArray2[i]);
	}
	free(pokeArray2);



	ASSERT_NO_THROW(DS.UpdateLevelsMain(2,2));

	int *pokeArray3 = NULL;
	ASSERT_NO_THROW(DS.GetAllPokemonsByLevel(-1, &pokeArray3, &num));
	ASSERT_EQUALS(5, num);
	int currentArray3[5] = { 4,2,3,1,5 };
	for (int i = 0; i < 5; i++)
	{
		ASSERT_EQUALS(currentArray3[i], pokeArray3[i]);
	}
	free(pokeArray3);
	int *pokeArray4 = NULL;
	ASSERT_NO_THROW(DS.GetAllPokemonsByLevel(1, &pokeArray4, &num));
	ASSERT_EQUALS(2, num);
	int currentArray4[2] = { 2,1 };
	for (int i = 0; i < 2; i++)
	{
		ASSERT_EQUALS(currentArray4[i], pokeArray4[i]);
	}
	free(pokeArray4);



	ASSERT_THROW(Pokedex::InvalidInput, DS.UpdateLevelsMain(-1,2));
	ASSERT_THROW(Pokedex::InvalidInput, DS.UpdateLevelsMain(2,-1));

	return true;
}

int main()
{
	RUN_TEST(basicTrainerTest);
	RUN_TEST(basicCatchFreeTest);
	RUN_TEST(basicLevelUpTest);
	RUN_TEST(basicGetTopTest);
	RUN_TEST(basicGetAllTest);
	RUN_TEST(basicEvolveTest);
	RUN_TEST(basicStonesTest);
	return 0;
}
