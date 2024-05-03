#include <raylib.h>
#include <rlgl.h>
#include "screen.h"

void draw(int grid[GWIDTH][GHEIGHT], Camera2D cam){
	int w = WIDTH / GWIDTH;
	int h = HEIGHT / GHEIGHT;
	BeginDrawing();
	ClearBackground(BLACK);
	BeginMode2D(cam);
	for (int i = 0; i < GWIDTH; i++){
		for (int j = 0; j < GHEIGHT; j++){
			if (grid[j][i] == 1){
				DrawRectangle(w * i, h * j, w, h, RED);
			}
		}
	}
	EndMode2D();
	EndDrawing();
}
