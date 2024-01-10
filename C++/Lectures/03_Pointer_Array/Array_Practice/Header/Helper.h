#pragma once

enum MoveDir
{
	MD_NONE,
	MD_LEFT,
	MD_RIGHT,
	MD_UP,
	MD_DOWN,
};

void HandleKeyinput();
void SetCursorPosition(int x, int y);
void SetCursorOnOff(bool visible);

extern MoveDir GMoveDir;