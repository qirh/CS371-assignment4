#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <unordered_map>
#include <utility>
#include "Darwin.h"

using namespace std;

bool instruction::operator == (const instruction &rhs){
    return (this->_name == rhs._name) && (this->_branch == rhs._branch);
}
bool instruction::operator == (const instruction &rhs) const{
    return (this->_name == rhs._name) && (this->_branch == rhs._branch);
}

Species::Species(){}

//Species methods
Species::Species(string name) : _name(name){
    _ptr_name = &_name;
}

void Species::addInstruction(string action){
    
    for (int i = 0; i < (int)action.length(); ++i){
        if (action[i] >= 'a' && action[i] <= 'z'){
            toupper(action[i]);
        }
    }

    transform(action.begin(), action.end(), action.begin(), ::toupper);

    instruction i;

    if (action == "HOP")
        i._name = HOP;

    else if (action == "LEFT")
        i._name = LEFT;

    else if (action == "RIGHT")
        i._name = RIGHT;

    else if (action == "INFECT")
        i._name = INFECT;

    else
        throw invalid_argument( "invalid instruction --> " + action);

    i._branch = -1;     //since there's no branch

    _instruction_set.push_back(i);
}

void Species::addInstruction(string control, const int &branch){
    
    for (int i = 0; i < (int)control.length(); ++i){
        if (control[i] >= 'a' && control[i] <= 'z'){
            toupper(control[i]);
        }
    }

    transform(control.begin(), control.end(), control.begin(), ::toupper);

    if (branch < 0)
        throw invalid_argument( "invalid, branch is negative" );

    instruction i;

    if (control == "IF_EMPTY"){
        i._name = IF_EMPTY;
        i._branch = branch;
    }
    else if (control == "IF_WALL"){
        i._name = IF_WALL;
        i._branch = branch;
    }
    else if (control == "IF_RANDOM"){
        i._name = IF_RANDOM;
        i._branch = branch;
    }
    else if (control == "IF_ENEMY"){
        i._name = IF_ENEMY;
        i._branch = branch;
    }
    else if (control == "GO"){
        i._name = GO;
        i._branch = branch;
    }
    else
        throw invalid_argument( "invalid instruction --> " + control);

    _instruction_set.push_back(i);
}

instruction Species::executeTilAction(object obj, const Species * const target, int &pc){
    bool done = false;

    while (!done){
        if (_instruction_set[pc]._name == IF_EMPTY){
            if (obj == EMPTY){
                pc = _instruction_set[pc]._branch;
            }
            else{
                ++pc;
            }
        }
        else if (_instruction_set[pc]._name == IF_WALL){
            if (obj == WALL){
                pc = _instruction_set[pc]._branch;
            }
            else{
                ++pc;
            }
        }
        else if (_instruction_set[pc]._name == IF_RANDOM){
            if (rand() % 2){
                pc = _instruction_set[pc]._branch;
            }
            else{
                ++pc;
            }
        }
        else if (_instruction_set[pc]._name == IF_ENEMY){
            if (target != nullptr){
                if ((obj == ENTITY) && (*this != *target)){
                    pc = _instruction_set[pc]._branch;
                }
                else{
                    ++pc;
                }
            }
            else{
                ++pc;
            }
        }
        else if (_instruction_set[pc]._name == GO){
            pc = _instruction_set[pc]._branch;
        }
        else{
            done = true;
        }
    }

    return _instruction_set[pc];
}

bool Species::operator == (const Species &rhs){
    return this->_name == rhs._name;
}

bool Species::operator != (const Species &rhs){
    return !(this->_name == rhs._name);
}

Creature::Creature(){}

Creature::Creature(Species spe, int dir) :_spe(spe), _pc(0){
    if (dir == 0)
        _dir = NORTH;
    else if (dir == 1)
        _dir = EAST;
    else if (dir == 2)
        _dir = SOUTH;
    else if (dir == 3)
        _dir = WEST;
    else
        throw invalid_argument("invalid_argument");
    _ptr_dir = &_dir;
}

bool Creature::executeAction(object obj, Creature * const target){
    instruction do_this;

    if (target != nullptr)
        do_this = _spe.executeTilAction(obj, &((*target)._spe), _pc);
    else
        do_this = _spe.executeTilAction(obj, nullptr, _pc);

    if (do_this._name == HOP){
        ++_pc;
        return true;
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
    else if (do_this._name == INFECT && target != nullptr){
        if (_spe != (*target)._spe){
            (*target)._spe = _spe;
            (*target)._pc = 0;
        }
    }

    ++_pc;
    return false;
}

char Creature::firstInital(){
    return tolower((*(_spe._ptr_name))[0]);
}

Darwin::Darwin(){}

Darwin::Darwin(int x, int y) : _x(x), _y(y){
    assert(_x > 0);
    assert(_y > 0);

    for(int i = 0; i < (_x*_y); ++i){
        _board.push_back(nullptr);
    }
}

void Darwin::addCreature(Creature &cr, const int &cr_x, const int &cr_y){

    if (cr_x >= _x || cr_y >= _y)
        throw invalid_argument( "invalid instruction, x or y are too high" );
    if (cr_x < 0 || cr_y < 0)
        throw invalid_argument( "invalid instruction, x or y are negative" );

    if (_board[cr_y*_x+cr_x] == nullptr)
        _board[cr_y*_x+cr_x] = &cr;
    else
        throw invalid_argument( "invalid instruction, that cell is occupied" );
}

void Darwin::simulate(int cycles){
    //int is the j, bool will be true if we shouldn't execute this creature
    unordered_map<int,bool> _map;
    object foo = EMPTY;
    Creature * bar = nullptr;

    for (int i = 0; i<= cycles; i++){        //loop for cycles
        (*this).show(i);
        _map.clear();
        for (int j =0; j< _x*_y; j++){

            if(_board[j] != nullptr){
                try{
                    _map.at(j);
                }
                //if we catch an exception, it means that creature hasn't been mapped and hasn't had a turn
                catch(const std::out_of_range& oor){

                    //get the object and the target!
                    if ( *((*(_board[j]))._ptr_dir) == NORTH){
                        if (j < _x){
                            foo = WALL;
                            bar = nullptr;
                        }
                        else if(_board[j -_x] == nullptr){
                            foo = EMPTY;
                            bar = nullptr;
                        }
                        else{
                            foo = ENTITY;
                            bar = _board[j-_x];
                        }
                    }
                    else if (*((*(_board[j]))._ptr_dir) == SOUTH){
                        if (j >= ((_x*_y) - _x)){
                            foo = WALL;
                            bar = nullptr;
                        }
                        else if(_board[j+_x] == nullptr){
                            foo = EMPTY;
                            bar = nullptr;
                        }

                        else{
                            foo = ENTITY;
                            bar = _board[j+_x];
                        }
                    }
                    else if (*((*(_board[j]))._ptr_dir) == EAST){
                        if ((j+1)%_x == 0){
                            foo = WALL;
                            bar = nullptr;
                        }

                        else if(_board[j+1] == nullptr){
                            foo = EMPTY;
                            bar = nullptr;
                        }

                        else{
                            foo = ENTITY;
                            bar = _board[j+1];
                        }
                    }
                    else if (*((*(_board[j]))._ptr_dir) == WEST){
                        if ((j%_x) == 0){
                            foo = WALL;
                            bar = nullptr;
                        }
                        else if(_board[j-1] == nullptr){
                            foo = EMPTY;
                            bar = nullptr;
                        }
                        else{
                            foo = ENTITY;
                            bar = _board[j-1];
                        }
                    }
                    //execute
                    if((*(_board[j])).executeAction(foo, bar)){

                        //we need to hop the creature
                        if(foo == EMPTY){
                            if ( *((*(_board[j]))._ptr_dir) == NORTH){
                                _board[j-_x] = _board[j];
                                _board[j] = nullptr;
                            }
                            else if ( *((*(_board[j]))._ptr_dir) == SOUTH){
                                _board[j+_x] = _board[j];
                                _board[j] = nullptr;
                                _map.insert(make_pair<int, bool>(j+_x, true));
                            }
                            else if ( *((*(_board[j]))._ptr_dir) == EAST){
                                _board[j+1] = _board[j];
                                _board[j] = nullptr;
                                _map.insert(make_pair<int, bool>(j+1, true));
                                //cout << "go east" << endl;
                            }
                            else if ( *((*(_board[j]))._ptr_dir) == WEST){
                                _board[j-1] = _board[j];
                                _board[j] = nullptr;
                                //cout << "go west" << endl;
                            }
                        }
                        //(*this).show();
                    }
                }
            }
        }
        // if(i == cycles)
        //     cout<<endl;
    }
}

void Darwin::show(int count){

        if (count < 10){
            cout << "Turn = " << count << "." << endl;
            cout << "  ";
            for(int i = 0; i < _x; i++)
                cout << i%10;

            for(int j = 0; j < _x*_y; j++){

                if ( (j%_x) == 0)
                    cout << "\n" << (j/_y)%10 << " ";

                if(_board[j] == nullptr){
                    cout << ".";
                }
                else{
                    cout << (*_board[j]).firstInital();
                }

            }

            cout << "\n" << endl;
        }
        else if (count % 100 == 0) {
            cout << "Turn = " << count << "." << endl;
            cout << "  ";
            for(int i = 0; i < _x; i++)
                cout << i%10;

            for(int j = 0; j < _x*_y; j++){

                if ( (j%_x) == 0)
                    cout << "\n" << (j/_y)%10 << " ";

                if(_board[j] == nullptr){
                    cout << ".";
                }
                else{
                    cout << (*_board[j]).firstInital();
                }

            }

            cout << "\n" << endl;
        }
}