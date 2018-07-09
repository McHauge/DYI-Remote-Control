
// ######################################################################
// ################ Main Functions for Serial on TX side ################
// ######################################################################


//################ Primary Serial Setup/Defaults ################
#pragma region Primary Serial Setup/Defaults

// ######## Serial Varibles ########
#pragma region Serial Varibels
// Setup the default values for the system

	// HC-12 PINS


	// for Packet_Setup_RF_RX_module():
		char RX_Braudrate = 0x08;		// Default: 8 = 115200
		char RX_CH = 0x01;				// Default:	1 = C001
		char RX_RF_Power = 0x08;		// Default: 8 = 20dBm
		char RX_RF_Mode = 0x03;			// Default: 3 = FU3
		char RX_Sleep = 0x00;			// Default: 0 = False

	// for Packet_RF_RX_Ready();
		char RX_Ready = 0x00;			// Default: 0 = False (don't check)

	// for Packet_RF_RX_Telemetry():
		char T_HC_12 = 0x00;			// Default: 0 = False (don't check)
		char T_S0 = 0x00;				// Default: 0 = False (don't check)
		char T_S1 = 0x00;				// Default: 0 = False (don't check)
		char T_S2 = 0x00;				// Default: 0 = False (don't check)
		char T_S3 = 0x00;				// Default: 0 = False (don't check)

	// for Packet_RF_RX_Gyro():
		char G1_X_MSB = 0x00;			// Default: 0
		char G1_X_LSB = 0x00;			// Default: 0
		char G1_Y_MSB = 0x00;			// Default: 0
		char G1_Y_LSB = 0x00;			// Default: 0
		char G2_X_MSB = 0x00;			// Default: 0
		char G2_X_LSB = 0x00;			// Default: 0
		char G2_Y_MSB = 0x00;			// Default: 0
		char G2_Y_LSB = 0x00;			// Default: 0

	// for Packet_RF_RX_DivSwitche():
		char S3_0_1 = 0x00;				// Default: 00
		char S3_2_3 = 0x00;				// Default: 00
		char S2_0_1 = 0x00;				// Default: 00
		char S2_2_3 = 0x00;				// Default: 00
		char S2_4_5 = 0x00;				// Default: 00
		char S2_6_7 = 0x00;				// Default: 00

	// for Packet_RF_RX_Pot():
		char POT_0_MSB = 0x00;			// Default: 0
		char POT_0_LSB = 0x00;			// Default: 0
		char POT_1_MSB = 0x00;			// Default: 0
		char POT_1_LSB = 0x00;			// Default: 0
		char POT_2_MSB = 0x00;			// Default: 0
		char POT_2_LSB = 0x00;			// Default: 0
		char POT_3_MSB = 0x00;			// Default: 0
		char POT_3_LSB = 0x00;			// Default: 0

	// for Packet_RF_RX_DivSwitche():
		char BNT_0_7 = 0x00;			// Default: 0
		char BNT_8_15 = 0x00;			// Default: 0

#pragma endregion

// ######## Serial Setup ########
#pragma region Serial Setup
		
	// Get Braudrate:
	int GetBraudrate(int x) {
		// Switch braudrate
		switch (x) // Switch between Braudrates
		{
		case 0: // if Braudrate 0 (1200) is selected
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
	void SerialSetup(int SerialNr,int x) { // nr = serial number, x = braudrate

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

	// Setup RF Connection
		void RF_Setup_packet() { 
			char setup[9] = { 0xFE, RX_Braudrate, RX_CH, RX_RF_Power, RX_RF_Mode, RX_Sleep, 0x00, 0x00, 0x00 };
			SendPacket(setup, sizeof setup, RFSerial);
		}

	// Ask RX if it's ready:
		void RX_Ready_packet() {	
			char setup1[9] = { 0xFD, RX_Ready, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			SendPacket(setup1, sizeof setup1, RFSerial);
		}

	// Ask for Telemetry data from RX:
		void Telemetry_packet() { 
			char setup2[9] = { 0xFC, T_HC_12, T_S0, T_S1, T_S2, T_S3, 0x00, 0x00, 0x00 };
			SendPacket(setup2, sizeof setup2, RFSerial);
		}

	// Send 2-Axis Gyro data
		void Gyro_packet() { 
			char setup3[9] = { 0x01, G1_X_MSB, G1_X_LSB, G1_Y_MSB, G1_Y_LSB, G2_X_MSB, G2_X_LSB, G2_Y_MSB, G2_Y_LSB };
			SendPacket(setup3, sizeof setup3, RFSerial);
		}

	// Send Switch data
		void Switch_packet() {	
			char setup4[9] = { 0x02, S3_0_1, S3_2_3, 0x00, 0x00, S2_0_1, S2_2_3, S2_4_5, S2_6_7 };
			SendPacket(setup4, sizeof setup4, RFSerial);
		}

	// Send Pot 0-3
		void Pot_packet() {	
			char setup5[9] = { 0x03, POT_0_MSB, POT_0_LSB, POT_1_MSB, POT_1_LSB, POT_2_MSB, POT_2_LSB, POT_3_MSB, POT_3_LSB };
			SendPacket(setup5, sizeof setup5, RFSerial);
		}

	// Send buttons 0-15
		void Button_packet() {	
			char setup6[9] = { 0x04, BNT_0_7, BNT_8_15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			SendPacket(setup6, sizeof setup6, RFSerial);
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
	case 0xEE:	
		if (debug == true) { Serial.println("RF_Setup_Telemetry packet recived"); }
		return 2;
		break;
	case 0xED:	
		if (debug == true) { Serial.println("RX_Ready_Telemetry packet recived"); }
		return 3;
		break;
	case 0xEC:	
		if (debug == true) { Serial.println("Telemetry_S0 packet recived"); }
		return 4;
		break;
	case 0xEB:	
		if (debug == true) { Serial.println("Telemetry_S1 packet recived"); }
		return 5;
		break;
	case 0xEA:	
		if (debug == true) { Serial.println("Telemetry_S2 packet recived"); }
		return 6;
		break;
	case 0xE9:	
		if (debug == true) { Serial.println("Telemetry_S3 packet recived"); }
		return 7;
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