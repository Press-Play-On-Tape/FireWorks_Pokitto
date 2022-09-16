#include "FireWorks.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title_Init() {

    this->gameState = GameState::Title;
    this->titleScreenVars.reset();
    PC::setFrameRate(60);

    this->playTheme(Themes::Main);

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() {


//     PD::setColor(7);
//     PD::adjustLineStep = 2;

//     PD::setCursor(0,0);
// //    PD::print("ABCDEFGHIJKLM\nNOPQTSTUVWXYZ\nabcdefghijklm\nnopqrstuvwxyz\n1234567890-=\n~!@#$%^&*()_+`\n[]{};':\"<>,./?");
//     PD::print("ABCDEFGHIJKLM\nNOPQTSTUVWXYZ\nabcdefghijklm\nnopqrstuvwxyz\n1234567890-=\n!@#$%&*()_+`\n[]{};':\"<>,./?");
//     return;


    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        switch (this->titleScreenVars.menu) {

            case MenuOptions::Play:
                this->gameState = GameState::Game_Init;
                break;

            case MenuOptions::Instructions:
                this->gameState = GameState::Instructions_Init;
                break;

        }

    }         

    if (PC::buttons.pressed(BTN_LEFT)) { 

        switch (this->titleScreenVars.menu) {

            case MenuOptions::Instructions:
                this->titleScreenVars.menu = MenuOptions::Play;
                break;

            case MenuOptions::Sounds:
                this->titleScreenVars.menu = MenuOptions::Instructions;
                break;

            default: break;

        }

    }         

    if (PC::buttons.pressed(BTN_RIGHT)) { 

        switch (this->titleScreenVars.menu) {

            case MenuOptions::Play:
                this->titleScreenVars.menu = MenuOptions::Instructions;
                break;

            case MenuOptions::Instructions:
                this->titleScreenVars.menu = MenuOptions::Sounds;
                break;

            default: break;

        }

    }         

    if (this->titleScreenVars.menu == MenuOptions::Sounds) {
            
        if (PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_A)) {

            this->cookie->sfx--;
            this->cookie->saveCookie();

            if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                this->muteTheme();
                
            }
            else {

                this->playTheme(Themes::Main);

            }

        }

        if (PC::buttons.pressed(BTN_DOWN)|| PC::buttons.pressed(BTN_B)) {

            this->cookie->sfx++;
            this->cookie->saveCookie();

            if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                this->muteTheme();
                
            }
            else {

                this->playTheme(Themes::Main);
                
            }
            
        }

    }


    // Create explosions ..

    if (PC::frameCount % 60 == 0) {

        this->explode(random(10, 90), random(10, 50), static_cast<ExplosionShape>(random(0, 3)), this->gameScreenVars.getColor());

    }



    // Render particles ..

    PD::drawBitmap(0, 31, Images::City_Top);
    PD::drawBitmap(0, 57, Images::City_Bot_00);
    this->renderParticles();


    // Sounds ..

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
            PD::drawBitmap(77, 80, Images::Sound_Music);
            break;

        case SoundEffects::SFX:
            PD::drawBitmap(77, 80, Images::Sound_SFX);
            break;

        case SoundEffects::Both:
            PD::drawBitmap(77, 80, Images::Sound_Both);
            break;

        default:
            PD::drawBitmap(77, 80, Images::Sound_None);
            break;

    }

    PD::drawBitmap(8, 25, Images::Title);
    PD::drawBitmap(21, 80, Images::Options);
    PD::drawBitmap(28, 2, Images::High);

    PD::setColor(5);

    switch (this->titleScreenVars.menu) {

        case MenuOptions::Play:
            PD::drawBitmap(21, 80, Images::Play_Highlighted[Images::Highlight_Seq[(PC::frameCount % 64) / 8]]);
            break;

        case MenuOptions::Instructions:
            PD::drawBitmap(47, 80, Images::Rules_Highlighted[Images::Highlight_Seq[(PC::frameCount % 64) / 8]]);
            break;

        case MenuOptions::Sounds:

            switch (this->cookie->sfx) {

                case SoundEffects::Music:
                    PD::drawBitmap(77, 80, Images::Sound_Music_Highlighted[Images::Highlight_Seq[(PC::frameCount % 64) / 8]]);
                    break;

                case SoundEffects::SFX:
                    PD::drawBitmap(77, 80, Images::Sound_SFX_Highlighted[Images::Highlight_Seq[(PC::frameCount % 64) / 8]]);
                    break;

                case SoundEffects::Both:
                    PD::drawBitmap(77, 80, Images::Sound_Both_Highlighted[Images::Highlight_Seq[(PC::frameCount % 64) / 8]]);
                    break;

                default:
                    PD::drawBitmap(77, 80, Images::Sound_None_Highlighted[Images::Highlight_Seq[(PC::frameCount % 64) / 8]]);
                    break;

            }

            break;
            
    }

    // Render current score ..

    {
        uint8_t digits[7] = {};
        extractDigits(digits, this->cookie->getScore());

        uint8_t location = 78;

        for (uint8_t j = 0; j < 7; ++j, location -= 5) {

            PD::drawBitmap(location, 2, Images::Numbers_Title[digits[j]]);

        }

    }

}
