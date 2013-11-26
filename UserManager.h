#ifndef USERMANGERH_GUARD
#define USERMANGERH_GUARD
#include "User.h"

class UserManager {
public:
	void addUser(const User& user);
	void deleteUser(User& user);
	User* validate(const string& username, const string& password);
	User* findByUsername(const string& username);
	bool hasUsername(const string& username);
private:

	UserList allUsers;

};




#endif
