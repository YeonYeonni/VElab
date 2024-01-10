# include <iostream>
using namespace std;
# include "Helper.h"
# include "Map.h"
# include "Player.h"
# include <windows.h>

int main()
{
	SetCursorOnOff(false);

	//MovePlayer(3, 2); // 플레이어를 이동

	// 게임은 종료하기 전까지 무한 루프가 돌아감
	while (true)
	{
		// 입력
		HandleKeyinput(); // 키 입력 받기

		// 로직
		HandleMove(); // 플레이어의 이동을 처리

		// 출력
		PrintMap1D();
	}
}