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
  
  
  //
  Serial.println(w_g);
  w_g/=10;
  Serial.println(w_g);
  f1=flowrate();
  delay(500);
  f2=flowrate();
     if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
    oldTime = millis();
    flowMilliLitres = (flowRate() / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
    unsigned int frac;
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate()));  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point
    // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
    frac = (flowRate - int(flowRate())) * 10;
    Serial.print(frac, DEC) ;      // Print the fractional part of the variable
    Serial.print("L/min");
    // Print the number of litres flowed in this second
    Serial.print("  Current Liquid Flowing: ");             // Output separator
    Serial.print(flowMilliLitres);
    Serial.print("mL/Sec");
    Serial.print("  Output Liquid Quantity: ");             // Output separator
    Serial.print(totalMilliLitres);
    Serial.println("mL"); 
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
   float green=2.43;
  float blue=3.21;
  char colour1[10];
  char colour3[10];
  st="";
  dtostrf(green,4,2,colour1);
  dtostrf(blue,4,2,colour3);
  String colour2=",";
  
  String war=st+colour1+colour2+colour3;
  Serial.println(war);
  }
}
float flowRate()
{
return (((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor);
}
