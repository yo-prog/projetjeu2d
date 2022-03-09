#include "func.h"
int main(int argc, char ** argv)
{
	int i, d, continu=1, niveau=0, vol=MIX_MAX_VOLUME/2;
	SDL_Surface *screen=NULL;
	menu menuprinc, menuoption;
	soncontinu music;
	sonbref son;
	SDL_Event event;
	TTF_Init();
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) !=0)
	{
		printf("Erreur: %s \n", SDL_GetError());
		return 1;
	}
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)==-1);
	{
		printf("%s", Mix_GetError());
	}
	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF|SDL_RESIZABLE | SDL_FULLSCREEN);
	if(screen ==NULL)
	{	
		printf("Erreur: %s \n", SDL_GetError());
		return 1;
	}
	initmenus(&menuprinc, &menuoption);
	initsoncontinu(&(music), "music.mp3");
	initsonbref(&son, "mouseover.wav");
	Mix_PlayMusic(music.music, -1);
	while(continu)
	{
		if(niveau==0)
			affichermenu(menuprinc, son, screen);
		else
			affichermenu(menuoption, son, screen);
		SDL_PollEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
			continu=0;
			break;
			case SDL_KEYDOWN:
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_j:
					break;
					case SDLK_o:
					niveau=1;
					break;
					case SDLK_q:
					continu=0;
					break;
					case SDLK_KP_PLUS:
					vol+=10;
					printf("%d", vol);
					Mix_VolumeMusic(vol);
					break;
					case SDLK_MINUS:
					case SDLK_f:
					break;
					case SDLK_n:
					case SDLK_ESCAPE:
					continu=0;
					break;			
				}
				break;
			}
			case SDL_MOUSEMOTION:
			if(niveau==0)
				mousemotionbouton(event,  menuprinc.boutons, menuprinc.nbbt, &son);
			else if(niveau==1)
				mousemotionbouton(event,  menuoption.boutons, menuprinc.nbbt, &son);
			break;
			case SDL_MOUSEBUTTONUP:
			if(niveau==0)
			{
				if(menuprinc.boutons[4].actif==1)
					niveau=1;
				else if(menuprinc.boutons[5].actif==1)
					continu=0;
			}
			else
			{
				if(menuoption.boutons[5].actif==1)
					niveau=0;
			}
			break;
		}
		event.type=0;
		SDL_Flip(screen);
	}
	liberer(&menuprinc);
	liberer(&menuoption);
	Mix_FreeMusic(music.music);
	Mix_FreeChunk(son.son);
	TTF_Quit();
	return 0;
}

