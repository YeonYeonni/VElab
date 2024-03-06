#pragma once

// 주소록
class AddressManager
{
	// SINGLETON
	DECLARE_SINGLE(AddressManager);

// 멤버 변수
public:
	char name[20];
	char tel[20];
	char email[20];

// 멤버 함수
public:
	void FindAddress(); // 교수님 정보 검색 
	void SaveSign(); // 교수님 싸인 저장
	void CountRestSign(); // 앞으로 남은 싸인 카운트
};