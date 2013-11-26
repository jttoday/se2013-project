#ifndef PROJECTSERVICEH_GUARD
#define PROJECTSERVICEH_GUARD
#include "User.h"
#include "Micropost.h"
#include "UserManager.h"
namespace SState{
	enum ServiceState { signin, signup, homepage };
}

class ProjectService {
public:
	ProjectService();
	void serve();
private:
	void prompt();		// give user proper prompt to choose;
	void getResonse();	// get user's response
	void doServe();		// do actual work according to user's response;

	void doSignin();
	void doSignup();
	void showHomepage();
	void postNewMicropost();
	void showMyMicroposts();
	void showMyInformation();
	void serchOtherUser();
	void deleteThisUser();
	void logOut();

	void showUser(User& user);
	void showInformation(User& user);
	void showMicroposts(User& user);


	typedef SState::ServiceState ServiceState;

	ServiceState serviceState;
	static UserManager userManager;
	User* currentUser;
	User* dstUser;

};


#endif
