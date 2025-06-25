/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#define ARENA_OFFSET_X 35
#define ARENA_OFFSET_Y 253
#define ARENA_LENGTH 4
Vector2 arenaShape[ARENA_LENGTH] = {
	{0+ARENA_OFFSET_X, 0+ARENA_OFFSET_Y},
	{565+ARENA_OFFSET_X, 0+ARENA_OFFSET_Y},
	{565+ARENA_OFFSET_X, 130+ARENA_OFFSET_Y},
	{0+ARENA_OFFSET_X,130+ARENA_OFFSET_Y}
};
Vector2 ButtonPos[4] = {
	{27, 432},   // fight button
	{185, 432},  // act button
	{343, 432},  // item button
	{501, 432}   // mercy button
};
int button_selected = 0; // 0 = fight, 1 = act, 2 = item, 3 = mercy
Vector2 SoulPos = { 200+253, 50+35 }; // position of the soul in the arena

void DrawShape(Vector2 *shape, int numPoints, Color color)
{
	for (int i = 0; i < numPoints; i++)
	{
		int nextIndex = (i + 1) % numPoints;
		DrawLineV(shape[i], shape[nextIndex], color);
	}
}

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(640, 480, "Hello Raylib");																																																																																																							// end the frame and get ready for the next one  (displ */
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Texture actbtt = LoadTexture  ("bt/act.png");
	Texture fightbtt = LoadTexture("bt/fight.png");
	Texture itembtt = LoadTexture ("bt/item.png");
	Texture mercybtt = LoadTexture("bt/mercy.png");
	Texture actbtt_selected = LoadTexture  ("bt/act-selected.png");
	Texture fightbtt_selected = LoadTexture("bt/fight-selected.png");
	Texture itembtt_selected = LoadTexture ("bt/item-selected.png");
	Texture mercybtt_selected = LoadTexture("bt/mercy-selected.png");
	Texture hearttexture = LoadTexture("ut-heart.png");
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();
		//DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);  
		//DrawLineV(arenaShape[0], arenaShape[1], RED);
		//DrawLineV(arenaShape[1], arenaShape[2], RED);
		//DrawLineV(arenaShape[2], arenaShape[3], RED);
		//DrawLineV(arenaShape[3], arenaShape[0], RED);
		DrawShape(arenaShape, ARENA_LENGTH, RED);
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);
		// draw our texture to the screen
		switch (button_selected)
		{
		case 0:
			DrawTextureV(fightbtt_selected, ButtonPos[0], WHITE);
			DrawTextureV(actbtt,   			ButtonPos[1], WHITE);
			DrawTextureV(itembtt,  			ButtonPos[2], WHITE);
			DrawTextureV(mercybtt, 			ButtonPos[3], WHITE);
			break;
		case 1:
			DrawTextureV(fightbtt, 			ButtonPos[0], WHITE);
			DrawTextureV(actbtt_selected, 	ButtonPos[1], WHITE);
			DrawTextureV(itembtt,  			ButtonPos[2], WHITE);
			DrawTextureV(mercybtt, 			ButtonPos[3], WHITE);
			break;
		case 2:
			DrawTextureV(fightbtt, 			ButtonPos[0], WHITE);
			DrawTextureV(actbtt,   			ButtonPos[1], WHITE);
			DrawTextureV(itembtt_selected,  ButtonPos[2], WHITE);
			DrawTextureV(mercybtt, 			ButtonPos[3], WHITE);
			break;
		case 3:
			DrawTextureV(fightbtt, 			ButtonPos[0], WHITE);
			DrawTextureV(actbtt,   			ButtonPos[1], WHITE);
			DrawTextureV(itembtt,  			ButtonPos[2], WHITE);
			DrawTextureV(mercybtt_selected, ButtonPos[3], WHITE);
			break;
		default:
			break;
		}
		DrawTexture(hearttexture, ButtonPos[button_selected].x+8, ButtonPos[button_selected].y+13, WHITE);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);
	UnloadTexture(actbtt);
	UnloadTexture(fightbtt);
	UnloadTexture(itembtt);
	UnloadTexture(mercybtt);
	UnloadTexture(actbtt_selected);
	UnloadTexture(fightbtt_selected);
	UnloadTexture(itembtt_selected);
	UnloadTexture(mercybtt_selected);
	UnloadTexture(hearttexture);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
