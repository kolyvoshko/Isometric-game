#include <SFML/Graphics.hpp>

#include "game_state.h"
#include "game_state_editor.h"
#include "game_state_start.h"
#include "map.h"

void GameStateEditor::draw(const float dt)
{
	this->game->window.clear(sf::Color::Black);

	this->game->window.setView(this->guiView);
    this->game->window.draw(this->game->background);
	
    this->game->window.setView(this->gameView);

    if (this->isPause == false)
        this->world.map.draw(this->game->window, dt);

    else
        this->world.map.draw(this->game->window, 0.0);

	this->game->window.setView(this->guiView);
	for(auto gui : this->guiSystem) this->game->window.draw(gui.second);

	return;
}

void GameStateEditor::update(const float dt)
{
    if (this->isPause == false)
        this->world.update(dt);

	/* Update the info bar at the bottom of the screen */
    this->guiSystem.at("infoBar").setEntryText(0, "Day: " + std::to_string(this->world.day));
    this->guiSystem.at("infoBar").setEntryText(1, "Plant: " + std::to_string(this->world.population_plant));
    this->guiSystem.at("infoBar").setEntryText(2, "Herbivotus: " + std::to_string(long(this->world.population_herbivorus)));
    this->guiSystem.at("infoBar").setEntryText(3, "Carnivorus: " + std::to_string(long(this->world.population_carnivorus)));
	this->guiSystem.at("infoBar").setEntryText(4, tileTypeToStr(currentTile->tileType));

	return;
}

void GameStateEditor::handleInput()
{
	sf::Event event;

    sf::Vector2f guiPos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->guiView);
	sf::Vector2f gamePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->gameView);
    auto moveSpeed = [&] (int a=1) {return a*50.0f*zoomLevel;};
	
	while(this->game->window.pollEvent(event))
	{
		switch(event.type)
        {
        case sf::Event::MouseMoved:
        {
            /* Pan the camera */
            if(this->actionState == ActionState::PANNING)
            {
                sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(this->game->window) - this->panningAnchor);
                gameView.move(-1.0f * pos * this->zoomLevel);
                panningAnchor = sf::Mouse::getPosition(this->game->window);
            }
            /* Select tiles */
            else if(actionState == ActionState::SELECTING)
            {
                sf::Vector2f pos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->gameView);
                selectionEnd.x = pos.y / (this->world.map.tileSize) + pos.x / (2*this->world.map.tileSize) - this->world.map.width * 0.5 - 0.5;
                selectionEnd.y = pos.y / (this->world.map.tileSize) - pos.x / (2*this->world.map.tileSize) + this->world.map.width * 0.5 + 0.5;

                this->world.map.clearSelected();
                if(this->currentTile->tileType == TileType::GRASS)
                {
                    this->world.map.select(selectionStart, selectionEnd, {this->currentTile->tileType, TileType::WATER});
                }
                else
                {
                    this->world.map.select(selectionStart, selectionEnd,
                        {
                            this->currentTile->tileType,    TileType::FOREST,
                            TileType::WATER,                TileType::ROAD,
                            TileType::RESIDENTIAL,          TileType::COMMERCIAL,
                            TileType::INDUSTRIAL
                        });
                }

                this->guiSystem.at("selectionCostText").setEntryText(0, "$" + std::to_string(this->currentTile->cost * this->world.map.numSelected));
                if(this->world.funds <= this->world.map.numSelected * this->currentTile->cost)
                    this->guiSystem.at("selectionCostText").highlight(0);
                else
                    this->guiSystem.at("selectionCostText").highlight(-1);
                this->guiSystem.at("selectionCostText").setPosition(guiPos + sf::Vector2f(16, -16));
                this->guiSystem.at("selectionCostText").show();
            }
            /* Highlight entries of the right click context menu */
            this->guiSystem.at("rightClickMenu").highlight(this->guiSystem.at("rightClickMenu").getEntry(guiPos));
            this->guiSystem.at("editorMenu").highlight(this->guiSystem.at("editorMenu").getEntry(guiPos));

            if (event.mouseMove.x  < 0.025*this->game->window.getSize().x)
                gameView.move(moveSpeed(-1), 0);

            if (event.mouseMove.x > 0.975*this->game->window.getSize().x)
                gameView.move(moveSpeed(1), 0);

            if (event.mouseMove.y  < 0.025*this->game->window.getSize().y)
                gameView.move(0, moveSpeed(-1));

            if (event.mouseMove.y > 0.975*this->game->window.getSize().y)
                gameView.move(0, moveSpeed(1));

            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            /* Start panning */
            if(event.mouseButton.button == sf::Mouse::Middle)
            {
                this->guiSystem.at("rightClickMenu").hide();
                this->guiSystem.at("selectionCostText").hide();

                if(this->actionState != ActionState::PANNING)
                {
                    this->actionState = ActionState::PANNING;
                    this->panningAnchor = sf::Mouse::getPosition(this->game->window);
                }
            }
            else if(event.mouseButton.button == sf::Mouse::Left)
            {
                /* Select a context menu entry */
                if(this->guiSystem.at("rightClickMenu").visible == true){
                    std::string msg = this->guiSystem.at("rightClickMenu").activate(guiPos);
                    if(msg != "flatten" && msg != "null") this->currentTile = &this->game->tileAtlas.at(msg);

                    this->guiSystem.at("rightClickMenu").hide();
                }
                /* Select map tile */
                else
                {
                    /* Select map tile */
                    if(this->actionState != ActionState::SELECTING)
                    {
                        this->actionState = ActionState::SELECTING;
                        selectionStart.x = gamePos.y / (this->world.map.tileSize) + gamePos.x / (2*this->world.map.tileSize) - this->world.map.width * 0.5 - 0.5;
                        selectionStart.y = gamePos.y / (this->world.map.tileSize) - gamePos.x / (2*this->world.map.tileSize) + this->world.map.width * 0.5 + 0.5;
                    }
                }

                if(this->guiSystem.at("editorMenu").visible == true){
                    std::string msg = this->guiSystem.at("editorMenu").activate(guiPos);
                    // TODO: save and load not implemented
                    if(msg == "save"){};
                    if(msg == "load"){};
                    if(msg == "main_menu"){
                        this->game->pushState(new GameStateStart(this->game));
                        this->guiSystem.at("editorMenu").hide();
                    }

                    if(msg == "exit"){
                        this->game->window.close();
                    }
                }
            }
            else if(event.mouseButton.button == sf::Mouse::Right)
            {
                /* Stop selecting */
                if(this->actionState == ActionState::SELECTING)
                {
                    this->actionState = ActionState::NONE;
                    this->guiSystem.at("selectionCostText").hide();
                    this->world.map.clearSelected();
                }
                else
                {
                    /* Open the tile select menu */
                    sf::Vector2f pos = guiPos;

                    if(pos.x > this->game->window.getSize().x - this->guiSystem.at("rightClickMenu").getSize().x)
                    {
                        pos -= sf::Vector2f(this->guiSystem.at("rightClickMenu").getSize().x, 0);
                    }
                    if(pos.y > this->game->window.getSize().y - this->guiSystem.at("rightClickMenu").getSize().y)
                    {
                        pos -= sf::Vector2f(0, this->guiSystem.at("rightClickMenu").getSize().y);
                    }
                    this->guiSystem.at("rightClickMenu").setPosition(pos);
                    this->guiSystem.at("rightClickMenu").show();
                }
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            /* Stop panning */
            if(event.mouseButton.button == sf::Mouse::Middle)
            {
                this->actionState = ActionState::NONE;
            }
            /* Stop selecting */
            else if(event.mouseButton.button == sf::Mouse::Left)
            {
                if(this->actionState == ActionState::SELECTING)
                {
                    /* Replace tiles if enough funds and a tile is selected */
                    if(this->currentTile != nullptr)
                    {
                        unsigned int cost = this->currentTile->cost * this->world.map.numSelected;
                        if(this->world.funds >= cost)
                        {
                            this->world.bulldoze(*this->currentTile);
                            this->world.funds -= this->currentTile->cost * this->world.map.numSelected;
                            this->world.tileChanged();
                        }
                    }
                    this->guiSystem.at("selectionCostText").hide();
                    this->actionState = ActionState::NONE;
                    this->world.map.clearSelected();
                }
            }
            break;
        }
        /* Zoom the view */
        case sf::Event::MouseWheelMoved:
        {
            if(event.mouseWheel.delta < 0)
            {
                gameView.zoom(2.0f);
                zoomLevel *= 2.0f;
            }
            else
            {
                gameView.zoom(0.5f);
                zoomLevel *= 0.5f;
            }
            break;
        }
        /* Close the window */
        case sf::Event::Closed:
        {
            this->game->window.close();
            break;
        }
        /* Resize the window */
        case sf::Event::Resized:
			{
				gameView.setSize(event.size.width, event.size.height);
				gameView.zoom(zoomLevel);
				guiView.setSize(event.size.width, event.size.height);
				this->guiSystem.at("infoBar").setDimensions(sf::Vector2f(event.size.width / this->guiSystem.at("infoBar").entries.size(), 16));
				this->guiSystem.at("infoBar").setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, event.size.height - 16), this->guiView));
				this->guiSystem.at("infoBar").show();
                this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
                this->game->background.setScale(
                    float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                    float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
				break;
			}
        /* Keyboard handle input */
        case sf::Event::KeyPressed:
        {
            switch (event.key.code)
            {
            /* Enter to menu */
            case sf::Keyboard::Escape:{
                if(this->guiSystem.at("editorMenu").visible == false){
                    this->guiSystem.at("editorMenu").show();
                    this->pause();
                }

                else{
                    this->guiSystem.at("editorMenu").hide();
                    this->pause();
                }

                break;
            }

            case sf::Keyboard::Up:{
                gameView.move(0, moveSpeed(-1));
                break;
            }

            case sf::Keyboard::W:{
                gameView.move(0, moveSpeed(-1));
                break;
            }

            case sf::Keyboard::Down:{
                gameView.move(0.0f, moveSpeed(1));
                break;
            }

            case sf::Keyboard::S:{
                gameView.move(0.0f, moveSpeed(1));
                break;
            }

            case sf::Keyboard::Left:{
                gameView.move(moveSpeed(-1), 0.0f);
                break;
            }

            case sf::Keyboard::A:{
                gameView.move(moveSpeed(-1), 0.0f);
                break;
            }

            case sf::Keyboard::Right:{
                gameView.move(moveSpeed(), 0.0f);
                break;
            }

            case sf::Keyboard::D:{
                gameView.move(moveSpeed(), 0.0f);
                break;
            }

            case sf::Keyboard::Add:{
                gameView.zoom(0.5f);
                zoomLevel *= 0.5f;
                break;
            }

            case sf::Keyboard::Subtract:{
                gameView.zoom(2.0f);
                zoomLevel *= 2.0f;
                break;
            }

            case sf::Keyboard::P:{
                this->pause();
                break;
            }

            case sf::Keyboard::F:{
                this->fullscreen();
                break;
            }
            default: break;
            }
        }

        default: break;

        }
    }

	return;
}

GameStateEditor::GameStateEditor(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);

    this->world = World("city", this->game->tileSize, this->game->tileAtlas);
    this->world.shuffleTiles();

    /* Create gui elements */
	this->guiSystem.emplace("rightClickMenu", Gui(sf::Vector2f(196, 16), 2, false, this->game->stylesheets.at("button"),
		{
            std::make_pair("Flatten ", "grass"),
            std::make_pair("Forest ", "forest" ),
            std::make_pair("Plant ", "plant"),
            std::make_pair("Herbivore ", "herbivore"),
            std::make_pair("Carnivore ", "carnivore")
		}));

    this->guiSystem.emplace("editorMenu", Gui(sf::Vector2f(600, 80), 20, false, this->game->stylesheets.at("button"),
        {
            std::make_pair(" Save map", "save"),
            std::make_pair(" Load map ", "load"),
            std::make_pair(" Exit to menu ", "main_menu"),
            std::make_pair(" Exit to windows ", "exit")
        }));
    this->guiSystem.at("editorMenu").setPosition(this->guiView.getSize()*0.5f);
    this->guiSystem.at("editorMenu").setOrigin(600/2, 80*2/3);

	this->guiSystem.emplace("selectionCostText", Gui(sf::Vector2f(196, 16), 0, false, this->game->stylesheets.at("text"),
		{ std::make_pair("", "") }));

	this->guiSystem.emplace("infoBar", Gui(sf::Vector2f(this->game->window.getSize().x / 5 , 16), 2, true, this->game->stylesheets.at("button"),
		{ std::make_pair("time", "time"),
        std::make_pair("plant", "plant"),
        std::make_pair("herbivore", "herbivore"),
        std::make_pair("carnivore", "carnivore"),
		std::make_pair("current tile", "tile") }));
	this->guiSystem.at("infoBar").setPosition(sf::Vector2f(0, this->game->window.getSize().y - 16));
	this->guiSystem.at("infoBar").show();
	
	this->zoomLevel = 1.0f;
	
	/* Centre the camera on the city.map */
    sf::Vector2f centre(this->world.map.width, this->world.map.height*0.5);
    centre *= float(0.5*this->world.map.tileSize);
	gameView.setCenter(centre);

    this->selectionStart = sf::Vector2i(0, 0);
    this->selectionEnd = sf::Vector2i(0, 0);
    
    this->currentTile = &this->game->tileAtlas.at("grass");
	this->actionState = ActionState::NONE;

}


void GameStateEditor::pause()
{
    if (false == this->isPause)
        this->isPause = true;

    else
        this->isPause = false;
}


void GameStateEditor::fullscreen()
{
    static bool isFullScreen = true;
    if (false == isFullScreen)
    {
        isFullScreen = true;
        this->game->window.create(sf::VideoMode(1366, 768), "GameLive", sf::Style::Fullscreen | sf::Style::Close);
    }

    else if (true == isFullScreen){
        isFullScreen = false;
        this->game->window.create(sf::VideoMode(800, 600), "Game Live", sf::Style::Default);
    }
}
