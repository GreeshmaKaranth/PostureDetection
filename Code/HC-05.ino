#include<SoftwareSerial.h> 
SoftwareSerial EEBlue(10, 11); // RX | TX 
//
void setup() { 
  Serial.begin(9600); 
  EEBlue.begin(9600); //Default Baud for comm, it may be different for your Module. 
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!."); 
} 
  
  void loop() { // Feed any data from bluetooth to Terminal. 
    if (EEBlue.available()) Serial.write(EEBlue.read()); // Feed all data from termial to bluetooth 
    if (Serial.available()) EEBlue.write(Serial.read()); 
}
//
//#define ledPin 5
//int state = 0;
//void setup() {
//  Serial.begin(38400);
//  pinMode(ledPin, OUTPUT);
//  digitalWrite(ledPin, LOW);
//   // Default communication rate of the Bluetooth module
//}
//void loop() {
//  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
//    state = Serial.read(); // Reads the data from the serial port
// }
// if (state == 'a') {
//  digitalWrite(ledPin, LOW); // Turn LED OFF
//  Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
//  state = 0;
// }
// else if (state == 'b') {
//  digitalWrite(ledPin, HIGH);
//  Serial.println("LED: ON");
//  state = 0;
// } 
//}

//
//void setup(){
//  Serial.begin(9600);
//  pinMode(5, OUTPUT);
//}
//
//void loop(){
//  if(Serial.available()>0){
//    char data= Serial.read();
//    switch(data){
//      case 'a': digitalWrite(5, LOW);break;
//      case 'd': digitalWrite(5, HIGH);break;
//      default: break;
//    }
//    Serial.println(data);
//  }
//  delay(50);
//}
