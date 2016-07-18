#include "MenuButton.h"

void MenuButton::setActive(const bool active) {
	m_pActive = active;
	m_iCurrentFrame = (int) active;
}
