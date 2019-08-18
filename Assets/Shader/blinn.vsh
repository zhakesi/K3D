#version 300 es
precision mediump float;

layout(location = 0) in vec3 a_vertex;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoord;
uniform mat4 mvp_mat;
uniform mat4 model_mat;
uniform mat4 normal_mat;
out vec3 v_vertex;
out vec3 v_normal;
out vec2 v_texcoord;

void main( void )
{
    v_vertex = vec3(model_mat * vec4(a_vertex, 1.0));
    v_normal = (normal_mat * vec4(a_normal, 1.0)).xyz;
    v_texcoord = a_texcoord;

    gl_Position = mvp_mat * vec4(a_vertex, 1.0);
}