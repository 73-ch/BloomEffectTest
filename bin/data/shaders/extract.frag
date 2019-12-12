#version 410

in vec2 v_texcoord;

uniform sampler2D input_texture;
uniform float min_bright;
uniform vec2 u_resolution;

out vec4 out_color;

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec3 tex = max(vec3(0.), (texture(input_texture, st) - min_bright).rgb);

    out_color = vec4(tex, 1.0);
    // out_color = vec4(st, 1.0 ,1.0);
}