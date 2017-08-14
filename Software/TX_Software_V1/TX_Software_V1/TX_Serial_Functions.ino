
// ######################################################################
// ################ Main Functions for Serial on TX side ################
// ######################################################################


//################ Primary Serial Setup/Defaults ################
#pragma region Primary Serial Setup/Defaults

// ######## Serial Varibles ########
#pragma region Serial Varibels
	// for Packet_Setup_RF_RX_module():
		char RX_Braudrate = 0x04;		// Default: 4 = 9600
		char RX_CH = 0x01;				// Default:	1 = C001
		char RX_RF_Power = 0x08;		// Default: 8 = 20DB
		char RX_RF_Mode = 0x03;			// Default: 3 = FU3
		char RX_Sleep = 0x00;			// Default: 0 = False

	// for Packet_RF_RX_Ready();
		char RX_Ready = 0x00;			// Default: 0 = False

	// for Packet_RF_RX_Telemetry():
		char T_HC_12 = 0x00;			// Default: 0 = False
		char T_S0 = 0x00;				// Default: 0 = False
		char T_S1 = 0x00;				// Default: 0 = False
		char T_S2 = 0x00;				// Default: 0 = False
		char T_S3 = 0x00;				// Default: 0 = False

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
		char POT_0_MSB = 0x00;				// Default: 0
		char POT_0_LSB = 0x00;				// Default: 0
		char POT_1_MSB = 0x00;				// Default: 0
		char POT_1_LSB = 0x00;				// Default: 0
		char POT_2_MSB = 0x00;				// Default: 0
		char POT_2_LSB = 0x00;				// Default: 0
		char POT_3_MSB = 0x00;				// Default: 0
		char POT_3_LSB = 0x00;				// Default: 0

	// for Packet_RF_RX_DivSwitche():
		char BNT_0_7 = 0x00;				// Default: 0
		char BNT_8_15 = 0x00;				// Default: 0

#pragma endregion

// ######## Serial Setup ########
#pragma region Serial Setup
	// Serial Setup:
	void SerialSetup(int SerialNr,int x) { // nr = serial number, x = braudrate
		switch (SerialNr)
		{
		case 0: // if serial 0 is selected this is also the USB
			Serial.begin(x);
			while (!Serial) {
				;
			}
			break;
		case 1:	// if serial 1 is selected
			Serial1.begin(x);
			while (!Serial1) {
				;
			}
			break;
		case 2: // if serial 2 is selected
			Serial2.begin(x);
			while (!Serial2) {
				;
			}
			break;
		case 3: // if serial 3 is selected
			Serial3.begin(x);
			while (!Serial3) {
				;
			}
			break;
		default:
			break;
		}
	}

	// A Debug Serial Port is always on Serial 0 as that is the USB
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
	void Packet_Setup_RF_RX_module(){
		char setup[9] = { 0xFF, RX_Braudrate, RX_CH, RX_RF_Power, RX_RF_Mode, RX_Sleep, 0x00, 0x00, 0x00 };
		SendPacket(setup, sizeof setup, RFSerial);
	}

	// Ask RX if it's ready:
	void Packet_RF_RX_Ready() {
		char setup[9] = { 0xFE, RX_Ready, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		SendPacket(setup, sizeof setup, RFSerial);
	}

	// Ask for Telemetry data from RX:
	void Packet_RF_RX_Telemetry() {
		char setup[9] = { 0xFD, T_HC_12, T_S0, T_S1, T_S2, T_S3, 0x00, 0x00, 0x00 };
		SendPacket(setup, sizeof setup, RFSerial);
	}

	// Send 2-Axis Gyro data
	void Packet_RF_RX_Gyro() {
		char setup[9] = { 0x01, G1_X_MSB, G1_X_LSB, G1_Y_MSB, G1_Y_LSB, G2_X_MSB, G2_X_LSB, G2_Y_MSB, G2_Y_LSB };
		SendPacket(setup, sizeof setup, RFSerial);
	}

	// Send 3-Way and 2-Way Switches
	void Packet_RF_RX_DivSwitche() {
		char setup[9] = { 0x02, S3_0_1, S3_2_3, 0x00, 0x00, S2_0_1, S2_2_3, S2_4_5, S2_6_7 };
		SendPacket(setup, sizeof setup, RFSerial);
	}

	// Send Pot 0-3
	void Packet_RF_RX_Pot() {
		char setup[9] = { 0x03, POT_0_MSB, POT_0_LSB, POT_1_MSB, POT_1_LSB, POT_2_MSB, POT_2_LSB, POT_3_MSB, POT_3_LSB };
		SendPacket(setup, sizeof setup, RFSerial);
	}

	// Send buttons 0-15
	void Packet_RF_RX_DivSwitche() {
		char setup[9] = { 0x04, BNT_0_7, BNT_8_15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		SendPacket(setup, sizeof setup, RFSerial);
	}

#pragma endregion

// ######## Transmit over Serial ########
#pragma region Transmit over Serial
	// Send a Packet over serial:
	void SendPacket(const char *Array, size_t Size, int SerialNr) {
	
	int tmp[16]; // <--- look at this later, virker kun hvis stører end "Size"

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
			Serial.print(tmp[i], HEX);
			Serial.print(" ");
		}
	}

	// Jump to next line on Debug Console
	if (debug == true) {
		Serial.println(" ");
	}
}
#pragma endregion

#pragma endregion
