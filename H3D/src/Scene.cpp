#include "Scene.hpp"
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include "Cursor.hpp"
#include "DebugLog.hpp"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::setViewport()
{
    glViewport(0, 0, window->getSize().x, window->getSize().y);
}

void Scene::setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        60.0,
        double(window->getSize().x) / double(window->getSize().y),
        0.1,
        100.0
    );
}

void Scene::setCamera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.f, 0.f, -5.f);
}

void Scene::addModel(std::shared_ptr<Model3D> model) {
	_models.push_back(model);
}


void Scene::drawModels() {
    for (auto& model : _models) {
        model->draw(_selectedModelId);
    }
}

int Scene::getHoveredModelId() {
    constexpr int BUFFER_SIZE = 64;
    GLuint selectBuffer[BUFFER_SIZE];

    GLint viewport[4];

    setViewport();
    glGetIntegerv(GL_VIEWPORT, viewport);

    glSelectBuffer(BUFFER_SIZE, selectBuffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // obszar kliknięcia: 1x1 pikseli
    gluPickMatrix(
        cursor->_position.x,
        viewport[3] - cursor->_position.y - 1,
        1.0,
        1.0,
        viewport
    );

    gluPerspective(
        60.0,
        double(window->getSize().x) / double(window->getSize().y),
        0.1,
        100.0
    );

    setCamera();

    for (auto& model : _models) {
        glLoadName(model->_id);
        model->draw(_selectedModelId);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glFlush();

    GLint hits = glRenderMode(GL_RENDER);

    if (hits <= 0) {
        return -1;
    }

    GLuint* ptr = selectBuffer;

    for (int i = 0; i < hits; i++)
    {
        GLuint namesCount = ptr[0];

        ptr += 3;

        for (GLuint j = 0; j < namesCount; j++)
        {
            GLuint id = *ptr;
            return id;
            ptr++;
        }
    }

    
}

void Scene::update() {
	_selectedModelId = getHoveredModelId();
}

void Scene::draw() {

    setViewport();
    setProjection();
    setCamera();

    drawModels();
}

std::shared_ptr<Scene> scene;