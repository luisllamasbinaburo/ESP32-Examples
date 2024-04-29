WebServer server(80);

#include "ESP32_Utils_Server.hpp"

void handleNotFound() {
	server.send(404, "text/plain", "Not found");
}

void InitServer()
{
   server.onNotFound([]() {                    // If the client requests any URI
      if (!HandleFileReadGzip(server.uri()))   // send it if it exists
         handleNotFound();  				   // otherwise, respond with a 404 (Not Found) error
   });
  
   server.begin();
   Serial.println("HTTP server started");
}
