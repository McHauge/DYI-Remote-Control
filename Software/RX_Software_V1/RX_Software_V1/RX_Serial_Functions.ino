
// ######################################################################
// ################ Main Functions for Serial on RX side ################
// ######################################################################


//######## - NOT Setup yet, just a copy of TX - ########

//################ Primary Serial Setup/Defaults ################
#pragma region Primary Serial Setup/Defaults

// ######## Serial Varibles ########
#pragma region Serial Varibels
// for Packet_Setup_RF_RX_module():
char RX_Braudrate = 0x08;		// Default: 8 = 115200
char RX_CH = 0x01;				// Default:	1 = C001
char RX_RF_Power = 0x08;		// Default: 8 = 20dBm
char RX_RF_Mode = 0x03;			// Default: 3 = FU3
char RX_Sleep = 0x00;			// Default: 0 = False

								// for Packet_RF_RX_Ready();
char RX_Ready = 0x00;			// Default: 0 = False (don't check)

#pragma endregion

// ######## Serial Setup ########
#pragma region Serial Setup

// Get Braudrate:
int GetBraudrate(int x) {
	// Switch braudrate
	switch (x) // Switch between Braudrates
	{
	case 0:	// if Braudrate 0 (1200) is selected
		return 1200;
		break;
	case 1: // if Braudrate 1 (2400) is selected
		return 2400;
		break;
	case 2: // if Braudrate 2 (4800) is selected
		return 4800;
		break;
	case 3: // if Braudrate 3 (9600) is selected
		return 9600;
		break;
	case 4: // if Braudrate 4 (19200) is selected
		return 19200;
		break;
	case 5: // if Braudrate 5 (38400) is selected
		return 38400;
		break;
	case 6: // if Braudrate 6 (57600) is selected
		return 57600;
		break;
	case 7: // if Braudrate 7 (115600) is selected
		return 115600;
		break;
	default:
		break;
	}
}

// Serial Setup:
void SerialSetup(int SerialNr, int x) { // nr = serial number, x = braudrate

// Open selected serial port with said braudrate
	switch (SerialNr) // Switch between serial ports
	{
	case 0: // if serial 0 is selected this is also the USB
		Serial.begin(GetBraudrate(x));
		while (!Serial) {}
		break;
	case 1:	// if serial 1 is selected
		Serial1.begin(GetBraudrate(x));
		while (!Serial1) {}
		break;
	case 2: // if serial 2 is selected
		Serial2.begin(GetBraudrate(x));
		while (!Serial2) {}
		break;
	case 3: // if serial 3 is selected
		Serial3.begin(GetBraudrate(x));
		while (!Serial3) {}
		break;
	default:
		break;
	}
}

// A Debug Serial Port is always on Serial 0 as that is the USB, if debug = true
void DebugSerial() {
	if (debug == true) {
		Serial.begin(115200);
		while (!Serial) {
			;
		}

		// inform the user
		Serial.println(" ");
		Serial.println("Debug: Serial 0 is Ready");
		Serial.println(" ");
	}
}
#pragma endregion

#pragma endregion

// ################ Protocols Div. Packets ################
#pragma region Protocols Div. Packets

// ######## Setup Packets ########
#pragma region Setup Packets
// A basic packet is 9 byte's long 8 data byte's and 1 ID byte
// Fx: ID , D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7

// Return RF configuration
void RF_Setup_Telemetry_packet() {
	char setup[9] = { 0xEE, RX_Braudrate, RX_CH, RX_RF_Power, RX_RF_Mode, RX_Sleep, 0x00, 0x00, 0x00 };
	SendPacket(setup, sizeof setup, RFSerial);
}

// Am my RX ready?
void RX_Ready_Telemetry_packet() {
	char setup1[9] = { 0xED, RX_Ready, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	SendPacket(setup1, sizeof setup1, RFSerial);
}

// Return Telemetry S0 data from RX:
void Telemetry_packet_S0() {
	char setup2[9] = { 0xEC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	SendPacket(setup2, sizeof setup2, RFSerial);
}

// Return Telemetry S1 data from RX:
void Telemetry_packet_S1() {
	char setup3[9] = { 0xEB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	SendPacket(setup3, sizeof setup3, RFSerial);
}

// Return Telemetry S2 data from RX:
void Telemetry_packet_S2() {
	char setup4[9] = { 0xEA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	SendPacket(setup4, sizeof setup4, RFSerial);
}

// Return Telemetry S3 data from RX:
void Telemetry_packet_S3() {
	char setup5[9] = { 0xE9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	SendPacket(setup5, sizeof setup5, RFSerial);
}

// Debug packet
void Debug_packet() {
	char setup6[9] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	SendPacket(setup6, sizeof setup6, RFSerial);
}

#pragma endregion

// ######## Recived Packet Execution ########
#pragma region Recived Packet Execution

// Detects what packet type was recived
int Recived_Packet() {
	switch (msg[0])
	{
	case 0xFF:	
		if (debug == true) { Serial.println("Debug packet recived"); }
		return 1;
		break;
	case 0xFE:	
		if (debug == true) { Serial.println("RF_Connection packet recived"); }
		return 2;
		break;
	case 0xFD:	
		if (debug == true) { Serial.println("RX_Ready packet recived"); }
		return 3;
		break;
	case 0xFC:	
		if (debug == true) { Serial.println("Telemetry packet recived"); }
		return 4;
		break;
	case 0x01:	
		if (debug == true) { Serial.println("Gyro packet recived"); }
		return 5;
		break;
	case 0x02:	
		if (debug == true) { Serial.println("Switch packet recived"); }
		return 6;
		break;
	case 0x03:	
		if (debug == true) { Serial.println("Pot packet recived"); }
		return 7;
		break;
	case 0x04:	
		if (debug == true) { Serial.println("Buttons packet recived"); }
		return 8;
		break;
	default:	
		if (debug == true) { Serial.println("ERROR Can't detect message type"); }
		return 0;
		break;
	}
}

#pragma endregion

// ######## Transmit over Serial ########
#pragma region Transmit over Serial

// Send a Packet over serial:
void SendPacket(const char *Array, size_t Size, int SerialNr) {

	int tmp[16]; // <--- look at this later, only works if bigger than "Size" (default = 16)

	// convert char array to uint8_t array
	for (int i = 0; i < Size; i++)
	{
		tmp[i] = uint8_t(Array[i]);
	}

	for (int i = 0; i < Size; i++) {
		switch (SerialNr)
		{
		case 0: // if serial 0 is selected this is also the USB
			Serial.write(tmp[i]);
			break;
		case 1:	// if serial 1 is selected
			Serial1.write(tmp[i]);
			break;
		case 2: // if serial 2 is selected
			Serial2.write(tmp[i]);
			break;
		case 3: // if serial 3 is selected
			Serial3.write(tmp[i]);
			break;
		default:
			break;
		}

		// To the debug Console
		if (debug == true) {
			Serial.print(tmp[i], HEX);				// Prints tmp to debug serial
			if (i % 2 == 0) { Serial.print(" "); }	// Prints " " as a spacer after even bytes
			if (i == 8) { Serial.println(""); }		// Moves onto next line 
		}
	}
}
#pragma endregion

// ######## Recive over Serial ########
#pragma region Recive over Serial

// Read data recived on Serial1 prints to Debug serial
void SerialRead() {
	for (int i = 0; i <9; i++) {					// Loops as long as a byte is recived
		while (!Serial1.available());				// wait for a character
		int incomingByte = Serial1.read();			// Reads recived byte into incommingByte
		msg[i] = incomingByte;						// Stores the byte in msg[]
		if (debug == true)
		{
			Serial.print(incomingByte, HEX);	 	// Prints to debug serial if debug = true
			if (i % 2 == 0) { Serial.print(' '); }	// Prints " " as a spacer after even bytes
		}
	}
	if (debug == true) { Serial.println(); }		// Moves onto next line
	Serial1.flush();
}
#pragma endregion

#pragma endregion

// ################ Other Functions ################
#pragma region Other Functions

#pragma endregion