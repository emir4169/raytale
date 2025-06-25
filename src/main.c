/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <stdlib.h>
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
struct PlayerStruct
{
	int LOVE;
	int HP;
	int maxHP;
	char name[6];
};
struct PlayerStruct player = { 1, 20, 20, "CHARA" };
int button_selected = 0; // 0 = fight, 1 = act, 2 = item, 3 = mercy
Vector2 SoulPos = { 36, 254 }; // position of the soul in the arena
int SoulSpeed = 4;
bool isSlow = false; // X button thingamajing
typedef enum BattleStateEnum { PLAYER = 0, ENEMY } BattleStateEnum; // this stores the core state of the battle
typedef enum ButtonEnum { FIGHT = 0, ACT, ITEM, MERCY } ButtonEnum; // this stores the buttons
typedef enum PlayerActionEnum { FIGHT_SE = 0, FIGHT_MG, ACT_SE, ACT_SA, ITEM_ACT, MERCY_SE } PlayerActionEnum; // SE stands for Select Enemy, MG stands for MiniGame and SA stands for Select Action
BattleStateEnum BattleState = PLAYER;
void DrawShape(Vector2 *shape, int numPoints, Color color)
{
	for (int i = 0; i < numPoints; i++)
	{
		int nextIndex = (i + 1) % numPoints;
		DrawLineV(shape[i], shape[nextIndex], color);
	}
}


void DrawShapeLS(Vector2 *shape, int numPoints, Color color, int thickness)
{
    // Calculate grid size
    const int gridSize = thickness;
    
    // Create a temporary point array
    Vector2 *tempPoints = (Vector2 *)malloc(numPoints * sizeof(Vector2));
    if (!tempPoints) return;
    
    // Draw the shape with perfect thickness
    for (int dx = -thickness; dx <= thickness; dx++) {
        for (int dy = -thickness; dy <= thickness; dy++) {
            // Skip center for even thickness to maintain symmetry
            if (thickness % 2 == 0 && dx == 0 && dy == 0) continue;
            
            // Apply offset to all points
            for (int i = 0; i < numPoints; i++) {
                tempPoints[i].x = shape[i].x + dx;
                tempPoints[i].y = shape[i].y + dy;
            }
            
            // Draw the offset shape
            DrawShape(tempPoints, numPoints, color);
        }
    }
    
    free(tempPoints);
}
void DrawTextFont(const char *text, int posX, int posY, int fontSize, Color color, Font font)
{
    // Check if default font has been loaded
    if (font.texture.id != 0)
    {
        Vector2 position = { (float)posX, (float)posY };

        int defaultFontSize = 13.333;   // Default Font chars height in pixel
        if (fontSize < defaultFontSize) fontSize = defaultFontSize;
        int spacing = fontSize/defaultFontSize;

        DrawTextEx(font, text, position, (float)fontSize, (float)spacing, color);
    }
}

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(30);
	// Create the window and OpenGL context
	InitWindow(640, 480, "Raytale");			// i owe you credits sawby08 for giving me the name inspiration and getting the sprites n stuff
	InitAudioDevice();
																																																																																																					// end the frame and get ready for the next one  (displ */
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
	Texture enemytexture = LoadTexture("test1.png");
	Font DTMono = LoadFont("font/determination-mono.ttf");
	Font utdotumche = LoadFont("font/undertale-dotumche.ttf");
	Font dotumche = LoadFont("font/dotumche.ttf");
	Font mars = LoadFont("font/mars.ttf");
	Texture kr_texture = LoadTexture("ui/spr_krmeter_0.png");
	Texture hp_texture = LoadTexture("ui/spr_hpname_0.png");
	Sound menuMoveSound = LoadSound("menuMove.ogg");
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
				PlaySound(menuMoveSound);
				button_selected++;
				if (button_selected > 3) button_selected = 0; // wrap around
			}
			else if (IsKeyPressed(KEY_LEFT))
			{
				PlaySound(menuMoveSound);
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
			if (SoulPos.x < arenaShape[0].x) SoulPos.x = arenaShape[0].x; // left side
			if (SoulPos.x > arenaShape[1].x - (16)) SoulPos.x = arenaShape[1].x - (16); // right side
			if (SoulPos.y < arenaShape[0].y) SoulPos.y = arenaShape[0].y; // top side
			if (SoulPos.y > arenaShape[2].y - (16)) SoulPos.y = arenaShape[2].y - (16); // bottom side
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
		// void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color);
		Rectangle arenaRect = { arenaShape[0].x-5, arenaShape[0].y-5, arenaShape[1].x+10 - arenaShape[0].x, arenaShape[2].y+10 - arenaShape[0].y };
		DrawRectangleLinesEx(arenaRect, 5, WHITE);
		//DrawShapeLS(arenaShape, ARENA_LENGTH, WHITE, 5); // draw the arena shape with a line width of 2
		//DrawLineStrip(arenaShape, ARENA_LENGTH, RED);
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawTextFont("Hello Raylib", 200,200,24,WHITE, mars);
		DrawTextFont(TextFormat("BattleState: %d", BattleState), 10, 10, 24, WHITE,mars);
		DrawTextFont(TextFormat("SOUL X: %d \nSOUL Y: %d", (int)SoulPos.x, (int)SoulPos.y), 10, 40, 24, WHITE,mars);
		//DrawTextureV(kr_texture, (Vector2){ 10, 70 }, WHITE);
		DrawTextFont(TextFormat("LV %d", player.LOVE), 148, 400, 24, WHITE,mars);
		DrawTextureV(hp_texture, (Vector2){ 240, 400 }, WHITE);
		//DrawRectangle(int posX, int posY, int width, int height, Color color);
		//love.graphics.rectangle( mode , x,   y,   width,                  height, rx, ry, segments )
		//love.graphics.rectangle('fill', 275, 400, player.stats.hp * 1.25, 21)
		DrawRectangle(275, 400, player.maxHP*1.25, 21, RED);
		DrawRectangle(275, 400, player.HP*1.25,21,YELLOW );

		DrawTextFont(player.name, 30, 400, 24, WHITE,mars);
		if (player.HP < 10) {
			DrawTextFont(TextFormat("0%d / %d ", player.HP, player.maxHP), 289 + player.maxHP*1.25, 400, 24, WHITE,mars);
		} else {
			DrawTextFont(TextFormat("%d / %d ", player.HP, player.maxHP), 289 + player.maxHP*1.25, 400, 24, WHITE,mars);
		}


		// draw our texture to the screen
		//DrawTextureV(enemytexture, (Vector2){ 145, 34 }, WHITE);
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
	UnloadSound(menuMoveSound);         
	UnloadTexture(enemytexture);
	UnloadTexture(kr_texture);
	UnloadTexture(hp_texture);
	UnloadFont(mars);
	UnloadFont(dotumche);
	UnloadFont(utdotumche);
	UnloadFont(DTMono);
	// destroy the window and cleanup the OpenGL context
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
