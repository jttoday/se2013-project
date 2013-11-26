#include "Micropost.h"


Micropost::Micropost(User& owner)
	:_owner(owner)
{ }


Micropost::Micropost(User& owner,const string& content)
	:_owner(owner), _content(content)
{ }

Micropost& Micropost::setContent(const string& content)
{
	_content = content;
	return *this;
}

Micropost& Micropost::operator=(const Micropost& rhs)
{
	_content = rhs._content;
	_fowards = rhs.fowards();
	return *this;
}

void Micropost::inc()
{
	++_fowards;
}

int Micropost::fowards() const
{
	return _fowards;
}


