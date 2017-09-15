#include <ESP8266WiFi.h>
 
const char* ssid = "The Wizarding Wireless Network";//type your ssid
const char* password = "Fizzing whizzbies";//type your password

IPAddress ip(10,0,1,128);
IPAddress subnet(255,255,252,0);
IPAddress gateway(10,0,1,1);

 
int bluePin = 2; // GPIO2 of ESP8266
int greenPin = 0; // GPIO0

WiFiServer server(80);//Service Port
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(bluePin, OUTPUT);
  digitalWrite(bluePin, 0);

  pinMode(greenPin, OUTPUT);
  digitalWrite(greenPin, 0);
   
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  // Match the request
  if (request.indexOf("BLUE=ON") != -1) 
  {
    digitalWrite(bluePin, 1);
  } 
  if (request.indexOf("BLUE=OFF") != -1)
  {
    digitalWrite(bluePin, 0);
  }
  if (request.indexOf("GREEN=ON") != -1) 
  {
    digitalWrite(greenPin, 1);
  }
  if (request.indexOf("GREEN=OFF") != -1) 
  {
    digitalWrite(greenPin, 0);
  }
  
  
  //Set ledPin according to the request
  //digitalWrite(ledPin, value);
   
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<br><br>");
  client.println("Click <a href=\"/BLUE=ON\">here</a> turn the blue LED on<br>");
  client.println("Click <a href=\"/BLUE=OFF\">here</a> turn the blue LED off<br>"); 
  client.println("Click <a href=\"/GREEN=ON\">here</a> turn the green LED on<br>");
  client.println("Click <a href=\"/GREEN=OFF\">here</a> turn the green LED off<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

}
