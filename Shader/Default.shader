#shader vertex
#version 330 core
layout (location = 0) in vec3 pos;
//layout (location = 1) in vec3 aColor;

uniform float u_scale;

void main() { 
    gl_Position = vec4(pos.x + pos.x * u_scale, pos.y + pos.y * u_scale, pos.z + pos.z * u_scale, 1.0);
}

#shader fragment
#version 330 core

out vec4 fragColor;
uniform vec4 u_color;


void main() { 
    fragColor= u_color;
}