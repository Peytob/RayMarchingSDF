#version 330 core

layout (location = 0) out vec4 fs_color;

uniform vec2 u_resolution;
uniform float u_time;
uniform vec3 u_cameraPosition;
uniform float u_fov;

const int MAX_STEPS = 255;
const float MAX_DISTANCE = 255.0;
const float EPSILON = 0.0001;

vec2 map(vec3 point) {
    point = mod(point, 4.0) - 4.0 * 0.5;
    float sphereDistance = length(point) - 1.0;
    return vec2(sphereDistance, 1.0); // distance - id
}

vec2 rayMarching(in vec3 rayOrigin, in vec3 rayDirection) {
    vec2 object = vec2(0.0);
    vec2 hit = vec2(0.0);

    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 currentPoint = rayOrigin + object.x * rayDirection;
        hit = map(currentPoint);
        object.x += hit.x;
        object.y = hit.y;
        if (abs(hit.x) < EPSILON || object.x > MAX_DISTANCE) {
            break;
        }
    }

    return object;
}

void render(inout vec3 pixelColor, in vec2 uvScreenCoordinates) {
    vec3 rayOrigin = u_cameraPosition;
    vec3 rayDirection = normalize(vec3(uvScreenCoordinates, u_fov));

    vec2 object = rayMarching(rayOrigin, rayDirection);

    if (object.x < MAX_DISTANCE) {
        pixelColor += 3.0 / object.x;
    }
}

void main() {
    vec2 uvScreenCoordinates = (2.0 * gl_FragCoord.xy - u_resolution.xy) / u_resolution.y;

    vec3 pixelColor = vec3(0.0);

    render(pixelColor, uvScreenCoordinates);

    fs_color = vec4(pixelColor, 1.0);
}
