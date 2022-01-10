#version 330 core

in vec3 fNormal;
in vec2 fTexcoord;
in vec3 fPos;

out vec4 FragColor;

uniform sampler2D texture1;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material mat;

struct Light{
   vec3 dir; // from light
   vec3 color;
};
uniform Light light;

uniform vec3 viewPos;

void main()
{
   float gamma = 2.2;
   vec3 norm = normalize(fNormal);
   vec3 lVec = normalize(light.dir);

   vec3 ambient = mat.ambient;

   float diff = max(dot(norm,-lVec),0.0);
   vec3 diffuse = diff * light.color * mat.diffuse * texture(texture1, fTexcoord).xyz;

   //vec3 reflectVec = reflect(lVec,norm);
   vec3 viewVec    = normalize(viewPos - fPos);
   vec3 halfwayVec = normalize(viewVec - lVec);
   vec3 specular = pow(max(dot(norm,halfwayVec),0.0),mat.shininess)
                     * light.color * mat.specular;
   //specular = pow(specular,vec3(1.0/gamma));


   FragColor = vec4((ambient + diffuse + specular),1.0);
   //FragColor.rgb = pow(FragColor.rgb,vec3(1.0/gamma));
}