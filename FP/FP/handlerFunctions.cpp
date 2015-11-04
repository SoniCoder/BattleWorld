#include "handlerFunctions.h"

bool FP_isPressed(SDL_Keycode key) {
	return ((CKeyboardHandler*)(m_struct.handlers.keyhandler))->isPressed(key);
}