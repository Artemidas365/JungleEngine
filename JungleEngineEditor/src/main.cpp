//
// Created by artyr on 26.08.2023.
//

#include "EngineCore.hpp"


int main(){
    JEE::EngineCore engine(800, 600, "test");

    engine.Init();

    GLuint texture1 = engine.generateTex("texture1.jpg");
    GLuint texture2 = engine.generateTex("texture2.png");
    engine.drawRect();
    engine.drawRect();

    while(!engine.Close())
    {
        engine.PreRender();
        engine.renderRect(texture1, 0, -1.0f);
        engine.renderRect(texture2, 0, 1.0f);
        engine.AfterRender();
    }

    engine.Stop();
    return engine.getReturnCode();
}
