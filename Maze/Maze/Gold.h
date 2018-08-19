#pragma once
#include <vector>
#include "Box.h"

class Gold
{
public:
	Gold();
	~Gold();

	Gold(int i_, int j_) :i(i_), j(j_) {
		Goldlist.push_back(this);
	};

	int i;
	int j;

	static std::vector<Gold*> Goldlist;


	bool CheckGameOver(std::vector<Box*> boxlist)
	{
		for (const auto iter : Goldlist)
		{
			bool result = false;
			for (const auto box : boxlist)
			{
				if (box->HasBox(iter->i, iter->j))
				{
					result = true;
					break;
				}
			}
			// 所有的box都没有出现在iter指向的位置
			if (result == false)
			{
				return false;
			}
		}
		return true;
	}
};

