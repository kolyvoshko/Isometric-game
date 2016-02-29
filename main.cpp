#include "src/game.h"
#include "src/game_state_start.h"

int main()
{
    Game game;

    game.pushState(new GameStateStart(&game));
    game.gameLoop();

    return 0;
}
