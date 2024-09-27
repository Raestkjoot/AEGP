#pragma once

#include <glad/glad.h>

class Window;

class Renderer {
public:
	Renderer::Renderer();

	void Render();

private:
	Window* _window = nullptr;

    float _vertices[12] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int _indices[6] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
};