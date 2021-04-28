// Wire Master Reader (I2C)
// The master reader will work with the slave sender.


#include <Wire.h>
#include <String.h>
// wire is the I2C library for arduino
// more information can be found at https://www.arduino.cc/en/Reference/Wire

void setup() {
  Wire.begin();        // join i2c bus (master do not need to specify the address)
  Serial.begin(9600);  // start serial for output
}

int n_slaves=1;
String mes=" ";
void loop() {
  for(int i=0;i<n_slaves;i++){
    Serial.println((String)"loop "+i+" ");
    communication(i);
  }
  delay(500);
}

void communication(int i){
  int slave_address=i+8;
  Serial.println((String)"slave_address "+slave_address+" ");
  Wire.beginTransmission(slave_address);
  Wire.write(0); //0 is the code for asking slave, how many new ID does it detect.
  Wire.endTransmission();
  Wire.requestFrom(slave_address, 1);
  char c = Wire.read(); 
  if(c=="0") return;
  else{
    int number_of_detection=(int)c-77;
    String m="number_of_detection " + number_of_detection + ' ';
    Serial.println(number_of_detection);
    for(int j=1;j<=number_of_detection;j++){
      Wire.beginTransmission(slave_address);
      Wire.write(j);
      Wire.endTransmission();
      Wire.requestFrom(slave_address, 9);
      while (Wire.available()) { // slave may send less than requested
        char d = Wire.read(); // receive a byte as character
        Serial.print(d);         // print the character
      }
    }
  }
  
}
