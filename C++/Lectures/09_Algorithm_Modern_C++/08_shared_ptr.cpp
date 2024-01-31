#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class Knight
{
public:
	~Knight() { }

	void Attack()
	{
		if (_target)
			_target->_hp -= _damage;
	}

public:
	int _hp = 100;
	int _damage = 10;
	Knight* _target = nullptr;
};

class RefCountBlock
{
public:
	int _refCount = 1; // 참조 개수
};

template<typename T>
class SharedPtr
{
public:
	SharedPtr() { }
	SharedPtr(T* ptr) : _ptr(ptr) 
	{
		if (ptr)
		{
			_block = new RefCountBlock();
			cout << "RefCount: " << _block->_refCount << endl;
		}
	}

	// 복사 용도
	SharedPtr(const SharedPtr& other) : _ptr(other._ptr), _block(other._block)
	{
		if (_ptr)
		{
			_block->_refCount++;
		}
	}

	void operator=(const SharedPtr& other)
	{
		_ptr = other._ptr;
		_block = other._block;

		if (_ptr)
			_block->_refCount++;
	}

	~SharedPtr()
	{
		if (_ptr)
		{
			_block->_refCount--;

			if (_block->_refCount == 0)
			{
				delete _ptr;
				delete _block;
				cout << "Delete Data" << endl;
			}
		}
	}

public:
	T* _ptr = nullptr;
	RefCountBlock* _block = nullptr;
};

void Test(shared_ptr<Knight> k)
{
	// refCount + 1
}

int main()
{
	SharedPtr<Knight>k1(new Knight());
	SharedPtr<Knight>k2(new Knight());

	SharedPtr<Knight> k3;
	k3 = k1;
}