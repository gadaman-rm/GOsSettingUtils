#ifndef GOsSettingUtils_h
#define GOsSettingUtils_h

#include <Arduino.h>
#include <LittleFS.h>
#include <iot_debug.h>
#include <ArduinoJson.h>

class GOsSettingUtils {
public:
  GOsSettingUtils();

  bool begin();
  void createSettingList();

private:
  bool initialized;
};

#endif
