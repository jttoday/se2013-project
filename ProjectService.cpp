#include "ProjectService.h"
#include "MyTool.h"
#include <iostream>
#include <string>
#include <fstream>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::flush;
using std::ifstream;
using std::ofstream;

ProjectService::ProjectService()
{
	serviceState = SState::signin;
}

UserManager ProjectService::userManager;

void ProjectService::serve()
{
	load();
	cout << "Welcome to this simple Micropost System" << endl;
	while(cin)
	{
		cout << "---------------------------------------" << endl;
		doServe();
	}
	cout << endl;
	save();

}



void ProjectService::save()
{
	ofstream os("dat");
	UserList users = userManager.allUsers;
	int n = users.size();
	os << n << ' ';
	for (int i=0; i < n; i++)
	{
		User user =  users[i];
		os << user.loginInfo().username() << ' ';
		os << user.loginInfo().password() << ' ';
		os << user.basicInfo().name() << ' ';
		os << user.basicInfo().birth() << ' ';

		MicropostList posts = user.posts();
		int nn = posts.size();
		os << nn << ' ';
		for (int j=0; j < nn; j++)
		{
			os << posts[j].content() << ' ';
		}
	}
}
	
void ProjectService::load()
{
	ifstream is("dat");
	int n;
	is >> n;
	if (!is)
		return;
	for (int i=0; i < n; ++i)
	{
		string username, password, name, birth;
		is >> username >> password >> name >> birth;
		User user(LoginInfo(username, password),
								 BasicInfo(name, male, birth));
		int nn;
		is >> nn;
		for (int j=0; j < nn; ++j)
		{
			string content;
			is >> content;
			Micropost mp(user, content);
			user.addMicropost(mp);
		}
		userManager.addUser(user);
	}
}
	


void ProjectService::doServe()
{
	switch(serviceState) {
	case SState::signin:
		doSignin();
		break;
	case SState::signup:
		doSignup();
		break;
	case SState::homepage:
		showHomepage();
		break;
	default:
		break;
	}
}
		
void ProjectService::doSignin()
{
	string username, password;
	cout << "Please login. " << endl;
	cout << "If you want to sign up, enter \"new\" as username." << endl;
	while(cin)
	{
		cout << "username:" << flush;
		cin >> username;
		if (username == "new")
		{
			serviceState = SState::signup;
			return;
		}
		cout << "password:" << flush;
		cin >> password;
		if ((currentUser = userManager.validate(username, password))
				!= NULL)
		{
			dstUser = currentUser;
			serviceState = SState::homepage;
			return;
		}
		else
		{
			cout << "Sorry, please try again." << endl;
		}
	}
}
					
void ProjectService::doSignup()
{
	cout << "Please fill in necessary information to finish sign up." << endl;
	cout << "ctrl+D to quit sign up." << endl;
	string username, password, name, birth;
	while (1)
	{
		cout << "username:" << flush;
		cin >> username;
		if (!cin)
		{
			cin.ignore();
			cin.clear();
			serviceState = SState::signin;
			return;
		}
		if (!userManager.hasUsername(username))
			break;
		cout << "Sorry, this username has been used." << endl;
	}
	while (1)
	{
		cout << "password:" << flush;
		cin >> password;
		if (!cin)
		{
			cin.clear();
			serviceState = SState::signin;
			return;
		}
		if (password.size() >=8 &&password.size() <= 32)
			break;
		cout << "Sorry, password should between 8 and 32." << endl;
	}
	cout << "name:" << flush;
	cin >> name;
	if (!cin)
	{
		cin.clear();
		serviceState = SState::signin;
		return;
	}
	cout << "birth:" << flush;
	cin >> birth;
	if (!cin)
	{
		cin.clear();
		serviceState = SState::signin;
		return;
	}
	LoginInfo li;
	li.setUsername(username).setPassword(password);
	BasicInfo bi;
	bi.setBirth(birth).setGender(male).setName(name);
	User user(li, bi);
	userManager.addUser(user);
	currentUser = userManager.validate(username, password);
	serviceState = SState::homepage;
}



void ProjectService::showHomepage()
{
	string option;
	cout << "Welcome! " << currentUser->basicInfo().name() << endl;
	cout << "enter the number before each instruction to tell what to do:" << endl;
	cout << "[1] make a new Micropost" << endl;
	cout << "[2] view my Microposts"   << endl;
	cout << "[3] show my infomation"   << endl;
	cout << "[4] serch other user by username " << endl;
	cout << "[5] update my information" << endl;
	cout << "[8] delete this account"  << endl;
	cout << "[9] log out"			   << endl;
	int opt;
	do {
		cout << "choose:" << flush;
		cin >> option;
		if (!cin) 
			return;
		opt = MyTool::stringToInt(option);
		switch (opt) {
		case 1:
			postNewMicropost();
			break;
		case 2:
			showMyMicroposts();
			break;
		case 3:
			showMyInformation();
			break;
		case 4:
			serchOtherUser();
			break;
		case 5:
			updateInformation();
			break;
		case 8:
			deleteThisUser();
			break;
		case 9:
			logOut();
			break;
		default:
			if (!cin)
				return;
			cout << "Sorry, please enter again" << endl;
			break;
		}
	} while (opt <1 || (opt > 5 && opt != 9 && opt != 8)); 
}


void ProjectService::postNewMicropost()
{
	string content;
	cout << "Enter the content:";
	cin.ignore();
	std::getline(cin, content);
	currentUser->addMicropost(Micropost(*currentUser, content));
	cout << "New Micropost has been created successfully" << endl;
}

void ProjectService::showMyMicroposts()
{
	showMicroposts(*currentUser);
}

void ProjectService::showMyInformation()
{
	showInformation(*currentUser);
}

void ProjectService::serchOtherUser()
{
	cout << "enter the user's username who you want to search " << endl;
	cout << "username:" << flush;
	string username;
	cin >> username;
	User* user = userManager.findByUsername(username);
	if (user == NULL)
		cout << "Sorry, no such user" << endl;
	else
	{
		dstUser = user;
		if (dstUser == currentUser)
			return;
		showUser(*user);
	}
}

void ProjectService::updateInformation()
{
	cout << "Enter the item you want to change." << endl;
	cout << "[1] password:" << endl;
	cout << "[2] name: " << currentUser->basicInfo().name() << endl;
	cout << "[3] birth: "<< currentUser->basicInfo().birth() << endl;
	string option;
	cin >> option;
	int opt = MyTool::stringToInt(option);
	switch(opt)
	{
	case 1:
		{
		string oldPassword;
		string newPassword;
		cout << "Your old password?:" << flush;
		cin >> oldPassword;
		if (oldPassword != currentUser->loginInfo().password())
		{
			cout << "Sorry, not correct." << endl;
			return;
		}
		else
		{
			cout << "New password?:" << endl;
			cin >> newPassword;
			currentUser->loginInfo().setPassword(newPassword);
			currentUser = userManager.updateUser(*currentUser);
			break;
		}
		}
	case 2:
		{
		string name;
		cout << "Your new name?:" << flush;
		cin >> name;
		currentUser->basicInfo().setName(name);
		currentUser = userManager.updateUser(*currentUser);
		break;
		}
	case 3:
		{
		string birth;
		cout << "Your new birth?:" << flush;
		cin >> birth;
		currentUser->basicInfo().setBirth(birth);
		currentUser = userManager.updateUser(*currentUser);
		break;
		}
	default:
		break;
	}
}



void ProjectService::deleteThisUser()
{
}

void ProjectService::logOut()
{
	currentUser = NULL;
	serviceState = SState::signin;
}


void ProjectService::showUser(User& user)
{

	cout << "This is home page of " << dstUser->basicInfo().name() << endl;
	bool hasFollowed = MyTool::isFans(*currentUser, *dstUser) ;
	if (hasFollowed)
		cout << "You have been his/her fan." << endl;
	else 
		cout << "You have not been his/her fan." << endl;
	cout << "enter the number before each instruction to tell what to do:" << endl;
	if (hasFollowed)
		cout << "[1] unfollow this user" << endl;
	else
		cout << "[1] follow this user" << endl;
	cout << "[2] show his/her infomation." << endl;
	cout << "[3] show his/her microposts." << endl;
	string option;
	cin >> option;
	int opt = MyTool::stringToInt(option);
	do {
		switch (opt) {
		case 1:
			if (hasFollowed)
			{
				currentUser->unfollow(*dstUser);
				cout << "Unfollow successfully." << endl;
			}
			else
			{
				currentUser->follow(*dstUser);
				cout << "Follow successsfully." << endl;
			}
			break;
		case 2:
			showUser(*dstUser);
			break;
		case 3:
			showMicroposts(*dstUser);
			break;
		default:
			if (!cin)
				return;
			cout << "Sorry, please enter again." << endl;
		}
	} while (opt < 1 || opt > 3);
}

void ProjectService::showMicroposts(User& user)
{
	MicropostList mlist = user.posts();
	cout << "Enter the number before to foward that micropost" << endl;
	cout << "Enter other characters to return to upper menu" << endl;
	for (int i = 0; i < mlist.size(); ++i)
	{
		cout << "[" << i+1 << "]";
		cout << user.basicInfo().name() << ":";
		cout << mlist[i].content() << endl;
	}
	int opt;
	string option;
	cin >> option;
	opt = MyTool::stringToInt(option);
	if (!cin)
		return;
	if (opt <1 || opt > mlist.size())
	{
		return;
	}
	else
	{
		currentUser->fowardMicropost(mlist[--opt]);
		cout << "Foward successfully" << endl;
	}
}
	
/*
 * TODO:
 */
void ProjectService::showInformation(User& user)
{
}

	
	





	



