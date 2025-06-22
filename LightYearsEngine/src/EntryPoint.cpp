#include "EntryPoint.h"
#include "framework/Application.h"

// Start here. GetApplication() provides the game
int main()
{
	ly::Application* app = GetApplication();
	app->Run();
	delete app;
}