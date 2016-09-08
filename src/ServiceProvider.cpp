#include "ServiceProvider.h"

static UserActions* s_userActions;

UserActions* ServiceProvider::getUserActions() {
	return s_userActions;
}

void ServiceProvider::setUserActions(UserActions* userActions) {
	free(s_userActions);
	s_userActions = userActions;
}

void ServiceProvider::clean() {
	free(s_userActions);
	s_userActions = 0;
}
