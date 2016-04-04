#include <iostream>
#include <vector>
#include "Darwin.h"

using namespace std;

struct instruction{
	instr _name;
	int _branch;

	instruction() : _name(-1), _branch(-1){}

	bool operator == (const instruction &rhs){
		return ((_name == rhs._name) && (_branch == rhs._branch));
	}
};
