#include "EditorWindowLayoutData.h"

#include "EditorWindow.h"

namespace LightRayEngine {
    EditorWindowLayoutData::EditorWindowLayoutData(const EditorWindow *editorWindow) {
        className = typeid(*editorWindow).name();
        width = editorWindow->width;
        title = editorWindow->title;
        height = editorWindow->height;
        positionX = editorWindow->positionX;
        positionY = editorWindow->positionY;
        isDocked = editorWindow->isDocked;
        dockId = editorWindow->dockId;
        isFocused = editorWindow->isFocused;
    }

    void EditorWindowLayoutData::SetupEditorWindow(EditorWindow *editorWindow) const {
        editorWindow->width = width;
        editorWindow->height = height;
        editorWindow->positionX = positionX;
        editorWindow->positionY = positionY;
        editorWindow->isDocked = isDocked;
        editorWindow->dockId = dockId;
        editorWindow->isFocused = isFocused;
    }

    void EditorWindowLayoutData::FromJson(JsonLibrary::JsonObject &jsonObject) {
        className = static_cast<std::string>(jsonObject["className"]);
        title = static_cast<std::string>(jsonObject["title"]);
        width = jsonObject["width"];
        height = jsonObject["height"];
        positionX = jsonObject["positionX"];
        positionY = jsonObject["positionY"];
        isDocked = jsonObject["isDocked"];
        dockId = jsonObject["dockId"];
        isFocused = jsonObject["isFocused"];
    }

    void EditorWindowLayoutData::ToJson(JsonLibrary::JsonObject &jsonObject) const {
        jsonObject["className"] = className;
        jsonObject["title"] = title;
        jsonObject["width"] = width;
        jsonObject["height"] = height;
        jsonObject["positionX"] = positionX;
        jsonObject["positionY"] = positionY;
        jsonObject["isDocked"] = isDocked;
        jsonObject["dockId"] = dockId;
        jsonObject["isFocused"] = isFocused;
    }
}
