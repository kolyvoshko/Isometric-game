#include <SFML/Graphics.hpp>

#include "game_state_start.h"
#include "game_state_editor.h"
#include "game_state.h"

void GameStateStart::draw(const float dt)
{
    this->game->window.setView(this->view);

    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->game->background);

	for(auto gui : this->guiSystem) this->game->window.draw(gui.second);

	return;
}

void GameStateStart::update(const float dt)
{
}

void GameStateStart::handleInput()
{
    sf::Event event;

    sf::Vector2f mousePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view);

    while(this->game->window.pollEvent(event))
    {
        switch(event.type)
        {
            /* Close the window */
            case sf::Event::Closed:
            {
                game->window.close();
                break;
            }
            /* Resize the window */
            case sf::Event::Resized:
            {
                this->view.setSize(event.size.width, event.size.height);
                this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->view));
                sf::Vector2f pos = sf::Vector2f(event.size.width, event.size.height);
                pos *= 0.5f;
                pos = this->game->window.mapPixelToCoords(sf::Vector2i(pos), this->view);
                this->guiSystem.at("menu").setPosition(pos);
                this->game->background.setScale(
                    float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                    float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
                break;
            }
            /* Highlight menu items */
            case sf::Event::MouseMoved:
            {
                this->guiSystem.at("menu").highlight(this->guiSystem.at("menu").getEntry(mousePos));
                break;
            }
            /* Click on menu items */
            case sf::Event::MouseButtonPressed:
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    std::string msg = this->guiSystem.at("menu").activate(mousePos);

                    if(msg == "new_game")
                    {
                        this->new_game();
                    }

                    if(msg == "load_game")
                    {
                        this->load_game();
                    }

                    if(msg == "editor_game")
                    {
                        this->editor();
                    }

                    if(msg == "exit_game")
                    {
                        this->exit();
                    }
                }
                break;
            }
            case sf::Event::KeyPressed:
            {
                if(event.key.code == sf::Keyboard::Escape) this->game->window.close();
                break;
            }
            default: break;
        }
    }

    return;
}

void GameStateStart::new_game()
{
    this->game->pushState(new GameStateEditor(this->game));
    return;
}

void GameStateStart::load_game()
{
    this->game->pushState(new GameStateEditor(this->game));
    return;
}


void GameStateStart::editor()
{
    this->game->pushState(new GameStateEditor(this->game));
    return;
}


void GameStateStart::exit()
{
    this->game->window.close();
    return;
}


GameStateStart::GameStateStart(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

    this->guiSystem.emplace("menu", Gui(sf::Vector2f(600, 80), 20, false, game->stylesheets.at("button"),
        { std::make_pair(" New game", "new_game"),
          std::make_pair(" Load game", "load_game"),
          std::make_pair(" Editor", "editor_game"),
          std::make_pair(" Exit", "exit_game")
          }));

	this->guiSystem.at("menu").setPosition(pos);
    this->guiSystem.at("menu").setOrigin(300, 80*2/3);
    this->guiSystem.at("menu").show();
}
