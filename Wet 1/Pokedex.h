#ifndef POKEDEX_H
#define POKEDEX_H


#include "list.h"
#include "Trainer.h"
#include <exception>
using std::exception;

class Pokedex {
	List<Trainer> trainers;
	avlTree<Pokemon,pokemonCompareByID> mainIdTree;
	avlTree<Pokemon,pokemonCompareByLevel> mainLevelTree;
	int maxPokemonID;
	int maxPokemonLevel; //TODO check if needed
private:
	Pokemon* mergeLevelMainArrays(Pokemon* a, Pokemon* b);
public:
	Pokedex();
	void addTrainer(int trainerID);
	void catchPokemon(int pokemonID, int trainerID, int level);
	void freePokemon(int pokemonID);
	void levelUp(int pokemonID, int levelIncrease);
	void getTopPokemon(int trainerID,int* pokemonID);
	void GetAllPokemonsByLevel(int trainerID, int **pokemons, int *numOfPokemon);
	void EvolvePokemon( int pokemonID, int evolvedID);
	void UpdateLevelsMain(int stoneCode, int stoneFactor);

	void updateMax();
	int getMaxPokemonId() const;
	void setMaxPokemonId(int maxPokemonId);
	int getMaxPokemonLevel() const;
	void setMaxPokemonLevel(int maxPokemonLevel);
	class InvalidInput :public exception {};
	class Failure :public exception {};
	class AllocationError :public exception {};
};



#endif /* POKEDEX_H_ */
