#include <LiquidCrystal.h> // includes the LiquidCrystal Library
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 
const int trigPin = 8; // Ultrasonic Sensor
const int echoPin = 9;
const int ledPin =  7;      // the number of the LED pin
const int buttonPin = 6;     // pushbutton pin
long duration;
int distance;
int thresh [5]= {24,18,12,6,0}; // Limits
int buttonState = 0;         // variable for reading the pushbutton status
void setup() {
lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(115200);
}

void loop() {
    buttonState = digitalRead(buttonPin);
     if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("---100% Full--- ");
    lcd.setCursor(0,0);
    lcd.print("                ");
    delay(1000);
  } else {
    // turn LED off:
    
    digitalWrite(ledPin, LOW);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
}
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
lcd.setCursor(0,0);
lcd.print("                ");
lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
lcd.print("Distance: "); // Prints string "Distance" on the LCD
lcd.print(distance); // Prints the distance value from the sensor
lcd.print(" cm");
delay(10);
if(distance<thresh[0]&&distance>=thresh[1]){
    Serial.print(" 25% Full");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print (" 25% Full");
    digitalWrite(ledPin, LOW);   
    }
  else if(distance<thresh[1]&&distance>=thresh[2]){
    Serial.print(" 50% Full");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(" 50% Full");
    digitalWrite(ledPin, LOW);
  }
  else if(distance<thresh[2]&&distance>=thresh[3]){
    Serial.print(" 75% Full");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(" 75% Full");
    digitalWrite(ledPin, LOW);
  }
  else if(distance<thresh[3]&&distance>=thresh[4]){
    Serial.print(" 100% Full");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(" 100% Full");
    digitalWrite(ledPin, HIGH);
  }
  else{
    Serial.print(" Empty"); // Empty will print if you take the sensor out of the bin or the sensor is not getting a reading
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(" Empty");
    digitalWrite(ledPin, LOW);
  }
  Serial.println();
  delay(1000);
}
