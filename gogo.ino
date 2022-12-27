 
#include "Adafruit_GFX.h"    // Core graphics library
#include "Adafruit_TFTLCD.h" // Hardware-specific library
#include "TouchScreen.h"

#include "MCUFRIEND_kbv.h"
#include <TEA5767.h>
#define light A9
TEA5767 radio = TEA5767();

float frequency = 98.2; //Enter your own Frequency
long baud = 115200; //Enter your own Baudrate
bool muted = false;
long lmillis = 0;
#define light A9
 // Pin assignments for the TFT touch screen  
 #define YP  A1  
 #define XM  A2  
 #define YM  7  
 #define XP  6  
 // Calibrated values for the TFT touch screen   
 #define TS_MINX  178  
 #define TS_MINY  75  
 #define TS_MAXX  931  
 #define TS_MAXY  895  
 // Instantiate the ts object  
 TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);  
 #define LCD_RD  A0  
 #define LCD_WR  A1  
 #define LCD_CD  A2  
 #define LCD_CS  A3  
 #define LCD_RESET A4  
 // Instantiate the tft object  
 MCUFRIEND_kbv tft;

 // Assign human-readable names to some common 16-bit color values:  
 #define BLACK  0x0000  
 #define BLUE  0x001F  
 #define RED   0xF800  
 #define GREEN  0x07E0  
 #define CYAN  0x07FF  
 #define MAGENTA 0xF81F  
 #define YELLOW 0xFFE0  
 #define WHITE  0xFFFF  
 #define BOXSIZE   40  
 #define PENRADIUS  3  
 #define MINPRESSURE 1
 #define MAXPRESSURE 1000  
 #define LED_PIN   A5  
 int touch = 0;  
 void setup() {  
  pinMode(LED_PIN, OUTPUT);  
  digitalWrite(LED_PIN, LOW);  
  Serial.begin(9600);  
  tft.reset();  
  tft.fillScreen(BLACK);
  tft.begin(0x7789);  
  tft.setRotation(2); // This settings works for me with correct orientation  
            // tft.setRotation(2);  
  tft.setTextColor(WHITE);  
  tft.setTextSize(1);  
  tft.fillScreen(BLACK);  
  tft.fillRect(0, 0, 1000, 120, GREEN);  
  tft.fillRect(0, 120, 1000, 120, RED);  
  tft.setCursor(15, 45);  
  tft.println("freq +");  
  tft.setCursor(128, 45);  
  tft.println("freq -");  
  tft.setTextColor(WHITE, BLACK);  
  tft.setTextSize(2);  
    //Setup Serial and I2C
  Serial.begin(baud);
  Wire.begin();
  radio.setStereoNC(1);
  //Set Frequency to start with
  radio.setFrequency(frequency);
  pinMode(light, INPUT);  // put your setup code here, to run once:
  pinMode(36, OUTPUT); 
  pinMode(38, OUTPUT); 

 }  
 void loop() {  
  // Get the touch points  
  TSPoint p = ts.getPoint();  
  // Restore the mode  
  pinMode(XM, OUTPUT);  
  pinMode(YP, OUTPUT);  
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {  
   p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());  
   p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());  
   // Touch area for box 1  
   if (p.x > 0 && p.x < 120) {  
    if (p.y > 0 && p.y < 120) {  
     touch ++;  
    }  
   }  
   // Touch area for box 2  
   if (p.x > 120 && p.x < 240) {  
    if (p.y > 0 && p.y < 120) {  
     touch --;  
    }  
   }  
  }
  
  if (touch >= 1) {  
   digitalWrite(LED_PIN, HIGH);  
   tft.setCursor(100,200);  
   tft.print(touch);  
 
   delay(100);  
  } 
   delay(500); 
Serial.print("------x--------");
Serial.println(p.x);  

 delay(500); 
Serial.print("-------y---------");
Serial.println(p.y);  
Serial.println(ts.readTouchY());
shit();

if(ts.readTouchY() != 1023){

if(ts.readTouchY() < 820){
  Serial.println("0");
  touch = 6;
  if(muted){
   radio.setMuted(false);
   muted = false;
  }
  else{
    radio.setMuted(true);
muted = true;
  }
}

if(ts.readTouchY()>  820 && ts.readTouchY() < 918){
  Serial.println("- freq");
  frequency = 100.6;
  touch = 100;
  radio.setMuted(false);
    radio.setFrequency(frequency);
}
else{
  if(ts.readTouchY() > 930 && ts.readTouchY() < 990){
  Serial.println(" + freq ");
  frequency = 98.2;
  touch = 98;
  radio.setMuted(false);
    radio.setFrequency(frequency);
  }
}
}

  // Process the touch in box 1  
  // /Serial.println( "y" p.y);  / Process the touch in box 2  
     
  if (touch <= 2) {  
   digitalWrite(LED_PIN, LOW);  
   tft.setCursor(100,200);  
   tft.print(touch);  
   
   delay(100);  
  }  
    //Check for User Input
  if(Serial.available()){
    float frequency = Serial.parseFloat(); //Read Frequency from Serial
    radio.setFrequency(frequency); //Set Frequency
  }
  
  //Check for time (active every second
  if(lmillis <= millis()){
    lmillis = millis() + 1000; //Read current time and add 1 second
    
	//Print Stats to Serial Console
  
  
  }

  
  
 }  

 void printFrequency(){
  float frequency = radio.getFrequency(); //Get Frequency
  Serial.print("Frequency: ");
  Serial.println(frequency, 2);
}

void printReady(){
  int rdy = radio.getReady(); //Get State
  Serial.print("Ready: ");
  Serial.println(rdy);
}

void printStereo(){
  bool stereo = radio.isStereo(); //Get Stereo
  Serial.print("Stereo: ");
  Serial.println(stereo);
}

void printSignalLevel(){
  short level = radio.getSignalLevel(); //Get Signal Level
  Serial.print("Signal (0-15): ");
  Serial.println(level);
}

void shit() {
  Serial.println(analogRead(light));
  if(analogRead(light) < 500){
    digitalWrite(36,HIGH);
    digitalWrite(38,HIGH);
  }
  else{
    digitalWrite(36,LOW);
    digitalWrite(38,LOW);
  }

}

