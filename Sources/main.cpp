#include <memory>
#include "LightRayCore/Application.h"

int main() {
    auto app = std::make_unique<LightRayEngine::Application>();
    if(app->Open())
    {
        app->Run();
    }

    return 0;
}
