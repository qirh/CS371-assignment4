#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Darwin.h"

using namespace std;

//Species methods
Species::Species(string name) : _name(name){
    _name_ptr = &_name;
}

void Species::addInstruction(string action){
	transform(action.begin(), action.end(), action.begin(), toupper);

    instruction i;

	if (action == "HOP"){
        i._name = HOP;
	}
    else if (action == "LEFT"){
        i._name = LEFT;
    }
    else if (action == "RIGHT"){
        i._name = RIGHT;
    }
    else if (action == "INFECT"){
        i._name = INFECT;
    }

    i._branch = -1;

	_instruction_set.push_back(i);
}

void Species::addInstruction(string control, const int &branch){
    transform(action.begin(), action.end(), action.begin(), toupper);

    instruction i;

    if (action == "IF_EMPTY"){
        i._name = IF_EMPTY;
        i._branch = branch;
    }
    else if (action == "IF_WALL"){
        i._name = IF_WALL;
        i._branch = branch;
    }
    else if (action == "IF_RANDOM"){
        i._name = IF_RANDOM;
        i._branch = branch;
    }
    else if (action == "IF_ENEMY"){
        i._name = IF_ENEMY;
        i._branch = branch;
    }
    else if (action == "GO"){
        i._name = GO;
        i._branch = branch;
    }

	_instruction_set.push_back(i);
}

instruction Species::executeTilAction(object obj, const Species &target, int &pc){
    bool done = false;

    while (!done){
        if (_instruction_set[pc] == IF_EMPTY){
            if (obj == EMPTY){
                pc = _instruction_set[pc]._branch;
            }
            else{
                ++pc;
            }
        }
        else if (_instruction_set[pc] == IF_WALL){
            if (obj == WALL){
                pc = _instruction_set[pc]._branch;
            }
            else{
                ++pc;
            }
        }
        else if (_instruction_set[pc] == IF_RANDOM){
            if (rand() % 2){
                pc = _instruction_set[pc]._branch;
            }
            else{
                ++pc;
            }
        }
        else if (_instruction_set[pc] == IF_ENEMY){
            if ((obj == ENTITY) && (*this != target)){
                pc = _instruction_set[pc]._branch;
            }
            else{
                ++pc;
            }
        }
        else if (_instruction_set[pc] == GO){
            pc = _instruction_set[pc]._branch;
        }
        else{
            done = true;
        }
    }

    return _instruction_set[pc];
}

bool Species::operator == (const Species &rhs){
	return equal(_name.begin(), _name.end(), rhs._name.begin());
}

bool Species::operator != (const Species &rhs){
    return !(*this == rhs);
}

Creature::Creature(Species spe, int dir) :_spe(spe), _dir(dir){
    _pc = 0;
}

void Creature::executeAction(object obj, Creature &rhs){
    instruction do_this = executeTilAction(obj, rhs._spe, _pc);

    if (do_this._name == HOP){
        //how do i move him on the board
    }
    else if (do_this._name == LEFT){
        if (_dir == NORTH){
            _dir = WEST;
        }
        else if (_dir == EAST){
            _dir = NORTH;
        }
        else if (_dir == SOUTH){
            _dir = EAST;
        }
        else if (_dir == WEST){
            _dir = SOUTH;
        }
    }
    else if (do_this._name == RIGHT){
        if (_dir == NORTH){
            _dir = EAST;
        }
        else if (_dir == EAST){
            _dir = SOUTH;
        }
        else if (_dir == SOUTH){
            _dir = WEST;
        }
        else if (_dir == WEST){
            _dir = NORTH;
        }
    }
    else if (do_this._name == INFECT){
        rhs._spe = _spe;
    }
}
