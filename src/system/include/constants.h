#pragma once

/*
 * In this file we define some global constants.
 *
 * Please note that the problem with global variables
 * is that anyone can change them whenever which makes
 * it extremely hard to reason about your code. But for
 * constants, this is not a problem since we cannot
 * change them, and therefore they stay the same during
 * the entire execution of the program.
 */

/*
 * define the size of the window.
 */
int const screen_width  { 800 };
int const screen_height { 600 };

/*
 * define how many fps we want our program to run in.
 */
double const fps { 60.0 };
