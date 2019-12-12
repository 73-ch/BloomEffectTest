#version 410

in vec3 v_normal;
in vec4 v_color;

uniform mat4 inv_matrix;
uniform vec3 light_direction;
uniform vec3 eye_direction;
uniform vec4 ambient_color;

out vec4 out_color;

void main() {
    vec3 inv_light = normalize(inv_matrix * vec4(light_direction, 0.)).xyz;
    vec3 inv_eye = normalize(inv_matrix * vec4(eye_direction, 0.0)).xyz;
    vec3 half_le = normalize(inv_light + inv_eye);
    float diffuse = clamp(dot(v_normal, inv_light), 0.0, 1.0);
    float specular = pow(clamp(dot(v_normal, half_le), 0., 1.), 50.);
    
    out_color = v_color * vec4(vec3(diffuse), 1.0) + vec4(vec3(specular), 1.0) + ambient_color;
}