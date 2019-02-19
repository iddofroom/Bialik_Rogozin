#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#define Mp3Busy      12   // 1 - not working, 0 working
#include <Wire.h>

void setup () {
  pinMode(Mp3Busy, INPUT); 
  Serial.begin (9600);
  mp3_set_serial (Serial);  //set Serial for DFPlayer-mini mp3 module 
  delay(1);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (25); // max volume is 30
  delay(1);  //wait 1ms for mp3 module to set volume
  Wire.begin(5);                // join i2c bus with address #9
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}


void loop () {  
 delay(100);
 
} 
void receiveEvent(int howMany)
{
  while(Wire.available() > 1) {  // loop through all but the last
    char c = Wire.read();        // receive byte as a character
    Serial.print(c);             // print the character
    mp3_stop(); // stop to play
   Serial.print("STOP"); 
    mp3_play (c); // play song 1
    Serial.print("play ");
    delay(2000);

  }
  int x = Wire.read();           // receive byte as an integer
  Serial.println(x);             // print the integer
}
