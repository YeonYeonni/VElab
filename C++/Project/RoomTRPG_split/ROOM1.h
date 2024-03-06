#pragma once
#include "ROOM.h"

class ROOM1 : public ROOM
{
public:
	ROOM1();
	virtual ~ROOM1() override;

	virtual void RoomScript() override;
};

