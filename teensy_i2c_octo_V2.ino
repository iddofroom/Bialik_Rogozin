#include <Wire.h>
#include <OctoWS2811.h>

const int ledsPerStrip = 200;
DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
int rainbowColors[180];
bool steps[9] = {false,false,false,false,false,false,false,false,false};
int stepsindex[9]= {800,824,849,1000,1024,1048,1200,1224,1248};
bool gameon = false;
int turnlist[100] ;
bool sleepy = true;
int xsl = 5;
int ysl = 5;

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0x101010
#define COLOR1   0x121409
#define COLOR2   0x120412
int colors[9] = {GREEN,RED,BLUE,PINK,ORANGE,YELLOW,WHITE,COLOR1,COLOR2};
void setup() {
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  for (int i=0; i<180; i++) {
    int hue = i * 2;
    int saturation = 100;
    int lightness = 10;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }
  leds.begin();
  digitalWrite(1, LOW);
  Wire.begin();             // join i2c bus (address optional for master)
  Serial.begin(9600);       // start serial for output
  randomSeed(analogRead(17));

}
void loop() {
  while ( sleepy)
    {defulatani();}
  gameon=true;
  resetfloor();
  Serial.println("simon says");  
  simon_say();
  Serial.println();
  delay(3000);
  
}
void simon_say(){
  xsl = 5;
  ysl=5;
  startani();
  int level = 0;
  int gamespeed = 300;
  randomizer();
  gameon = true;
  while (gameon)
  {
     Serial.print("game- round ");  
     Serial.println(level);  
    for (int lev = 0; lev<level+1;lev++)
    {
       Serial.print("animation ");  
     Serial.println(turnlist[lev]); 
      playani(turnlist[lev]); 
    }
    
    for (int lev = 0; lev<level+1;lev++)
    { 
      sleepy = true;
      while ( sleepy)
         {stepsniff();}
      if ( whatstep() != turnlist[lev])
      {
       loseani();
       gameon=false;
       Serial.println( whatstep()); 
       Serial.println(turnlist[lev]); 
       sleepy=true;
       break; 
       }
       else
       {playani(turnlist[lev]);}      
    }
    if (gameon){
      winani();
      level++;
      }
  }
}

int whatstep(){
  for (int dos = 0; dos<9;dos++){
    if (steps[dos])
      {return dos;} 
  }  
}
void stepsniff(){
  delay(300);
getsteps();
  }
void winani(){
  
}
void loseani(){
  
}
void shourtani(){
  
}
void blackscreen(){
  for (int y=0; y < 800; y++) {
        leds.setPixel(y, 00000000);}
         leds.show();
      
}
void playani(int number){
  
     for (int y=1; y < 201; y++) {
        leds.setPixel(200-y, colors[number]);
        leds.setPixel(400-y, colors[number]);
        leds.setPixel(600-y, colors[number]);
        leds.setPixel(800-y, colors[number]);
         leds.show();
         delay(1);}
         
   for (int y=200; y > 0; y--) {
        leds.setPixel(200-y, 00000000);
        leds.setPixel(400-y, 00000000);
        leds.setPixel(600-y, 00000000);        
        leds.setPixel(800-y, 00000000);
        leds.show();
        delayMicroseconds(3);}
        delay(200);
}
void  randomizer() {
  for (int l =0; l<100; l++){
    turnlist[l]=random(9);}
}
void defulatani(){
  rainbow(180,10,500);
  }

void startani(){
   for (int y=400; y >0;  y--) {
        leds.setPixel(800-y, RED);  
        leds.setPixel(400-y, RED);
        leds.show();
        delay(2);}
 
   for (int y=0; y < 800; y++) {
        leds.setPixel(y, 00000000);}
   leds.show();
}
bool steponfloor (){
  bool tempi = false;
  for (int s=0; s<9 ; s++){
    if (steps[s]){
      tempi=true;
      }
    }
  return tempi; 
}

void resetfloor(){
    for (int k=0; k<9;k++){
      for (int j=0;j<25;j++){
       leds.setPixel(stepsindex[k]+j, colors[k]);}}
    leds.show();
    }
bool getsteps(){
  bool geti = false;
  int cnt = 0;
  Serial.print("read: ");
  Wire.requestFrom(8, 6);   // request 6 bytes from slave device #8
  while(Wire.available()) { // slave may send less than requested
    char c = Wire.read();   // receive a byte as character
    if (c=='1'){Serial.println(cnt);steps[cnt] = true; sleepy=false; geti=true;}
    else{ steps[cnt] = false;}
    cnt++;
  }
  Wire.requestFrom(7, 3);   // request 6 bytes from slave device #8
  while(Wire.available()) { // slave may send less than requested
    char c = Wire.read();   // receive a byte as character
    if (c=='1'){Serial.println(cnt);steps[cnt] = true; sleepy=false; geti=true;}
    else{steps[cnt] = false;}
    cnt++;
  }
  Serial.println();
  return geti;
}
int xy(int x, int y){
  int temp = 0;
  if (y<16){temp=+200;}
  if (y<11){temp=+200;}
  if (y<6){temp=+200;}
  temp = temp + ((x-1)*5);
  if ( x%2 == 0)// זוגי
    { temp = temp+(y%5); } //שארית
  else
    { temp = temp+5-(y%5) ;} //שארית  
  Serial.println(temp);
  return temp;
}
void rainbow(int phaseShift, int cycleTime, int speedy)
{
  int color, x, y, wait;

  wait = cycleTime * 1000 / ledsPerStrip;
  for (color=0; color < 180; color++) {
    digitalWrite(1, HIGH);
    for (x=0; x < ledsPerStrip; x++) {
      for (y=0; y < 4; y++) {
        int index = (color + x + y*phaseShift/2) % 180;
        leds.setPixel(x + y*ledsPerStrip, rainbowColors[index]);
      }
    }
    leds.show();
    digitalWrite(1, LOW);
    if (color%10==0)
     { if (getsteps()){break;}}
   if (color%3==0)
    {delayMicroseconds(wait*speedy);}
  }   
}
