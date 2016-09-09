#include "ServiceProvider.h"

static UserActions* s_userActions;

UserActions* ServiceProvider::getUserActions() {
	return s_userActions;
}

void ServiceProvider::setUserActions(const char* mappingFile) {
	free(s_userActions);
	s_userActions = new UserActions();
	s_userActions->setActionsFromFile(mappingFile);
}

void ServiceProvider::clean() {
	free(s_userActions);
	s_userActions = 0;
}
