#shader vertex
#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
uniform float u_scale;
out vec2 texCoord;

void main() { 
    gl_Position = vec4(pos.x + pos.x * u_scale, pos.y + pos.y * u_scale, pos.z + pos.z * u_scale, 1.0);
    color = aColor;
    texCoord = aTex;

}

#shader fragment
#version 330 core

out vec4 fragColor;
in vec2 texCoord;
in vec3 color;

uniform sampler2D tex0;

void main() { 
    fragColor= texture(tex0, texCoord);
}