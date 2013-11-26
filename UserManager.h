#ifndef USERMANGERH_GUARD
#define USERMANGERH_GUARD
#include "User.h"
#include "ProjectService.h"

class UserManager {
public:
	void addUser(const User& user);
	void deleteUser(User& user);
	User* validate(const string& username, const string& password);
	User* findByUsername(const string& username);
	User* updateUser(User& user);
	bool hasUsername(const string& username);
	friend class ProjectService;
private:

	UserList allUsers;

};




#endif
