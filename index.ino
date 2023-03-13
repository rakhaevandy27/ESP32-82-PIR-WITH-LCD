
#include <LiquidCrystal_I2C.h> //inlude library for LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); //initial,addres,hpx,wpx


const int trigPin = 9; //trigger pin
const int echoPin = 8; //echo pin

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
#define ledr 3 //define led red on GPIO 3
#define ledg 2 //define led green on GPIO 2
#define relay 4 //define relay on GPIO 4 (OPTIONAL)


long duration; //variable for time
float distanceCm; //variable for distance on CM(Centi Meter)
float distanceInch; //variable for distance on INCH

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledr,OUTPUT); // Sets the red led as an Output
  pinMode(ledg,OUTPUT); // Sets the green led as an Output
  pinMode(relay,OUTPUT); // Sets the relay as an Output
  lcd.begin(); //lcd begin or starting the module //sometimes other library version use lcd.begin(16,2)
  lcd.backlight(); //turn on lcd led backlight
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

  //logic function for executing 
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
