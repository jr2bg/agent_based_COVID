// g++ GOL_sdl.cpp -w -lSDL2 -lSDL2_image -o GOL


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using std::vector;


int main( int argc, char* args[] ){ 
  // pp_side -> pixels per side
  // n_cell -> identificar el barrido del array, para el render
  const int n_rows = 250, n_cols = 250, pp_side = 3, pp_line = 0;
  int i, j; // contadores para barrido
  int r, c; // row y column

  bool is_init = true;


  //Screen dimension constants
  const int SCREEN_WIDTH = n_cols * (pp_side + pp_line)-pp_line;
  const int SCREEN_HEIGHT = n_rows * (pp_side + pp_line)-pp_line;
  const int TOTAL_CELLS = n_rows * n_cols;


  // inicializando los gráficos
  SDL_Window  * window = nullptr;
  SDL_Renderer * renderer = nullptr;
  SDL_Texture * texture = nullptr;
  SDL_Surface * surface = nullptr;


  window = SDL_CreateWindow("GRapHics",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							SCREEN_WIDTH,
							SCREEN_HEIGHT,
							SDL_WINDOW_SHOWN);


  renderer = SDL_CreateRenderer( window, -1,
								SDL_RENDERER_ACCELERATED);


  SDL_SetRenderDrawColor( renderer, 165, 165, 165, 255 );

  bool quit = false;

  SDL_Event e;

  while(!quit){
	while ( SDL_PollEvent(&e) !=0 ){
	  if (e.type == SDL_QUIT){
				quit = true;
			}
      if (is_init){
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_RETURN: // enter presionado
				is_init = false;
			}
		}

		// selección de los cuadros negros
		else if (e.button.button == SDL_BUTTON_LEFT){
			printf("--- LEFT PUSHED---\n");
			r = e.button.y/ (pp_side + pp_line);
			c = e.button.x/ (pp_side + pp_line);
			printf("x ->  %d; y -> %d\n", e.button.x, e.button.y);
			printf("c ->  %d; r -> %d\n",r,c);

		
		}
	  }
    }

    //Clear screen; gray background
	SDL_SetRenderDrawColor( renderer, 165, 165, 165, 255 );
	SDL_RenderClear( renderer );
	
    /*
	//Render white filled quad
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

	// creación de las posiciones de los cuadros
	for (r = 0; r < n_rows; r++){
	  for (c = 0; c < n_cols ; c++){
	    // para células vivas
        if (lattice[r][c] == 1){
	      live_cells.push_back({c*(pp_side +pp_line),r * (pp_side +pp_line), pp_side, pp_side});
	    }
	    // para células muertas
        else {
		  death_cells.push_back({c*(pp_side +pp_line),r * (pp_side +pp_line), pp_side, pp_side});
	    }
	  }
	}
	// renderización
	for (auto const &w : death_cells) {
	  SDL_RenderFillRect( renderer, &w);
	}

	//Render black filled quad
	SDL_SetRenderDrawColor( renderer,0, 0, 0, 255 );
	for (auto const &w : live_cells) {
	  SDL_RenderFillRect( renderer, &w);
	}
    */
	//Update screen
	SDL_RenderPresent( renderer );
	// delay de 100 milisegundos
	SDL_Delay(100);
	// free memory de los vectores con las células vivas y muertas
	//death_cells.clear();
	//live_cells.clear();

	// mientras corresponda a la parte de GOL
	if (!is_init){
	  printf("****---------   EVOLUCION  ------------*****\n" );
	  //evolution(lattice, neighbourhood, n_rows, n_cols, n_lattice);
	}
  }
  // destruir el render y window
  SDL_DestroyRenderer( renderer );
  SDL_DestroyWindow( window );
  window = nullptr;
  renderer = nullptr;

  // quitando partes de los gráficos
  IMG_Quit();
  SDL_Quit();


  return 0;

}
