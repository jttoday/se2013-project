#ifndef MICROPOSTH_GUARD
#define MICROPOSTH_GUARD
#include <vector>
#include <string>
using std::vector;
using std::string;

class User;
class Micropost;
typedef vector<Micropost> MicropostList;

class Micropost {
public:
	Micropost(User& owner);
	Micropost(User& owner, const string& content);
	Micropost& setContent(const string& content);
	Micropost& operator=(const Micropost& rhs);
	void inc(); 
	int fowards() const;
private:
	User& _owner;
	int _fowards;
	string _content;
};




#endif
