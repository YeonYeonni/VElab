# include <iostream>
using namespace std;

int main()
{
	int arr[10]; // int 타입의 10칸짜리 배열 arr 생성

	// 1. 인덱싱 값 할당
	arr[0] = 10;
	arr[1] = 20;

	// 2. 반복문
	for (int i = 0; i < 5; i++)
	{
		arr[i] = i * 10;
	}

	// 3, 초기값 설정
	int arr[5] = { 1, 2, 3, 4, 5 };
}