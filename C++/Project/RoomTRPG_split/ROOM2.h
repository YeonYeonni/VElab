#pragma once
#include "ROOM.h"

class ROOM2 : public ROOM
{
public:
	ROOM2();
	virtual ~ROOM2() override;

	virtual void RoomScript() override;
};

