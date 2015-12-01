#include "Pokedex.h"

Pokemon * Pokedex::mergeLevelMainArrays(Pokemon * a, Pokemon * b) {
	if (!a || !b) {
		return NULL;
	}
	int numOfPokemons = mainIdTree.getSize();
	Pokemon* merged = new Pokemon[numOfPokemons];
	if (!merged) {
		return NULL;
	}
	int aIndex = 0, bIndex = 0;
	pokemonCompareByLevel comparer = pokemonCompareByLevel();
	for (int i = 0; i < numOfPokemons; i++) {
		if (comparer(a[aIndex], b[bIndex])) {
			merged[i] = a[aIndex];
			aIndex++;
		} else {
			merged[i] = b[bIndex];
			bIndex++;
		}
	}

	return merged;
}

Pokedex::Pokedex() :
		maxPokemonID(-1) {
}

void Pokedex::addTrainer(int trainerID) {
	if (trainerID <= 0) {
		throw InvalidInput();
	}
	Iterator<Trainer> trainer = trainers.find(TrainerCompare(trainerID));
	if (trainer != trainers.end()) {
		throw Failure();
	}
	trainers.insert(Trainer(trainerID), trainers.begin());

}

void Pokedex::catchPokemon(int pokemonID, int trainerID, int level) {
	if (pokemonID <= 0 || trainerID <= 0 || level <= 0) {
		throw InvalidInput();
	}
	Iterator<Trainer> trainer = trainers.find(TrainerCompare(trainerID));
	if (trainer == trainers.end()) {
		throw Failure();
	}
	Pokemon pokemon(pokemonID, trainerID, level);
	bool status = mainIdTree.insert(pokemon);
	if (!status) {
		throw Failure();
	}
	bool status2 = mainLevelTree.insert(pokemon);
	if (!status2) {
		throw Failure();
	}
	bool status3 = (*trainer).getIdTree().insert(pokemon);
	if (!status3) {
		throw Failure();
	}
	bool status4 = (*trainer).getLevelTree().insert(pokemon);
	if (!status4) {
		throw Failure();
	}
	(*trainer).updateMax();
	this->updateMax();
}

void Pokedex::freePokemon(int pokemonID) {
	if (pokemonID <= 0) {
		throw InvalidInput();
	}
	Pokemon pokemon(pokemonID, NO_POKEMON, NO_POKEMON);
	avlNode<Pokemon, pokemonCompareByID>* pokemonNode = mainIdTree.find(
			pokemon);
	if (!pokemonNode) {
		throw Failure();
	}
	Pokemon toRemove(pokemonID, pokemonNode->getData().getTrainerId(),
			pokemonNode->getData().getLevel());
	bool status = mainIdTree.remove(toRemove);
	if (!status) {
		throw Failure();
	}
	bool status2 = mainLevelTree.remove(toRemove);
	if (!status2) {
		throw Failure();
	}
	int trainerID = toRemove.getTrainerId();
	Iterator<Trainer> trainer = trainers.find(TrainerCompare(trainerID));
	bool status3 = (*trainer).getIdTree().remove(toRemove);
	if (!status3) {
		throw Failure();
	}
	bool status4 = (*trainer).getLevelTree().remove(toRemove);
	if (!status4) {
		throw Failure();
	}
	(*trainer).updateMax();
	this->updateMax();
}

void Pokedex::levelUp(int pokemonID, int levelIncrease) {
	if (pokemonID <= 0 || levelIncrease <= 0) {
		throw InvalidInput();
	}
	Pokemon pokemon(pokemonID, NO_POKEMON, NO_POKEMON);
	avlNode<Pokemon, pokemonCompareByID>* pokemonNode = mainIdTree.find(
			pokemon);
	if (!pokemonNode) {
		throw Failure();
	}
	int trainerID = pokemonNode->getData().getTrainerId();
	int level = pokemonNode->getData().getLevel();
	this->freePokemon(pokemonID);
	this->catchPokemon(pokemonID, trainerID, level + levelIncrease);
}

void Pokedex::getTopPokemon(int trainerID, int* pokemonID) {
	if (trainerID == 0 || pokemonID == NULL) {
		throw InvalidInput();
	}
	if (trainerID < 0) {
		*pokemonID = this->getMaxPokemonId();
		return;
	}
	Iterator<Trainer> trainer = trainers.find(TrainerCompare(trainerID));
	if (trainer == trainers.end()) {
		throw Failure();
	}
	*pokemonID = (*trainer).getMaxPokemonId();
}

void Pokedex::GetAllPokemonsByLevel(int trainerID, int ** pokemons,
		int *numOfPokemon) {
	if (trainerID == 0||!pokemons ||!numOfPokemon) {
		throw InvalidInput();
	}
	if (trainerID < 0) {
		*numOfPokemon = mainLevelTree.getSize();
		int* pokemonArray = (int*) malloc(sizeof(int) * *numOfPokemon);
		if (pokemonArray == NULL) {
			throw AllocationError();
		}
		Pokemon* levelArray = mainLevelTree.inOrder();
		for (int i = 0; i < *numOfPokemon; i++) {
			pokemonArray[i] = levelArray[i].getID();
		}
		delete[] levelArray;
		*pokemons = pokemonArray;
		return;
	}

	Iterator<Trainer> trainer = trainers.find(TrainerCompare(trainerID));
	if (trainer == trainers.end()) {
		throw Failure();
	}
	//avlTree<Pokemon, pokemonCompareByLevel> trainerLevelTree =	(*trainer).getLevelTree();
	//*numOfPokemon = trainerLevelTree.getSize();
	*numOfPokemon = (*trainer).getLevelTree().getSize();
	int* pokemonArray = (int*) malloc(sizeof(int) * *numOfPokemon);
	if (pokemonArray == NULL) {
		throw AllocationError();
	}
	Pokemon* levelArray = (*trainer).getLevelTree().inOrder();
	for (int i = 0; i < *numOfPokemon; i++) {
		pokemonArray[i] = levelArray[i].getID();
	}
	*pokemons = pokemonArray;
	delete[] levelArray;
	return;
}

void Pokedex::EvolvePokemon(int pokemonID, int evolvedID) {
	if (pokemonID <= 0 || evolvedID <= 0) {
		throw InvalidInput();
	}

	Pokemon current(pokemonID, 1, 1);
	avlNode<Pokemon, pokemonCompareByID>* foundCurrent = mainIdTree.find(
			current);
	if (!foundCurrent) {
		throw Failure();
	}
	Pokemon evolved(evolvedID, 1, 1);
	avlNode<Pokemon, pokemonCompareByID>* foundEvolved = mainIdTree.find(
			evolved);
	if (foundEvolved) {
		throw Failure();
	}
	current = foundCurrent->getData();
	int trainerID = current.getTrainerId(), level = current.getLevel();
	freePokemon(pokemonID);
	catchPokemon(evolvedID, trainerID, level);
}

void Pokedex::UpdateLevelsMain(int stoneCode, int stoneFactor) {
	if (stoneCode <1 || stoneFactor < 1)
	{
		throw InvalidInput();
	}
	int numOfPokemons = mainIdTree.getSize();
	if (numOfPokemons < 1)
	{
		return;
	}
	Pokemon* notAffected = new Pokemon[numOfPokemons];
	Pokemon* affected = new Pokemon[numOfPokemons];
	Pokemon* currentArray = mainLevelTree.inOrder();
	int affectedIndex = 0, notIndex = 0;
	for (int i = 0; i < numOfPokemons; i++) {
		if (currentArray[i].getID() % stoneCode == 0) {
			Pokemon current(currentArray[i].getID(),
					currentArray[i].getTrainerId(),
					currentArray[i].getLevel() * stoneFactor);
			affected[affectedIndex] = current;
			affectedIndex++;
		} else {
			notAffected[notIndex] = currentArray[i];
			notIndex++;
		}
	}
	Pokemon* merged = mergeLevelMainArrays(affected, notAffected);
	mainLevelTree.clear();
	mainLevelTree.buildEmpty(numOfPokemons);
	int mergedIndex = 0;
	mainLevelTree.inOrderInsert(merged, &mergedIndex);


	updateMax();

	Pokemon* iDArray = mainIdTree.inOrder();
	for (int i = 0; i < numOfPokemons; i++) {
		if (iDArray[i].getID() % stoneCode == 0) {
			int newLevel = iDArray[i].getLevel() * stoneFactor;
			iDArray[i].setLevel(newLevel);
		}
	}
	int iDIndex = 0;
	mainIdTree.inOrderInsert(iDArray, &iDIndex);

	delete[] iDArray;
	delete[] notAffected;
	delete[] affected;
	delete[] currentArray;
	delete[] merged;

	Iterator<Trainer> trainerIt = trainers.begin();
	while (trainerIt != trainers.end()) {
		(*trainerIt).updateLevels(stoneCode, stoneFactor);
		++trainerIt;
	}
}


void Pokedex::updateMax() {
	avlNode<Pokemon, pokemonCompareByLevel>* ptr = mainLevelTree.getRoot();
	if (!ptr) {
		this->setMaxPokemonId(NO_POKEMON);
		return;
	}
	while (ptr->getLeft()) {
		ptr = ptr->getLeft();
	}
	this->setMaxPokemonId(ptr->getData().getID());
}

int Pokedex::getMaxPokemonId() const {
	return maxPokemonID;
}

void Pokedex::setMaxPokemonId(int maxPokemonId) {
	maxPokemonID = maxPokemonId;
}

