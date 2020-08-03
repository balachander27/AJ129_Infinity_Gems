#include <HX711.h>
#define DOUT  4
#define CLK  3
HX711 scale;
float calibration_factor = -1240;
float temp_wt;
float w_g;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  
  long zero_factor = scale.read_average(); //Get a baseline reading
  scale.set_scale(calibration_factor);
  Serial.print("Zero factor: "); 
  Serial.println(zero_factor);
  Serial.print("calibration_factor: ");
  Serial.print(calibration_factor);

}

void loop() {
  
  
  
  w_g=0;
  for(int i=0;i<10;i++)
  {
    temp_wt=scale.get_units();
    temp_wt/=3.61;
    w_g+=temp_wt;    
  }
  Serial.println(w_g);
  w_g/=10;
  Serial.println(w_g);
  
 
  

}
