#include <memory>
#include "Core/EditorApplication.h"

int main() {
    auto app = std::make_unique<LightRayEngine::EditorApplication>();
    if(app->Open())
    {
        app->Run();
    }

    return 0;
}
