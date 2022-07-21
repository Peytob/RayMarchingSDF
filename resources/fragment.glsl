#version 330 core

out vec3 fs_color;

in vec4 vs_position;

uniform float u_resolution;
uniform float u_time;

vec3 render(in vec2 uvScreenCoordinates) {
    return vec3(1.0, uvScreenCoordinates.xy);
}

void main() {
    vec2 uvScreenCoordinates = (2.0 * gl_FragCoord.xy - u_resolution.xy) / u_resolution.y;
    vec3 color = (uvScreenCoordinates);

    fs_color = color * u_time;
}
