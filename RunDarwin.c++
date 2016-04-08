// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ----------
    // darwin 8x8
    // ----------

     Species food("food");
     food.addInstruction("LEFT");
     food.addInstruction("GO", 0);

     Species hopper("hopper");
     hopper.addInstruction("HOP");
     hopper.addInstruction("GO", 0);

     Species rover("rover");
     rover.addInstruction("IF_ENEMY", 9);
     rover.addInstruction("IF_EMPTY", 7);
     rover.addInstruction("IF_RANDOM", 5);
     rover.addInstruction("LEFT");
     rover.addInstruction("GO", 0);
     rover.addInstruction("RIGHT");
     rover.addInstruction("GO", 0);
     rover.addInstruction("HOP");
     rover.addInstruction("GO", 0);
     rover.addInstruction("INFECT");
     rover.addInstruction("GO", 0);

     Species trap("trap");
     trap.addInstruction("IF_ENEMY", 3);
     trap.addInstruction("LEFT");
     trap.addInstruction("GO", 0);
     trap.addInstruction("INFECT");
     trap.addInstruction("GO", 0);

    cout << "*** Darwin 8x8 ***" << endl;
    srand(0);
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */

    Creature t1_f1(food, 1);
    Creature t1_h1(hopper, 0);
    Creature t1_h2(hopper, 1);
    Creature t1_h3(hopper, 2);
    Creature t1_h4(hopper, 3);
    Creature t1_f2(food, 0);

    Darwin t1_board(8, 8);
    t1_board.addCreature(t1_f1, 0, 0);
    t1_board.addCreature(t1_h1, 3, 3);
    t1_board.addCreature(t1_h2, 4, 3);
    t1_board.addCreature(t1_h3, 4, 4);
    t1_board.addCreature(t1_h4, 3, 4);
    t1_board.addCreature(t1_f2, 7, 7);
    t1_board.simulate(5);

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */

    Creature t2_t1(trap, 2);
    Creature t2_h1(hopper, 1);
    Creature t2_r1(rover, 0);
    Creature t2_t2(trap, 3);

    Darwin t2_board(9, 7);
    t2_board.addCreature(t2_t1, 0, 0);
    t2_board.addCreature(t2_h1, 2, 3);
    t2_board.addCreature(t2_r1, 4, 5);
    t2_board.addCreature(t2_t2, 8, 6);
    t2_board.simulate(5);

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    Creature t3_f1(food, 1);
    Creature t3_f2(food, 1);
    Creature t3_f3(food, 1);
    Creature t3_f4(food, 1);
    Creature t3_f5(food, 1);
    Creature t3_f6(food, 1);
    Creature t3_f7(food, 1);
    Creature t3_f8(food, 1);
    Creature t3_f9(food, 1);
    Creature t3_f10(food, 1);
    Creature t3_h1(hopper, 2);
    Creature t3_h2(hopper, 3);
    Creature t3_h3(hopper, 1);
    Creature t3_h4(hopper, 0);
    Creature t3_h5(hopper, 1);
    Creature t3_h6(hopper, 3);
    Creature t3_h7(hopper, 3);
    Creature t3_h8(hopper, 2);
    Creature t3_h9(hopper, 1);
    Creature t3_h10(hopper, 0);
    Creature t3_r1(rover, 2);
    Creature t3_r2(rover, 0);
    Creature t3_r3(rover, 1);
    Creature t3_r4(rover, 1);
    Creature t3_r5(rover, 3);
    Creature t3_r6(rover, 3);
    Creature t3_r7(rover, 0);
    Creature t3_r8(rover, 2);
    Creature t3_r9(rover, 1);
    Creature t3_r10(rover, 2);
    Creature t3_t1(trap, 0);
    Creature t3_t2(trap, 1);
    Creature t3_t3(trap, 2);
    Creature t3_t4(trap, 3);
    Creature t3_t5(trap, 0);
    Creature t3_t6(trap, 0);
    Creature t3_t7(trap, 1);
    Creature t3_t8(trap, 1);
    Creature t3_t9(trap, 2);
    Creature t3_t10(trap, 2);

    Darwin t3_board(72, 72);

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;}