#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/System.hpp>
#include <string>
#include <map>

#include "game_state.h"
#include "map.h"
#include "gui.h"
#include "world.h"

enum class ActionState { NONE, PANNING, SELECTING };

class GameStateEditor : public GameState
{
	private:

    ActionState actionState;
    
	sf::View gameView;
	sf::View guiView;
    
    World world;

    sf::Vector2i panningAnchor;
    float zoomLevel;
    
    sf::Vector2i selectionStart;
    sf::Vector2i selectionEnd;
    
    Tile* currentTile;
    
    std::map<std::string, Gui> guiSystem;

    bool isPause;

    void fullscreen();
    void pause();

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateEditor(Game* game);
};

#endif /* GAME_STATE_EDITOR_HPP */
