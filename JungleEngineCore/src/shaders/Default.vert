#version 330 core
layout (location = 0) in vec3 aPos1;
layout (location = 1) in vec3 aPos2;
layout (location = 2) in vec3 aPos3;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos1, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
