#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		SoundEffects sfx = SoundEffects::Both;
		uint32_t score = 0;


	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->sfx = SoundEffects::Both;
			this->score = 0;
			this->saveCookie();

		}
		

		uint32_t getScore() {

			return score;

		}


		void setScore(uint32_t score) {

			this->score = score;

		}

};