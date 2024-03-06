#include "pch.h"
#include "RoomManager.h"
#include "Inventory.h"
#include "numlist.h"

void RoomManager::Start(Inventory* correction, Numplay* num, Inventory* name, Inventory* number)
{
	while (true)
	{
		cout << "학위를 선택하세요." << endl;
		cout << "(1) 1년 안에 졸업해야한다는 통보를 받은 '나' . (2) 대학원에 진학한다는 이유로 이별을 경험한 '나'.  " << endl;
		cout << " > ";

		int choice;
		cin >> choice;
		cout << "=============================================================" << endl;

		// (1) 박사 행동
		if (choice == PT_BACHELOR)
		{
			cout << "박사 학위 도전자 " << " :: 당신이 받아야 할 서명의 총 개수는 3개입니다." << endl;
			cout << "=============================================================" << endl;
			char DE[] = "박사생";
			char playerType = PlayerType::PT_BACHELOR;

			// 임시로 사용할 박사 초깃값
			string* prof1 = new string("채교수");
			string* prof2 = new string("김교수");
			string* prof3 = new string("박교수");

			correction->AddInven(prof1);
			correction->AddInven(prof2);
			correction->AddInven(prof3);
		}

		// (2) 석사 행동
		if (choice == PT_MASTER)
		{
			cout << "석사 학위 도전자 " << " :: 당신이 받아야 할 서명의 총 개수는 3개입니다." << endl;
			cout << "=============================================================" << endl;
			char DE[] = "석사생";
			char playerType = PlayerType::PT_MASTER;

			// 임시로 사용할 석사 초깃값
			string* prof1 = new string("채교수");
			string* prof2 = new string("김교수");
			string* prof3 = new string("박교수");
			correction->AddInven(prof1);
			correction->AddInven(prof2);
			correction->AddInven(prof3);
		}
		break;
	}
}

void RoomManager::ROOM1(Inventory* correction, Numplay* num, Inventory* name, Inventory* number)
{
	while (true)
	{
		cout << "=============================================================" << endl;
		cout << "눈을 뜨자 *해외발신*" << "01011112222" << "이라는 꺼림직한 단어만 액정 위에 나타나있다." << endl;
		cout << "(1) 전화를 받는다. (2) 전화를 거절한다" << endl;
		cout << " > ";
		int input;
		cin >> input;
		cout << "=============================================================" << endl;
		cout << "=============================================================" << endl;

		// (1) 전화를 받는다
		if (input == 1)
		{
			cout << "-정적-" << endl;
			cout << "...누구세요?" << endl;
			cout << "...일이 난건 아닌가 보군, 오늘 아침에 하기로 한 회의는 왜 접속 안한거지? 졸업하기 싫은건가? 논문 제출 안할거야?" << endl;
			cout << "예? 회의요? 누구세요?" << endl;
			cout << "뭔!.... 내 지금은 좋은 말이 나갈거 같지가 않으니 정신 차리고 다시 연락하게 " << endl;
			//cout << "-노한 음성과 함께 하루가 시작되었습니다! 주변을 둘러보려면 아무 키나 입력하세요- " << endl;
			//cin >> trs;
			cout << "주변을 둘러보니 당신의 눈 앞에 매혹적인 초록병이 있고 젖은 논문 서명지가 있습니다. 당신의 지도교수님은 '채교수님' 입니다." << endl;
			cout << "해외 발신 전화번호를 추가해주세요" << endl;

			num->_Play();

			//주소록에서 A 찾기
			string* prof = new string("채교수");
			if (name->AddInven(prof))
				cout << "채교수님을 주소록에 저장했음." << endl;

			cout << "졸업을 하기까지 앞으로 " << correction->_signCount - name->_signCount << " 명의 교수님이 남았다." << endl;
			cout << "=============================================================" << endl;
			cout << "=============================================================" << endl;
			break;
		}
		// (2) 전화를 거절한다
		if (input == 2)
		{
			cout << "M_signInfo.Name" << " 은 다시 깊은 잠에 빠져들고 말았다." << endl;
			cout << "=============================================================" << endl;
			cout << "==========================GAME OVER==========================" << endl;
			cout << "=============================================================" << endl;
		}
	}
}

void RoomManager::ROOM2(Inventory* correction, Numplay* num, Inventory* name, Inventory* number)
{
	while (true)
	{
		cout << "전화를 끊고 연구실 안 나의 자리를 둘러보았다" << endl;
		cout << "(1) 책장을 모두 훝어보기 (2) 나의 데스크탑을 탐색하기" << endl;
		cout << " > ";
		int input;
		cin >> input;
		cout << "=============================================================" << endl;

		// (1) 책장을 모두 훝어보기
		if (input == 1)
		{
			cout << "책장에는 졸업을 준비하며 썼던 학회지 논문이 꽂혀있다." << endl;
			cout << "논문을 꺼내어 살펴보니 교신저자 교수님의 이름만 확인할 수 있었다." << endl;

			cout << "=============================================================" << endl;

			cout << " '교신저자 : 김교수' " << endl;

			cout << "=============================================================" << endl;

			cout << "이메일이 적혀있는 부분은 햇빛에 바래 보이지 않는다." << endl;

			cout << "=============================================================" << endl;

			cout << " '어디에 물어봐야할까?' " << endl;
			cout << "1) 행정실에 전화하여 교수님의 연락처를 물어보기 2) 대학원 홈페이지에서 교수님의 연락처를 검색하기" << endl;
			cout << " > ";
			int ans1;
			cin >> ans1;


			// 교수님의 이름이 주소록에 있으면 인벤토리에 추가


			if (ans1 == 1)
			{
				cout << "=============================================================" << endl;

				cout << " ... ... ..." << endl;
				cout << " 행정실 직원: '무슨 일로 전화 주셨나요?'" << endl;
				cout << " 나         : '교수님 연락처를 문의드리려고 합니다' " << endl;

				cout << "=============================================================" << endl;

				cout << " 행정실 직원: '교수님 성함을 말씀해주세요'" << endl;
				cout << ">> 교수님의 이름을 입력하시오 <<" << endl;

				//num->_Play();

				string judge("김교수"); // 문자 비교 
				string* prof = new string();;
				cin >> *prof;
				if (*prof == judge)
				{
					//address.FindAddress(); //교수님 연락처 검색
					//address.SaveSign(); // 교수님 싸인 획득
					cout << "=============================================================" << endl;

					cout << "교수님의 연락처 01033334444 를 얻었다!" << endl;
					cout << "졸업을 하기까지 앞으로 " << correction->_signCount - name->_signCount << " 명의 교수님이 남았다." << endl;
					cout << "이제 다른 교수님께 싸인을 받으러 가자!!" << endl;

					cout << "=============================================================" << endl;
					name->AddInven(prof);
					break;
				}
				else
				{
					cout << "재입력 하시오." << endl;
				}
			}

			else if (ans1 == 2)
			{
				cout << "대학원 홈페이지에서 교수님 이름을 입력하여 전화번호를 획득하세요" << endl;

				cout << "=============================================================" << endl;

				num->_App();

				cout << "=============================================================" << endl;

				cout << "김교수님의 전화번호를 입력하여 서명을 받으세요" << endl;

				string kimnum("01033334444"); // 문자 비교 
				string* kim = new string();;
				cin >> *kim;
				if (*kim == kimnum)
				{
					cout << "=============================================================" << endl;
					cout << "교수님서명을 얻었다!" << endl;
					cout << "졸업을 하기까지 앞으로 " << correction->_signCount - name->_signCount << " 명의 교수님이 남았다." << endl;
					cout << "이제 다른 교수님께 싸인을 받으러 가자!!" << endl;
					name->AddInven(kim);
				}

			}
		}

		///교신 최종

		// (2) 나의 데스크탑을 탐색하기
		if (input == 2)
		{
			cout << "바탕화면에는 내가 이전에 학회지에 투고했던 논문 파일이 있다." << endl;
			cout << "논문 파일을 열어 확인해보니 이전 저장 버전으로 교수님의 정보를 아예 찾을 수 없었다." << endl;

			cout << "=============================================================" << endl;
			cout << "다른 곳을 둘러보자!" << endl;
			cout << "1) 책장을 둘러보기  2) 다른 교수님을 먼저 찾으러 가기" << endl;
			cout << " > ";
			int ans2;
			cin >> ans2;
			cout << "=============================================================" << endl;
			cout << "=============================================================" << endl;

			// 1) 책장을 둘러보기
			if (ans2 == 1)
			{
				cout << "책장에는 졸업을 준비하며 썼던 학회지 논문이 꽂혀있다." << endl;
				cout << "논문을 꺼내어 살펴보니 교신저자 교수님의 이름만 확인할 수 있었다." << endl;

				cout << "=============================================================" << endl;

				cout << " '교신저자 : 김교수' " << endl;

				cout << "=============================================================" << endl;

				cout << "이메일이 적혀있는 부분은 햇빛에 바래 보이지 않는다." << endl;

				cout << "=============================================================" << endl;

				cout << " '어디에 물어봐야할까?' " << endl;
				cout << "1) 행정실에 전화하여 교수님의 연락처를 물어보기 2) 대학원 홈페이지에서 교수님의 연락처를 검색하기" << endl;
				cout << " > ";
				int ans3;
				cin >> ans3;


				// 교수님의 이름이 주소록에 있으면 인벤토리에 추가


				if (ans3 == 1)
				{
					cout << "=============================================================" << endl;

					cout << " ... ... ..." << endl;
					cout << " 행정실 직원: '무슨 일로 전화 주셨나요?'" << endl;
					cout << " 나         : '교수님 연락처를 문의드리려고 합니다' " << endl;

					cout << "=============================================================" << endl;

					cout << " 행정실 직원: '교수님 성함을 말씀해주세요'" << endl;
					cout << ">> 교수님의 이름을 입력하시오 <<" << endl;

					//num->_Play();

					string judge("김교수"); // 문자 비교 
					string* prof = new string();;
					cin >> *prof;
					if (*prof == judge)
					{
						//address.FindAddress(); //교수님 연락처 검색
						//address.SaveSign(); // 교수님 싸인 획득
						cout << "=============================================================" << endl;

						cout << "교수님의 연락처 01033334444 를 얻었다!" << endl;
						cout << "졸업을 하기까지 앞으로 " << correction->_signCount - name->_signCount << " 명의 교수님이 남았다." << endl;
						cout << "이제 다른 교수님께 싸인을 받으러 가자!!" << endl;

						cout << "=============================================================" << endl;
						name->AddInven(prof);
						break;
					}
					else
					{
						cout << "재입력 하시오." << endl;
					}
				}
				//대학원 홈페이지 문의
				else if (ans3 == 2)
				{
					cout << "대학원 홈페이지에서 교수님 이름을 입력하여 전화번호를 획득하세요" << endl;

					cout << "=============================================================" << endl;

					num->_App();

					cout << "=============================================================" << endl;

					cout << "김교수님의 전화번호를 입력하여 서명을 받으세요" << endl;

					string kimnum("01033334444"); // 문자 비교 
					string* kim = new string();;
					cin >> *kim;
					if (*kim == kimnum)
					{
						cout << "=============================================================" << endl;
						cout << "교수님서명을 얻었다!" << endl;
						cout << "졸업을 하기까지 앞으로 " << correction->_signCount - name->_signCount << " 명의 교수님이 남았다." << endl;
						cout << "이제 다른 교수님께 싸인을 받으러 가자!!" << endl;
						name->AddInven(kim);
					}

				}

				// 2) 다른 교수님을 먼저 찾으러 가기
				else if (ans2 == 2)
				{
					break;
				}
			}
		}
	}
}

void RoomManager::ROOM2_1(Inventory* correction, Numplay* num, Inventory* name, Inventory* number)
{
	while (true)
	{
		cout << "책장에는 졸업을 준비하며 썼던 학회지 논문이 꽂혀있다." << endl;
		cout << "논문을 꺼내어 살펴보니 교신저자 교수님의 이름만 확인할 수 있었다." << endl;

		cout << "=============================================================" << endl;

		cout << " '교신저자 : 김교수' " << endl;

		cout << "=============================================================" << endl;

		cout << "이메일이 적혀있는 부분은 햇빛에 바래 보이지 않는다." << endl;

		cout << "=============================================================" << endl;

		cout << " '어디에 물어봐야할까?' " << endl;
		cout << "1) 행정실에 전화하여 교수님의 연락처를 물어보기 2) 대학원 홈페이지에서 교수님의 연락처를 검색하기" << endl;
		cout << " > ";
		int ans1;
		cin >> ans1;


		// 교수님의 이름이 주소록에 있으면 인벤토리에 추가


		if (ans1 == 1)
		{
			cout << "=============================================================" << endl;

			cout << " ... ... ..." << endl;
			cout << " 행정실 직원: '무슨 일로 전화 주셨나요?'" << endl;
			cout << " 나         : '교수님 연락처를 문의드리려고 합니다' " << endl;

			cout << "=============================================================" << endl;

			cout << " 행정실 직원: '교수님 성함을 말씀해주세요'" << endl;
			cout << ">> 교수님의 이름을 입력하시오 <<" << endl;

			//num->_Play();

			string judge("김교수"); // 문자 비교 
			string* prof = new string();;
			cin >> *prof;
			if (*prof == judge)
			{
				//address.FindAddress(); //교수님 연락처 검색
				//address.SaveSign(); // 교수님 싸인 획득
				cout << "=============================================================" << endl;

				cout << "교수님의 연락처 01033334444 를 얻었다!" << endl;
				cout << "졸업을 하기까지 앞으로 " << correction->_signCount - name->_signCount << " 명의 교수님이 남았다." << endl;
				cout << "이제 다른 교수님께 싸인을 받으러 가자!!" << endl;

				cout << "=============================================================" << endl;
				name->AddInven(prof);
				break;
			}
			else
			{
				cout << "재입력 하시오." << endl;
			}
		}

		else if (ans1 == 2)
		{
			cout << "대학원 홈페이지에서 교수님 이름을 입력하여 전화번호를 획득하세요" << endl;

			cout << "=============================================================" << endl;

			num->_App();

			cout << "=============================================================" << endl;

			cout << "김교수님의 전화번호를 입력하여 서명을 받으세요" << endl;

			string kimnum("01033334444"); // 문자 비교 
			string* kim = new string();;
			cin >> *kim;

			cout << "마지막 교수님의 연락처를 얻었다!" << endl;
			cout << "졸업을 하기까지 앞으로 " << correction->_signCount - name->_signCount << " 명의 교수님이 남았다." << endl;
			cout << "=============================================================" << endl;
			cout << "=============================================================" << endl;
			name->AddInven(kim);
			break;
			}
		}
	}


void RoomManager::ROOM3(Inventory* correction, Numplay* num, Inventory* name, Inventory* number)
{
	while (true)
	{
		cout << "이제 신임 교수님 차례군..." << endl;
		cout << "잠시만 남은 시간이 5분이라고?" << endl;
		cout << "제출 마감까지 남은 시간은 단 5분. 이젠 방법이 없다. 운명에 맡기자." << endl;
		cout << "=============================================================" << endl;
		cout << " " << endl;
		cout << "'이교수'님과 '박교수'님" << endl;
		cout << " " << endl;
		cout << "=============================================================" << endl;
		cout << "두 신임 교수님 중 어느 분께 연락을 드릴까?" << endl;
		cout << " > ";
		string* prof = new string();;
		cin >> *prof;
		cout << "=============================================================" << endl;
		cout << "=============================================================" << endl;

		//SaveSign(professor, input); // 교수님 싸인 주소록에서 탐색 -> 획득
		name->AddInven(prof);
		cout << "졸업을 하기까지 앞으로 " << correction->_signCount - name->_signCount << " 명의 교수님이 남았다." << endl;
		cout << "=============================================================" << endl;
		cout << "=============================================================" << endl;
		break;
	}
}

void RoomManager::Ending(Inventory* correction, Numplay* num, Inventory* name, Inventory* number)
{
	while (true)
	{
		name->SortInven();
		correction->SortInven();

		// 정답지 확인
		cout << "정답 싸인은?" << endl;
		for (int i = 0; i < correction->_signCount; i++)
		{
			cout << *correction->_signs[i] << " ";
		}
		cout << endl;

		// 인벤토리 확인
		cout << "플레이어가 수집한 싸인의 수는 " << name->_signCount << "개" << endl;
		cout << "플레이어가 수집한 싸인은?" << endl;
		for (int i = 0; i < name->_signCount; i++)
		{
			cout << *name->_signs[i] << " ";
		}
		cout << endl;

		// 게임 성공/실패
		bool gameClear = true;

		for (int i = 0; i < name->_signCount; i++)
		{
			if (*correction->_signs[i] != *name->_signs[i])
			{
				cout << "정답 교수님 : " << *correction->_signs[i] << ", " << "수집한 교수님 : " << *name->_signs[i] << endl;
				cout << "졸업 실패!";
				gameClear = false;
				break;
			}
		}

		if (gameClear)
		{
			cout << "졸업 성공!";
		}
		break;
	}
}