#include "Core.hpp"
#pragma comment (lib ,"imm32.lib")
#include <Windows.h>

namespace rpf {

	Core* Core::CORE = nullptr;
	int Core::highest_score = 0;

	Core::Core() : mode(Mode::IN_GAME), rm(&window) {//mode(Mode::MAIN_MENU)
		window.create(sf::VideoMode::VideoMode(rh.s_width, rh.s_height), "Ryan PlatFormer v1.0", sf::Style::Resize | sf::Style::Close);
		window.setFramerateLimit(60);
		window.setKeyRepeatEnabled(false);
		ImmAssociateContext(window.getSystemHandle(), NULL);
		now = nullptr;
		rh.music.play();
		Core::CORE = this;
	}
	
	void Core::Run() {
		switchMode(Mode::IN_GAME);//start with ...
		while (window.isOpen())
			this->update();
	}

	void Core::update() {
		sf::Event e;
		while (window.pollEvent(e))
			if (e.type == sf::Event::Closed)
				window.close();
			else if (e.type == sf::Event::Resized) {
				float screenWidth = 160.f;
				float screenHeight = 96.f;
				sf::Vector2u size = window.getSize();
				float heightRatio = screenHeight / screenWidth;
				float widthRatio = screenWidth / screenHeight;
				if (size.y * widthRatio <= size.x)
				{
					size.x = size.y * widthRatio;
				}
				else if (size.x * heightRatio <= size.y)
				{
					size.y = size.x * heightRatio;
				}
				window.setSize(size);
			}
			else
				now->handleEvent(e);
		now->update();
		rm.Render();
	}

	void Core::switchMode(Mode mode) {
		switch (mode) {
		case Mode::IN_GAME:
			now = new Game(&rm, &rh);
			break;
		case Mode::GAME_OVER:
			now = new GameOverMenu(&rm, &rh);
			break;
		case Mode::CLOSED:
			window.close();
			break;
		}
	}

	
}