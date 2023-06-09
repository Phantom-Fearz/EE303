#include <WiFi.h>
// wifi details
char ssid[] = "NETGEAR63";
char password[] = "littlecello367";
WiFiClient client;
// server details
char server[] = "54.78.246.30";
int port = 8081;
#define BUFSIZE 512

String readResponse() {
char buffer[BUFSIZE];
memset(buffer, 0, BUFSIZE);
client.readBytes(buffer, BUFSIZE);
String response(buffer);
return response;
}
int getStatusCode(String& response) {
String code = response.substring(9, 12);
return code.toInt();
}
String getResponseBody(String& response) {
int split = response.indexOf("\r\n\r\n");
String body = response.substring(split+4, response.length());
body.trim();
return body;
}

bool connect() {
 if (!client.connect(server, port)) {
   Serial.println("error connecting to server");
   return false;
 }
 Serial.println("connected to server");
return true;
}

void connectToWiFi() {
Serial.print("Connecting to network: ");
Serial.print(ssid);
Serial.flush();
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
Serial.flush();
delay(300);
}
Serial.println("Connected");
Serial.print("Obtaining IP address");
Serial.flush();
while (WiFi.localIP() == INADDR_NONE) {
Serial.print(".");
Serial.flush();
delay(300);
}
Serial.println();
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());
}

void randomDestination(){
  client.println("GET /api/random-destination/bcb39484 HTTP/1.1");
  client.println("Host: localhost:8081");
}

void sendPosition(int position){
  String postBody("position=");
postBody += position;
//Serial.println(postBody);
// send post request and headers
connect();
client.println("POST /api/arrived/bcb39484 HTTP/1.1");
client.println("Content-Type: application/x-www-form-urlencoded");
client.print("Content-Length: ");
client.println(postBody.length());
client.println("Connection: close");
client.println();
// send post body
client.println(postBody);
}

void receiveResponse(){
// read response
connect();
String response = readResponse();
// get status code
int statusCode = getStatusCode(response);
if (statusCode == 200) {
// success, read body
String body = getResponseBody(response);
// check if at final destination
if (!body.equals("undefined")) {
destination = body.toInt();
}
}
}
