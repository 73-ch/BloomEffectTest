#version 410

in vec4 position;
in vec4 color;
in vec4 normal;

uniform mat4 modelViewProjectionMatrix;

out vec3 v_normal;
out vec4 v_color;

void main() {
    v_normal = normal.xyz;
    v_color = vec4(1.0);

    gl_Position = modelViewProjectionMatrix * vec4(position.xyz, 1.0);
}