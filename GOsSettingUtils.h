#ifndef GOsSettingUtils_h
#define GOsSettingUtils_h

#include <Arduino.h>
#include <LittleFS.h>
#include <iot_debug.h>
#include <ArduinoJson.h>
#include <map>
#include <vector>

class GOsSettingUtils {
public:
  GOsSettingUtils();

  bool begin();
  void createSettingList();

  // Add a new tab with parameters
  void addTab(const char* tabName);

  // Add a parameter to the current tab
  void addParam(const char* paramName, const char* paramType);

  // Function to get the value of a parameter by its name
  String getParamValue(const char* paramName);

  // Function to set the value of a parameter by its name
  void setParamValue(const char* paramName, const char* paramValue);

  // Function to select the current tab
  void selectTab(const char* tabName);

  // Function to get a list of all tab names
  std::vector<String> getAllTabs();

private:
  bool initialized;

  // Private variables and functions for internal use
  struct Parameter {
    String type;
    String value;
  };

  std::map<String, std::map<String, Parameter>> tabs;
  String currentTab;
};

#endif
