#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
uniform mat4 model_matrix;

out vec4 color;
void main(){

     gl_Position = model_matrix*vPosition;
     color = vColor;
    
}
