#include "Helper.h"
# include <windows.h> // console을 다루기 위한 windows api

MoveDir GMoveDir; // 플레이어의 이동할 방향

// 커서 위치를 원하는 좌표로 이동
void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x, (SHORT)y };
	::SetConsoleCursorPosition(output, pos); // 표준 제공 함수에 ::을 붙임
}

// 커서 깜빡임을 없앨 수 있는 함수
void SetCursorOnOff(bool visible)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = visible;
	::SetConsoleCursorInfo(output, &cursorInfo);
}

// 상하좌우 키 입력 받기 (현재 상태를 입력받기)
void HandleKeyinput()
{
	if (::GetAsyncKeyState(VK_LEFT) & 0x8000)
		GMoveDir = MD_LEFT;
	else if (::GetAsyncKeyState(VK_RIGHT) & 0x8000)
		GMoveDir = MD_RIGHT;
	else if (::GetAsyncKeyState(VK_UP) & 0x8000)
		GMoveDir = MD_UP;
	else if (::GetAsyncKeyState(VK_DOWN) & 0x8000)
		GMoveDir = MD_DOWN;
	else
		GMoveDir = MD_NONE;

}