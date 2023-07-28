#include "GOsSettingUtils.h"

GOsSettingUtils::GOsSettingUtils() : initialized(false)
{
  currentTab = "";
}

bool GOsSettingUtils::begin()
{
  if (initialized)
  {
    return true;
  }

  if (!LittleFS.begin())
  {
    DEBUG_MSG("Failed to mount LittleFS!");
    return false;
  }

  initialized = true;
  return true;
}

void GOsSettingUtils::addTab(const char *tabName)
{
  currentTab = tabName;
  tabs[currentTab] = std::map<String, Parameter>();
}

void GOsSettingUtils::addParam(const char *paramName, const char *paramType)
{
  if (currentTab == "")
  {
    DEBUG_MSG("Error: No active tab. Please call addTab() first.");
    return;
  }

  tabs[currentTab][paramName] = {paramType, ""};
}

String GOsSettingUtils::getParamType(const char *paramName)
{
  if (currentTab == "")
  {
    DEBUG_MSG("Error: No active tab. Please call addTab() first.");
    return "";
  }

  if (tabs[currentTab].count(paramName) > 0)
  {
    return tabs[currentTab][paramName].type;
  }
  else
  {
    DEBUG_MSG("Error: Parameter not found in the current tab.");
    return "";
  }
}

String GOsSettingUtils::getParamValue(const char *paramName)
{
  if (currentTab == "")
  {
    DEBUG_MSG("Error: No active tab. Please call addTab() first.");
    return "";
  }

  if (tabs[currentTab].count(paramName) > 0)
  {
    return tabs[currentTab][paramName].value;
  }
  else
  {
    DEBUG_MSG("Error: Parameter not found in the current tab.");
    return "";
  }
}

void GOsSettingUtils::setParamValue(const char *paramName, const char *paramValue)
{
  if (currentTab == "")
  {
    DEBUG_MSG("Error: No active tab. Please call addTab() first.");
    return;
  }

  if (tabs[currentTab].count(paramName) > 0)
  {
    tabs[currentTab][paramName].value = paramValue;
  }
  else
  {
    DEBUG_MSG("Error: Parameter not found in the current tab.");
  }
}

void GOsSettingUtils::selectTab(const char *tabName)
{
  if (tabs.count(tabName) > 0)
  {
    currentTab = tabName;
  }
  else
  {
    DEBUG_MSG("Error: Tab not found.");
  }
}

std::vector<String> GOsSettingUtils::getAllTabNames()
{
  std::vector<String> tabNames;
  for (const auto &tab : tabs)
  {
    tabNames.push_back(tab.first);
  }
  return tabNames;
}

std::vector<String> GOsSettingUtils::getAllParamsInTab(const char *tabName)
{
  std::vector<String> paramNames;
  if (tabs.count(tabName) > 0)
  {
    for (const auto &param : tabs[tabName])
    {
      paramNames.push_back(param.first);
    }
  }
  return paramNames;
}

bool GOsSettingUtils::writeToJsonFile()
{
  if (!initialized)
  {
    DEBUG_MSG("LittleFS not initialized. Call begin() first!");
    return false;
  }

  DynamicJsonDocument jsonDocument(2048); // Set the size of the JSON document

  // Iterate through all the tabs
  for (const auto &tab : tabs)
  {
    JsonArray paramArray = jsonDocument.createNestedArray(tab.first);
    for (const auto &param : tab.second)
    {
      JsonObject paramObject = paramArray.createNestedObject();
      paramObject["name"] = param.first;
      paramObject["type"] = param.second.type;
      paramObject["value"] = param.second.value;
    }
  }
  File settingListFile = LittleFS.open("/settingList.lst", "w");
  if (!settingListFile)
  {
    DEBUG_MSG("Failed to create settingList.lst file!");
    return false;
  }
  serializeJson(jsonDocument, settingListFile);
  settingListFile.close();
  DEBUG_MSG("JSON data written to settingList.lst successfully!");

  return true;
}