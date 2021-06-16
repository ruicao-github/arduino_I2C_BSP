#include <Wire.h>
#include <String.h>
#include <Array.h>
//https://www.arduino.cc/reference/en/libraries/array/

void setup() {
  Wire.begin(10);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // interupt function.
  Wire.onRequest(requestEvent); // interupt function. 
  //Serial.begin(9600);  // start serial for output and debuging
}

unsigned long diff=0;
const int ELEMENT_COUNT_MAX = 20; //max buffer size for storing detection messages
Array<String,ELEMENT_COUNT_MAX> buffer_;
union unsignLong
{
   unsigned long longNumber;
   byte longBytes[4];
} time_;

int x; //message request index received from the master.
// 0: asking how many detection does the slave detect.
//other positive int: request for the detection message of that index. (imagine the detection message is stored in an array)

void loop() {
  generateRandomMessageAndStoreInBuffer();
  delay(500);
}


void generateRandomMessageAndStoreInBuffer(){
  int rand_n=random(10); //random ID for new detection message
  char time_zero_padded[10];
  sprintf(time_zero_padded,"%010d", millis()+diff);
  //Serial.println(time_zero_padded);
  if(rand_n<5) buffer_.push_back((String)"Message" + rand_n + ' '+time_zero_padded);  
}

int buffer_size;
void requestEvent() {
  if(x==0){
    buffer_size=buffer_.size();
    Wire.write(buffer_size); // reply that how many IDs have been detected (stored in buffer)
    return;
  }
//  else{
//    Serial.println((String)"send message "+x);
//  }

  Wire.write(buffer_[x-1].c_str());
  if(x==buffer_size) buffer_.clear();
}

void receiveEvent()
{
  int j=0;
  while(Wire.available())    // slave may send less than requested
  {
    time_.longBytes[j] = Wire.read();
    j++;    
  }
  if(j==1) x=(int)time_.longBytes[0]; // read the message request index
  else diff=time_.longNumber-millis();
  //Serial.println((String)"message index requested is "+x);
  
}
