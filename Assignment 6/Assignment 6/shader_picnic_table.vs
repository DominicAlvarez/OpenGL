#version 430 core

layout (location = 0) in vec4 position;
layout (location = 2) in vec3 normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform vec3 Ambient;
uniform vec3 LightColor;
uniform vec4 LightPosition; // in camera or eye coordinate
uniform vec3 MaterialColor;
uniform float Shininess;


out vec4 fColor;

void main(void){

vec4 eyeSpacePosition = view_matrix*model_matrix*position;
 vec3 eyeSpaceNormal = mat3(view_matrix*model_matrix)*normal;


//
 vec3 N = normalize(eyeSpaceNormal);
 vec3 L = normalize(LightPosition.xyz-eyeSpacePosition.xyz);

 vec3 V = normalize(vec3(0,0,0)-eyeSpacePosition.xyz);
 vec3 H = normalize(L+V);
 
 

 vec3 diffuse =  LightColor * (max(dot(L,N), 0.0));

 vec3 specular = LightColor *( pow(max(dot(N, H), 0.0),Shininess));

 
 vec4 totalColor = vec4((Ambient+diffuse)*vec3(MaterialColor) + specular, 1.0);

 fColor = min(totalColor, vec4(1.0));
 //fColor =  vec4(1.0);

  gl_Position = projection_matrix*view_matrix*model_matrix*position;



}
