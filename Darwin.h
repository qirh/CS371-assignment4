//Species -> Creature -> Darwin Board

//Species has a set of instructions or a program that it runs through

//---------
// include
//---------

#include <iostream>
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

    instruction();

    bool operator == (const instruction &rhs);
};

class Species{
private:
    vector<instruction> _instructions_set;

public:
    Species();

    void addInstruction(string action);

    void addInstruction(string control, int branch);

    //return the new pc for the creature
    int executeTilAction(object obj, Creature &rhs);

    bool operator == (const Species &rhs);
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

    void executeAction(object obj, Creature &rhs);

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
