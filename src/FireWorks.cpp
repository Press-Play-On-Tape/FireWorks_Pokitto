#include "FireWorks.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;

}

void Game::loop() {

    PD::clear();
    PC::buttons.pollButtons();

    switch (this->gameState) {

        case GameState::Splash:
            this->splashScreen();
            break;

        case GameState::Title_Init:
            this->title_Init();
            [[fallthrough]]

        case GameState::Title:
            this->title();
            break;

        case GameState::Game_Init:
            this->muteTheme();
            this->game_Init();
            [[fallthrough]]

        case GameState::ShowTarget_Init:
            this->showTarget_Init();
            [[fallthrough]]

        case GameState::ShowTarget:
            this->showTarget();
            break;

        case GameState::Game:
            this->game();
            break;

        case GameState::TargetAchieved_Init:
            this->targetAchieved_Init();
            [[fallthrough]]

        case GameState::TargetAchieved:
            this->targetAchieved();
            break;

        case GameState::ShowOver_Init:
            this->showOver_Init();
            [[fallthrough]]

        case GameState::ShowOver:
            this->showOver();
            break;

        case GameState::Instructions_Init:
            this->instructions_Init();
            [[fallthrough]]

        case GameState::Instructions:
            this->instructions();
            break;

    }

}
