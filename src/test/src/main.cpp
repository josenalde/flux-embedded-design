#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);
int result;
void setup() {
  // put your setup code here, to run once:
  result = myFunction(2, 3);
  Serial.begin(9600);
  Serial.println(result);
}

void loop() {
  Serial.println(result);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}