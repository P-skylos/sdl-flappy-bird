#include <SDL.h>
#include <iostream>

struct coord
{
	int x;
	int y;
};

int probe(int seed, int max){
	return ((seed + 47)*67)%max;
}

void render_pillar(coord& c, SDL_Rect& pillar, SDL_Renderer* renderer){
	int gap = 200;
	pillar.x =c.x;
	pillar.y = c.y-pillar.h;
	SDL_RenderFillRect(renderer, &pillar);
	pillar.y = c.y+gap;
	SDL_RenderFillRect(renderer, &pillar);
	if (pillar.x < -pillar.w){c.x = 700; c.y = probe(c.y, 400);}
}
//game declarations
int y_velocity = 1;
int x_velocity = 3;
int gravity    = 1;
int jump_accel = 10;
coord pillars[] = {{500,17}, {800, 107}, {1100, 83}};
SDL_Rect pillar{500,10,100,480}; //x,y,w,h
SDL_Rect bird{10,250, 40, 40};

int main(int argc, char** argv){
	//declare handles which will be bound by reference later
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event e;

	//init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	return 1;
	}

	//bind here
	SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);


	//main loop
	bool running = true;
	while(running){
		//event handling
		while(SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){running=false;}
			if (e.type == SDL_KEYDOWN){
				switch(e.key.keysym.sym){
					case SDLK_SPACE:
						y_velocity = jump_accel;
						break;
				}
			}
		}

		//backdrop
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);

		//pillar
		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		for (coord& c:pillars){
			render_pillar(c, pillar, renderer);
			c.x -= x_velocity;
		}

		//bird
		bird.y -= y_velocity;
		SDL_SetRenderDrawColor(renderer,255,100,0,255);
		SDL_RenderFillRect(renderer, &bird);

		//draw
		SDL_RenderPresent(renderer);
		SDL_Delay(20);

		//gravity
		if (y_velocity > -5) {y_velocity -= gravity;} //smaller number goes up
		// std::cerr<<x_velocity<<':'<<pillars[0]<<'\n';
		if (bird.y > 450) {
			bird.y=450;
			//y_velocity=0;
		}

		//collision

	}

}