#include "UserManager.h"

void UserManager::addUser(const User& user)
{
	allUsers.push_back(user);
}

void UserManager::deleteUser(User& user)
{
}

User* UserManager::validate(const string& username, const string& password)
{
	User* user = findByUsername(username);
	if (user == NULL)
		return NULL;
	if (user->loginInfo().password() == password)
		return user;
	return NULL;
}

bool UserManager::hasUsername(const string& username)
{
	return findByUsername(username) != NULL;
}

User* UserManager::findByUsername(const string& username)
{
	for (user_it it = allUsers.begin(); it != allUsers.end(); ++it)
	{
		if (it->loginInfo().username() == username)
			return &(*it);
	}
	return NULL;
}
