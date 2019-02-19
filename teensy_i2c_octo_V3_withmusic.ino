#include <Wire.h>
#include <OctoWS2811.h>

const int ledsPerStrip = 200;
DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
int rainbowColors[180];
bool steps[9] = {false,false,false,false,false,false,false,false,false};
int stepsindex[9]= {824,800,849,1000,1024,1048,1200,1224,1248};
bool gameon = false;
int turnlist[100] ;
bool sleepy = true;

#define RED    0xE00000
#define GREEN  0x00E000
#define BLUE   0x0000E0
#define YELLOW 0x77E000
#define PINK   0xFF1088
#define ORANGE 0xE0AA00
#define WHITE  0x666666
#define COLOR1   0x00AAAA
#define COLOR2   0x55BB22
int colors[9] = {RED,GREEN,YELLOW,PINK,ORANGE,BLUE,WHITE,COLOR1,COLOR2};
void setup() {
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH) ;
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
  delay(800);
  sleepy = true;
 blackscreen();
  while ( sleepy)
    {defulatani();}
  gameon=true;
  resetfloor();
  Serial.println("simon says");  
  simon_say();
  Serial.println();
}
void simon_say(){
  sendmusic(1,1);
  startani();
  int level = 0;
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
      sendmusic(0,turnlist[lev]);
      playani(turnlist[lev]); 
    }
    
    for (int lev = 0; lev<level+1;lev++)
    { 
      sleepy = true;
      while ( sleepy)
         {stepsniff();}
      if ( whatstep() != turnlist[lev])
      {
            sendmusic(1,2);
       loseani();
       gameon=false;
       Serial.println( whatstep()); 
       Serial.println(turnlist[lev]); 
       sleepy=true;
       break; 
       }
       else
       {shortani(turnlist[lev]);}      
    }
    if (gameon){
          sendmusic(1,3);
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
  rainbow(180,5,50);
  blackscreen();
}
void loseani(){
  blackfloor();
  for (int x=21; x<41;x++){
    for (int y=11;y<21;y++){
        leds.setPixel(xy(x,y), BLUE);
        leds.setPixel(xy(41-x,21-y), BLUE);
        leds.setPixel(xy(41-x,y), BLUE);
        leds.setPixel(xy(x,21-y), BLUE);       
        leds.setPixel(xy(x-1,y-1), BLUE);
        leds.setPixel(xy(42-x,22-y), BLUE);
        leds.setPixel(xy(42-x,y-1), BLUE);
        leds.setPixel(xy(x-1,22-y), BLUE);
        leds.setPixel(xy(x-2,y-2), BLUE);
        leds.setPixel(xy(43-x,23-y), ORANGE);
        leds.setPixel(xy(43-x,y-2), ORANGE);
        leds.setPixel(xy(x-2,22-y), ORANGE);
        
        leds.show();
        delay(8);  
    }
      
  }
  delay(500);
  
}
void blackscreen(){
  for (int y=0; y < 800; y++) {
        leds.setPixel(y, 00000000);}
         leds.show();
      
}
void shortani (int number){
  
     for (int y=1; y < 101; y++) {
      for (int j=1;j<9;j++)
      {leds.setPixel((j*100)-y, colors[number]);}
      leds.show();
        
        }
        for (int y=1; y < 101; y++) {
      for (int j=1;j<9;j++)
      {leds.setPixel((j*100)-y, 00000000);}
      leds.show();
        
        }

}
void playani(int number){
    switch (number){
    case 0 :
    {
        for (int k=1; k < 3; k++) {
          for (int t=1; t < 5; t++) {
              for (int x=1; x < 41; x++) {
                for (int y=1; y < 21; y++) {
                   if ((xy(x,y)+t)%5==0)
                    {leds.setPixel(xy(x,y), colors[number]);}
                   else
                    {leds.setPixel(xy(x,y), 00000000);
                    }}}
          
          leds.show();
          delay(200);       
          }
          }
          blackscreen();
        break;  
    }
    case  1 :
    {
     for (int y=1; y < 201; y++) {
        leds.setPixel(200-y, colors[number]);
        leds.setPixel(400-y, colors[number]);
        leds.setPixel(600-y, colors[number]);
        leds.setPixel(800-y, colors[number]);
        leds.show();
        if (y%4==0) {delay(2);}
        }
         blackscreen();
      break;
      }
      case 2:
     {for (int y=1; y < 201; y++) {
        leds.setPixel(y, colors[number]);
        leds.setPixel(200+y, colors[number]);
        leds.setPixel(400+y, colors[number]);
        leds.setPixel(600+y, colors[number]);
        leds.show();
        if (y%4==0) {delay(2);}
        }        
        blackscreen();
         break;}
         case 3:{     
        for (int k=1; k < 5; k++) {
          for (int t=1; t < 10; t++) {
            for (int s=0;s<800;s++){leds.setPixel(s, 00000000);}
            for (int x=1; x < 41; x++) {
                for (int y=1; y < 21; y++) {
                   if ((x+y+k)%3==0)
                    {leds.setPixel(xy(x,y), colors[number]);}
                  }}        
          leds.show();
          delay(40);       
          }
          }
          blackscreen();
        break;
          }
          case 4: 
      {
       blackscreen();
        for (int k=1; k < 8; k++) {
          for (int t=1; t < 10; t++) {
            for (int s=0;s<800;s++){leds.setPixel(s, 00000000);}
            for (int x=1; x < 41; x++) {
                for (int y=1; y < 21; y++) {
                   if ((y+k)%4==0 || (y+k)%4==1)
                    {leds.setPixel(xy(x,y), colors[number]);}
                  }}        
          leds.show();
          delay(40);       
          }
          }
          blackscreen();
        break;
       }
       case 5:
      {
        
       blackscreen();
        for (int k=1; k < 6; k++) {
          for (int t=1; t < 10; t++) {
            for (int s=0;s<800;s++){leds.setPixel(s, 00000000);}
            for (int x=1; x < 41; x++) {
                for (int y=1; y < 21; y++) {
                   if ((x+k)%6==0 || (x+k)%6==1)
                    {leds.setPixel(xy(x,y), colors[number]);}
                  }}        
          leds.show();
          delay(20);       
          }
          }
          blackscreen();
        break;
        }
      case 6:{
          for (int t=1; t < 40; t++) {
            for (int s=0;s<800;s++){leds.setPixel(s, 00000000);}
            for (int x=1; x < 41; x++) {
                for (int y=1; y < 21; y++) {
                   if (x<t)
                    {leds.setPixel(xy(x,y), colors[number]);
                    if (x>3){leds.setPixel(xy(x-3,y), 00000000);}
                  }}}        
          leds.show();
          delay(40);       
          
          }
          blackscreen();
        break;
        }
      case 7 :
      {  
          for (int t=1; t < 7; t++) {
            for (int s=0;s<800;s++){leds.setPixel(s, 00000000);}
            for (int x=1; x < 41; x++) {
                for (int y=1; y < 21; y++) {
                   if (random(2)==1)
                    {leds.setPixel(xy(x,y), colors[number]);}
                  }}        
          leds.show();
          delay(150);       
          
          }
          blackscreen();
        break;
        }
        case 8:
{  
          for (int t=1; t < 7; t++) {
            for (int s=0;s<800;s++){leds.setPixel(s, 00000000);}
            for (int x=1; x < 41; x++) {
                for (int y=1; y < 21; y++) {
                   if ((x==t || y==t||21-y==t || 41-x==t)&& x>=t && x<=41-t && y>=t && y<=41-t )
                    {leds.setPixel(xy(x,y), colors[number]);
                    leds.setPixel(xy(x-1,y), colors[number]);
                    }
                  }}        
          leds.show();
          delay(150);       
          
          }
          blackscreen();
        break;
         }        
    }  delay(200);
}
void  randomizer() {
  for (int l =0; l<100; l++){
    turnlist[l]=random(9);
  }

}
void defulatani(){
  rainbow(180,10,500);
  }

void startani(){
   for (int y=400; y >0;  y--) {
        for (int k =0;k<9;k++){
        leds.setPixel(792+k-y, 00000000);  
        leds.setPixel(392+k-y, 00000000);}
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
      for (int j=0;j<24;j++){
       leds.setPixel(stepsindex[k]+j, colors[k]);leds.show();delay(2);}
       delay(80);leds.show();}

    }
void blackfloor(){
   for (int k=8; k>-1;k--){
      for (int j=24;j>-1;j--){
       leds.setPixel(stepsindex[k]+j,00000000);leds.show();delay(2);}
       delay(80);leds.show();}

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
  return geti;
}
int xy(int x, int y){
  
  //delay(300);
  //Serial.print(x);
  // Serial.print("-");
  // Serial.print(y);
  // Serial.print("-");
  int temp = 0;
  if (y<16){temp=temp+200;}
  if (y<11){temp=temp+200;}
  if (y<6){temp=temp+200;}
  temp = temp + (x*5)-5;
    if ((y>5 && y<11) || y>15)
  {
  if ( (2+x)%2 == 0)// זוגי
    { temp = temp+((5+y)%5); } //שארית
  else
    { temp = temp+5-((5+y)%5)+1 ;} //שארית  
}
  else
  {    
  if ( (2+x)%2 == 1){ temp = temp+((5+y)%5); } 
  else{ temp = temp+5-((5+y)%5)+1 ;} //שארית  
  }
  if (y%5==0){temp=temp+5;}
  if ((10+y)%10==0 && (x+2)%2==1 ){temp=temp-10;}
  if ((2+x)%2 == 0 && (y==5 || y==15)){temp=temp-10;}
  temp=temp-1;
  return temp;
}
void sendmusic(int file1, int file2)
{
  Wire.beginTransmission(5);  // transmit to device #5
  Wire.write(file1);
  Wire.write(file2);
  // sends one byte
  Wire.endTransmission(); 
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
