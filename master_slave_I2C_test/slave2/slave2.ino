#include <Wire.h>
#include <String.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #10
  Wire.onReceive(receiveEvent); // interupt function.
  Wire.onRequest(requestEvent); // interupt function. If the request is received from the master, the interupt will be invoked.
}

int message_index=0;

void loop() {
  delay(100);
}


void requestEvent() {
  c1+=1;
  String message="Message";
  message=message + message_index + ' ';
  Wire.write(message.c_str()); 
}

void receiveEvent()
{
  c2+=1;
  int x = (int)Wire.read()-77; // receive byte as a character
  if(x==0){
    Wire.write(3);
  }
  else{
  message_index=x;
  }
}
