//
// Created by MrFlyingChip on 14.07.2024.
//

#ifndef LIGHTRAYENGINE_MENUTOOLBAR_H
#define LIGHTRAYENGINE_MENUTOOLBAR_H

#include <functional>
#include <map>
#include <queue>
#include <string>
#include <vector>

namespace LightRayEngine {
    class MenuToolbar {
    public:
        void Initialize();

        void ShowToolbar() const;

    private:
        struct MenuItemData {
            std::string label;
            std::vector<MenuItemData> childDataList;
            std::function<void()> callback;
        };

        struct TempMenuItemData {
            std::map<std::string, TempMenuItemData> childDataMap;
            std::function<void()> callback;

            MenuItemData Convert(const std::string &label) const {
                MenuItemData itemData;
                itemData.label = label;
                itemData.callback = callback;
                for (const auto &children: childDataMap) {
                    itemData.childDataList.push_back(children.second.Convert(children.first));
                }

                return itemData;
            }
        };

        static std::map<std::string, TempMenuItemData> ConstructMenuItems();

        void CopyItemMap(const std::map<std::string, TempMenuItemData> &itemMap);

        static std::queue<std::string> GetItemPath(const std::string &fullPath);

        static void ShowMenuItem(const MenuItemData &menuItemData);

        std::vector<MenuItemData> m_rootItemDataList;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_MENUTOOLBAR_H
