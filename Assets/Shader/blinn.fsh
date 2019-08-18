#version 300 es
precision mediump float;
in vec3 v_vertex;
in vec3 v_normal;
in vec2 v_texcoord;
uniform vec3 eye;
uniform sampler2D text;
uniform float ambient_k;
uniform float diffuse_k;
uniform float specular_k;
uniform float shininess;
vec3 lightColor = vec3(0.9, 0.8, 0.75);
vec3 lightPos = vec3(-10.0, 30.0, 20.0);
layout(location = 0) out vec4 FragColor;
void main()
{
    vec3 normal = normalize(v_normal);
    vec3 lightDir = normalize(lightPos - v_vertex);
    vec3 viewDir = normalize(eye - v_vertex);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float diffuse = max(dot(normal, lightDir), 0.0);
    diffuse = ambient_k + diffuse_k * diffuse;

    float specular = pow(max(dot(normal, halfwayDir), 0.0), shininess * 32.0);
    specular = specular_k * specular;

    vec3 basecolor = texture(text, v_texcoord).rgb;

    vec3 result = diffuse * basecolor * lightColor + specular * lightColor;

    FragColor = vec4(result, 1.0);
}