#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class Knight
{
public:
	~Knight()
	{
		cout << "~Knight()" << endl;
	}

	void Attack()
	{
		if (_target.expired())
		{
			shared_ptr<Knight> spr = _target.lock();
		}
	}

public:
	int _hp = 100;
	int _damage = 10;
	weak_ptr<Knight> _target;
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

class UniquePtr
{
private:
	void operator=(const UniquePtr&) {}
};

int main()
{
	{
		shared_ptr<Knight>k1(new Knight());
		weak_ptr<Knight> weak = k1;
		shared_ptr<Knight>k2(new Knight());

		k1->_target = k2;
		k2->_target = k1;
	}
}