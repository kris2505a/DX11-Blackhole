#shader vertex
#version 330 core
layout (location = 0) in vec3 pos;
void main() { 
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}

#shader fragment
#version 330 core
out vec4 fragColor;
void main() { 
    fragColor= vec4(0.3f, 0.5f, 0.8f, 1.0f);
}