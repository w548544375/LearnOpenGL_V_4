#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 oNormal;
in vec3 oFragPos;
in vec2 oCoord;


uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = light.ambient * texture(material.diffuse,oCoord).rgb;

    vec3 nor = normalize(oNormal);
    vec3 lightDir = normalize(light.position - oFragPos);

    float diff = max(dot(nor,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,oCoord).rgb;

    vec3 viewDir = normalize(viewPos - oFragPos);
    vec3 reflectDir = reflect(-lightDir,nor);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular,oCoord).rgb;

    vec3 emission = texture(material.emission,oCoord).rgb;

    FragColor = vec4(ambient + diffuse + specular + emission,1.0);
}
