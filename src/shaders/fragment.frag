#version 330 core

// Input
in vec3 inNormal;
in vec3 inFragPos;

// Output
out vec4 FragColor;

// Constants
float lightColorComp = 0.7f;
vec3 lightColor = vec3(lightColorComp, lightColorComp, lightColorComp);
vec3 lightPos = vec3(-100.0f, 50.0f, 100.0f);
vec3 color = vec3(1.0f, 0.5f, 0.31f);

void main()
{
    // Ambient
	float ambientStrength = 0.5f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 normal = normalize(inNormal);
    vec3 lightDir = normalize(lightPos - inFragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor; 

    // Final color
	vec3 result = (ambient + diffuse) * color;
	FragColor = vec4(result, 1.0);
}
