#pragma once

// �ּҷ�
class AddressManager
{
	// SINGLETON
	DECLARE_SINGLE(AddressManager);

// ��� ����
public:
	char name[20];
	char tel[20];
	char email[20];

// ��� �Լ�
public:
	void FindAddress(); // ������ ���� �˻� 
	void SaveSign(); // ������ ���� ����
	void CountRestSign(); // ������ ���� ���� ī��Ʈ
};