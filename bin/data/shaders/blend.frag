#version 410

uniform vec2 u_resolution;
uniform vec2 shrink_resolution;

uniform sampler2D input1;
uniform sampler2D input2;

out vec4 out_color;

void main() {
    vec3 color;

    vec2 st = gl_FragCoord.xy / u_resolution;

    color = texture(input1, st).rgb;
    color += texture(input2, st).rgb;

    // gamma
    // color = vec3(1.) - exp(-color);
    // color = pow(color, vec3(0.45454545454545453));

    out_color = vec4(color, 1.0);

}