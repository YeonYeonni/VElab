#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Node
{
public:
	Node(int data) : data(data), prev(nullptr), next(nullptr) {} // 생성자

public:
	T data;
	Node* prev;
	Node* next;
};

template<typename T>
class Iterator
{
public:
	Iterator() : _node(nullptr) { }
	Iterator(Node<T>* node) : _node(node) { }

	// ++it
	Iterator& operator++()
	{
		_node = _node->next;
		return *this;
	}

	// it++
	Iterator& operator++(int)
	{
		Iterator temp = *this;
		_node = _node->next;
		return temp;
	}

	// *
	T& operator*()
	{
		return _node->data;
	}

	// ==
	bool operator==(const Iterator& other)
	{
		return _node == other._node;
	}

	// !=
	bool operator!=(const Iterator& other)
	{
		return _node != other._node;
	}

public:
	Node<T>* _node;
};

template<typename T>
class List
{
public:
	using iterator = Iterator<T>;

	iterator begin() { return iterator(_head->next); }
	iterator end() { return iterator(_tail); }

	List() // 생성자
	{
		_head = new Node<T>(0);
		_tail = new Node<T>(0);
		_head->next = _tail;
		_tail->prev = _head;
	}
	~List() // 소멸자
	{
		Node<T>* node = _head;
		while (node) // null check
		{
			Node<T>* deleteNode = node;
			node = node->next; // Node* nextNode = node->next; // next값을 가져와 node에 덮어씌우기
			delete deleteNode;
		}
	}

	Node<T>* GetNode(int index)
	{
		Node<T>* node = _head->next; // dummy head 다음
		if (node == _tail) // dummy head 다음이 dummy tail일 경우
			return nullptr;

		for (int i = 0; i < index; i++)
		{
			if (node == _tail->prev)
				return nullptr;

			node = node->next;
		}
		return node;
	}

	void Print()
	{
		Node<T>* node = _head->next; // dummy head 다음
		while (node != _tail)
		{
			cout << node->data << " ";
			node = node->next;
		}
		cout << endl;
	}

	// Head 앞에 노드를 추가하는 함수
	Node<T>* AddAtHead(int data)
	{
		Node<T>* node = new Node<T>(data);
		Node<T>* nextNode = _head->next; // 더미 헤드의 다음

		// 새 노드와 [1] 연결
		node->next = nextNode;
		nextNode->prev = node;

		// 새 노드와 더미 헤드 연결
		_head->next = node;
		node->prev = _head;

		return node;
	}

	// Tail 앞에 노드를 추가하는 함수
	Node<T>* AddAtTail(int data)
	{
		Node<T>* node = new Node<T>(data);
		Node<T>* prevNode = _tail->prev;

		prevNode->next = node;
		node->prev = prevNode;
		node->next = _tail;
		_tail->prev = node;

		return node;
	}

	void Insert(Node<T>* posNode, int data)
	{
		Node<T>* node = new Node<T>(data);
		Node<T>* prevNode = posNode->prev;
		prevNode->next = node;
		node->prev = prevNode;
		node->next = posNode;
		posNode->prev = node;
	}

	void Remove(Node<T>* node)
	{
		Node<T>* prevNode = node->prev;
		Node<T>* nextNode = node->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;

		delete node;

		return nextNode;
	}

private:
	Node<T>* _head = nullptr;
	Node<T>* _tail = nullptr;
};

