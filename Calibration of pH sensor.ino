const int potPin=34; // define out input pin in the ESP
float ph; // define variable
float Value=0; // define variable
 
void setup() {
  Serial.begin(9600);
  pinMode(potPin,INPUT);
  delay(1000);
}

 void loop(){ 
    Value= analogRead(potPin); // read the voltage 
    Serial.print(Value);
    Serial.print(" | ");
    float voltage=Value*(3.3/4095.0); // calibration the measured voltage
    ph=(3.3*voltage); // calculation the pH
    Serial.print("ph Val = ");
    Serial.println(ph); // print the pH value
    delay(1000);
 }
