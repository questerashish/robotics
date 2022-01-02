#include "ESP8266WiFi.h"
#include "Servo.h"
#include "WiFiClient.h"
//ESP Web Server Library to host a web page
#include "ESP8266WebServer.h"

#define LED 2  
//---------------------------------------------------------------
//Our HTML webpage contents in program memory
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>WiFi LED on off demo: 1</h1><br>
Ciclk to turn <a href="ledOn" target="myIframe">LED ON</a><br>
Ciclk to turn <a href="ledOff" target="myIframe">LED OFF</a><br>
LED State:<iframe name="myIframe" width="100" height="25" frameBorder="0"><br>
<hr>
</center>

</body>
</html>
)=====";
//---------------------------------------------------------------

Servo servo;
// WiFi parameters to be configured
const char* ssid = "AK"; // Write here your router's username
const char* password = "12345678"; // Write here your router's password

ESP8266WebServer server(80);

void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleLEDon() { 
 Serial.println("LED on page");
 //digitalWrite(LED,LOW); //LED is connected in reverse
 servo.write(180);
 delay(1000);
 servo.write(0);
 delay(1000);
 server.send(200, "text/html", "ON"); //Send ADC value only to client ajax request
}

void handleLEDoff() { 
 Serial.println("LED off page");
 //digitalWrite(LED,HIGH); //LED off
 servo.write(0);
 delay(1000);
 server.send(200, "text/html", "OFF"); //Send ADC value only to client ajax request
}





void setup(void)
{ 
  Serial.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/ledOn", handleLEDon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/ledOff", handleLEDoff);

  server.begin();                  //Start server
  Serial.println("HTTP server started");

}
void loop() {
  server.handleClient(); 
}
