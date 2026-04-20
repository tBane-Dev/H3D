#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "gl/glu.h"

#include "DebugLog.hpp"
#include "Window.hpp"
#include "Textures.hpp"
#include "Cursor.hpp"
#include "Time.hpp"
#include "Element.hpp"

#include "Vertex3D.hpp"
#include "Mesh3D.hpp" 
#include "Model3D.hpp"
#include "Scene.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    window = std::make_unique<sf::Window>(sf::VideoMode(sf::Vector2u(1280, 720), 32u), "H3D", sf::State::Windowed, settings);
    window->setVerticalSyncEnabled(true);

    loadTextures();
    cursor = std::make_shared<Cursor>();

	scene = std::make_shared<Scene>();

    std::shared_ptr<Model3D> cube1 = std::make_shared<Model3D>();
    std::shared_ptr<Model3D> cube2 = std::make_shared<Model3D>();
    
    cube2->_z = -1.f;
    cube2->_x = -1.f;

    sf::Time cubeMovementTimer = currentTime;
	scene->addModel(cube1);
	scene->addModel(cube2);


    // OpenGL init
    glClearDepth(1.f);
    glClearColor(0.25f, 0.25f, 0.25f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    while (window->isOpen())
    {
        cursor->update();

        prevTime = currentTime;
        currentTime = mainClock.getElapsedTime();

        while (auto event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window->close();
        }

        cube1->_rx += 0.1f;
        cube1->_ry += 0.1f;
		if (cube1->_rx >= 360.f) cube1->_rx -= 360.f;
		if (cube1->_ry >= 360.f) cube1->_ry -= 360.f;

        scene->update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->draw();

        window->display();
    }

    return 0;
}
