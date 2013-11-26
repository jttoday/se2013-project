#include "User.h"


bool operator==(const User& a, const User& b)
{
	return a.loginInfo().username()
		   == b.loginInfo().username();
}

/* class User functions */
User::User(const LoginInfo& loginInfo, const BasicInfo& basicInfo)
	:_basicInfo(basicInfo), _loginInfo(loginInfo)
{
}

User& User::follow(User& following)
{
	_followings.push_back(following);
	following.addFan(*this);
	return *this;
}

User& User::unfollow(User& following)
{
	for (user_it it = _followings.begin(); 
			it != _followings.end(); ++it)
	{
		if (*it == following)
			_followings.erase(it);
	}
	following.removeFan(*this);
	return *this;
}

const LoginInfo& User::loginInfo() const
{
	return _loginInfo;
}

const BasicInfo& User::basicInfo() const
{
	return _basicInfo;
}

User& User::addMicropost(const Micropost& micropost)
{
	_posts.push_back(micropost);
	return *this;
}

User& User::fowardMicropost(Micropost& micropost)
{
	_posts.push_back(micropost);
	micropost.inc();
	return *this;
}

UserList& User::fans()
{
	return _fans;
}

UserList& User::followings()
{
	return _followings;
}

MicropostList& User::posts()
{
	return _posts;
}

User& User::addFan(User& fan)
{
	_fans.push_back(fan);
	return *this;
}

User& User::removeFan(User& fan)
{
	for (user_it it = _fans.begin(); it != _fans.end(); ++it)
	{
		if (*it == fan)
			_fans.erase(it);
	}
	return *this;
}

/* class User functions end */

/* class LoginInfo functions */
LoginInfo::LoginInfo()
{ }

LoginInfo& LoginInfo::setPassword(const string& password)
{
	_password = password;
	return *this;
}

LoginInfo& LoginInfo::setUsername(const string& username)
{
	_username = username;
	return *this;
}

const string& LoginInfo::username() const
{
	return _username;
}

const string& LoginInfo::password() const
{
	return _password;
}
/* class LoginInfo functions end */

/* class BasicInfo functions */

BasicInfo::BasicInfo()
{ }

BasicInfo& BasicInfo::setName(const string& name)
{
	_name = name;
	return *this;
}

BasicInfo& BasicInfo::setGender(Gender gender)
{
	_gender = gender;
	return *this;
}

BasicInfo& BasicInfo::setBirth(const string& birth)
{
	_birth = birth;
	return *this;
}

const string& BasicInfo::name() const
{
	return _name;
}

Gender BasicInfo::gender() const
{
	return _gender;
}

const string& BasicInfo::birth() const
{
	return _birth;
}

/* BasicInfo functions end */

/* static helper function */

/* static helper function end */


