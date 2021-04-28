#include <Wire.h>
#include <String.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #10
  Wire.onReceive(receiveEvent); // interupt function.
  Wire.onRequest(requestEvent); // interupt function. 
  Serial.begin(9600);  // start serial for output and debuging
}

int x; //message request index received from the master.
// 0: asking how many detection does the slave detect.
//other positive int: request for the detection message of that index. (imagine the detection message is stored in an array)

void loop() {
  delay(100);
}


void requestEvent() {
  if(x==0){
    Wire.write(3); // reply that 3 ID has been detected
    return;
  }
  else{
    Serial.println((String)"send message "+x);
  }
  String message="Message";
  message=message + x + ' '; //send the detection message of that message index
  Wire.write(message.c_str()); 
}

void receiveEvent()
{
  x = Wire.read(); // read the message request index
  Serial.println((String)"message index requested is "+x);
  
}
