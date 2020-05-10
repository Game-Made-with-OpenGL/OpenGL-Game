#include "Window.h"

unsigned int Window::GetScreenHeight() {
	return screenHeight;
}

unsigned int Window::GetScreenWidth() {
	return screenWidth;
}

void Window::SetScreenHeight(unsigned int value) {
	screenHeight = value;
}

void Window::SetScreenWidth(unsigned int value) {
	screenWidth = value;
}

unsigned int Window::screenWidth = 0, Window::screenHeight = 0;