// include the library code:
#include <LiquidCrystal.h>

#define NUMBER 16

int inByte = 0;         // incoming serial byte
int sensorValue=0;
int sensorValues[NUMBER];
int sensorValueSum;
int currentNumber=0;
int i, valuesNumber;
float tempc=0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(P2_3, P2_4, P2_0, P1_5, P1_4, P1_3);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("t=  .  C");
  
  lcd.setCursor(0, 1);
  // initialize the digital pin as an output.
  pinMode(P1_0, OUTPUT);     
  pinMode(P1_6, OUTPUT);     

  analogReference(INTERNAL1V5);
  analogRead(TEMPSENSOR); // first reading usually wrong

  Serial.begin(9600);
  
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
  
  sensorValue = analogRead(TEMPSENSOR);  
  sensorValues[currentNumber] = sensorValue;
  if (currentNumber++ >= NUMBER) {currentNumber = 0;}
  
  sensorValueSum = 0;
  valuesNumber = 0;
  for (i=0;i<NUMBER;i++)
  {
    if (sensorValues[i]!=0)
    {
      sensorValueSum += sensorValues[i];
      valuesNumber++;
    }
  }
  
  sensorValue  = sensorValueSum / valuesNumber;
  //tempc = ((float)sensorValue - 673)*422,53/1023;
  tempc = ((float)sensorValue - 673)*15/36,352;

  if (Serial.available() > 0) {
    // get incoming byte:
    //inByte = Serial.read();
    //Serial.write(inByte);
    ;
  }



  Serial.print("t=");
  Serial.print(tempc);
  Serial.print("\n");

  lcd.setCursor(2, 0);
  lcd.print(tempc);
  
  digitalWrite(P1_0, HIGH);   // set the LED on
  digitalWrite(P1_6, LOW);    // set the LED off
  delay(200);              // wait for a second
  digitalWrite(P1_0, LOW);    // set the LED off
  digitalWrite(P1_6, HIGH);   // set the LED on
  delay(200);              // wait for a second
}


