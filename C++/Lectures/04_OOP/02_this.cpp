public:
	// ¸â¹ö ÇÔ¼ö
	void HealME(int value)
	{
		this->hp += value; // hp += value;
	}

	void HealMe(Knight* thisPtr, int value)
	{
		thisPtr->hp += value;
	}