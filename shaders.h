#ifndef SHADERS_H
#define SHADERS_H

#define VERT_SH "varying vec3 worldPos;"\
"varying vec3 worldNormal;"\
"void main()"\
"{"\
"gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;"\
"worldPos = gl_Position.xyz/gl_Position.w;"\
"worldNormal = gl_NormalMatrix * gl_Normal;"\
"gl_FrontColor  = gl_Color;"\
"gl_TexCoord[0] = gl_MultiTexCoord0;"\
"}";

#define FRAG_SH "varying vec3 worldPos;"\
"varying vec3 worldNormal;"\
"uniform sampler2D texture1;"\
"void main()"\
"{"\
"if(gl_Color.rgb == vec3(1,1,1) ) {"\
"vec3 lightPos = vec3(0,0,0);"\
"vec3 toLight = normalize(worldPos - lightPos);"\
"float L = max(0,dot(normalize(worldNormal),toLight));"\
"L = min(1,L+0.2);"\
"gl_FragColor = texture2D(texture1,gl_TexCoord[0].xy)*L;"\
"}"\
"else {"\
"if(length(gl_Color.rgb) >= length(vec3(0.9,0.9,0)) ) {"\
"float fade = 1.0 - length(gl_TexCoord[0].xy);"\
"gl_FragColor.rgb = vec3(0.0, 0.7, 0.9 ) * fade;"\
"float sine = ((atan(gl_TexCoord[0].x,gl_TexCoord[0].y) / 3.14 + 1.0) / 2.0) * 360.0;"\
"int sinei = int(sine);"\
"if(sinei % 40 <= 20) {"\
"gl_FragColor.rgb *= 0.8;"\
"}"\
"else {"\
"gl_FragColor.rgb *= 0.9;"\
"}"\
"}"\
"else {"\
"gl_FragColor = gl_Color;"\
"}"\
"}"\
"int darken = (int(gl_FragCoord.y)) % 4;"\
"if( darken >= 2 ) {"\
"gl_FragColor *= 0.95;"\
"}"\
"}";

#endif // SHADERS_H
