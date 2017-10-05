
// #####################################################################
// ################### Main Function File for HC-12 ####################
// #####################################################################

// Setup HC-12 Board
char HC_Setup(int power, int mode, int braud, int channel, int reset) {	// Braudrate , Mode , Channel , Power

	// --> Need to make a better way of selecting <--

	//Set HC-12 in config mode
	digitalWrite(reset, LOW);
	delay(100);
	// Check if ready
	Serial1.write("AT");
	delay(50);
	// Set Power
	switch (power)
	{
	case 0: // if Power 0 (-1dBm) is selected
		Serial1.write("AT+P1");
		break;
	case 1: // if Power 1 (2dBm) is selected
		Serial1.write("AT+P2");
		break;
	case 2: // if Power 2 (5dBm) is selected
		Serial1.write("AT+P3");
		break;
	case 3: // if Power 3 (8dBm) is selected
		Serial1.write("AT+P4");
		break;
	case 4: // if Power 4 (11dBm) is selected
		Serial1.write("AT+P5");
		break;
	case 5: // if Power 5 (14dBm) is selected
		Serial1.write("AT+P6");
		break;
	case 6: // if Power 6 (17dBm) is selected
		Serial1.write("AT+P7");
		break;
	case 7: // if Power 7 (20dBm) is selected
		Serial1.write("AT+P8");
		break;
	default:
		break;
	}
	delay(50);
	// Set mode
	switch (mode)
	{
	case 0: // if Mode 0 (FU1) is selected
		Serial1.write("AT+FU1");
		break;
	case 1: // if Mode 1 (FU2) is selected
		Serial1.write("AT+FU2");
		break;
	case 2: // if Mode 2 (FU3) is selected
		Serial1.write("AT+FU3");
		break;
	default:
		break;
	}
	delay(50);
	// Set the Braudrate
	switch (braud)
	{
	case 0: // if Braudrate 0 (1200) is selected
		Serial1.write("AT+B1200");
		break;
	case 1: // if Braudrate 1 (2400) is selected
		Serial1.write("AT+B2400");
		break;
	case 2: // if Braudrate 2 (4800) is selected
		Serial1.write("AT+B4800");
		break;
	case 3: // if Braudrate 3 (9600) is selected
		Serial1.write("AT+B9600");
		break;
	case 4: // if Braudrate 4 (19200) is selected
		Serial1.write("AT+B19200");
		break;
	case 5: // if Braudrate 5 (38400) is selected
		Serial1.write("AT+B38400");
		break;
	case 6: // if Braudrate 6 (57600) is selected
		Serial1.write("AT+B57600");
		break;
	case 7: // if Braudrate 7 (115600) is selected
		Serial1.write("AT+B115600");
		break;
	default:
		break;
	}
	delay(50);
	// Set the channel
	Serial1.write("AT+C001");
	delay(50);
	// Set up for 8bit data packet
	Serial1.write("AT+U8N1"); //To set serial port format to be 8 data bits, no check, and 1 stop bit.
	delay(50);

	// Inform user if debug = true
	if (debug == true) {
		delay(50);
		Serial.println();
		Serial.println("HC-12 module has been configured:");
		while (Serial1.available()) {		// Prints the confimtion returned from HC-12
			Serial.write(Serial1.read());
		}
		Serial.println();
	}

	// Set HC-12 in normal operation
	delay(50);
	digitalWrite(reset, HIGH);

}

// Ask HC-12 What current settings is
char HC_Current(int reset) {
	//Set HC-12 in config mode
	digitalWrite(reset, LOW);
	delay(100);

	//	Get current config 	
	delay(50);
	Serial1.write("AT+RX");

	delay(50);
	char msg[50];
	int i = 1;
	while (Serial1.available()) {		// Prints the confimtion returned from HC-12
		msg[i] = Serial1.read();
		// Inform user if debug = true
		if (debug == true) {
			delay(10);
			if (i == 1) {
				Serial.println();
				Serial.println("HC-12 Current config:");
			}
			Serial.write(msg[i]);
		}

		i++;
	}

	// Set HC-12 in normal operation
	delay(50);
	digitalWrite(reset, HIGH);

}

// A function that allows serialpassthrough when needed
void Serialpassthrough() {
	if (Serial.available()) {      // If anything comes in Serial (USB),
		Serial1.print(Serial.read(), HEX);   // read it and send it out Serial1 (pins 0 & 1)
	}

	if (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
		Serial.print(Serial1.read(),HEX);   // read it and send it out Serial (USB)
	}
}

// Set up HC-12 Reset pin
void HC_DefaultPinSetup(int reset) {
	pinMode(reset, OUTPUT);
	digitalWrite(reset, HIGH);	// Set HC-12 in normal operation
}


