/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <stdlib.h>
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "main.h"
struct PlayerStruct player = { 1, 20, 20, "CHARA" };
int button_selected = 0; // 0 = fight, 1 = act, 2 = item, 3 = mercy
Vector2 SoulPos = { 36, 254 }; // position of the soul in the arena
int SoulSpeed = 4;
bool isSlow = false; // X button thingamajing
PlayerActionEnum PlayerAction = SB; // SB is select button
BattleStateEnum BattleState = PLAYER;
// dialogue stuff
char dialogueTBR[7][256] = {"* You encountered the Dummy","* Criticize","* Criticize","* Criticize","* Criticize","* Criticize","* Criticize"}; // what we are gonna render
char dialogueSF[7][256] = {"","","","","","","",""}; // string of how much we have rendered so far
int dialogueIndexes[7] = {0,0,0,0,0,0,0}; // index of the current dialogue character
bool dialogueEnabled[7] = {true,false,false,false,false,false,false}; // which dialogue strings are gonna be shown
// function to increment the dialogue index along with the string
void dinc(int index) {
	if (dialogueIndexes[index] < strlen(dialogueTBR[index])) {
		dialogueSF[index][dialogueIndexes[index]] = dialogueTBR[index][dialogueIndexes[index]];
		dialogueIndexes[index]++;
	} else {
		dialogueSF[index][dialogueIndexes[index]] = '\0'; // null terminate the string
	}
}
bool dcheck(int index) {
	if (dialogueIndexes[index] < strlen(dialogueTBR[index])) {
		return true; // still has characters to render
	} else {
		return false; // no more characters to render
	}
}

void dreset(int index) {
	dialogueIndexes[index] = 0; // reset the index
	//dialogueSF[index][0] = '\0'; // reset the string
	for (int i = 0; i < strlen(dialogueTBR[index]); i++) {
		dialogueSF[index][i] = ' '; // reset the string properly
	}
}
void handleSoulMovement() {
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
}
void selectButtonHandler(Sound menuMoveSound) {

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
					if (IsKeyPressed(KEY_Z)){
						switch (button_selected)
						{
						case FIGHT:
							PlayerAction = FIGHT_SE;
							break;
						case ACT:
							PlayerAction = ACT_SE;
							break;
						case ITEM:
							PlayerAction = ITEM_ACT;
							break;
						case MERCY:
							PlayerAction = MERCY_SE;
							break;
						}
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
	Font DTMono = LoadFont("font/dtmono.fnt");//, 26, NULL, 95);
	Font utdotumche  = LoadFont("font/undertale-dotumche.ttf"); // utdotumche
	Font dotumche = LoadFont("font/dotumche.ttf");
	Font mars = LoadFont("font/mars.ttf");
	Texture kr_texture = LoadTexture("ui/spr_krmeter_0.png");
	Texture hp_texture = LoadTexture("ui/spr_hpname_0.png");
	Sound menuMoveSound = LoadSound("menuMove.ogg");
	//Image tmp1=LoadImageFromTexture(DTMono.texture);
    //ImageAlphaClear(&tmp1,(Color){0,0,0,0},0.5);
    //UnloadTexture(DTMono.texture);
    //DTMono.texture=LoadTextureFromImage(tmp1);
    //UnloadImage(tmp1);
    //SetTextureFilter(DTMono.texture,TEXTURE_FILTER_POINT);
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		if (IsKeyPressed(KEY_ENTER)){
			BattleState = (BattleState == PLAYER) ? ENEMY : PLAYER; // toggle between player and enemy state
		}
		switch (BattleState)
		{
		case PLAYER:
			switch (PlayerAction)
			{
				case (SB): dialogueEnabled[0] = true; dialogueEnabled[1] = false; selectButtonHandler(menuMoveSound); break; // select button
				case (ACT_SE):
				    SoulPos = (Vector2){SoulPositions[0].x, SoulPositions[0].y+10};
					dialogueEnabled[0] = false;
					strcpy(dialogueTBR[1], "* Test Enemy");
					strcpy(dialogueSF[1], "* Test Enemy"); // okay fine i didnt HAVE to do it this time
					dialogueEnabled[1] = true;
					if (IsKeyPressed(KEY_Z)) {
						PlayerAction = ACT_SA; // select action
						dreset(0);
					}
					break;
				case (ACT_SA):
					
					dreset(1);
					strcpy(dialogueTBR[1], "* Take damage");
					strcpy(dialogueSF[1], "* Take damage"); // i hate that i have to do this for it to WORK
					if (IsKeyPressed(KEY_Z)) {
						dialogueEnabled[1] = false; // disable the first action dialogue
						SoulPos = (Vector2){9999,9999};
						strcpy(dialogueTBR[1],"*                           ");
						strcpy(dialogueSF[1], "*                           ");
						dreset(1);
						strcpy(dialogueTBR[0], "* You took damage.");
						dialogueEnabled[0] = true;
						dreset(0);
						player.HP -= 1;
						PlayerAction = ACT_TEXT; // go to the text action so we cant get ourselves into a inf act loop
					}
				case (ACT_TEXT):
					if (!dcheck(0) && IsKeyPressed(KEY_Z)){
						PlayerAction = SB; // go back to select button
						strcpy(dialogueTBR[0], "* Ouch.");
						strcpy(dialogueSF[0], "*                           ");
						dreset(0);
					}
				break;
				default:
					if (IsKeyPressed(KEY_X)){
						if (BattleState == PLAYER){
							PlayerAction = SB;
						} else {
							BattleState = PLAYER; // this is just for now
						}
					}
					break;
				break;
			}
			break;
		case ENEMY:
			for (int i = 0; i < 7; i++) {
				dialogueEnabled[i] = false;
			}
			handleSoulMovement();
			break;
		}

		// drawing
		BeginDrawing();
		//DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);  
		//DrawLineV(arenaShape[0], arenaShape[1], RED);
		//DrawLineV(arenaShape[1], arenaShape[2], RED);
		if (dialogueEnabled[0] == true) { // main text
			dinc(0);
			DrawTextEx(DTMono, dialogueSF[0], (Vector2){52-4, 274-6}, 32, 0, WHITE); // IT WOOOOOOORKS
		}
		for (int i = 1; i < 7; i++) {
			if (dialogueEnabled[i] == true) { // nonmain text
				dinc(i);
				DrawTextEx(DTMono, dialogueSF[i], SoulPositions[i-1], 32, 0, WHITE); // IT WOOOOOOORKS
			}
		}

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
			DrawTextureV(fightbtt, 			ButtonPos[0], WHITE);
			DrawTextureV(actbtt,   			ButtonPos[1], WHITE);
			DrawTextureV(itembtt,  			ButtonPos[2], WHITE);
			DrawTextureV(mercybtt, 			ButtonPos[3], WHITE);
			switch (button_selected)
			{
				case FIGHT:
					DrawTextureV(fightbtt_selected, ButtonPos[0], WHITE);
					break;
				case ACT:
					DrawTextureV(actbtt_selected, 	ButtonPos[1], WHITE);
					break;
				case ITEM:
					DrawTextureV(itembtt_selected,  ButtonPos[2], WHITE);
					break;
				case MERCY:
					DrawTextureV(mercybtt_selected, ButtonPos[3], WHITE);
					break;
				default:
					break;
			}
			if (PlayerAction == SB){
				DrawTexture(hearttexture, ButtonPos[button_selected].x+8, ButtonPos[button_selected].y+13, RED);
			} else {
				DrawTextureV(hearttexture, SoulPos, RED);
			}
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
