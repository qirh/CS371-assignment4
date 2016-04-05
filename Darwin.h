#ifndef DARWIN_H
#define DARWIN_H

//Species -> Creature -> Darwin Board

//Species has a set of instructions or a program that it runs through

//---------
// include
//---------

#include <string>
#include <vector>

using namespace std;

//---------
// species
//---------

enum instr {HOP, LEFT, RIGHT, INFECT, IF_EMPTY, IF_WALL, IF_RANDOM, IF_ENEMY, GO};
enum direc {NORTH, EAST, SOUTH, WEST};
enum object {WALL, ENTITY, EMPTY};

//--------------------
// instruction struct
//--------------------

struct instruction{
public:
    instr _name;
    int _branch;
};

class Species{
private:
    vector<instruction> _instructions_set;
    string _name;

public:
    string const * _name_ptr;

    Species(string name);

    void addInstruction(string action);

    void addInstruction(string control, const int &branch);

    instruction executeTilAction(object obj, const Species &rhs, int &pc);

    bool operator == (const Species &rhs);

    bool operator != (const Species &rhs);
};

//-----------
// creatures
//-----------

class Creature{
private:
    Species _spe;
    int _pc;
    direc _dir;

public:
    direc const * _ptr_dir;

    Creature(Species spe, int dir);

    void executeAction(object obj, Creature &target);

    bool isRelated(const Creature &rhs);
};


//--------
// Darwin
//--------

class Darwin{
private:
    int _x, _y;
    vector<Creature *> _board;

public:
    Darwin(int x, int y);

    addCreature(Creature cr, int cr_x, int cr_y);

    simulate(int cycles);

    show();
};

#endif