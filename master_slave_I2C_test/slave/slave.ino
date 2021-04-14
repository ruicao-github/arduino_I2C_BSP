#include <Wire.h>

void setup() {
  Wire.begin(10);                // join i2c bus with address #10
  Wire.onRequest(requestEvent); // interupt function. If the request is received from the master, the interupt will be invoked.
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("S3 "); // respond with message of 3 bytes
}
