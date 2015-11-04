#ifndef FP_HKEYHANDLER
#define FP_HKEYHANDLER
#include "Engine.h"
class CKeyboardHandler
{
public:
	CKeyboardHandler();
	~CKeyboardHandler();
	void keyboardhandler();
	void setstate(SDL_Keycode key, bool state);
	bool isPressed(SDL_Keycode key);
	bool wasPressedNowReleased(SDL_Keycode key);
private:
	bool keystate[256];
	bool pressedThenReleased[256];
};
#endif