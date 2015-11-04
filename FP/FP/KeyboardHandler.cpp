#include "KeyboardHandler.h"


CKeyboardHandler::CKeyboardHandler()
{
	for (int c = 0; c < 255; c++)
	{
		keystate[c] = 0;
		pressedThenReleased[c] = 0;
	}
}


CKeyboardHandler::~CKeyboardHandler()
{
}

void CKeyboardHandler::keyboardhandler(){ 
	for (int c = 0; c < 255; c++)
	{
		pressedThenReleased[c] = 0;
	} 
}
void CKeyboardHandler::setstate(SDL_Keycode key, bool state){
	if (keystate[key] == SDL_PRESSED && state == SDL_RELEASED) pressedThenReleased[key] = 1;
	if (state == SDL_PRESSED && pressedThenReleased[key]!=0) pressedThenReleased[key] = 0;
	if (keystate[key] != state) keystate[key] = state;
}
bool CKeyboardHandler::isPressed(SDL_Keycode key){
	return keystate[key];
}
bool CKeyboardHandler::wasPressedNowReleased(SDL_Keycode key){
	return pressedThenReleased[key];
}