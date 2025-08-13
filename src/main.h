
#define ARENA_OFFSET_X 32
#define ARENA_OFFSET_Y 250
#define ARENA_LENGTH 4
Vector2 arenaShape[ARENA_LENGTH] = {
	{0+ARENA_OFFSET_X, 0+ARENA_OFFSET_Y},
	{573+ARENA_OFFSET_X, 0+ARENA_OFFSET_Y},
	{573+ARENA_OFFSET_X, 137+ARENA_OFFSET_Y},
	{0+ARENA_OFFSET_X,137+ARENA_OFFSET_Y}
};
Vector2 ButtonPos[4] = {
	{27, 432},   // fight button
	{185, 432},  // act button
	{343, 432},  // item button
	{501, 432}   // mercy button
};
Vector2 SoulPositions[6] = {
    {68,288}, // slot 1
    {324,288}, // slot 2
    {68,320}, // slot 3
    {324,320},  // slot 4
    {68,352}, // slot 5
    {324,352} //slot 6
    };
struct PlayerStruct
{
	int LOVE;
	int HP;
	int maxHP;
	char name[6];
};
// 0 = fight, 1 = act, 2 = item, 3 = mercy
typedef enum ActsEnum { ACT_TAKEONEDAMAGE = 0, ACT_HEALBYONE } ActsEnum;
typedef enum BattleStateEnum { PLAYER = 0, ENEMY } BattleStateEnum; // this stores the core state of the battle
typedef enum ButtonEnum { FIGHT = 0, ACT, ITEM, MERCY } ButtonEnum; // this stores the buttons
typedef enum PlayerActionEnum { SB = 0, FIGHT_SE, FIGHT_MG, ACT_SE, ACT_SA, ITEM_ACT, MERCY_SE, ACT_TEXT } PlayerActionEnum; // SE stands for Select Enemy, MG stands for MiniGame and SA stands for Select Action
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