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
			node = node->next; // next���� ������ node�� �����
			
			delete deleteNode;
		}
	}

	Node* GetNode(int index)
	{
		// ù ��° ������ ����
		Node* node = _head->next;

		// ���� ����Ʈ�� ����ְų� ������ ����� return
		if (node == _tail)
			return nullptr;

		// �־��� �ε������� ��带 ã�ư���
		for (int i = 0; i < index; i++)
		{
			// ���� �����ϰų� �� ������ ����� ��� return
			if (node == _tail->prev)
				return nullptr;

			// ���� ���� �̵�
			node = node->next;
		}
		// ã�� ��� ��ȯ
		return node;
	}

	void Print()
	{
		// ù ��° ������ ����
		Node* node = _head->next;

		// ���� ����Ʈ�� ������ ��ȸ�ϸ� ������ ���
		while (node != _tail)
		{
			cout << node->data << " "; // ���� ����� ������ ���
			node = node->next; // ���� ���� �̵�
		}
		cout << endl;
	}

	// Head �տ� ��带 �߰�
	Node* AddAtHead(int data)
	{
		// ���ο� ��� ����
		Node* node = new Node(data);

		// ���� ����� ���� ��� ��������
		Node* nextNode = _head->next;

		// �� ���� ���� ��� �� ����
		nextNode->prev = nextNode;
		nextNode->prev = node;

		// �� ���� ��� ����
		_head->next = node;
		node->prev = _head;

		// �߰��� ����� ������ ��ȯ
		return node;
	}

	// Tail �տ� ��带 �߰�
	Node* AddAtTail(int data)
	{
		// ���ο� ��� ����
		Node* node = new Node(data);

		// ���� ������ ���� ��� ��������
		Node* prevNode = _tail->prev;

		// �� ���� ���� ��� �� ����
		prevNode->next = node;
		node->prev = prevNode;

		// �� ���� ���� ����
		node->next = _tail;
		_tail->prev = node;

		// �߰��� ����� ������ ��ȯ
		return node;
	}

	// posNode ������ ���ο� ��带 ����
	void Insert(Node* posNode, int data)
	{
		// ���ο� ��� ����
		Node* node = new Node(data);

		// posNode�� ���� ��� ��������
		Node* prevNode = posNode->prev;

		// ���� ���� ���ο� ��� ����
		prevNode->next = node;
		node->prev = prevNode;

		// ���ο� ���� posNode ����
		node->next = posNode;
		posNode->prev = node;
	}

	// �־��� ��带 ���� ����Ʈ���� ����
	void Remove(Node* node)
	{
		// ����� ����, ���� ��� ��������
		Node* prevNode = node->prev;
		Node* nextNode = node->next;

		// ���� ���� ���� ��� ����
		prevNode->next = nextNode;

		// ��� ����
		nextNode->prev = prevNode;
		delete node;
	}

private:
	Node* _head = nullptr;
	Node* _tail = nullptr;
};