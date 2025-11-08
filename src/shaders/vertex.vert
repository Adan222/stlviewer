#version 330 core

// Layout
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Output
out vec3 inNormal;
out vec3 inFragPos;

void main()
{
    inNormal = vec3(model * vec4(aNormal, 0.0));
    inFragPos = vec3(model * vec4(aPos, 1.0));

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}