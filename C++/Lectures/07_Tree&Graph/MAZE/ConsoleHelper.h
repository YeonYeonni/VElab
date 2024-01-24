#pragma once

// Console 색상
enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

class ConsoleHelper
{
public:
	static void SetCursorPosition(int32 x, int32 y); // 커서 좌표
	static void SetCursorColor(ConsoleColor color); // 커서 색상
	static void ShowConsoleCursor(bool flag); // 커서 깜빡임
};

