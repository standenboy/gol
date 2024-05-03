#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <string.h>
#include "draw.h"
#include "screen.h"

int initGrid[GHEIGHT][GWIDTH];
int initNewGrid[GHEIGHT][GWIDTH];
int (*grid)[GWIDTH] = initGrid;

bool paused = true;

int countFriends(int x, int y){
	int friends = 0;
	
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
			if (grid[y+i][x+j] == 1)
				friends++;
	if (grid[y][x] == 0)
		return friends;
	else
		return friends - 1;
}

int isAlive(int x, int y){
	int friends = countFriends(x, y);
	if (grid[y][x] == 1){
		if (friends <= 1){
			return 0;
		}else if (friends >= 4){
			return 0;
		}else if (friends == 2){
			return 1;
		}else if (friends == 3){
			return 1;
		}
	}else{
		if (friends == 3){
			return 1;
		}
	}
	return 0;
}

void gol(){
	int (*newGrid)[GWIDTH] = initNewGrid;
	memcpy(newGrid, grid, GWIDTH * GHEIGHT * sizeof(int));


	for (int y = 0; y < GHEIGHT; y++)
		for (int x = 0; x < GWIDTH; x++)
			newGrid[y][x] = isAlive(x, y);

	memcpy(grid, newGrid, GWIDTH * GHEIGHT * sizeof(int));
}

int framecount = 0;

int main(){
	InitWindow(WIDTH, HEIGHT, "gol");
	SetTargetFPS(60);

	Camera2D camera = { 0 };
	camera.zoom = 1.0f;

	while (!WindowShouldClose()){
		framecount++;
		draw(grid, camera); 
		if (!paused){
			if (framecount % 20 == 0){	
				gol();
			}
		}

		int w = WIDTH / GWIDTH;
		int h = HEIGHT / GHEIGHT;
		Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera);

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			Vector2 mouseG = {mouse.x/w, mouse.y/h};
			grid[(int)mouseG.y][(int)mouseG.x] = 1;
		}
		else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
			Vector2 mouseG = {mouse.x/w, mouse.y/h};
			grid[(int)mouseG.y][(int)mouseG.x] = 0;
		}
		if (IsKeyDown(KEY_P)){
			if (paused){
				paused = false;
			} else{
				paused = true;
			}
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f/camera.zoom);

			camera.target = Vector2Add(camera.target, delta);
		}

		float wheel = GetMouseWheelMove();
		if (wheel != 0){
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

			camera.offset = GetMousePosition();
			camera.target = mouseWorldPos;

			const float zoomIncrement = 0.125f;

			camera.zoom += (wheel*zoomIncrement);
			if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
		}
	}

	CloseWindow();
}
