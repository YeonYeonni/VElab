# include <iostream>
using namespace std;
# include "Helper.h"
# include "Map.h"
# include "Player.h"
# include <windows.h>

int main()
{
	SetCursorOnOff(false);

	//MovePlayer(3, 2); // �÷��̾ �̵�

	// ������ �����ϱ� ������ ���� ������ ���ư�
	while (true)
	{
		// �Է�
		HandleKeyinput(); // Ű �Է� �ޱ�

		// ����
		HandleMove(); // �÷��̾��� �̵��� ó��

		// ���
		PrintMap1D();
	}
}