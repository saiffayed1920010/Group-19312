#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;
WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char* myWriteAPIKey = SECRET_WRITE_APIKEY;
float number1 = 0;
float number2 = 0;
String myStatus = "";
const int analogInPin = 39;
int sensorValue = 0;



#include "HX711.h"
#define calibration_factor -229000
// 229000 for kg  zero_factor 276088
// 226 for gram
#define zero_factor 276088
#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 4
HX711 scale;



const int Ph_analog = 34;
float ph;
float Value = 0;



void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);




  Serial.println("Demo of zeroing out a scale from a known value");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.set_offset(zero_factor);
  Serial.println("Readings:");
  pinMode(Ph_analog, INPUT);
}




void loop() {


  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("\nConnected.");
  }


  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
  ThingSpeak.setStatus(myStatus);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(5000);



  Value = analogRead(Ph_analog);
  Serial.print(Value);
  Serial.print(" | ");
  float voltage = Value * (3.3 / 4095.0);
  ph = (3.3 * voltage);
  Serial.print("ph Val = ");
  Serial.println(ph);
  number1 = ph;



  Serial.print("Reading: weight = ");
  Serial.print(scale.get_units() * -1, 1);
  Serial.print(" kg");
  Serial.println();
  number2 = scale.get_units() * -1;
  Serial.print("\n");
  delay(1000);



  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
}
