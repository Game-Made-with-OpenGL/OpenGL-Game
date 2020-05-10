#include "Input.h"

#include <iostream>

Input::Input() {

}

Input::~Input() {

}

void Input::PressKey(unsigned int keyID) {
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	auto it = _mapNames.find(keyID);
	if (it != _mapNames.end()) {
		string mapName = it->second;
		_keyMap[mapName] = true;
		if (!_previousKeyMap[mapName]) _previousKeyMap[mapName] = false;
	}
}

void Input::ReleaseKey(unsigned int keyID) {
	auto it = _mapNames.find(keyID);
	if (it != _mapNames.end()) {
		string mapName = it->second;
		_keyMap[mapName] = false;

		if (_flagKeyMap[mapName] == 0) _previousKeyMap[mapName] = false;

		_flagKeyMap[mapName] = -1;
	}
}

void Input::SetMouseCoords(float x, float y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

// Returns true if the key is press down, and return false after that until it realese
bool Input::GetKeyDown(string name) {
	if (!_flagKeyMap[name] || _flagKeyMap[name] == -1) _flagKeyMap[name] = 0;

	auto it = _keyMap.find(name);
	auto lastInput = _previousKeyMap.find(name);
	if (it != _keyMap.end() && lastInput != _previousKeyMap.end() && it->second != lastInput->second) {
		_previousKeyMap[name] = true;
		
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

// Returns true if the key is release from the press
bool Input::GetKeyUp(string name) {
	if (!_flagKeyMap[name] || _flagKeyMap[name] == -1) _flagKeyMap[name] = 1;

	// Check if it is pressed this frame, and wasn't pressed last frame
	if (GetKeyDown(name) == false && GetKey(name) == false && _previousKeyMap[name] ) {
		_previousKeyMap[name] = false;
		return true;
	}

	return false;
}

// Returns true if the key is held down
bool Input::GetKey(string name) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _keyMap.find(name);
	if (it != _keyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

void Input::InputMapping(string mappingName, unsigned int keyId) {
	_mapNames.insert(pair<unsigned int, string>(keyId, mappingName));
}

void Input::PollInput() {
	SDL_Event evt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			state = Settings::State::EXIT;
			break;
		case SDL_MOUSEMOTION:
			SetMouseCoords((float)evt.motion.x, (float)evt.motion.y);
			break;
		case SDL_KEYDOWN:
			PressKey(evt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			ReleaseKey(evt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			PressKey(evt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			ReleaseKey(evt.button.button);
			break;
		/*case SDL_CONTROLLERDEVICEADDED:
			OpenGameController();
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			CloseGameController();
			break;*/
		case SDL_CONTROLLERBUTTONDOWN:
			PressKey(evt.cbutton.button);
			break;
		case SDL_CONTROLLERBUTTONUP:
			ReleaseKey(evt.cbutton.button);
			break;
		}
	}
}

Settings::State Input::GetState() {
	return state;
}

unordered_map<unsigned int, string> Input::_mapNames;
unordered_map<string, bool> Input::_keyMap;
unordered_map<string, bool> Input::_previousKeyMap;
unordered_map<string, int> Input::_flagKeyMap;
glm::vec2 Input::_mouseCoords;
Settings::State Input::state;