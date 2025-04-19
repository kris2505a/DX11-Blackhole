#shader vertex
#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

uniform float u_scale;

out vec2 v_texCoord;

void main() { 
    gl_Position = vec4(pos.x + pos.x * u_scale, pos.y + pos.y * u_scale, pos.z + pos.z * u_scale, 1.0);
    v_texCoord = texCoord;
}

#shader fragment
#version 330 core

out vec4 fragColor;
uniform vec4 u_color;
uniform sampler2D u_texture;
in vec2 v_texCoord;

void main() { 
    vec4 texColor = texture(u_texture, v_texCoord);
    fragColor = texColor;
}