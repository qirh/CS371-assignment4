/*
  added opreator == (2)
  uppercase
*/

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"
#include "Darwin.h"

using namespace std;

// -----------
// TestDarwin
// -----------

// -----------
// species_addInstruction
// -----------
TEST(SpeciesFixture, addInstruction_1)
{
  instruction a; a._name = HOP; a._branch = -1;
  instruction b; b._name = LEFT; b._branch = -1;
  instruction c; c._name = RIGHT; c._branch = -1;
  instruction d; d._name = IF_WALL; d._branch = 3;

  vector<instruction> tmp;
  tmp.push_back(a);
  tmp.push_back(b);
  tmp.push_back(b);
  tmp.push_back(c);
  tmp.push_back(d);

  Species f ("food");
  f.addInstruction("hOp");
  f.addInstruction("left");
  f.addInstruction("left");
  f.addInstruction("right");
  f.addInstruction("if_wall", 3);
  
  ASSERT_EQ(f._instruction_set, tmp);

}

TEST(SpeciesFixture, addInstruction_2)
{
  Species f ("food");
  f.addInstruction("hoP");
  f.addInstruction("left");
  f.addInstruction("left");
  f.addInstruction("right");
  f.addInstruction("if_wall", 3);

  Species fo ("food");
  fo.addInstruction("hop");
  fo.addInstruction("left");
  fo.addInstruction("left");
  fo.addInstruction("right");
  fo.addInstruction("if_wall", 3);

  ASSERT_EQ(f._instruction_set, fo._instruction_set);
}

TEST(SpeciesFixture, addInstruction_3)
{
  instruction a; a._name = INFECT; a._branch = -1;
  instruction b; b._name = LEFT; b._branch = -1;
  instruction c; c._name = RIGHT; c._branch = -1;
  instruction d; d._name = HOP; d._branch = -1;
  instruction e; e._name = IF_WALL; e._branch = 3;
  instruction f; f._name = IF_RANDOM; f._branch = 5;

  vector<instruction> tmp;
  tmp.push_back(a);
  tmp.push_back(b);
  tmp.push_back(e);
  tmp.push_back(c);
  tmp.push_back(d);
  tmp.push_back(f);

  Species f ("food");
  f.addInstruction("infect");
  f.addInstruction("left");
  f.addInstruction("if_wall", 3);
  f.addInstruction("right");
  f.addInstruction("hOp");
  f.addInstruction("IF_RANDOM", 5);
  
  ASSERT_EQ(f._instruction_set, tmp);
}

// -----------
// species_executeTilAction
// -----------
TEST(SpeciesFixture, executeTilAction_1) 
{
}
TEST(SpeciesFixture, executeTilAction_2) 
{
}
TEST(SpeciesFixture, executeTilAction_3) 
{
}

// ------------
// creature_executeAction
// ------------
TEST(CreatureFixture, executeAction_1) 
{
}
TEST(CreatureFixture, executeAction_2) 
{
}
TEST(CreatureFixture, executeAction_3) 
{
}

// ------------
// darwin_addCreature
// ------------
TEST(DarwinFixture, addCreature_1) 
{
}
TEST(DarwinFixture, addCreature_2) 
{
}
TEST(DarwinFixture, addCreature_3) 
{
}

// ------------
// darwin_simulate
// ------------
TEST(DarwinFixture, simulate_1) 
{
}
TEST(DarwinFixture, simulate_2) 
{
}
TEST(DarwinFixture, simulate_3) 
{
}

// ------------
// darwin_show
// ------------
TEST(DarwinFixture, show_1) 
{
}
TEST(DarwinFixture, show_2) 
{
}
TEST(DarwinFixture, show_3) 
{
}