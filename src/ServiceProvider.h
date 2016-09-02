#ifndef __ServiceProvider__
#define __ServiceProvider__

#include "UserActions.h"

class ServiceProvider {
	public:
	static UserActions* getUserActions();
	static void setUserActions(UserActions* userActions);
	static void clean();
};

#endif
