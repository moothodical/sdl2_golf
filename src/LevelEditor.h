#pragma once

#include <SDL.h>

#include "util/Math.h"

class LevelEditor
{
private:
	const int CELL_SIZE = 32;
public:
	LevelEditor();
	void Update();
};
