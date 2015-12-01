#ifndef TRAINER_H
#define TRAINER_H

#include "AVLTree.h"
#include "Pokemon.h"

#define NO_POKEMON -1

class Trainer {
	int trainerID;
	int maxPokemonLevel; // is needed?
	int maxPokemonID;
	avlTree<Pokemon, pokemonCompareByLevel> levelTree;
	avlTree<Pokemon, pokemonCompareByID> idTree;
private:
	Pokemon * mergeLevelArrays(Pokemon * a, Pokemon * b);
public:
	Trainer(int trainerID);
	int getMaxPokemonId() const;
	void setMaxPokemonId(int maxPokemonId);
	int getMaxPokemonLevel() const;
	void setMaxPokemonLevel(int maxPokemonLevel);
	int getTrainerId() const;
	void setTrainerId(int trainerId);
	bool addPokemon(Pokemon& pokemon);
	bool removePokemon(Pokemon& pokemon);
	avlTree<Pokemon, pokemonCompareByID>& getIdTree();
	avlTree<Pokemon, pokemonCompareByLevel>& getLevelTree();
	void updateMax();
	void updateLevels(int stoneCode, int stoneFactor);
};

class TrainerCompare {
	int ID;
public:
	TrainerCompare(int ID) :
			ID(ID) {
	}
	bool operator()(Trainer& trainer) const {
		return trainer.getTrainerId() == ID;
	}
};

#endif /* TRAINER_H_ */
