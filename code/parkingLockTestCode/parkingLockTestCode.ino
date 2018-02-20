#include  "ParkingLock.h"
int testVals[50]= {1,2,3,4,5,
                6,7,7,7,7,
                7,7,7,7,7,
                7,6,5,4,3,
                2,1,1,1,1,
                2,3,4,5,6,
                7,8,8,8,8,
                8,8,8,8,8,
                8,7,6,5,4,
                1,1,1,1,1};
int freq = 100;       //100hz
int windowTime = 100; //100ms window size, which corresponds to 10 calls
int tol = 3;
int processedOut = 0;
ParkingLock test1 = ParkingLock(freq, windowTime, tol);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("-- initialized --");
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<50; i++) {
    processedOut = test1.processParkingLock(testVals[i]);
    Serial.print(testVals[i]);
    Serial.print("\t");
    Serial.println(processedOut);
    delay(200);
  }
  delay(3000);
}
