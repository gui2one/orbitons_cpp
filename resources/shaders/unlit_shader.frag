#version 400

struct Material{
    vec3 color; 
};


uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

in vec3 f_color;

uniform Material material;
void main() {

    gl_FragColor = vec4(material.color, 1.0);
    // gl_FragColor = vec4(1.0,0,0, 1.0);

}