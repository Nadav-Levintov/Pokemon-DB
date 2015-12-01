#include "Pokedex.h"
#include "testing.h"
#include <iostream>

using namespace std;

bool basicPokadexTest()
{
	Pokedex DS=Pokedex();
	DS.addTrainer(1);
	DS.catchPokemon(1, 1, 1);
	int poke= DS.getMaxPokemonId();
	ASSERT_EQUALS(1, poke);
	return true;
}

int main()
{
	RUN_TEST(basicPokadexTest);


	return 0;
}
