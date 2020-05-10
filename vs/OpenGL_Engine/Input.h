#pragma once
#include <SDL/SDL.h>
#include <string>
#include <unordered_map>
#include <GLM/glm.hpp>
#include "Settings.h"

using namespace std;

static class Input {
public:
	Input();
	~Input();
	// Input Handling
	static void PressKey(unsigned int keyID);
	static void ReleaseKey(unsigned int keyID);
	static void SetMouseCoords(float x, float y);
	// Returns true if the key is held down
	static bool GetKeyDown(string name);
	// Returns true if the key was just pressed
	static bool GetKeyUp(string name);
	// getters
	static glm::vec2 GetMouseCoords(){ return _mouseCoords; }
	// Returns true if the key is held down
	static bool GetKey(string name);

	static Settings::State GetState();

	static void InputMapping(string mappingName, unsigned int keyId);

	static void PollInput();
private:
	static unordered_map<unsigned int, string> _mapNames;
	static unordered_map<string, bool> _keyMap;
	static unordered_map<string, bool> _previousKeyMap;
	static unordered_map<string, int> _flagKeyMap; //0 KeyDown, 1 KeyUp , -1 normal
	static glm::vec2 _mouseCoords;
	static Settings::State state;
};
