#ifndef FP_HMULTI_SPRITE
#define FP_HMULTI_SPRITE

#include "Engine.h"
class FP_CMULTI_SPRITE
{
public:
	FP_CMULTI_SPRITE(const char* src, int nelehori, int neleverti);
	~FP_CMULTI_SPRITE();
	void Draw(int m, int n, int x, int y);
	void Draw(int m, int n, int x, int y, int w, int h);
	void Draw(int m, int n, float x, float y, float w, float h);
	void Draw(int m, int n, int x, int y, float scale);
private:
	SDL_Texture* textureptr;
	int imgWidth;
	int imgHeight;
	int nelehori;
	int	neleverti;
	int eleWidth;
	int eleHeight;
	SDL_Rect Disprect;
	SDL_Rect CropRect;
};
#endif
