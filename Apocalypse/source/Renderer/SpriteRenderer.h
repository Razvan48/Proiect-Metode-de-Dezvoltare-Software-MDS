#pragma once 

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ResourceManager/Texture.h"
#include "../ResourceManager/Shader.h"

class SpriteRenderer
{
public:
    SpriteRenderer();
    ~SpriteRenderer();

    // renders a defined quad textured with given sprite
    void draw(Shader& shader, const Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    // render state
    GLuint VAO;
};

