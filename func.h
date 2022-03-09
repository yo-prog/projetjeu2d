#ifndef Image_H
#define Image_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
typedef struct
{
	SDL_Rect posecran;
	SDL_Surface * srf;
}Surface;

typedef struct
{	
	Surface surface;
	TTF_Font *police;
	SDL_Color clr;
	char *fp, *msg;
	int taille;
}texte;

typedef struct
{
	Mix_Music *music;
}soncontinu;

typedef struct
{
	Mix_Chunk *son;
	int actif;
}sonbref;

typedef struct
{
	Surface img;	
	int actif;
}Bouton;

typedef struct
{
	Surface img;
	Bouton *boutons;
	texte *textes;
	int nbbt, nbtxt;
}menu;

void initimage(Surface *img, char fim[], int x, int y, int w, int h);
void inittext(texte *txt, char fp[],char m[], int t, int x, int y, int w, int h, int r, int g, int b);
void initsoncontinu(soncontinu *music, char fm[]);
void initsonbref(sonbref *son, char fs[]);
void initmenus(menu *menuprinc, menu *menuoption);
void initBouton(Bouton *bt, char fim[], int x, int y, int w, int h);
void initboutons(menu *menuprinc, menu *menuoption);
void mousemotionbouton(SDL_Event event, Bouton boutons[], int n, sonbref *son);
void affichersurface(Surface p, SDL_Surface *screen);
void affichermenu(menu menu, sonbref son, SDL_Surface *screen);
void afficherboutons(Bouton boutons[], int n, sonbref son, SDL_Surface *screen);
void liberer(menu *menu);

#endif

