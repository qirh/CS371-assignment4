#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Darwin.h"

using namespace std;

//Species methods
Species::Species(string name) : _name(name){}

void Species::addInstruction(string action){
	transform(action.begin(), action.end(), action.begin(), toupper);
	if (){

	}
	_instruction_set.push_back(i);
}

void Species::addInstruction(string control, int branch){
	_instruction_set.push_back(i);
}

int Species::executeTilAction(object obj, Creature &rhs){

}

bool Species::operator == (const Species &rhs){
	return equal(_name.begin(), _name.end(), rhs._name.begin());
}
