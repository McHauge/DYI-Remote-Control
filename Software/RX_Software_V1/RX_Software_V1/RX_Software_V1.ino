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

// Enable debug on serial
const bool debug = true; // Enable debug

// Default pins
int HC_Reset = 22;	// HC-12 reset/program pin (default = 22)

// RF Serial Port default = 1 and braudrate = 3 (9600)
int RFSerial = 1;	// Select 0,1,2,3
int RFBraud = 3;	// Select 0 (1200), 1 (2400), 2 (4800), 3 (9600), 4 (19200), 5 (38400), 6 (57600), 7 (115200)
int RFMode = 2;		// Select 0 (FU1), 1 (FU2), 2(FU3)
int RFChannel = 1;	// Select 0-100
int RFPower = 7;	// Select 0 (-1dBm), 1 (2dBm), 2 (5dBm), 3 (8dBm), 4 (11dBm), 5 (14dBm), 6 (17dBm), 7 (20dBm)

// Other values
byte msg[9];		// Array with return data from serial recive (default = msg[9])

#pragma endregion

// ################ Main Program ################
#pragma region Main Program

// The setup function runs once when you press reset or power the board
void setup() {
	HC_DefaultPinSetup(HC_Reset);
	DebugSerial();												// Serial 0 Bruadrate 115200, Runs the debug serial setup
	SerialSetup(RFSerial, RFBraud);								// Serial 1, Bruadrate 9600
	HC_Setup(RFPower, RFMode, RFBraud, RFChannel, HC_Reset);	// Configure the HC-12 Module
	HC_Current(HC_Reset);										// Reads current HC-12 config
}

// The loop function runs over and over again until power down or reset
void loop() {

	SerialRead();
	if (Recived_Packet() == 1) { Serial.println("test"); Debug_packet(); }
	
	//Debug_packet();
	//delay(1000);

}

#pragma endregion