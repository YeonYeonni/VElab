#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>

enum class ObjectType
{
	Player,
	Monster,
	Projectile,
	Env,
};

class Object
{
public:
	Object(ObjectType type) : _type(type) { }
	virtual ~Object() { }

	// start
	virtual void Init()
	{

	}

	// Update
	virtual void Update()
	{

	}

public:
	ObjectType GetObjectType() { return _type; }

	int _id = 0;
	ObjectType _type;
};

/*
class Player
{
public:
	Player() : _id(0) { }
	Player(int id) : _id(id){ }

	int _id;
};
*/

class Player : public Object
{
public:
	Player() : Object(ObjectType::Player) { }
	Player(int id) : Object(ObjectType::Player) { }
};

class Monster : public Object
{
public:
	Monster() : Object(ObjectType::Monster) { }
};

class Projectile : public Object
{
public:
	Projectile() : Object(ObjectType::Projectile) { }
};

class Field
{
public:
	static Field* GetInstance()
	{
		static Field field;
		return &field;
	}

	void Update()
	{
		for (auto& item : _objects)
		{
			Object* obj = item.second;
			obj->Update();
		}
	}

	void Add(Object* player)
	{
		_objects.insert(make_pair(player->_id, player));
	}

	void Remove(int id)
	{
		_objects.erase(id);
	}

	Object* Get(int id)
	{
		auto findIt = _objects.find(id);
		if (findIt != _objects.end())
			return findIt->second;
		return nullptr;
	}

private:
	// vector? list? map? hash_map?
	unordered_map<int, Object*> _objects;
	//unordered_map<int, Player*> _players;
	//unordered_map<int, Monster*> _monsters;
	//unordered_map<int, Projectile*> _projectile;
	//unordered_map<int, Env*> _env;
};

int main()
{
	Field::GetInstance()->Add(new Player(1));

	Object* obj = Field::GetInstance()->Get(1);
	if (obj && obj->GetObjectType() == ObjectType::Player)
	{
		Player* player = static_cast<Player*>(obj);
	}
	
	Player* player = dynamic_cast<Player*>(Field::GetInstance()->Get(1));
	if (player)
	{

	}
}