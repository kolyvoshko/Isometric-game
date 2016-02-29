#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "game_state.h"
#include "gui.h"

class GameStateStart : public GameState
{
    private:

    sf::View view;

    std::map<std::string, Gui> guiSystem;

    void new_game();
    void load_game();
    void editor();
    void exit();
    
    public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    GameStateStart(Game* game);
};

#endif /* GAME_STATE_START_HPP */
