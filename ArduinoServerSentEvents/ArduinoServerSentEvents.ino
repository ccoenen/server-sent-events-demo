/*
 Server-Sent Events / EventSource DEMO
 Claudius Coenen
 based on Web Server example by David A. Mellis and Tom Igoe

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog input attached to pins A0 (optional)
 * Digital input attached to pins 5 or 6 (optional)

 This is free software. Use, modify and tinker with it however you like!
 LICENSED UNDER CC-BY-4.0 http://creativecommons.org/licenses/by/4.0/
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 42);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    skipRequest(client);
    serverSentEventHeader(client);
    while (client.connected()) {
      serverSentEvent(client);
      delay(16); // round about 60 messages per second
    }

    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void skipRequest(EthernetClient client) {
  // an http request ends with a blank line
  boolean currentLineIsBlank = true;
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.write(c);
      // if you've gotten to the end of the line (received a newline
      // character) and the line is blank, the http request has ended,
      // so you can send a reply
      if (c == '\n' && currentLineIsBlank) {
        return;
      }
      if (c == '\n') {
        // you're starting a new line
        currentLineIsBlank = true;
      }
      else if (c != '\r') {
        // you've gotten a character on the current line
        currentLineIsBlank = false;
      }
    }
  }
}

void serverSentEventHeader(EthernetClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/event-stream;charset=UTF-8");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Access-Control-Allow-Origin: *");  // allow any connection. We don't want Arduino to host all of the website ;-)
  client.println("Cache-Control: no-cache");  // refresh the page automatically every 5 sec
  client.println();
  client.flush();
}

void serverSentEvent(EthernetClient client) {
  client.println("event: arduino"); // this name could be anything, really.
  client.print("data: {");
  client.print("\"A0\": ");
  client.print(1.0 * analogRead(0) / 1024.0);
  client.print(", \"in5\": ");
  client.print(digitalRead(5));
  client.print(", \"in6\": ");
  client.print(digitalRead(6));
  client.println("}");
  client.println();
  client.flush();
}

