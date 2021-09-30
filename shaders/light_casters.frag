#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shinness;
};

struct Light {
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


in vec2 oCoord;
in vec3 oNormal;
in vec3 FragPos;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;


out vec4 fragColor;

void main()
{
    vec3 normal = normalize(oNormal);
    vec3 lightDir = normalize(light.position - FragPos);
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse,oCoord).rgb;


    // diffuse 漫反射
    float diff = max(dot(lightDir,normal),0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,oCoord).rgb;

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shinness);
    vec3 specular = light.specular * spec * texture(material.specular,oCoord).rgb;

    //spotlight soft edge
    float theta = dot(lightDir,normalize(-light.direction));
    float episilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff)/episilon,0.0,1.0);

    diffuse *= intensity;
    specular *= intensity;
    //attenuation 衰减
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant +light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *=  attenuation;

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result,1.0);

    // ambient
//      vec3 ambient = light.ambient * texture(material.diffuse, oCoord).rgb;

//      // diffuse
//      vec3 norm = normalize(oNormal);
//      vec3 lightDir = normalize(light.position - FragPos);
//      float diff = max(dot(norm, lightDir), 0.0);
//      vec3 diffuse = light.diffuse * diff * texture(material.diffuse, oCoord).rgb;

//      // specular
//      vec3 viewDir = normalize(viewPos - FragPos);
//      vec3 reflectDir = reflect(-lightDir, norm);
//      float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shinness);
//      vec3 specular = light.specular * spec * texture(material.specular, oCoord).rgb;

//      // spotlight (soft edges)
//      float theta = dot(lightDir, normalize(-light.direction));
//      float epsilon = (light.cutOff - light.outerCutOff);
//      float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
//      diffuse  *= intensity;
//      specular *= intensity;

//      // attenuation
//      float distance    = length(light.position - FragPos);
//      float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//      ambient  *= attenuation;
//      diffuse   *= attenuation;
//      specular *= attenuation;

//      vec3 result = ambient + diffuse + specular;
//      fragColor = vec4(result, 1.0);
}
