#version 330 core

out vec4 colorOut;
uniform float time;
uniform float zoom;

void main()
{
    float red = sin(time + gl_FragCoord.x * zoom) * 0.5 + 0.5;
    float green = sin(time + gl_FragCoord.y * zoom) * 0.5 + 0.5;
    float blue = sin(time + gl_FragCoord.x * zoom + gl_FragCoord.y * zoom) * 0.5 + 0.5;

    colorOut = vec4(red, green, blue, 1.0);
}
