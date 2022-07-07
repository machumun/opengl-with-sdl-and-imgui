#include "asset_manager.hpp"

using hid::AssetManager;

void AssetManager::loadStandardStaticMeshes()
{
    loadStaticMeshes({{"ui_plane", "assets/models/ui_plane.obj"},
                      {"plane", "assets/models/plane.obj"},
                      {"crate", "assets/models/crate.obj"}});
}
