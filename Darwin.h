#ifndef DARWIN_H
#define DARWIN_H

//Species -> Creature -> Darwin Board

//Species has a set of instructions or a program that it runs through

//---------
// include
//---------

#include <string>
#include <vector>
#include "gtest/gtest.h"
using namespace std;

//---------
// enums to hold instruction names
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

    //Equality and Inequality operators 
    bool operator == (const instruction &rhs);
    bool operator == (const instruction &rhs) const;
    bool operator != (const instruction &rhs);
    bool operator != (const instruction &rhs) const;
};

//---------
// species
//---------

class Species{
private:
    //instruction set for the species
    vector<instruction> _instruction_set;
    //name of the species
    string _name;

    FRIEND_TEST(SpeciesFixture, addInstruction_1);
    FRIEND_TEST(SpeciesFixture, addInstruction_2);
    FRIEND_TEST(SpeciesFixture, addInstruction_3);

public:
    //pointer to the name
    const string * _ptr_name;

    Species();
    Species(string name);
    //add an action instruction
    void addInstruction(string action);
    //add a control instruction
    void addInstruction(string control, const int &branch);

    /*  ***     */  instruction executeTilAction(object obj, const Species * const rhs, int &pc);

    //Equality and Inequality operators 
    bool operator == (const Species &rhs);
    bool operator == (const Species &rhs) const;
    bool operator != (const Species &rhs);
    bool operator != (const Species &rhs) const;
};

//-----------
// creatures
//-----------

class Creature{
private:
    Species _spe;
    int _pc;    //program counter
    direc _dir; //direction

public:
    //pointer for the direction
    direc const * _ptr_dir;

    Creature();

    Creature(Species spe, int dir);

    bool executeAction(object obj, Creature * const target);
    //will get the first initial of the species' name
    char firstInital();

    //Equality and Inequality operators 
    bool operator == (const Creature &rhs);
    bool operator == (const Creature &rhs) const;
    bool operator != (const Creature &rhs);
    bool operator != (const Creature &rhs) const;
};


//--------
// Darwin
//--------

class Darwin{
private:
    int _x;
    int _y;
    vector<Creature *> _board;

    FRIEND_TEST(DarwinFixture, end_1);
    FRIEND_TEST(DarwinFixture, end_2);

public:
    Darwin();

    Darwin(int x, int y);

    void addCreature(Creature &cr, const int &cr_x, const int &cr_y);

    void simulate(int cycles);

    void show(int count);

    // iterator functions
    Creature * begin();
    Creature * begin() const;
    Creature * end();
    Creature * at(int i);

    //Equality and Inequality operators 
    bool operator == (const Darwin &rhs);
    bool operator == (const Darwin &rhs) const;
    bool operator != (const Darwin &rhs);
    bool operator != (const Darwin &rhs) const;
};

#endif