#include <HX711.h>
#define DOUT  4
#define CLK  3
#define rl  7
HX711 scale;
float calibration_factor = -1240;
float temp_wt;
float w_g;
byte statusLed    = 13;

byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 7.5;

volatile byte pulseCount;  

//float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;
SoftwareSerial s(5,6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  Serial.println("HX711 calibration sketch");
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
  
  long zero_factor = scale.read_average(); //Get a baseline reading
  scale.set_scale(calibration_factor);
  Serial.print("Zero factor: "); 
  Serial.println(zero_factor);
  Serial.print("calibration_factor: ");
  Serial.print(calibration_factor);
attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

void loop() {
  
  
  //;
  f1=(flowRate() / 60) * 1000;
  delay(500);
  f2=(flowRate() / 60) * 1000;
  if(f2>f1)// Only process counters once per second
  { 
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
    oldTime = millis();
    flowMilliLitres = (flowRate() / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
    pulseCount = 0;
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
  else if(f2==0)
  {   w_g=0;
  for(int i=0;i<10;i++)
  {
    temp_wt=scale.get_units();
    temp_wt/=3.61;
    w_g+=temp_wt;    
  }
   w_g/=10;
   delay(500);
   pinMode(7,HIGH);
   delay(2000);
   pinMode(7,LOW);
   attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
   float weight=w_g;
   float vol=totalMilliLitres;
   char w[10];
   char v[10];
   st=" ";
  st="";
  dtostrf(weight,4,2,w);
  dtostrf(vol,4,2,v);
  String colour2=",";
  
  String war=st+colour1+weight+vol+st;

if(s.available()>0)
{
 s.write(war);
}
   
  }
}
float flowRate()
{
return (((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor);
}
