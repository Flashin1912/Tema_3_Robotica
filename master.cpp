#include <SPI.h>
#include <LiquidCrystal.h>
#include <Servo.h>


//LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(8, 3, 7, 6, 5, 4);
const int ButonStart = 2;
int roundStart = 0;
volatile int receivedData;
int i = 1;


Servo myServo;

const int slaveSelectPin = 10;

void setup() {
  Serial.begin(9600); 
  pinMode(ButonStart, INPUT_PULLUP);
  lcd.begin(16, 2);  // LCD pe 16 coloane si 2 randuri
  lcd.print("Bun venit!");
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.attachInterrupt();
  pinMode(slaveSelectPin, OUTPUT);   
  //digitalWrite(slaveSelectPin, HIGH);
  myServo.attach(9);
  myServo.write(0);
}

ISR(SPI_STC_vect) {
  // Read received data from Master
  receivedData = SPDR;
}

void loop() {
  lcd.setCursor(0, 1); 
  
  digitalWrite(SS, LOW);       
  //byte receivedData = SPI.transfer(0x00); 
 
  if(digitalRead(ButonStart) == LOW && roundStart == 0)
  {
    lcd.print ("Start!");
    roundStart = 1;
    delay(100);
  }
  if(roundStart == 1)
  {
    i = (i==179 ? 0 : i+1);
    myServo.write(i*10);
    delay(1000);
    
  }
  else
  {
    delay(100);
  }
  digitalWrite(SS, HIGH); 
} 
