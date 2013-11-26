#ifndef MYTOOLH_GUARD_
#define MYTOOLH_GUARD_
#include <sstream>
#include <string>
#include "User.h"

class MyTool {
public:
	static int stringToInt(const std::string& str)
	{
		std::istringstream is(str);
		int n;
		is >> n;
		return n;
	}
	static bool isFans(User& fan, User& following)
	{
		for (user_it it = fan.followings.begin();
				it != fan.followings.end();++it)
		{
			if (*it == following)
				return true;
		}
		return false;
	}
		
};


#endif
