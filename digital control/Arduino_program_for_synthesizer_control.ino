#include <SPI.h> 
// Configuration based on digipot datasheet information 
const int CSPin = 10; //Chip Select Pin 
const float max_voltage = 5.0; //Digipot Max Voltage 
const int max_steps = 255; // 8-bit Digipot hence 256 distinct steps 
// Frequency responses per volt of the two oscillators and voltage offset 
float vco1fpv = 92.700;  
float vco1Offset = 20.853;  
float vco2fpv = 107.120;  
float vco2Offset = 25.894;  
// defining note frequencies (Iowa State University) 
const float C = 261.626, D = 293.665, E = 329.628, G = 391.995; 

// Notes for Bassline/Chords (Octave lower) 
const float C_L = 130.81, G_L = 196.00; 
const float rest = 0.0; // command to not play a melody note 
const float hold = -1.0; // command to sustain bass notes 
// Setting the melody notes for VCO 1 
float melody1[] = { 
E, D, C, D, E, E, E, rest, 
D, D, D, rest, E, G, G, rest, 
E, D, C, D, E, E, E, E, 
D, D, E, D, C, rest 
}; 
// Setting the bassline notes for VCO 2 (simple chords) 
float melody2[] = { 
C_L, hold, hold, hold, hold, hold, hold, rest, 
G_L, hold, hold, rest, C_L, hold, hold, rest, 
C_L, hold, hold, hold, hold, hold, hold, hold, 
G_L, hold, hold, hold, C_L, rest 

}; 
// defining the note durations 
float noteLengths[] = { 
1, 1, 1, 1, 1, 1, 2, 0.5, 
1, 1, 2, 0.5, 1, 1, 2, 0.5, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 4, 1 
}; 
// setting the tempo of the song 
int temp = 250;  
void setup() { 
pinMode(CSPin, OUTPUT); 
digitalWrite(CSPin, HIGH); // Programming Chip Select Pin 
SPI.begin(); // start SPI (Serial Peripheral Interface) bus 
} 

void loop() { 
int Num_of_notes = sizeof(melody1) / sizeof(melody1[0]); 
for (int i = 0; i < Num_of_notes; i++) { 
// Melody control for VCO 1 
if (melody1[i] == rest) { 
pot_signal(0, 0); // silence it when 'rest' comes up 
} else { 
VCO1_settings(melody1[i]); 
} 
// Bass/Chords control for VCO2 
if (melody2[i] == rest) { 
pot_signal(1, 0); 
} else if (melody2[i] != hold) { 
// only update if it's not a hold 
VCO2_settings(melody2[i]); 
} 
 
// wait based on duration 
int waitTime = noteLengths[i] * temp; 
delay(waitTime); 
} 
delay(3000); // three second pause before looping again 
} 
// converting frequency to voltage for first VCO 
void VCO1_settings(float freq) { 
float volts = (freq - vco1Offset) / vco1fpv; 
// determining the potentiometer step for each voltage value 
int step_value = (volts/max_voltage) * max_steps; 

step_value = constrain(step_value, 0, 255); 
pot_signal(0, step_value); 
} 
// same thing for second oscillator 
void VCO2_settings(float freq) { 
float volts = (freq - vco2Offset) / vco2fpv; 
int step_value = (volts / max_voltage) * max_steps; 
step_value = constrain(step_value, 0, 255); 
pot_signal(1, step_value); 
} 
// handles SPI writing to digipot 
void pot_signal(int pot_select, int val) { 
// choosing command depending on potentiometer index 
byte cmd; 
if (pot_select == 0) { 
cmd = 0x11; 
} else { 
cmd = 0x12; 
} 
// Chip select logic for control of each potentiometer 
digitalWrite(CSPin, LOW); 
SPI.transfer(cmd); 
SPI.transfer(val); 
digitalWrite(CSPin, HIGH); 
}
