//
// Created by artyr on 26.08.2023.
//

#include "EngineCore.hpp"


int main(){
    JEE::EngineCore engine(800, 600, "test");

    engine.Init();

    GLuint texture1 = engine.generateTex("texture1.jpg");
    GLuint texture2 = engine.generateTex("texture2.png");
    GLuint texture3 = engine.generateTex("texture3.png");

    JEE::Shader Default("../../JungleEngineCore/src/shaders/Default.vert",
                        "../../JungleEngineCore/src/shaders/Default.frag");

    JEE::Shader Lighting("../../JungleEngineCore/src/shaders/Lighting.vert",
                         "../../JungleEngineCore/src/shaders/Lighting.frag");

    JEE::Shader RT("../../JungleEngineCore/src/shaders/RT.vert",
                   "../../JungleEngineCore/src/shaders/RT.frag");

    engine.setShader(Lighting);
    //engine.setBGColor(0.0f, 0.0f, 0.0f, 1.0f);

    unsigned int cubeVAO = 0, cubeVBO = 0,
            planeVAO = 0, planeVBO = 0,
            lightVAO = 0, lightVBO = 0;

    while(!engine.Close())
    {
        engine.PreRender();

        engine.renderPlane(planeVAO, planeVBO, texture3);
        engine.renderCube(cubeVAO, cubeVBO, texture1, 0, -1.0f, 0.5f, 0.0f, 'r');
        engine.renderCube(cubeVAO, cubeVBO, texture2, 0, 1.0f, 0.50001f);
        engine.LightSrc(lightVAO, lightVBO, glm::vec3(0.0f, 4.0f, 0.0f));

        engine.AfterRender();
    }

    engine.Stop();
    return engine.getReturnCode();
}
