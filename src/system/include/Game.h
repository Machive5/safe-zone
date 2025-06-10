#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>

#include "State.h"

class Game {

public:

    /*
     * Constructor of Game.
     *
     * Will perform these tasks:
     * - initialize the current_state with an initial state (welcome
     *   screen),
     * - Fill the states map with the States needed during the game
     * - spawn a window with the specified titlebar, width and height
     *   (in pixels)
     */
    Game (std::string const & title, unsigned width, unsigned height);

    /*
     * Run the main loop of the state machine, and therefore by extension
     * the entire game.
     *
     * Each iteration of the main loop go through these steps:
     * - Handle all window events from the event queue (these include
     *   key presses/releases, mouse movement, resizing of the window
     *   and more).
     *
     *   What this means is that we check if the user has requested
     *   to close the window and therefore the game, and for any other
     *   events we pass them on to the state.
     * - Update the current state.
     *
     *   This means running any logic that the state might have, for
     *   example; move objects, check for collision, manage resources
     *   etc. This step will probably perform the vast majority of the
     *   logic in the project (depending on the project of course).
     *
     * - Draw the currently active state to the window.
     *
     *   This step will simply pass the window to the state and will
     *   thus allow the state to draw itself onto the windows. This
     *   is beneficial since we now have completely decoupled the
     *   state from the Game class, thus allowing all behaviour of a
     *   state to be implemented in the corresponding class without
     *   having to touch any other code.
     */
    void start ();

private:
    /*
     * SFML representation of window which we can draw on.
    */
    sf::RenderWindow window;


    /*
     * Container for all states in the game.
     * Current_state keeps track on the current state
     */
    std::map<int, std::unique_ptr<State>> states;
    int current_state;


    /*
     * If true, then the game should keep on run, otherwise the next
     * iteration of the game loop will not run.
     */
    bool running;


    void handle_events(); 

    /*
     * This function puts the program to sleep for a certain
     * period of time in order to keep a steady framerate.
     * The inargument is how many milliseconds the current iteration
     * took to complete.
     *
     * Say that the game is supposed to run at 60 frames per second (fps).
     * This means that each frame should take exactly 1000/60 = 16.666...
     * milliseconds to run. If it took longer, then there is not much
     * we can do about it, but if it took a shorter amount of time,
     * then request that our program sleep for the remaining time.
     */
    void delay (sf::Clock & clock) const;
};

#endif // GAME_H

