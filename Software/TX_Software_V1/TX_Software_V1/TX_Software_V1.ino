/*
 Name:		TX_Software_V1.ino
 Created:	3/20/2017 8:17:24 PM
 Author:	AndreasH
*/

// ####################################################################
// ################ Main Program For TX Remote Control ################
// ####################################################################


// ################ Main Configuration and Value's Setup ################
#pragma region Main Config/Setup

// If debug serial sould be on
const bool debug = true;

// RF Serial Port = 1
int RFSerial = 1;
int RFBaud = 9600;

#pragma endregion

// ################ Main Program ################
#pragma region Main Program

// the setup function runs once when you press reset or power the board
void setup() {
	DebugSerial(); // Serial 0 Bruadrate 115200
	SerialSetup(RFSerial, RFBaud); // Serial 1, Bruadrate 9600
}

// the loop function runs over and over again until power down or reset
void loop() {

	// test setup:

	char test[9] = { 0xFF, 0x02, 0xAB, 0xC9, 0x11, 0x15, 0xC8, 0x00, 0x30 };

	SendPacket( test, sizeof test, RFSerial);


	delay(1000);

}

#pragma endregion