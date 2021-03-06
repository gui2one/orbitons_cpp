#version 400

layout(location = 0) in vec3 position;
// layout(location = 1) in vec3 normal;
// layout(location = 2) in vec2 t_coords;

uniform mat4 u_model;

void main() {
    gl_Position = u_model * vec4(position, 1.0);
}