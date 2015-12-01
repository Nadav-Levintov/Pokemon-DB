#include "Pokedex.h"
#include "testing.h"
#include <iostream>

using namespace std;

bool basicCatchFreeTest()
{
	Pokedex DS=Pokedex();
	DS.addTrainer(1);
	DS.catchPokemon(1, 1, 1);
	int poke= DS.getMaxPokemonId();
	ASSERT_EQUALS(1, poke);
	DS.freePokemon(1);
	poke = DS.getMaxPokemonId();
	ASSERT_EQUALS(-1, poke);
	return true;
}

bool basicLevelUpTest()
{
	Pokedex DS = Pokedex();
	DS.addTrainer(1);
	DS.catchPokemon(1, 1, 1);
	DS.catchPokemon(2, 1, 3);
	int poke = DS.getMaxPokemonId();
	ASSERT_EQUALS(2, poke);
	DS.levelUp(1, 5);
	poke = DS.getMaxPokemonId();
	ASSERT_EQUALS(1, poke);
	return true;
}

int main()
{
	RUN_TEST(basicCatchFreeTest);
	RUN_TEST(basicLevelUpTest);

	return 0;
}
