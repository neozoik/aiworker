#include <ESP8266WiFi.h>          

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <CertStoreBearSSL.h>
BearSSL::CertStore certStore;

#define GHOTA_USER "neozoik"
#define GHOTA_REPO "aiworker"
#define GHOTA_CURRENT_TAG "0.0.1"
#define GHOTA_BIN_FILE "aiworker.ino.nodemcu.bin"
#define GHOTA_ACCEPT_PRERELEASE 0

#include <ESP_OTA_GitHub.h>

ESPOTAGitHub ESPOTAGitHub(&certStore, GHOTA_USER, GHOTA_REPO, GHOTA_CURRENT_TAG, GHOTA_BIN_FILE, GHOTA_ACCEPT_PRERELEASE);

void setup() {

    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(10000);
  
    SPIFFS.begin();
    int numCerts = certStore.initCertStore(SPIFFS, PSTR("/certs.idx"), PSTR("/certs.ar"));
    Serial.print(F("Number of CA certs read: "));
    Serial.println(numCerts);
    if (numCerts == 0) {
      Serial.println(F("No certs found. Did you run certs-from-mozill.py and upload the SPIFFS directory before running?"));
      return; 
    }

    digitalWrite(LED_BUILTIN, LOW);    
    delay(1000);                       
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(1000);                       

    WiFiManager wifiManager;
    wifiManager.autoConnect();

    Serial.println("Checking for update...");
    if (ESPOTAGitHub.checkUpgrade()) {
      Serial.print("Upgrade found at: ");
      Serial.println(ESPOTAGitHub.getUpgradeURL());
    if (ESPOTAGitHub.doUpgrade()) {
      Serial.println("Upgrade complete."); 
    } else {
      Serial.print("Unable to upgrade: ");
      Serial.println(ESPOTAGitHub.getLastError());
    }
    } else {
      Serial.print("Not proceeding to upgrade: ");
      Serial.println(ESPOTAGitHub.getLastError());
    }

}

void loop() {

    digitalWrite(LED_BUILTIN, HIGH);   
    delay(1000);      
                                       
        
}
