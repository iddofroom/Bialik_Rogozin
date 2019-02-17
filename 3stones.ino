
#include <Wire.h>
#include "HX711.h"
///////////////////////////////////////
#define calibration_factor -14050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define minw  0.2   // change this value of cell load have lot of noice
#define maxw  20 // same as value before
#define sensors  3
#define DOUT1 3
#define CLK1  2
#define DOUT3  9
#define CLK3  8
#define DOUT2  11
#define CLK2  10
bool stons[3] = {false,false,false};
float history[9][3] ={(0,0,0),(0,0,0),(0,0,0)};
HX711 scale1(DOUT1, CLK1);
HX711 scale2(DOUT2, CLK2);
HX711 scale3(DOUT3, CLK3);
void setup() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");
  scale1.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale1.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale2.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale2.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale3.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale3.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  Wire.begin(7);                // join i2c bus with address #7
  Wire.onRequest(requestEvent); // register event
  history[0][0]=scale1.get_units();
  history[1][0]=scale2.get_units();
  history[2][0]=scale3.get_units()   ;   
 }
// List of patterns to cycle through.  Each is defined as a separate function below.

void loop() {
   for (int k=0;k<sensors;k++)
      {
      history[k][2]=history[k][1];
      history[k][1]=history[k][0];
      }
   history[0][0]=scale1.get_units();
   history[1][0]=scale2.get_units();
   history[2][0]=scale3.get_units();
   for (int k=0;k<sensors;k++)
      {Serial.print(history[k][0], 1); Serial.print(" ");} //scale.get_units() returns a float
   Serial.println();
   for (int k=0;k<sensors;k++)
      { stons[k] = false;
        if ( abs(history[k][0]-history[k][1])>minw && abs(history[k][0]-history[k][1])<maxw && abs(history[k][1]-history[k][2])>minw && abs(history[k][1]-history[k][2])<maxw && abs(history[k][0]-history[k][2])>minw && abs(history[k][0]-history[k][2])<maxw )
        {stons[k]=true;Serial.println("-------------------------");}}       
delay(100);
}
void requestEvent() {
  for (int l=0; l<sensors;l++)
  {
    if (stons[l]){Wire.write("1");Serial.print("yes ");}
    else{Wire.write("0");Serial.print("no ");}
    }
  Serial.println();
}
