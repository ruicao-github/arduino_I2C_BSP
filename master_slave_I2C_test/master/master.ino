// Wire Master Reader (I2C)
// The master reader will work with the slave sender.


#include <Wire.h> 
// wire is the I2C library for arduino
// more information can be found at https://www.arduino.cc/en/Reference/Wire

void setup() {
  Wire.begin();        // join i2c bus (master do not need to specify the address)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  // add 3 slaves, each will send a message to the master at regular interval
  add_slave_and_print_message(8,3);
  add_slave_and_print_message(9,3);
  add_slave_and_print_message(10,3);
}


// Instead of writing out the sub-routine for every slave, I condense it into a reusable function.
// this function will initialize the reader for a specific slave
// the address of the slave and the length of the message (byte_limit) will be the input to the function

void add_slave_and_print_message(int address, int bytes_limit){
  Wire.requestFrom(address,bytes_limit);    // initialuze the reader
  // a length limit will be set. The part of the message that exceeds the length of the length limit will
  // be discarded. Each ASCI character will take 1 byte.
  // for example, for a limit of 3 byte, if the slave sender sends a message "complete", only "com" will be
  // by the master.

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  delay(500);
}
