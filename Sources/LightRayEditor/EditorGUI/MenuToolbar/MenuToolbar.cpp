//
// Created by MrFlyingChip on 14.07.2024.
//

#include "MenuToolbar.h"
#include "MenuItems.h"

#include <sstream>
#include <imgui.h>

namespace LightRayEngine {
    void MenuToolbar::Initialize() {
        auto itemMap = ConstructMenuItems();
        CopyItemMap(itemMap);
    }

    void MenuToolbar::ShowToolbar() const {
        if (ImGui::BeginMainMenuBar()) {
            for (const auto &rootItem: m_rootItemDataList) {
                ShowMenuItem(rootItem);
            }

            ImGui::EndMainMenuBar();
        }
    }

    std::map<std::string, MenuToolbar::TempMenuItemData> MenuToolbar::ConstructMenuItems() {
        std::map<std::string, TempMenuItemData> rootItemDataMap;

        for (const auto &menuItem: menuItems) {
            auto menuItemPathList = GetItemPath(menuItem.path);
            std::map<std::string, TempMenuItemData> *currentMap = &rootItemDataMap;
            while (!menuItemPathList.empty()) {
                std::string currentPathPart = menuItemPathList.front();
                menuItemPathList.pop();
                if (currentMap->find(currentPathPart) == currentMap->cend()) {
                    currentMap->insert({currentPathPart, TempMenuItemData()});
                }
                TempMenuItemData *tempDataItem = &currentMap->at(currentPathPart);
                currentMap = &tempDataItem->childDataMap;
                if (menuItemPathList.empty()) {
                    tempDataItem->callback = menuItem.callback;
                }
            }
        }

        return rootItemDataMap;
    }

    void MenuToolbar::CopyItemMap(const std::map<std::string, TempMenuItemData> &itemMap) {
        for (const auto &item: itemMap) {
            m_rootItemDataList.push_back(item.second.Convert(item.first));
        }
    }

    std::queue<std::string> MenuToolbar::GetItemPath(const std::string &fullPath) {
        std::queue<std::string> result;
        std::stringstream ss(fullPath);

        while (ss.good()) {
            std::string substr;
            getline(ss, substr, '/');
            result.push(substr);
        }

        return result;
    }

    void MenuToolbar::ShowMenuItem(const MenuItemData &menuItemData) {
        auto label = menuItemData.label.c_str();
        if (menuItemData.childDataList.empty()) {
            if (ImGui::MenuItem(label) && menuItemData.callback) {
                menuItemData.callback();
            }
        } else {
            if (ImGui::BeginMenu(label)) {
                for (const auto &childData: menuItemData.childDataList) {
                    ShowMenuItem(childData);
                }
                ImGui::EndMenu();
            }
        }
    }

} // LightRayEngine