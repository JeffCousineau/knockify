#include <ESP8266WiFi.h>

// PushingBox scenario DeviceId code and API
String deviceId = "";
const char* logServer = "api.pushingbox.com";

const char* ssid = "";
const char* password = "";

int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;

const int ledPin = LED_BUILTIN;      // LED connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 50;  // threshold value to decide when the detected sound is a knock or not

void setup() {
  Serial.begin(74880);
  // Sending a notification to your mobile phone
  // function takes the message as a parameter
  sendNotification("Front door knocking sensor intialized");
}

void sendNotification(String message){

  Serial.println("- connecting to Home Router SSID: " + String(ssid));
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("- succesfully connected");
  Serial.println("- starting client");
  
  WiFiClient client;

  Serial.println("- connecting to pushing server: " + String(logServer));
  if (client.connect(logServer, 80)) {
    Serial.println("- succesfully connected");
    
    String postStr = "devid=";
    postStr += String(deviceId);
    postStr += "&message_parameter=";
    postStr += String(message);
    postStr += "\r\n\r\n";
    
    Serial.println("- sending data...");
    
    client.print("POST /pushingbox HTTP/1.1\n");
    client.print("Host: api.pushingbox.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("- stopping the client");
}

void loop() {
    // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);
  Serial.println(sensorReading);
  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // toggle the status of the ledPin:
    ledState = !ledState;
    // update the LED pin itself:
    digitalWrite(ledPin, ledState);
    // send the string "Knock!" back to the computer, followed by newline
    sendNotification("Someone is knocking !");
    Serial.println("Knock!");
    delay(2000);
  }
  delay(100);  // delay to avoid overloading the serial port buffer
  
  
}
