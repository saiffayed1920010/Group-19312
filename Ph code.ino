const int potPin=34;
float ph;
float Value=0;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(potPin,INPUT);
  delay(1000);
}




 void loop(){ 

 
    Value= analogRead(potPin);
    /*Serial.print(Value);
    Serial.print(" | ");*/
    float voltage=Value*(3.3/4095.0);
    ph=(3.3*voltage);
    Serial.print("ph Val = ");
    
    
    
    
    
    
    Serial.println(ph*1.14);
    //delay(1000);
 }