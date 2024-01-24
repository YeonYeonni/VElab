#pragma once

// Console ����
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
	static void SetCursorPosition(int32 x, int32 y); // Ŀ�� ��ǥ
	static void SetCursorColor(ConsoleColor color); // Ŀ�� ����
	static void ShowConsoleCursor(bool flag); // Ŀ�� ������
};

