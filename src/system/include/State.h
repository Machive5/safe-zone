#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <string>

// int const MENU_STATE{0};
int const SCENE1{0};

class State
{
public:

    // this is a base class so a virtual destructor is needed
    virtual ~State () = default;

    /*
     * This function is called for each event which occurs
     * in the window. It is the responsibility of the state
     * to filter out any events it is interested in, since
     * no filtering is performed before calling this function.
     *
     * What this means is that if a state only wants to know
     * if a certain event has happened, the state needs to
     * check for that event inside this function.
     */
    virtual void handle_event (sf::Event event) = 0;

    /*
     * The 'update' function is called every iteration of the
     * game loop, no more and no less.
     */
    virtual void update () = 0;

    /*
     * Render the state onto the screen through a 'RenderTarget'.
     *
     * A RenderTarget is an abstract class which defines an
     * interface for rendering to a canvas. Two types
     * of RenderTargets exist in SFML:
     * - RenderWindow; draw directly to a window.
     * - RenderTexture; draw onto a texture which can be extracted
     *   later on using the 'getTexture' member function.
     */
    virtual void render(sf::RenderTarget & target) = 0;

    /*
     * Return the new state if it should change,
     * otherwise return the current state
     */
    virtual int get_next_state() = 0;

};

#endif //STATE_H
