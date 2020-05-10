#include "TurnBasedGame.h"
#include "Scene.h"

Scene scene;

TurnBasedGame::TurnBasedGame()
{
	
}


TurnBasedGame::~TurnBasedGame()
{
}

void TurnBasedGame::Init()
{
	InputMapping();
	scene.Init();
}

void TurnBasedGame::Update()
{
	if (Input::GetKeyDown("Quit")) {
		SDL_Quit();
		exit(0);
	}

	scene.Update();
}

void TurnBasedGame::Render()
{
	//Setting Viewport
	glViewport(0, 0, Window::GetScreenWidth(), Window::GetScreenHeight());

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	scene.Render();
}

void TurnBasedGame::InputMapping() {
	// Add input mapping
	// to offer input change flexibility you can save the input mapping configuration in a configuration file (non-hard code) !
	Input::InputMapping("Move Right", SDLK_RIGHT);
	Input::InputMapping("Move Left", SDLK_LEFT);
	Input::InputMapping("Move Right", SDLK_d);
	Input::InputMapping("Move Left", SDLK_a);
	Input::InputMapping("Move Right", SDL_BUTTON_RIGHT);
	Input::InputMapping("Move Left", SDL_BUTTON_LEFT);
	Input::InputMapping("Move Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	Input::InputMapping("Move Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	Input::InputMapping("Quit", SDLK_ESCAPE);
	Input::InputMapping("Jump", SDLK_SPACE);
	Input::InputMapping("Jump", SDL_CONTROLLER_BUTTON_A);

	Input::InputMapping("Attack", SDLK_1);
	Input::InputMapping("Deffend", SDLK_2);
	Input::InputMapping("Run", SDLK_3);
}



int main(int argc, char** argv) {
	TurnBasedGame tbg = TurnBasedGame();
	Engine::ScratchEngine &game = tbg;
	game.Start("Test", 800, 600, false, WindowFlag::WINDOWED, 60, 1);

	return 0;
}
