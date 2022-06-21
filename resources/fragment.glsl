#version 330 core

out vec3 fs_color;

in vec4 vs_position;

uniform float time;

bool inSphere(vec2 center, float radius, vec2 point) {
    return sqrt( (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y) ) > radius * radius;
}

const vec3 orangeColor = vec3(1.0, 0.5, 0.25);

void main()
{
    bool isFragmentInCircle = inSphere(vec2(0, 0), 0.8, vs_position.xy);
    if (isFragmentInCircle) {
        fs_color = orangeColor * sin(time);
    } else {
        fs_color = orangeColor * cos(time);
    }
}
