#include <SPI.h>

const int buttonPin = A0; 
const int led1R = 7;    
const int led1G = 6;    
const int led1B = 5;    
const int led2R = 4;    
const int led2G = 3;    
const int led2B = A5;

const int RGB1_R = A1;
const int RGB1_G = A2;
const int RGB1_B = A3;
const int RGB2_R = A4;
const int RGB2_G = 9;
const int RGB2_B = 8;

volatile int receivedData = 0;
volatile byte buttonPressed = 0;
int activeButton = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(led1R, OUTPUT);
  pinMode(led1G, OUTPUT);
  pinMode(led1B, OUTPUT);
  pinMode(led2R, OUTPUT);
  pinMode(led2G, OUTPUT);
  pinMode(led2B, OUTPUT);
  
  
  pinMode(10, INPUT);
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.attachInterrupt();
  //attachInterrupt(digitalPinToInterrupt(2), sendButtonPress, FALLING);
  
}

void loop() {
  volatile int temp = analogRead(buttonPin);  
  Serial.println(temp);  
  
  if (buttonPressed != 0) {
    SPDR = buttonPressed;
    buttonPressed = 0;   
  }
  
  if (temp < 50)                    
  {
    digitalWrite(led1G, LOW);
    digitalWrite(led1R, LOW);
    digitalWrite(led1B, LOW);
    digitalWrite(led2G, LOW);
    digitalWrite(led2R, LOW);
    digitalWrite(led2B, LOW);
  }
  else if (temp < 100)               
  {
    digitalWrite(led1G, LOW);
    digitalWrite(led1R, HIGH);
    digitalWrite(led1B, LOW);
    digitalWrite(led2G, LOW);
    digitalWrite(led2R, LOW);
    digitalWrite(led2B, LOW);
    sendButtonPress(1);
  }
  else if (temp < 150)               
  {
    digitalWrite(led1G, HIGH);
    digitalWrite(led1R, LOW);
    digitalWrite(led1B, LOW);
    digitalWrite(led2G, LOW);
    digitalWrite(led2R, LOW);
    digitalWrite(led2B, LOW);
    sendButtonPress(2);
  }
  else if (temp < 210)               
  {
    digitalWrite(led1G, LOW);
    digitalWrite(led1R, LOW);
    digitalWrite(led1B, HIGH);
    digitalWrite(led2G, LOW);
    digitalWrite(led2R, LOW);
    digitalWrite(led2B, LOW);
    sendButtonPress(3);
  }
  else if (temp < 300)                
  {
    digitalWrite(led1G, LOW);
    digitalWrite(led1R, LOW);
    digitalWrite(led1B, LOW);
    digitalWrite(led2G, LOW);
    digitalWrite(led2R, HIGH);
    digitalWrite(led2B, LOW);
    sendButtonPress(4);
  }
  else if (temp < 500)
  {
    digitalWrite(led1G, LOW);
    digitalWrite(led1R, LOW);
    digitalWrite(led1B, LOW);
    digitalWrite(led2G, HIGH);
    digitalWrite(led2R, LOW);
    digitalWrite(led2B, LOW);
    sendButtonPress(5);
  }
  else                                
  {
    digitalWrite(led1G, LOW);
    digitalWrite(led1R, LOW);
    digitalWrite(led1B, LOW);
    digitalWrite(led2G, LOW);
    digitalWrite(led2R, LOW);
    digitalWrite(led2B, HIGH);
    sendButtonPress(6);
  }
  delay(100);                        
}

void setActiveLed() {
  if (activeButton == 1) {
    digitalWrite(led1G, LOW);
    digitalWrite(led1R, LOW);
    digitalWrite(led1B, LOW);
    digitalWrite(led2G, LOW);
    digitalWrite(led2R, LOW);
    digitalWrite(led2B, LOW);
  } else if (activeButton == 2) {
    digitalWrite(led1G, LOW);
    digitalWrite(led1R, LOW);
    digitalWrite(led1B, LOW);
    digitalWrite(led2G, LOW);
    digitalWrite(led2R, LOW);
    digitalWrite(led2B, LOW);
  } else {
    digitalWrite(led1G, LOW);
    digitalWrite(led1R, LOW);
    digitalWrite(led1B, LOW);
    digitalWrite(led2G, LOW);
    digitalWrite(led2R, LOW);
    digitalWrite(led2B, LOW);
  }
}

void sendButtonPress(int buttonNumber) {
  buttonPressed = buttonNumber;
}

ISR(SPI_STC_vect) {
  // Read received data from Master
  receivedData = SPDR;
}
