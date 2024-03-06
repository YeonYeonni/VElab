#include "pch.h"
#include "Inventory.h"

// ������
Inventory::Inventory()
{
	// �迭�� ��� ���� null�� �ʱ�ȭ
	for (int i = 0; i < MAX_SLOT; i++)
		_signs[i] = nullptr;
}

// �Ҹ���
Inventory::~Inventory()
{
}

// FindEmptySlot �Լ��� ����� �� ���� ��ġ�� ���� ��, ���ϴ� ���� ����. signCount�� 1 ����.
bool Inventory::AddInven(string* sign)
{
	// ���� ó��) �޾ƿ� ���� null�̸� AddInven �Լ��� �������� ����.
	if (sign == nullptr)
		return false;

	// FindEmpty �Լ� ���. �� ���� ��ġ�� emptySlot�� ����.
	int emptySlot = FindEmptySlot();

	// ���� ó��) FindEmpty �Լ� �۵��� ���� (-1) �ϸ� AddInven �Լ��� �������� ����.
	if (emptySlot < 0)
		return false;

	// ���� �۵�
	_signs[emptySlot] = sign; // �� ���� ���ϴ� ���� ����.
	_signCount++; // ���� �迭�� ������ 1 ����.
	return true;
}

// FindItemSlot �Լ��� ����� ã���� �ϴ� ���� ��ġ�� ���� ��, ���� null�� ����. signCount�� 1 ����
bool Inventory::RemoveInven(string* sign)
{
	// ���� ó��) �޾ƿ� ���� null�̸� RemoveInven �Լ��� �������� ����.
	if (sign == nullptr)
		return false;

	// FindItemSlot �Լ� ���. �����ϰ��� �ϴ� ���� ��ġ�� slot�� ����.
	int slot = FindItemSlot(sign);

	// ���� ó��) FindItemSlot �Լ� �۵��� ���� (-1) �ϸ� RemoveInven �Լ��� �������� ����.
	if (slot < 0)
		return false;

	// ���� �۵�
	_signs[slot] = nullptr; // ���� �ִ� ���� null�� ����.
	_signCount--; // ���� �迭�� ������ 1 ����.
	return true;
}

// �迭�� �������� ����
bool Inventory::SortInven()
{
	if (_signCount > 0)
	{
		std::sort(_signs, _signs + _signCount, [](string* a, string* b)
			{ return *a < *b; });
		return true;
	}
	return false;
}

// �迭 ��ü�� null�� �ʱ�ȭ
void Inventory::Clear()
{
	for (int i = 0; i < MAX_SLOT; i++)
	{
		if (_signs[i])
		{
			delete _signs[i];
			_signs[i] = nullptr;
		}
	}
}

// �迭�� ��ȸ�ϸ鼭 �� ���� ��ġ�� ��ȯ
int Inventory::FindEmptySlot()
{
	// ���� �۵�
	for (int i = 0; i < MAX_SLOT; i++)
	{
		// ���� ���� ���� ã���� �� ��ġ�� ��ȯ.
		if (_signs[i] == nullptr)
			return i;
	}

	// ���� �߻�) �迭�� ��� �������� -1 ��ȯ.
	return -1;
}

// �迭�� ��ȸ�ϸ鼭 ã���� �ϴ� ���� ��ġ�� ��ȯ.
int Inventory::FindItemSlot(string* sign)
{
	// ���� �۵�
	for (int i = 0; i < MAX_SLOT; i++)
	{
		// ���ϴ� ���� ã���� �� ��ġ�� ��ȯ.
		if (_signs[i] == sign)
			return i;
	}
	// ���� �߻�) ã���� �ϴ� ���� ������ -1 ��ȯ.
	return -1;
}
