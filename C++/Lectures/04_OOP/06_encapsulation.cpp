#include <iostream>
using namespace std;

// 접근 지정자
// Public vs protected vs private

class Car
{
public:
	void MoveHandle() {}
	void PushPedal() {}
	void OpenDoor() {}

private:
	void Disassemble() {} // 차를 분해
	void PutFuelInEngine() {} // 엔진에 연료를 공급
	void ConnectCircuit() {} // 회로 연결

protected:
	void ProtectedTest() {}

public:
	// 핸들
	// 페달
	// 문
	// 전기선
};

int main()
{
	Car c;
}