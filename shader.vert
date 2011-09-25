// simple vertex shader

varying vec3 worldPos;
varying vec3 worldNormal;

void main()
{
	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
	worldPos = gl_Position.xyz/gl_Position.w;
	worldNormal = gl_NormalMatrix * gl_Normal;
	gl_FrontColor  = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}

