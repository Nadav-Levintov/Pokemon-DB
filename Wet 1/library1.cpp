#include "library1.h"
#include "Pokedex.h"
#include <exception>


void* Init() {
	Pokedex* DS;
	try {
		DS = new Pokedex;
	}
	catch (std::bad_alloc& b) {
		return NULL;
	}
	return (void*) DS;
}

StatusType AddTrainer(void * DS, int trainerID) {
	if (!DS) {
		return INVALID_INPUT;
	}
	Pokedex* pDS = (Pokedex*) DS;
	try{
		pDS->addTrainer(trainerID);
	}
	catch (std::bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	catch (Pokedex::Failure& f){
		return FAILURE;
	}
	catch (Pokedex::InvalidInput& f) {
		return INVALID_INPUT;
	}
	return SUCCESS;
}

StatusType CatchPokemon(void * DS, int pokemonID, int trainerID, int level) {
	if (!DS) {
		return INVALID_INPUT;
	}
	Pokedex* pDS = (Pokedex*) DS;
	try{
		pDS->catchPokemon(pokemonID, trainerID, level);
	}
	catch (std::bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	catch (Pokedex::Failure& f){
		return FAILURE;
	}
	catch (Pokedex::InvalidInput& f) {
		return INVALID_INPUT;
	}
	return SUCCESS;
}

StatusType FreePokemon(void * DS, int pokemonID) {
	if (!DS) {
		return INVALID_INPUT;
	}
	Pokedex* pDS = (Pokedex*) DS;
	try{
		pDS->freePokemon(pokemonID);
	}
	catch (std::bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	catch (Pokedex::Failure& f){
		return FAILURE;
	}
	catch (Pokedex::InvalidInput& f) {
		return INVALID_INPUT;
	}
	return SUCCESS;
}

StatusType LevelUp(void * DS, int pokemonID, int levelIncrease) {
	if (!DS) {
		return INVALID_INPUT;
	}
	Pokedex* pDS = (Pokedex*) DS;
	try{
		pDS->levelUp(pokemonID, levelIncrease);
	}
	catch (std::bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	catch (Pokedex::Failure& f){
		return FAILURE;
	}
	catch (Pokedex::InvalidInput& f) {
		return INVALID_INPUT;
	}
	return SUCCESS;
}

StatusType EvolvePokemon(void * DS, int pokemonID, int evolvedID) {
	if (!DS) {
		return INVALID_INPUT;
	}
	Pokedex* pDS = (Pokedex*) DS;
	try{
		pDS->EvolvePokemon(pokemonID, evolvedID);
	}
	catch (std::bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	catch (Pokedex::Failure& f){
		return FAILURE;
	}
	catch (Pokedex::InvalidInput& f) {
		return INVALID_INPUT;
	}
	return SUCCESS;
}

StatusType GetTopPokemon(void * DS, int trainerID, int * pokemonID) {
	if (!DS) {
		return INVALID_INPUT;
	}
	Pokedex* pDS = (Pokedex*) DS;
	try{
		pDS->getTopPokemon(trainerID, pokemonID);
	}
	catch (std::bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	catch (Pokedex::Failure& f){
		return FAILURE;
	}
	catch (Pokedex::InvalidInput& f) {
		return INVALID_INPUT;
	}
	return SUCCESS;
}

StatusType GetAllPokemonsByLevel(void * DS, int trainerID, int ** pokemons,
		int * numOfPokemon) {
	if (!DS) {
		return INVALID_INPUT;
	}
	Pokedex* pDS = (Pokedex*) DS;
	try{
		pDS->GetAllPokemonsByLevel(trainerID, pokemons, numOfPokemon);
	}
	catch (std::bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	catch(Pokedex::AllocationError& a){
		return ALLOCATION_ERROR;
	}
	catch (Pokedex::Failure& f){
		return FAILURE;
	}
	catch (Pokedex::InvalidInput& f) {
		return INVALID_INPUT;
	}
	return SUCCESS;
}

StatusType UpdateLevels(void * DS, int stoneCode, int stoneFactor) {
	if (!DS) {
		return INVALID_INPUT;
	}
	Pokedex* pDS = (Pokedex*) DS;
	try{
		pDS->UpdateLevelsMain(stoneCode, stoneFactor);
	}
	catch (std::bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	catch (Pokedex::Failure& f){
		return FAILURE;
	}
	catch (Pokedex::InvalidInput& f) {
		return INVALID_INPUT;
	}
	return SUCCESS;
}

void Quit(void ** DS) {
	if (!DS) {
		return;
	}
	Pokedex* pDS = (Pokedex*) (*DS);
	delete pDS;
	*DS = NULL;
}
