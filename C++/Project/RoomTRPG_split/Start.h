#pragma once
#include "ROOM.h"

class Start : public ROOM
{
public:
	Start();
	virtual ~Start() override;

	virtual void RoomScript() override;

};