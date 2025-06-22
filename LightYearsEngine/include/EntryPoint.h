#pragma once

// Foward declaration. For some reason, including a pointer means we don't need the whole header file
namespace ly
{
	class Application;
}
// Some other class will implement this (the game)
extern ly::Application* GetApplication();
