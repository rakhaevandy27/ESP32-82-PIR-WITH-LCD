
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


const int trigPin = 9;
const int echoPin = 8;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
#define ledr 3
#define ledg 2
#define relay 4


long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledr,OUTPUT);
  pinMode(ledg,OUTPUT);
  pinMode(relay,OUTPUT);
  lcd.begin();
  lcd.backlight();
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = (duration*SOUND_VELOCITY)/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  Serial.println("----------------");
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);

  //print on lcd
  lcd.setCursor(0,0);
  lcd.print("(cm)   :  ");
  lcd.print(distanceCm);
  lcd.setCursor(0, 1);
  lcd.print("(inch) :  ");
  lcd.print(distanceInch);

  if(distanceCm < 30 || distanceCm <= 50){
    digitalWrite(relay,LOW);
    delay(5);
    digitalWrite(relay,HIGH);
    delay(5);
  }
  else{
    digitalWrite(relay,HIGH);
  }

  delay(100);
}