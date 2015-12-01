#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>

class Pokemon {
	int id;
	int trainerID;
	int level;
private:
public:

	Pokemon() :
		id(-1), trainerID(-1), level(-1) {
	}
	Pokemon(Pokemon& p)  {
		id = p.getID();
		level = p.getLevel();
		trainerID = p.getTrainerId();
	}
	Pokemon(int id, int trainerID, int level) :
		id(id), trainerID(trainerID), level(level) {
	}
	;
	~Pokemon() {
	}
	int getID() {
		return id;
	}
	int getLevel() {
		return level;
	}
	void setID(int& newId) {
		id = newId;
	}
	void setLevel(int& newLevel) {
		level = newLevel;
	}

	int getTrainerId() const {
		return trainerID;
	}

	void setTrainerId(int trainerId) {
		trainerID = trainerId;
	}
	Pokemon& operator=(Pokemon& pokemon) {
		this->id = pokemon.getID();
		this->level = pokemon.getLevel();
		this->trainerID = pokemon.getTrainerId();
		return *this;
	}
};

class pokemonCompareByID {
public:
	pokemonCompareByID() {
	}
	~pokemonCompareByID() {
	}
	bool operator()(Pokemon& a, Pokemon& b) {
		if (a.getID() < b.getID())
			return true;
		return false;
	}
};

class pokemonCompareByLevel {
public:
	pokemonCompareByLevel() {
	}
	~pokemonCompareByLevel() {
	}
	bool operator()(Pokemon& a, Pokemon& b) {
		if (a.getLevel() > b.getLevel()) {
			return true;
		}
		else if (a.getLevel() < b.getLevel()) {
			return false;
		}
		else {
			pokemonCompareByID comparer = pokemonCompareByID();
			bool result = comparer(a, b);
			return result;
		}
	}
};

#endif /*POKEMON.H*/
