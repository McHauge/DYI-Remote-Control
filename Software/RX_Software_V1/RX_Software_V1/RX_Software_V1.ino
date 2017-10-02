/*
 Name:		RX_Software_V1.ino
 Created:	10/2/2017 2:17:53 PM
 Author:	McHauge
*/

// ####################################################################
// ################ Main Program For RX Remote Control ################
// ####################################################################

//######## - NOT Setup yet, just a copy of TX - ########

// ################ Main Configuration and Value's Setup ################
#pragma region Main Config/Setup

// If debug serial sould be on
const bool debug = true; // Enable debug

// RF Serial Port default = 1 and braudrate = 7 (115200)
int RFSerial = 1; // Select 0,1,2,3
int RFBraud = 7;  // Select 0 (1200), 1 (2400), 2 (4800), 3 (9600), 4 (19200), 5 (38400), 6 (57600), 7 (115200)

#pragma endregion

// ################ Main Program ################
#pragma region Main Program

// The setup function runs once when you press reset or power the board
void setup() {
	DebugSerial(); // Serial 0 Bruadrate 115200, Runs the debug serial setup
	SerialSetup(RFSerial, RFBraud); // Serial 1, Bruadrate 115200
}

// The loop function runs over and over again until power down or reset
void loop() {

	// Test setup:

	char test[9] = { 0xFF, 0x02, 0xAB, 0xC9, 0x11, 0x15, 0xC8, 0x00, 0x30 };

	SendPacket(test, sizeof test, RFSerial);

	delay(1000);

}

#pragma endregion