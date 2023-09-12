// adapted from https://www.shadertoy.com/view/tllSWj

#version 330 core

uniform vec2 resolution;
uniform vec2 center;
uniform float zoom;
uniform int max_iterations;
uniform int samples;

out vec4 fragColor;

vec2 complexMult(vec2 a, vec2 b) {
	return vec2(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);
}

float testMandelbrot(vec2 coord) {
	vec2 testPoint = vec2(0,0);
	for (int i = 0; i < max_iterations; i++){
		testPoint = complexMult(testPoint,testPoint) + coord;
        float ndot = dot(testPoint,testPoint);
		if (ndot > 7.0) {
            float sl = float(i) - log2(log2(ndot))+4.0;
			return sl*.0025;
		}
	}
	return 0.0;
}

vec4 mapColor(float mcol) {
    return vec4(0.5 + 0.5*cos(2.7+mcol*30.0 + vec3(0.0,.6,1.0)),1.0);
}

const float offsetsD = .5;
const float offsetsD2 = .25;
const float offsetsD3 = .125;
const float offsetsD4 = .075;
const vec2 offsets[16] = vec2[](
    vec2(-offsetsD,-offsetsD),
    vec2(offsetsD,offsetsD),
    vec2(-offsetsD,offsetsD),
    vec2(offsetsD,-offsetsD),
    vec2(-offsetsD2,-offsetsD2),
    vec2(offsetsD2,offsetsD2),
    vec2(-offsetsD2,offsetsD2),
    vec2(offsetsD2,-offsetsD2),
    vec2(-offsetsD3,-offsetsD3),
    vec2(offsetsD3,offsetsD3),
    vec2(-offsetsD3,offsetsD3),
    vec2(offsetsD3,-offsetsD3),
    vec2(-offsetsD4,-offsetsD4),
    vec2(offsetsD4,offsetsD4),
    vec2(-offsetsD4,offsetsD4),
    vec2(offsetsD4,-offsetsD4)
);

void main( ) {
    const vec2 zoomP = vec2(-.7451544,.1853);
    float zoomTime = 70.0;
    float tTime = 9.0 + abs(mod(zoom + zoomTime,zoomTime* 2.0)-zoomTime);
    tTime = (145.5/(.0005*pow(tTime,5.0)));
    vec2 aspect = vec2(1,resolution.y/resolution.x);
    
    vec2 mouse = center.xy/resolution.x;

    vec4 outs = vec4(0.0);
    
    for(int i = 0; i < samples; i++) {        
        vec2 fragment = (gl_FragCoord.xy+offsets[i])/resolution.x;    
        vec2 uv = (zoomP + tTime * (fragment-mouse));
        outs += mapColor(testMandelbrot(uv));
    }
	fragColor = outs/float(samples);
}