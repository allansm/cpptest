#define useSDL2

#include <allansm/simple/sdl2/init.hpp>
#include <allansm/io.hpp>

int x,y;
bool stop = false;
int main(int argc,char ** argv){
	sdl2 t;
	
	t.width = 1366;
	t.height = 768;

	t.event = [](event e){
		if(e.type == SDL_MOUSEMOTION){
			if(!stop){
				SDL_GetGlobalMouseState(&x,&y);
			}	
		}
    		if(e.type == SDL_MOUSEBUTTONDOWN){	
			if(stop){
				stop = false;
			}else{
				stop = true;
			}
		}		
	};

	t.callback = [](window win){	
		auto screenSurface = SDL_GetWindowSurface(win);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));	
		
		SDL_Rect rect = {x-50, y-50, 100, 100};
		SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
		SDL_UpdateWindowSurface(win);
	};
	
	t.start();	

	return 0;
}
