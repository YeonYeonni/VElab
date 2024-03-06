#pragma once
#include "ROOM.h"

class End : public ROOM
{
public:
	End();
	virtual ~End() override;

	virtual void RoomScript() override;
};

