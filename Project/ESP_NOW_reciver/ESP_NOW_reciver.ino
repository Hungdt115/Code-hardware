#include <ESP8266WiFi.h>
#include <espnow.h>

const char *ssid = "RDElex";
const char *pass = "77namhai88";

#define LED 2


String path = "/";
int t1;
bool data;
#define  FIREBASE_HOST  "smart-controler-default-rtdb.firebaseio.com/"
#define  FIREBASE_AUTH "d4FMonKbHYlHi97OBpeqW6d5gvHSjEXhMDPCZi0K"

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  char a[32];
  int temp, humi, f, g, h, k;

  float c;
  String d;
  bool e;
  

} struct_message;

// Create a struct_message called myData
struct_message myData;



// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("tempeture: ");
  Serial.println(myData.temp);
  Serial.print("Humidity: ");
  Serial.println(myData.humi);
  Serial.print("String: ");
  Serial.println(myData.d);
  Serial.print("Bool: ");
  Serial.println(myData.e);
  
  int rssi_display = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.println(rssi_display);
  Serial.println();


}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_AP_STA);




  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
  
}

void loop() {


}
