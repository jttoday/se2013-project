#ifndef USERH_GUARD
#define USERH_GUARD
#include "Micropost.h"
#include <vector>
#include <list>
using std::vector;
using std::list;

enum Gender{ male, female };

class User;
typedef vector<User> UserList;
typedef UserList::iterator user_it;
class LoginInfo;
class BasicInfo;
class AdditionInfo;

class LoginInfo {
public:
	LoginInfo();
	LoginInfo& setPassword(const string& password);
	LoginInfo& setUsername(const string& username);
	const string& username() const;
	const string& password() const;
private:
	string _username;
	string _password;
};

class BasicInfo {
public:
	BasicInfo();
	BasicInfo& setName(const string& name);
	BasicInfo& setGender(Gender gender);
	BasicInfo& setBirth(const string& birth);
	const string& name() const;
	Gender gender() const;
	const string& birth() const;
private:
	string _name;
	string _birth;
	Gender _gender;
};

class User {
public:
	User(const LoginInfo& loginInfo, const BasicInfo& basicInfo);

	User& follow(User& following);
	User& unfollow(User& following);

	const LoginInfo& loginInfo() const;
	const BasicInfo& basicInfo() const;

	User& addMicropost(const Micropost& micropost);
	User& fowardMicropost(Micropost& micropost);
	
	UserList& fans();
	UserList& followings();

	MicropostList& posts();

private:
	User& addFan(User& fan);
	User& removeFan(User& fan);
	
	UserList		_followings;
	UserList		_fans;
	MicropostList	_posts;
	LoginInfo		_loginInfo;
	BasicInfo		_basicInfo;


};

bool operator==(const User& a, const User& b);



#endif
