//on 27-05-2019(Amlan)
//single axis stepper stage,x value 400 per mm length,


const int stepPin = 3;             //CLK+
const int dirPin = 5;             //CH+
const int swPin = 13;            //limit Switch
const int TravelLength = 200;    // max travel length of stage = 200 mm,
const int SampleLength = 10;    // in mm 


long CenteringPulses;
long MovementPulses;

void setup() {
  
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(swPin,INPUT);  //limit Switch
  Serial.begin(9600);
   CenteringPulses = (TravelLength+SampleLength)*200L; //L for long
   MovementPulses = (SampleLength*400L); //L for long
  
}
void loop() {
   // Homing
    Serial.println("HOMING");
    while (digitalRead(swPin) == LOW) {
      digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
       for(long x = 0; x < 1200; x++) // Makes 200 pulses for making one full cycle rotation
       { digitalWrite(stepPin,HIGH); 
         delayMicroseconds(50); // increasing delayMicroseconds Decreases RPM
         digitalWrite(stepPin,LOW); 
         delayMicroseconds(50); // increasing delayMicroseconds Decreases RPM
                                  }
    }
     delay(200);
  

  // going to center
   Serial.println("CENTERING");
    digitalWrite(dirPin,LOW);  
    for(long x = 0; x < CenteringPulses ; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(50); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(50); }
    delay(200);
 
  //looping for +X & -X
  for(int i = 0; i<3; i++){
   //+X DIRECTION 
    Serial.println("+X DIRECTION");
    digitalWrite(dirPin,HIGH); 
    for(int x = 0; x < MovementPulses; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(50); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(50); 
     }
  delay(100);
   //-X DIRECTION
   Serial.println("-X DIRECTION");
   digitalWrite(dirPin,LOW); 
    for(int x = 0; x < MovementPulses; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(50);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(50);    
  }
   delay(100);
 }
}
