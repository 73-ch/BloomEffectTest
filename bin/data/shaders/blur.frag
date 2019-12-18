#version 410

in vec2 v_texcoord;

uniform sampler2D input_texture;

uniform vec2 u_resolution;

const float[5] weights = float[](0.2270270, 0.1945945, 0.1216216, 0.0540540, 0.0162162);

ivec2 clampCoord(ivec2 coord, ivec2 size) {
    return max(min(coord, size - 1), 0);
}

uniform bool is_vertical;

out vec4 out_color;

void main() {
    vec4 color = vec4(0.0);

    vec2 st = gl_FragCoord.xy / u_resolution;
    vec3 sum = weights[0] * texture(input_texture, st).rgb;

    for (int i = 1; i < 5; i++) {
        vec2 offset = (is_vertical ? vec2(0, i) : vec2(i, 0)) / u_resolution;
        sum += weights[i] * texture(input_texture, fract(st + offset), 0).rgb;
        sum += weights[i] * texture(input_texture, fract(st - offset), 0).rgb;
    }


    // if (is_vertical) {
    //     for (int i = 0; i < SAMPLE_COUNT; i++) {
    //         color += texture(input_texture, st + offsets_v[i]) * weights_v[i];
    //     }
    // } else {
    //     for (int i = 0; i < SAMPLE_COUNT; i++) {
    //         color += texture(input_texture, st + offsets_h[i]) * weights_h[i];
    //     }
    // }

    out_color = vec4(sum, 1.0);
}