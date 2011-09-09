#pragma once

#include <SDL\SDL_mixer.h>
#include <string>

class GameSound{
	public:

		GameSound(void);
		~GameSound();
		bool initSound();
		void loadSound(std::string name);
		void loadChunk(std::string name);

	private:

		Mix_Music *music;
		Mix_Chunk *effect;

};