#include <SDL/SDL.h>
#include "func.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

void initimage(Surface *img, char fim[], int x, int y, int w, int h)
{
	img->srf = NULL;
	img->srf=IMG_Load(fim);
	if(img->srf == NULL)
	{
		printf("Unable to load image: %s\n", SDL_GetError());
		return;
	}
	img->posecran.x=x;
	img->posecran.y=y;
	img->posecran.w=w;
	img->posecran.h=h;
}
void inittext(texte *txt, char fp[], char m[],int t, int x, int y, int w, int h, int r, int g, int b)
{
	int n;
	n=strlen(fp);
	txt->fp=(char*)malloc(n*sizeof(char));
	strcpy(txt->fp, fp);
	n=strlen(m);
	txt->msg=(char*)malloc(n*sizeof(char));
	strcpy(txt->msg, m);
	txt->taille=t;
	txt->police=TTF_OpenFont(fp, t);
	txt->clr.r=r;
	txt->clr.g=g;
	txt->clr.b=b;
	txt->surface.srf=NULL;
	txt->surface.srf=TTF_RenderText_Blended(txt->police, txt->msg, txt->clr);
	if(txt->surface.srf == NULL)
	{
		printf("Unable to load image: %s\n", SDL_GetError());
		return;
	}
	txt->surface.posecran.x=x;
	txt->surface.posecran.y=y;
	txt->surface.posecran.w=w;
	txt->surface.posecran.h=h;
}
void initsoncontinu(soncontinu *music, char fm[])
{
	music->music=NULL;
	music->music = Mix_LoadMUS(fm);
	if( music->music == NULL )
	{
		printf("Unable to load music: %s\n", SDL_GetError());
		return ;    
	}
}

void initsonbref(sonbref *son, char fs[])
{
	son->son=NULL;
	son->son=Mix_LoadWAV(fs);
	if( son->son == NULL )
	{
		printf("Unable to load sound: %s\n", SDL_GetError());
		return ;    
	}
	son->actif=0;
	
}

void initmenus(menu *menuprinc, menu *menuoption)
{
	initimage(&(menuprinc->img),"menubackg.png", 0, 0, 0, 0);
	menuprinc->nbtxt=1;
	menuprinc->textes=(texte*) malloc (sizeof(texte));
	inittext(menuprinc->textes, "Masterina.ttf", "Chrono-paradox", 65, 640/4-35, 0, 155, 57, 255, 255, 0);
	initimage(&(menuoption->img),"optionbackg.png", 0, 0, 0, 0);
	initboutons(menuprinc, menuoption);
	menuoption->nbtxt=0;
	menuprinc->nbtxt=1;
}

void initBouton(Bouton *bt, char fim[], int x, int y, int w, int h)
{
	initimage(&(bt->img), fim, x, y, w, h);	
	bt->actif=0;
}

void initboutons(menu *menuprinc, menu *menuoption)
{
	menuprinc->nbbt=6;
	menuoption->nbbt=6;
	menuprinc->boutons=(Bouton*)malloc(sizeof(Bouton)*menuprinc->nbbt);
	menuoption->boutons=(Bouton*)malloc(sizeof(Bouton)*menuoption->nbbt);

	initBouton(menuprinc->boutons, "play.png", 640/2-155/2, 194, 155, 33);
	initBouton(menuprinc->boutons+1, "settings.png", 640/2-155/2, 261, 157, 24);
	initBouton(menuprinc->boutons+2, "quit.png", 640/2-155/2, 328, 155, 26);
	initBouton(menuprinc->boutons+3, "playselected.png", 640/2-155/2, 194, 155, 33);
	initBouton(menuprinc->boutons+4, "settingsselected.png", 640/2-155/2, 261, 155, 24);
	initBouton(menuprinc->boutons+5, "quitselected.png", 640/2-155/2, 328, 155, 24);
	
	initBouton(menuoption->boutons, "modefullscreensombre.jpg", 640/2-155/2, 145, 135, 49);
	initBouton(menuoption->boutons+1, "modenormalsombre.jpg", 640/2-155/2, 204, 137, 50);
	initBouton(menuoption->boutons+2, "quitteroptionsombre.jpg", 640/2-155/2, 264, 197, 70);
	initBouton(menuoption->boutons+3, "modefullscreenclair.jpg", 640/2-155/2, 145, 135, 49);
	initBouton(menuoption->boutons+4, "modenormalclair.jpg", 640/2-155/2, 204, 137, 50);
	initBouton(menuoption->boutons+5, "quitteroptionsclair.jpg", 640/2-155/2, 264, 197, 70);

}

void mousemotionbouton(SDL_Event event, Bouton boutons[], int n, sonbref *son)
{
	int i;
	son->actif=0;
	for(i=n/2;i<n;i++)
	{
		if(event.motion.x >= boutons[i].img.posecran.x && event.motion.x <= boutons[i].img.posecran.x+boutons[i].img.posecran.w && event.motion.y>=boutons[i].img.posecran.y&& event.motion.y<=boutons[i].img.posecran.y+boutons[i].img.posecran.h)
		{
			if(boutons[i].actif==0)
			{
				son->actif=1;				
				boutons[i].actif=1;
			}

		}
		else
			boutons[i].actif=0;
	}
}

void affichersurface(Surface p, SDL_Surface *screen)
{
	SDL_BlitSurface(p.srf, NULL, screen, &p.posecran);
}

void afficherboutons(Bouton boutons[], int n, sonbref son, SDL_Surface *screen)
{
	int i, j;
	for(i=n/2;i<n;i++)
	{
		if(boutons[i].actif==1) 
			j=i;
		else 
			j=i-n/2;
		affichersurface(boutons[j].img, screen);	
	}
	if(son.actif==1)
		Mix_PlayChannel( -1, son.son, 0 );
}

void affichermenu(menu menu, sonbref son, SDL_Surface *screen)
{
	int i;
	affichersurface(menu.img, screen);
	for(i=0;i<menu.nbtxt;i++)
		affichersurface(menu.textes[i].surface, screen);
	afficherboutons(menu.boutons, menu.nbbt, son, screen);
}
void liberer(menu *menu)
{
	int i;
	SDL_FreeSurface(menu->img.srf);
	for(i=0;i<menu->nbbt;i++)
		SDL_FreeSurface(menu->boutons[i].img.srf);
	for(i=0;i<menu->nbtxt;i++)
		TTF_CloseFont(menu->textes[i].police);
}


