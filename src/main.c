/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include <stdio.h>
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
int SoulSpeed = 4;
bool isSlow = false; // X button thingamajing
typedef enum BattleStateEnum { PLAYER = 0, ENEMY } BattleStateEnum; // this stores the core state of the battle
BattleStateEnum BattleState = PLAYER;
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
	SetTargetFPS(30);
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
		if (IsKeyPressed(KEY_ENTER)){
			BattleState = (BattleState == PLAYER) ? ENEMY : PLAYER; // toggle between player and enemy state
		}
		switch (BattleState)
		{
		case PLAYER:
			if (IsKeyPressed(KEY_RIGHT))	
			{
				button_selected++;
				if (button_selected > 3) button_selected = 0; // wrap around
			}
			else if (IsKeyPressed(KEY_LEFT))
			{
				button_selected--;
				if (button_selected < 0) button_selected = 3; // wrap around
			}
			break;
		case ENEMY:
			if (IsKeyDown(KEY_X))
			{
				isSlow = true;
			} else if (IsKeyUp(KEY_X))
			{
				isSlow = false;
			}
			if (IsKeyDown(KEY_RIGHT))
			{
				SoulPos.x += SoulSpeed/(isSlow ? 2 : 1);
			}
			if (IsKeyDown(KEY_LEFT))
			{
				SoulPos.x -= SoulSpeed/(isSlow ? 2 : 1);
			}
			if (IsKeyDown(KEY_UP))
			{
				SoulPos.y -= SoulSpeed/(isSlow ? 2 : 1);
			}
			if (IsKeyDown(KEY_DOWN))
			{	
				SoulPos.y += SoulSpeed/(isSlow ? 2 : 1);
			}
			// keep the soul inside the arena
			if (SoulPos.x < arenaShape[0].x + 0) SoulPos.x = arenaShape[0].x + 0; // left side
			if (SoulPos.x > arenaShape[1].x - 16) SoulPos.x = arenaShape[1].x - 16; // right side
			if (SoulPos.y < arenaShape[0].y + 0) SoulPos.y = arenaShape[0].y + 0; // top side
			if (SoulPos.y > arenaShape[2].y - 16) SoulPos.y = arenaShape[2].y - 16; // bottom side
		default:
			break;
		}

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
		DrawText(TextFormat("BattleState: %d", BattleState), 10, 10, 20, WHITE);
		// draw our texture to the screen
		switch (BattleState)
		{
		case PLAYER:
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
			DrawTexture(hearttexture, ButtonPos[button_selected].x+8, ButtonPos[button_selected].y+13, RED);
			break;
			case ENEMY:
				DrawTextureV(fightbtt, 			ButtonPos[0], WHITE);
				DrawTextureV(actbtt,   			ButtonPos[1], WHITE);
				DrawTextureV(itembtt,  			ButtonPos[2], WHITE);
				DrawTextureV(mercybtt, ButtonPos[3], WHITE);
				DrawTextureV(hearttexture, SoulPos, RED);
			}
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
