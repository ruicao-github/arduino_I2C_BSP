#include <Wire.h>
//#include <String.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #10
  Wire.onReceive(receiveEvent); // interupt function.
  Wire.onRequest(requestEvent); // interupt function. If the request is received from the master, the interupt will be invoked.
  Serial.begin(9600);  // start serial for output
}

int x;
int y;
void loop() {
  delay(100);
}


void requestEvent() {
  Serial.println("reply");
  y=x;
  Wire.write(y); 
}

void receiveEvent()
{
  while(Wire.available())    // slave may send less than requested
  {
    x = Wire.read(); 
    Serial.println(x);
  }
 
}
