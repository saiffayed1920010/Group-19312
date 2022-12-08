#include "HX711.h" // define the library of the module
#define LOADCELL_DOUT_PIN  2 // define the ESP pins
#define LOADCELL_SCK_PIN  4 // define the ESP pins
HX711 scale;
float calibration_factor = -208560.00; // define the calibration factor
// -208560.00 for kilogram
// -226 for gram

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // reading of the load cell
  scale.set_scale();
  scale.tare();	//Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  Serial.print(scale.get_units()*-1, 1);
  Serial.print(" Kg"); //Change this to g and re-adjust the calibration factor
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())  // for editing the calibration factor
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1000;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1000;
  }
}
