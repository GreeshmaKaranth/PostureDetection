#include "MPU9250.h"
#include <math.h>
#include <SPI.h>  
#define buzzer 12

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;
int LED1 = 3; // Red
int LED2 = 4; // Green
int LED3 = 5; // White
int buzzstate = 0;

void setup() {
  Serial.begin(9600);
  //pinMode(5, OUTPUT);
  // serial to display data
  //Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);

  pinMode(LED1, OUTPUT); // Red
  pinMode(LED2, OUTPUT); // Green
  pinMode(LED3, OUTPUT); // Yellow
  
  digitalWrite(LED1,LOW); // Red
  digitalWrite(LED2,LOW); // Green
  digitalWrite(LED3,LOW); // Yellow

  pinMode(buzzer, OUTPUT); // Buzzer
  digitalWrite(buzzer, 0);
}

void loop() {
 // read the sensor
 // IMU.readSensor();
  char data;
  if(Serial.available()>0){
    data= Serial.read();
    while(data!='0'){
      IMU.readSensor();
    //switch(data){
      
     // case 'a': 
        //IMU.readSensor();
        digitalWrite(5, LOW);
        if(IMU.getAccelZ_mss()>=0 && IMU.getAccelZ_mss()<3.5){
        Serial.print("Good posture\n");
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(buzzer, 0);
        buzzstate = 0;
      }
        else if((IMU.getAccelZ_mss()>=3.5 && IMU.getAccelZ_mss()<6.0))
         {
          Serial.print("Okay Posture\n");
          digitalWrite(LED1, HIGH);
          digitalWrite(LED2, LOW);
          digitalWrite(LED3, LOW);
          digitalWrite(buzzer, 0);
          buzzstate = 0;
        }
        else if(IMU.getAccelZ_mss()>=6.0 || IMU.getAccelZ_mss()<=-2){
          Serial.print("Bad posture\n");
          digitalWrite(LED1, LOW);
          digitalWrite(LED2, HIGH);
          digitalWrite(LED3, LOW);
          if(!buzzstate)
           { delay(5000);}
          digitalWrite(buzzer, 1);
          buzzstate = 1;
        }
        delay(1000);
        //break;
          if(Serial.available()>0){
            data= Serial.read();
          }
    }
  // case 'd': 
      //IMU.readSensor();
//      if(data=='d'){
//        digitalWrite(LED1, LOW);
//        digitalWrite(LED2, LOW);
//        digitalWrite(LED3, LOW);
//        digitalWrite(buzzer, 0);
//      }
      
      //break;
      
    //default: break;
    
    
    if(data=='0'){
      Serial.println("Device switched off.\n");
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(buzzer, 0);
    }
  }
   //Serial.println(data);
}
