#include "GOsSettingUtils.h"

GOsSettingUtils::GOsSettingUtils() : initialized(false) {
    currentTab = "";
}

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

void GOsSettingUtils::addTab(const char* tabName) {
  currentTab = tabName;
  tabs[currentTab] = std::map<String, Parameter>();
}

void GOsSettingUtils::addParam(const char* paramName, const char* paramType) {
  if (currentTab == "") {
    DEBUG_MSG("Error: No active tab. Please call addTab() first.");
    return;
  }

  tabs[currentTab][paramName] = {paramType, ""};
}

String GOsSettingUtils::getParamValue(const char* paramName) {
  if (currentTab == "") {
    DEBUG_MSG("Error: No active tab. Please call addTab() first.");
    return "";
  }

  if (tabs[currentTab].count(paramName) > 0) {
    return tabs[currentTab][paramName].value;
  } else {
    DEBUG_MSG("Error: Parameter not found in the current tab.");
    return "";
  }
}

void GOsSettingUtils::setParamValue(const char* paramName, const char* paramValue) {
  if (currentTab == "") {
    DEBUG_MSG("Error: No active tab. Please call addTab() first.");
    return;
  }

  if (tabs[currentTab].count(paramName) > 0) {
    tabs[currentTab][paramName].value = paramValue;
  } else {
    DEBUG_MSG("Error: Parameter not found in the current tab.");
  }
}

void GOsSettingUtils::selectTab(const char* tabName) {
  if (tabs.count(tabName) > 0) {
    currentTab = tabName;
  } else {
    DEBUG_MSG("Error: Tab not found.");
  }
}

std::vector<String> GOsSettingUtils::getAllTabs() {
  std::vector<String> tabNames;
  for (const auto& tab : tabs) {
    tabNames.push_back(tab.first);
  }
  return tabNames;
}