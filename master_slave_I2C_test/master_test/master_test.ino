// Wire Master Reader (I2C)
// The master reader will work with the slave sender.


#include <Wire.h>
#include <String.h>
// wire is the I2C library for arduino
// more information can be found at https://www.arduino.cc/en/Reference/Wire

void setup() {
  Wire.begin();        // join i2c bus (master do not need to specify the address)
  Serial.begin(9600);  // start serial output for debuging (otherwise Serial.print will not work)
}

int n_slaves=3; //define available number of slaves
void loop() {  //loop through the communication with each slave
  for(int i=0;i<n_slaves;i++){
    //Serial.println((String)"loop "+i+" ");
    communication(i);
  }
  delay(500);
}

void communication(int i){ //function that handles the communication
  int slave_address=i+8; //slave address starts at 8
  Serial.println((String)"slave_address "+slave_address+" ");
  Wire.beginTransmission(slave_address);
  Wire.write(0); //0 is the code for asking slave, how many new ID does it detect.
  Wire.endTransmission();
  Wire.requestFrom(slave_address, 1); //read the answer from slave (how many new ID does it detect)
  int c = Wire.read(); 
  if(c==0) return; //return if no detection. move on to the next slave.
  else{
    int number_of_detection=c;
    Serial.println((String)"number_of_detection " + number_of_detection);
    for(int j=1;j<=number_of_detection;j++){ //loop to request for each detection message
      Wire.beginTransmission(slave_address);
      Wire.write(j); //send the request that the master want the jth message
      Wire.endTransmission();
      Wire.requestFrom(slave_address, 9); //read the message returned from the slave
      while (Wire.available()) { // slave may send less than requested
        char d = Wire.read(); // receive a byte as character
        Serial.print(d);         // print the message
      }
      Serial.println();
    }
  }
  
}
