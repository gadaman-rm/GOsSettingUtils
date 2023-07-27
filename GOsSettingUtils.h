#ifndef GOsSettingUtils_h
#define GOsSettingUtils_h

#include <Arduino.h>
#include <LittleFS.h>
#include <iot_debug.h>
#include <map>
#include <vector>

class GOsSettingUtils
{
public:
  GOsSettingUtils();

  bool begin();
  void createSettingList();

  // Add a new tab with parameters
  void addTab(const char *tabName);

  // Add a parameter to the current tab
  void addParam(const char *paramName, const char *paramType);

  // Function to get the value of a parameter by its name
  String getParamValue(const char *paramName);

  // Function to set the value of a parameter by its name
  void setParamValue(const char *paramName, const char *paramValue);

  // Function to select the current tab
  void selectTab(const char *tabName);

  // Function to get all tab names as a vector
  std::vector<String> getAllTabNames();

  // Function to get all parameter names within a tab as a vector
  std::vector<String> getAllParamsInTab(const char *tabName);

private:
  bool initialized;
  struct Parameter
  {
    String type;
    String value;
  };
  // Private variables and functions for internal use
  std::map<String, std::map<String, Parameter>> tabs;
  String currentTab;
};

#endif
