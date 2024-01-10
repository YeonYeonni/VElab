# include "Player.h"
# include "Map.h"
# include "Helper.h"

// �÷��̾� �̵� ���
bool canMove = true;

// �÷��̾��� ��ġ �ʱ�ȭ
int GPlayerX = 2;
int GPlayerY = 2;

// �÷��̾� �̵�
void MovePlayer(int x, int y)
{
	// ���� üũ (x��, y�� ���)
	if (x < 0 || x >= MAP_SIZE)
		return; // ������ �Ѿ�� ����
	if (y < 0 || y >= MAP_SIZE)
		return;

	// �� üũ
	int index = y * MAP_SIZE + x; // 5ĭ�� �����ϸ� ���� �ٷ� �Ѿ�� ��Ģ
	if (GMap1D[index] == 1)
		return; // ���̸� ����

	// ���� ��ġ ����
	{
		int Index = GPlayerY * MAP_SIZE + GPlayerX; // ���� ��ġ
		GMap1D[Index] = 0; // ���� ��ġ�� 0���� ����
	}

	// �� ��ġ�� �̵�
	{
		GPlayerX = x;
		GPlayerY = y;
		int Index = GPlayerY * MAP_SIZE + GPlayerX; // ���ο� ��ġ
		GMap1D[Index] = 2; // ���ο� ��ġ�� 2�� ����
	}
}

// �÷��̾� �̵�
void HandleMove()
{
	// Ű�� ������ ������ ��� �̵��ϱ� ������ Ű�� ���� ������ ������ �����̵��� ����.
	if (GMoveDir == MD_NONE)
	{
		canMove = true; //Ű���带 �� (��� ó��)
		return;
	}

	if (canMove == false) // ������ �� ���� ����
		return;

	canMove = false;

	switch (GMoveDir)
	{
	case MD_LEFT:
		MovePlayer(GPlayerX - 1, GPlayerY);
		break;
	case MD_RIGHT:
		MovePlayer(GPlayerX + 1, GPlayerY);
		break;
	case MD_UP:
		MovePlayer(GPlayerX, GPlayerY - 1);
		break;
	case MD_DOWN:
		MovePlayer(GPlayerX, GPlayerY + 1);
		break;
	}
}