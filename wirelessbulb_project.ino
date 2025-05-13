#include <WiFiS3.h>   // Library for Arduino UNO R4 WiFi

// Replace with your WiFi network details
const char* ssid = "WIFI_NAME";      
const char* password = "WIFI_PASSWORD";  

WiFiServer server(80);  // Create server on port 80 (HTTP)

const int relayPin = 2;  // Relay control pin (you can change if needed)

void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Relay OFF by default

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP()); // Show IP address

  server.begin(); // Start server
}

void loop() {
  WiFiClient client = server.available(); // Listen for clients

  if (client) {
    Serial.println("New Client Connected");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    if (request.indexOf("/ON") != -1) {
      digitalWrite(relayPin, HIGH); // Turn ON bulb
    }
    if (request.indexOf("/OFF") != -1) {
      digitalWrite(relayPin, LOW); // Turn OFF bulb
    }

    // Build simple HTML page
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1>SriTu Hobby IOT system</h1>");
    client.println("<a href=\"/ON\"><button style=\"height:100px;width:200px;font-size:30px;\">ON</button></a>");
    client.println("<a href=\"/OFF\"><button style=\"height:100px;width:200px;font-size:30px;\">OFF</button></a>");
    client.println("</html>");

    delay(1);
    Serial.println("Client disconnected");
  }
}
