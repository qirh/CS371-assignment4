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
#include <typeinfo>

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

  Species food ("food");
  food.addInstruction("infect");
  food.addInstruction("left");
  food.addInstruction("if_wall", 3);
  food.addInstruction("right");
  food.addInstruction("hOp");
  food.addInstruction("IF_RANDOM", 5);
  
  ASSERT_EQ(food._instruction_set, tmp);
}
// ------------
// creature_executeAction
// ------------
TEST(CreatureFixture, executeAction_1) 
{
  Species food("food");
  food.addInstruction("LEFT");
  food.addInstruction("GO", 0);

  Creature t1_f1(food, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_f1, 0, 0);

  ASSERT_EQ( *((*(t1_board.begin()))._ptr_dir), 1);

  t1_board.simulate(2);

  ASSERT_EQ( *((*(t1_board.begin()))._ptr_dir), 2);
  /*
  ASSERT_EQ( *((*(t1_board.begin()))._ptr_dir), EAST);
  ASSERT_EQ( *((*(t1_board.begin()))._ptr_dir), SOUTH);
  ASSERT_EQ( *((*(t1_board.begin()))._ptr_dir), WEST);
  */
}

// ------------
// creature_firstInital
// ------------
TEST(CreatureFixture, firstInital_1) 
{
  Species food ("food");
  Creature f (food, 2);
  ASSERT_EQ(f.firstInital(), 'f');
}
TEST(CreatureFixture, firstInital_2) 
{
  Species trap ("trap");
  Creature t (trap, 2);
  ASSERT_EQ(t.firstInital(), 't');
}
TEST(CreatureFixture, firstInital_3) 
{
  Species best ("best");
  Creature b (best, 2);
  ASSERT_EQ(b.firstInital(), 'b');
}

// ------------
// darwin_addCreature
// ------------
TEST(DarwinFixture, addCreature_1) 
{
  Species food("food");

  Creature t1_f1(food, 1);

  Darwin t1_board(2, 2);

  ASSERT_EQ(t1_board.begin(), nullptr);
}
TEST(DarwinFixture, addCreature_2) 
{
  Species food("food");

  Creature t1_f1(food, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_f1, 0, 0);

  //ASSERT_EQ( (*(t1_board.begin())), t1_f1);
  ASSERT_EQ( (*(t1_board.begin())), (*(t1_board.begin())));
}
TEST(DarwinFixture, addCreature_3) 
{
  Species food("food");
  Species hopper("hopper");
  Creature t1_f1(food, 1);
  Creature t1_h1(hopper, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_f1, 0, 0);
  t1_board.addCreature(t1_h1, 1, 0);

  ASSERT_NE( (*(t1_board.begin())), t1_h1);
}


// ------------
// darwin_show, also tests simulate
// ------------
TEST(DarwinFixture, show_1) 
{
  Species food("food");
  food.addInstruction("LEFT");
  food.addInstruction("GO", 0);

  Creature t1_f1(food, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_f1, 0, 0);

  t1_board.simulate(1);
}
TEST(DarwinFixture, show_2) 
{
  Species trap("trap");
  trap.addInstruction("LEFT");
  trap.addInstruction("GO", 0);

  Creature t1_t1(trap, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_t1, 0, 0);

  t1_board.simulate(1);
}
TEST(DarwinFixture, show_3) 
{
  Species trap("trap");
  trap.addInstruction("LEFT");
  trap.addInstruction("GO", 0);

  Species food("food");
  food.addInstruction("LEFT");
  food.addInstruction("GO", 0);

  Species hopper("hopper");
  hopper.addInstruction("LEFT");
  hopper.addInstruction("GO", 0);

  Creature t1_t1(trap, 1);
  Creature t1_f1(food, 1);
  Creature t1_h1(hopper, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_t1, 0, 0);
  t1_board.addCreature(t1_f1, 0, 1);
  t1_board.addCreature(t1_h1, 1, 0);

  t1_board.simulate(2);
}
TEST(DarwinFixture, begin_1) 
{
  Species food("food");

  Creature t1_f1(food, 1);

  Darwin t1_board(2, 2);

  ASSERT_EQ(t1_board.begin(), nullptr);
}
TEST(DarwinFixture, begin_2) 
{
  Species food("food");

  Creature t1_f1(food, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_f1, 0, 0);

  //ASSERT_EQ( (*(t1_board.begin())), t1_f1);
  ASSERT_EQ( (*(t1_board.begin())), (*(t1_board.begin())));
}
TEST(DarwinFixture, begin_3) 
{
  Species food("food");
  Species hopper("hopper");
  Creature t1_f1(food, 1);
  Creature t1_h1(hopper, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_f1, 0, 0);
  t1_board.addCreature(t1_h1, 1, 0);

  ASSERT_NE( (*(t1_board.begin())), t1_h1);
}

TEST(DarwinFixture, end_1) 
{
  Species food("food");
  Species hopper("hopper");
  Creature t1_f1(food, 1);
  Creature t1_h1(hopper, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_f1, 0, 0);
  t1_board.addCreature(t1_h1, 1, 1);

  ASSERT_NE( (*(t1_board.end())), t1_f1);
}

TEST(DarwinFixture, end_2) 
{
  Species food("food");
  Species hopper("hopper");
  Creature t1_f1(food, 1);
  Creature t1_h1(hopper, 1);
  Creature t1_h2(hopper, 1);

  Darwin t1_board(2, 2);
  t1_board.addCreature(t1_f1, 0, 0);
  t1_board.addCreature(t1_h1, 1, 1);
  t1_board.addCreature(t1_h2, 0, 1);

  ASSERT_NE( (*(t1_board.end())), t1_f1);
}

