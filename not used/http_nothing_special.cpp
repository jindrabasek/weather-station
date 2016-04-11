

	/*// if there's a successful connection
					if (client.connect("arduino.cc", 80)) {
						Serial.println("Connecting...");

						// send the HTTP PUT request
						client.println(F("GET /asciilogo.txt HTTP/1.1"));
						client.println(F("Host: arduino.cc"));
						client.println(F("Connection: close"));
						client.println();
					} else {
						// if you couldn't make a connection
						Serial.println(F("Connection failed"));
					}

					delay(50);

					while (client.available()) {
						char c = client.read();
						Serial.write(c);
					}*/

