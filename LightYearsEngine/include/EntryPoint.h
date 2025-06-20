#pragma once

// Foward declaration. For some reason, including a pointer means we don't need the whole header file
namespace ly
{
	class Application;
}
extern ly::Application* GetApplication();