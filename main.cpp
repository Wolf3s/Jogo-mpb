#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#define WIDTH 640
#define HEIGHT 448

enum KEY_PRESS
{
	DEFAULT,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	TOTAL,
	NULL_KEY = 0
};

bool init_screen();

bool load_media();

void close_everything();

SDL_Surface* loadSurface(std::string path);

SDL_Window* window = NULL;

SDL_Surface* surface = NULL;

SDL_Surface* currentSurface = NULL;

SDL_Surface* keys[KEY_PRESS::TOTAL];

bool success;

bool init_screen()
{
	int ret;
	
	ret = SDL_Init(SDL_INIT_EVERYTHING);

	if(ret < 0)
	{
		std::cout << "Could not initialize sdl2";
	}

	window = SDL_CreateWindow("SDL Event", SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);	

	if(window)
	{
		surface = SDL_GetWindowSurface(window);
	}
	
	return success;
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* loaded = SDL_LoadBMP(path.c_str());
	if(loaded == NULL)
	{
		std::cout << "Could not load image! " << path.c_str() << "SDL_Error " << SDL_GetError();
	}
	return loaded;
}

bool load_media()
{
	keys[KEY_PRESS::DEFAULT] = loadSurface("assets/mpb.bmp");
	if (keys[KEY_PRESS::DEFAULT] == NULL)
	{
		std::cout << "Could not load the following image: mpb.bmp";
		return success = false;
	}

	keys[KEY_PRESS::UP] = loadSurface("assets/Construcao.bmp");
	if (keys[KEY_PRESS::UP] == NULL)
	{
		std::cout << "Could not load the following image: Construcao.bmp";
		return success = false;
	}

	keys[KEY_PRESS::LEFT] = loadSurface("assets/Chao_De_Giz.bmp");
	if(keys[KEY_PRESS::LEFT] == NULL) 
	{
		std::cout << "Could not load the following image: Chao_De_Giz.bmp";
		return success = false;
	}

	keys[KEY_PRESS::RIGHT] = loadSurface("assets/Voce_e_linda.bmp");
	if(keys[KEY_PRESS::RIGHT] == NULL)
	{
		std::cout << "Could not load the following image: Voce_e_linda.bmp";
		return success = false;
	}

	keys[KEY_PRESS::DOWN] = loadSurface("assets/Acenda_o_farol.bmp");
	if(keys[KEY_PRESS::DOWN] == NULL)
	{
		std::cout << "Could not load the following image: Acenda_o_farol.bmp";
		return success = false;
	}

	return success;
}

void close_everything()
{
	SDL_DestroyWindow(window);
	for (int i = 0; i < KEY_PRESS::TOTAL; ++i)
	{
		SDL_FreeSurface(keys[i]);
		keys[i] = NULL;
	}
	SDL_Quit();
}

int main(int args, char* argv[])
{
	 if(init_screen())
	 {
		 std::cout << "Screen could not initialize" << SDL_GetError();
	 }

	 else
	 {
	    if(load_media())
		{
			std::cout << "Could not load everything" << SDL_GetError();
		}

		bool quit = true;

		SDL_Event event;

		currentSurface = keys[KEY_PRESS::DEFAULT];

		while(quit)
		{
		   while(SDL_PollEvent(&event))
		   {
		      if(event.type == SDL_QUIT)
			  {
				  quit = false;
			  }
			  
			  else if(event.type == SDL_KEYDOWN)
			  {
				 switch(event.key.keysym.sym)
				 {
				    case SDLK_UP:
						currentSurface = keys[KEY_PRESS::UP];
						std::cout << "Pressed";
					break;
					
					case SDLK_DOWN:
						currentSurface = keys[KEY_PRESS::DOWN];
						std::cout << "Pressed";
					break;

					case SDLK_LEFT:
						currentSurface = keys[KEY_PRESS::LEFT];
						std::cout << "Pressed";
					break;

					case SDLK_RIGHT:
						currentSurface = keys[KEY_PRESS::RIGHT];
						std::cout << "Pressed";
					break;

					default:
						currentSurface = keys[KEY_PRESS::DEFAULT];
						std::cout << "Loaded";
					break;
				 }
			  }
			  SDL_BlitSurface(currentSurface, NULL, surface, NULL);
			  SDL_UpdateWindowSurface(window);
		   }
		}
	 }
	 close_everything();
	 return 0;
}