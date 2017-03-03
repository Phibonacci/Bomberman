#version 120

uniform vec4 uColor;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec3 fNormal;
varying vec2 fUv;

void main(void)
{
	vec4 c = texture2D(fTexture0, fUv) * fColor;
	if (c[0] == 0 && c[1] == 0 && c[2] == 0)
	   c = uColor;
	if (c[0] == 1 && c[1] == 1 && c[2] == 1)
	   c = vec4(0, 0, 0, 1);
	gl_FragColor = c;
}