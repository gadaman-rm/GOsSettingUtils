#include "GOsSettingUtils.h"

GOsSettingUtils::GOsSettingUtils() : initialized(false) {}

bool GOsSettingUtils::begin() {
  if (initialized) {
    return true;
  }

  if (!LittleFS.begin()) {
    DEBUG_MSG("Failed to mount LittleFS!");
    return false;
  }

  initialized = true;
  return true;
}

void GOsSettingUtils::createSettingList() {
  if (!initialized) {
    DEBUG_MSG("LittleFS not initialized. Call begin() first!");
    return;
  }

  File settingListFile = LittleFS.open("/settingList.lst", "w");
  if (!settingListFile) {
    DEBUG_MSG("Failed to create settingList.lst file!");
    return;
  }

  Dir dir = LittleFS.openDir("/");
  while (dir.next()) {
    settingListFile.println(dir.fileName());
  }

  settingListFile.close();
  DEBUG_MSG("File list created successfully!");
}
