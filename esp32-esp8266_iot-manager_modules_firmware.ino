#include "set.h"

void setup() {
  //--------------------------------------------------------------
  File_system_init();
  Serial.println("SPIFFS_init");
  //--------------------------------------------------------------
  CMD_init();
  Serial.println("[V] CMD_init");
  //--------------------------------------------------------------
  All_init();
  Serial.println("[V] All_init");
  //--------------------------------------------------------------
  WIFI_init();
  Serial.println("[V] WIFI_init");
  //--------------------------------------------------------------
  statistics_init();
  Serial.println("[V] statistics_init");
  //--------------------------------------------------------------
  initUpgrade();
  Serial.println("[V] initUpgrade");
  //--------------------------------------------------------------
  Web_server_init();
  Serial.println("[V] Web_server_init");
  //--------------------------------------------------------------
  MQTT_init();
  Serial.println("[V] MQTT_init");
  //--------------------------------------------------------------
  Time_Init();
  Serial.println("[V] Time_Init");
  //--------------------------------------------------------------
  Push_init();
  Serial.println("[V] Push_init");
  //--------------------------------------------------------------
  UDP_init();
  Serial.println("[V] UDP_init");
  //--------------------------------------------------------------



  ts.add(TEST, 5000, [&](void*) {

    getMemoryLoad("[i] periodic check of");
    //String json = "{}";
    //jsonWriteStr(json, "test6", GetTime());
    //ws.textAll(json);

  }, nullptr, true);


  just_load = false;
}


void loop() {

#ifdef OTA_enable
  ArduinoOTA.handle();
#endif

#ifdef WS_enable
  ws.cleanupClients();
#endif

  not_async_actions();

  handleMQTT();
  handleCMD_loop();
  handleButton();
  handleScenario();
  handleUdp();

  ts.update();
}

void not_async_actions() {
  do_mqtt_connection();
  do_upgrade_url();
  do_upgrade();
  do_udp_data_parse();
  do_mqtt_send_settings_to_udp();
}
