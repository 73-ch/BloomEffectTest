#version 410

uniform vec2 u_resolution;

uniform sampler2D input1;
uniform sampler2D input2;

out vec4 out_color;

void main() {
    vec4 color;

    vec2 st = gl_FragCoord.xy / u_resolution;

    color = texture(input1, st);
    color += texture(input2, st);

    out_color = color;
}