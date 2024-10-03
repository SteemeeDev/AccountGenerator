#include "Application.h"

int main(){
    App::AppSpecifications specs{
        "Hello ImGui & OpenGL",
        1600,
        900,
    };

    auto app = App::Application(specs);
    app.Loop();
}
