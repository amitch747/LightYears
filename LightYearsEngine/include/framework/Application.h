#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
namespace ly
{
	class World;
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		void Run();

		// Need template so that we can define different worlds (no editor)
		template<typename WorldType>
		weak<WorldType> LoadWorld();

		sf::Vector2u GetWindowSize();

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow mWindow;
		float mTargetFrameRate;
		sf::Clock mTickClock;

		// Actors may need their own references too, thus shared
		shared<World> currentWorld;
		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		// Shared pointer to the world. Provide reference to Application 
		shared<WorldType> newWorld{ new WorldType{this} };
		// Base type is World so it can hold pointer to whatever WorldType is
		currentWorld = newWorld;
		currentWorld->BeginPlayInternal();
		return newWorld;
	}

}