#include <iostream>
using namespace std;

// ���� ������
// Public vs protected vs private

class Car
{
public:
	void MoveHandle() {}
	void PushPedal() {}
	void OpenDoor() {}

private:
	void Disassemble() {} // ���� ����
	void PutFuelInEngine() {} // ������ ���Ḧ ����
	void ConnectCircuit() {} // ȸ�� ����

protected:
	void ProtectedTest() {}

public:
	// �ڵ�
	// ���
	// ��
	// ���⼱
};

int main()
{
	Car c;
}