#pragma once
#include <iostream>
using namespace std;

class Node
{
	using T = int;
public:
	Node(int data) : data(data), prev(nullptr), next(nullptr) {}

public:
	T data;
	Node* prev;
	Node* next;
};

class List
{
public:
	List()
	{
		_head = new Node(0);
		_tail = new Node(0);
		_head->next = _tail;
		_tail->prev = _head;
	}
	~List()
	{
		Node* node = _head;
		while (node != nullptr)
		{
			Node* deleteNode = node;

			// Node* nextNode = node->next;
			node = node->next; // next값을 가져와 node에 덮어쓰기
			
			delete deleteNode;
		}
	}

	Node* GetNode(int index)
	{
		// 첫 번째 노드부터 시작
		Node* node = _head->next;

		// 연결 리스트가 비어있거나 범위를 벗어나면 return
		if (node == _tail)
			return nullptr;

		// 주어진 인덱스까지 노드를 찾아가기
		for (int i = 0; i < index; i++)
		{
			// 끝에 도달하거나 끝 이전의 노드인 경우 return
			if (node == _tail->prev)
				return nullptr;

			// 다음 노드로 이동
			node = node->next;
		}
		// 찾은 노드 반환
		return node;
	}

	void Print()
	{
		// 첫 번째 노드부터 시작
		Node* node = _head->next;

		// 연결 리스트의 끝까지 순회하며 데이터 출력
		while (node != _tail)
		{
			cout << node->data << " "; // 현재 노드의 데이터 출력
			node = node->next; // 다음 노드로 이동
		}
		cout << endl;
	}

	// Head 앞에 노드를 추가
	Node* AddAtHead(int data)
	{
		// 새로운 노드 생성
		Node* node = new Node(data);

		// 현재 헤드의 다음 노드 가져오기
		Node* nextNode = _head->next;

		// 새 노드와 다음 노드 간 연결
		nextNode->prev = nextNode;
		nextNode->prev = node;

		// 새 노드와 헤드 연결
		_head->next = node;
		node->prev = _head;

		// 추가된 노드의 포인터 반환
		return node;
	}

	// Tail 앞에 노드를 추가
	Node* AddAtTail(int data)
	{
		// 새로운 노드 생성
		Node* node = new Node(data);

		// 현재 테일의 이전 노드 가져오기
		Node* prevNode = _tail->prev;

		// 새 노드와 이전 노드 간 연결
		prevNode->next = node;
		node->prev = prevNode;

		// 새 노드와 테일 연결
		node->next = _tail;
		_tail->prev = node;

		// 추가된 노드의 포인터 반환
		return node;
	}

	// posNode 다음에 새로운 노드를 삽입
	void Insert(Node* posNode, int data)
	{
		// 새로운 노드 생성
		Node* node = new Node(data);

		// posNode의 이전 노드 가져오기
		Node* prevNode = posNode->prev;

		// 이전 노드와 새로운 노드 연결
		prevNode->next = node;
		node->prev = prevNode;

		// 새로운 노드와 posNode 연결
		node->next = posNode;
		posNode->prev = node;
	}

	// 주어진 노드를 연결 리스트에서 제거
	void Remove(Node* node)
	{
		// 노드의 이전, 다음 노드 가져오기
		Node* prevNode = node->prev;
		Node* nextNode = node->next;

		// 이전 노드와 다음 노드 연결
		prevNode->next = nextNode;

		// 노드 삭제
		nextNode->prev = prevNode;
		delete node;
	}

private:
	Node* _head = nullptr;
	Node* _tail = nullptr;
};