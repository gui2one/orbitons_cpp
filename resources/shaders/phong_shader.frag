#version 400
// out vec4 frag_color;

struct Material{
    vec3 diffuseColor;
    vec3 specularColor;
};

in vec3 f_position;
in vec3 f_normal;

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;


uniform vec3 u_lightPos;    
uniform vec3 u_cameraPos;    

uniform Material material;

void main() {

    float shininess = 50.0;
    vec3 lightColor = vec3(1,1,1);
    vec3 normal = normalize(f_normal);

    vec3 lightDir = normalize( f_position - u_lightPos);
    vec3 viewDir = normalize(f_position - u_cameraPos  );
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specular = lightColor * spec * material.specularColor;
    
    float diff = max(dot(normal, lightDir),0.0);
    gl_FragColor = vec4( diff * material.diffuseColor + specular, 1.0);
//   gl_FragColor = vec4(f_normal, 1.0);
}