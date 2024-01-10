#include "Helper.h"
# include <windows.h> // console�� �ٷ�� ���� windows api

MoveDir GMoveDir; // �÷��̾��� �̵��� ����

// Ŀ�� ��ġ�� ���ϴ� ��ǥ�� �̵�
void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x, (SHORT)y };
	::SetConsoleCursorPosition(output, pos); // ǥ�� ���� �Լ��� ::�� ����
}

// Ŀ�� �������� ���� �� �ִ� �Լ�
void SetCursorOnOff(bool visible)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = visible;
	::SetConsoleCursorInfo(output, &cursorInfo);
}

// �����¿� Ű �Է� �ޱ� (���� ���¸� �Է¹ޱ�)
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