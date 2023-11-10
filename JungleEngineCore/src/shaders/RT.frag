#version 330 core
out vec4 FragColor;

in vec3 aPos1;
in vec3 aPos2;
in vec3 aPos3;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 BGCol;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Ray{
    vec3 Orig;
    vec3 Dir;
    vec4 Col;
};

bool isOnLight(vec3 point, vec3 lPos){
    if((point.x<1.0f && point.x>-1.0f) && point.y == 1.0f && (point.z<1.0f && point.z>-1.0f) ){
        return true;
    }
}


void main() {
    vec4 TexColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);
    vec3 norm = normalize(Normal);
    vec3 lnorm = normalize(lightPos);
    Ray ray;
    ray.Orig = viewPos;
    ray.Dir = FragPos;
    ray.Col = vec4(lightColor, 1.0f);
    for (int i = 0; i < 1; i++) {
        ray.Orig = ray.Dir;
        ray.Dir = normalize(2 * dot(norm, ray.Dir) * (norm - ray.Dir));



    }

    FragColor = ray.Col;
}