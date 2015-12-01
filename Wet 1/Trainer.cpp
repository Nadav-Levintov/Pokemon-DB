#include "Trainer.h"


Trainer::Trainer(int trainerID) :
		trainerID(trainerID), maxPokemonID(
		NO_POKEMON) {
}

int Trainer::getMaxPokemonId() const {
	return maxPokemonID;
}

void Trainer::setMaxPokemonId(int maxPokemonID) {
	this->maxPokemonID = maxPokemonID;
}



int Trainer::getTrainerId() const {
	return trainerID;
}

void Trainer::setTrainerId(int trainerId) {
	trainerID = trainerId;
}

bool Trainer::addPokemon(Pokemon& pokemon) {
	bool status = this->idTree.insert(pokemon);
	if (!status) {
		return status;
	}
	bool status2 = this->levelTree.insert(pokemon);
	if (!status2) {
		return status2;
	}
	this->updateMax();
	return true;
}

void Trainer::updateMax() {
	avlNode<Pokemon, pokemonCompareByLevel>* ptr = levelTree.getRoot();
	if (!ptr) {
		this->setMaxPokemonId(NO_POKEMON);
		return;
	}
	while (ptr->getLeft()) {
		ptr = ptr->getLeft();
	}
	this->setMaxPokemonId(ptr->getData().getID());
}

void Trainer::updateLevels(int stoneCode, int stoneFactor)
{
	int numOfPokemons = idTree.getSize();
	if (numOfPokemons < 1)
	{
		return;
	}
	Pokemon* notAffected = new Pokemon[numOfPokemons];
	Pokemon* affected = new Pokemon[numOfPokemons];
	Pokemon* currentArray = levelTree.inOrder();
	int affectedIndex = 0, notIndex = 0;
	for (int i = 0; i < numOfPokemons; i++) {
		if (currentArray[i].getID() % stoneCode == 0) {
			Pokemon current(currentArray[i].getID(),
				currentArray[i].getTrainerId(),
				currentArray[i].getLevel() * stoneFactor);
			affected[affectedIndex] = current;
			affectedIndex++;
		}
		else {
			notAffected[notIndex] = currentArray[i];
			notIndex++;
		}
	}
	Pokemon* merged = mergeLevelArrays(affected, notAffected);

	levelTree.clear();
	levelTree.buildEmpty(numOfPokemons);
	int mergedIndex = 0;
	levelTree.inOrderInsert(merged, &mergedIndex);


	updateMax();

	Pokemon* iDArray = idTree.inOrder();
	for (int i = 0; i < numOfPokemons; i++) {
		if (iDArray[i].getID() % stoneCode == 0) {
			int newLevel = iDArray[i].getLevel() * stoneFactor;
			iDArray[i].setLevel(newLevel);
		}
	}
	int iDIndex = 0;
	idTree.inOrderInsert(iDArray, &iDIndex);

	delete[] iDArray;
	delete[] notAffected;
	delete[] affected;
	delete[] currentArray;
	delete[] merged;

	}


avlTree<Pokemon, pokemonCompareByID>& Trainer::getIdTree() {
	return idTree;
}

avlTree<Pokemon, pokemonCompareByLevel>& Trainer::getLevelTree() {
	return levelTree;
}

bool Trainer::removePokemon(Pokemon& pokemon) {
	bool status = this->idTree.remove(pokemon);
	if (!status) {
		return status;
	}
	bool status2 = this->levelTree.remove(pokemon);
	if (!status2) {
		return status2;
	}
	this->updateMax();
	return true;
}

Pokemon * Trainer::mergeLevelArrays(Pokemon * a, Pokemon * b)
{
	if (!a || !b)
	{
		return NULL;
	}
	int numOfPokemons = idTree.getSize();
	Pokemon* merged = new Pokemon[numOfPokemons];
	if (!merged)
	{
		return NULL;
	}
	int aIndex = 0, bIndex = 0;
	pokemonCompareByLevel comparer = pokemonCompareByLevel();
	for (int i = 0; i < numOfPokemons; i++)
	{
		if (comparer(a[aIndex], b[bIndex]))
		{
			merged[i] = a[aIndex];
			aIndex++;
		}
		else
		{
			merged[i] = b[bIndex];
			bIndex++;
		}
	}

	return merged;
}
