/*
 Name:		TX_Software_V1.ino
 Created:	3/20/2017 8:17:24 PM
 Author:	McHauge
*/

// ####################################################################
// ################ Main Program For TX Remote Control ################
// ####################################################################


// ################ Main Configuration and Value's Setup ################
#pragma region Main Config/Setup

// If debug serial sould be on
const bool debug = true; // Enable debug

// Default pins
int HC_Reset = 22;

// RF Serial Port default = 1 and braudrate = 3 (9600)
int RFSerial = 1;	// Select 0,1,2,3
int RFBraud = 3;	// Select 0 (1200), 1 (2400), 2 (4800), 3 (9600), 4 (19200), 5 (38400), 6 (57600), 7 (115200)
int RFMode = 2;		// Select 0 (FU1), 1 (FU2), 2(FU3)
int RFChannel = 1;	// Select 0-100
int RFPower = 7;	// Select 0 (-1dBm), 1 (2dBm), 2 (5dBm), 3 (8dBm), 4 (11dBm), 5 (14dBm), 6 (17dBm), 7 (20dBm)
#pragma endregion

// ################ Main Program ################
#pragma region Main Program

// The setup function runs once when you press reset or power the board
void setup() {
	DefaultPinSetup();
	DebugSerial(); // Serial 0 Bruadrate 115200, Runs the debug serial setup
	SerialSetup(RFSerial, RFBraud); // Serial 1, Bruadrate 115200
	HC_Setup( RFPower, RFMode, RFBraud, RFChannel, HC_Reset); // Configure the HC-12 Module
	HC_Current(HC_Reset);
}

// The loop function runs over and over again until power down or reset
void loop() {

// Test setup:
//	char test[9] = { 0xFF, 0x02, 0xAB, 0xC9, 0x11, 0x15, 0xC8, 0x00, 0x30 };
//	SendPacket( test, sizeof test, RFSerial);
//	delay(1000);

}

#pragma endregion