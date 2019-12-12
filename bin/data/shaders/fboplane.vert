#version 410

in vec4 position;
in vec2 texcoord;
in vec3 normal;

uniform mat4 modelViewProjectionMatrix;

out vec2 v_texcoord;

void main() {

    v_texcoord = texcoord;

    gl_Position = modelViewProjectionMatrix * position;
    
}