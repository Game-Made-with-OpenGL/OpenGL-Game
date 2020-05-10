#ifndef  WINDOW_H
#define WINDOW_H
#pragma once

static class Window {
public:
	static unsigned int GetScreenHeight();

	static unsigned int GetScreenWidth();

	static void SetScreenHeight(unsigned int value);

	static void SetScreenWidth(unsigned int value);

private :
	static unsigned int screenWidth, screenHeight;
};

#endif // ! WINDOW_H


