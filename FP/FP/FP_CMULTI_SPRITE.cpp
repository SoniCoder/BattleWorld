#include "FP_CMULTI_SPRITE.h"



FP_CMULTI_SPRITE::FP_CMULTI_SPRITE(const char* src,int passed_nelehori, int passed_neleverti)
	:nelehori(passed_nelehori), neleverti(passed_neleverti)
{
	textureptr = IMG_LoadTexture(m_struct.renderer, src);
	imgHeight = 0;
	imgWidth = 0;
	SDL_QueryTexture(textureptr, NULL, NULL, &imgWidth, &imgHeight);
	eleWidth = imgWidth / nelehori;
	eleHeight = imgHeight / neleverti;
	Disprect.w = eleWidth;
	Disprect.h = eleHeight;
	CropRect.w = eleWidth;
	CropRect.h = eleHeight;
}


FP_CMULTI_SPRITE::~FP_CMULTI_SPRITE()
{
}

void FP_CMULTI_SPRITE::Draw(int m, int n, int x, int y) {
	/*
	Not that here m and n are the indices of the required element and are zero indexed
	*/
	CropRect.x = m*eleWidth;
	CropRect.y = n*eleHeight;
	Disprect.x = x;
	Disprect.y = y;


	//std::cout << x << y << CropRect.x << CropRect.y << std::endl;
	SDL_RenderCopy(m_struct.renderer, textureptr, &CropRect, &Disprect);
}

void FP_CMULTI_SPRITE::Draw(int m, int n, int x, int y, int w, int h) {
	/*
	Not that here m and n are the indices of the required element and are zero indexed
	*/
	CropRect.x = m*eleWidth;
	CropRect.y = n*eleHeight;
	Disprect.x = x;
	Disprect.y = y;
	Disprect.w = w;
	Disprect.h = h;
	SDL_RenderCopy(m_struct.renderer, textureptr, &CropRect, &Disprect);
}

void FP_CMULTI_SPRITE::Draw(int m, int n, float x, float y, float w, float h) {
	/*
	Not that here m and n are the indices of the required element and are zero indexed
	*/
	CropRect.x = m*eleWidth;
	CropRect.y = n*eleHeight;
	Disprect.x = fp_float_to_int_width(x);
	Disprect.y = fp_float_to_int_height(y);
	Disprect.w = fp_float_to_int_width(w);
	Disprect.h = fp_float_to_int_height(h);
	SDL_RenderCopy(m_struct.renderer, textureptr, &CropRect, &Disprect);
}

void FP_CMULTI_SPRITE::Draw(int m, int n, int x, int y, float scale) {
	/*
	Not that here m and n are the indices of the required element and are zero indexed
	*/
	CropRect.x = m*eleWidth;
	CropRect.y = n*eleHeight;
	Disprect.x = (int)(m_struct.window.wtostd*x);
	Disprect.y = (int)(m_struct.window.wtostd*y);
	Disprect.w = (int)(eleWidth*scale*m_struct.window.wtostd);
	Disprect.h = (int)(eleHeight*scale*m_struct.window.wtostd);
	SDL_RenderCopy(m_struct.renderer, textureptr, &CropRect, &Disprect);
}