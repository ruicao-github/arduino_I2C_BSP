// Wire Master Reader (I2C)
// The master reader will work with the slave sender.


#include <Wire.h>
#include <String.h>
// wire is the I2C library for arduino
// more information can be found at https://www.arduino.cc/en/Reference/Wire

void setup() {
  Wire.begin();        // join i2c bus (master do not need to specify the address)
  Serial.begin(9600);
}

//int n_slaves=1;

void loop() {
  //for(int i=0;i<n_slaves;i++){
    //Serial.println((String)"loop "+i+" ");
    communication(0);
  //}
  delay(500);
}

void communication(int i){
  int slave_address=i+8;
  //Serial.println((String)"slave_address "+slave_address+" ");
  Wire.beginTransmission(slave_address);
  Wire.write(1); //0 is the code for asking slave, how many new ID does it detect.
  Wire.endTransmission();
  Wire.requestFrom(slave_address, 1);
  while (Wire.available()) { // slave may send less than requested
        int d = Wire.read(); // receive a byte as character
        Serial.print(d);         // print the character
  }
 
Serial.println();


  
}
