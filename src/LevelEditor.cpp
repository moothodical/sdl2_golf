#include "LevelEditor.h"

LevelEditor::LevelEditor()
{

}

void LevelEditor::Update()
{
	// convert the mouse pos into cell pos
	int x, y;
	SDL_GetMouseState(&x, &y);

	Vector2f cell(x / CELL_SIZE, y / CELL_SIZE);
	if (cell.x > 0)
	{

	}

}