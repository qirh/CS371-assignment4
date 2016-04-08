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
  instruction a; a._name = "hop";
  instruction b; b._name = "left";
  instruction c; c._name = "right";
  instruction d; d._name = "if_wall"; d._branch = 3;

  vector<instruction> tmp (a, b, b, c, d);

  Species food ("food");
  food.addInstruction("hop");
  food.addInstruction("left");
  food.addInstruction("left");
  food.addInstruction("right");
  food.addInstruction("if_wall", 3);

  ASSERT_EQ(food._instructions_set, tmp);

}
TEST(SpeciesFixture, addInstruction_2)
{
}
TEST(SpeciesFixture, addInstruction_3)
{
}
TEST(SpeciesFixture, addInstruction_4)
{
}
TEST(SpeciesFixture, addInstruction_5)
{
}
TEST(SpeciesFixture, addInstruction_6)
{
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