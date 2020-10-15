#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Initialize custom serial for DFPlayer (RX, TX).
SoftwareSerial mySoftwareSerial(2, 3);

// Initialize DFPlayer
DFRobotDFPlayerMini myMP3Player;

int evenNumberList[4] = {2, 4, 6};
int oddNumberList[4] = {1, 3, 5};
int randomNumber;

const uint8_t trigPin = 7;
const uint8_t echoPin = 5;
const uint8_t pirPin = 8; 
int pirSensor;
long duration;
int distance;

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pirPin, INPUT);

  Serial.println();
  Serial.println(F("Initializing DFPlayer..."));

  //Use softwareSerial to communicate with MP3
  if (!myMP3Player.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  
  Serial.println(F("DFPlayer Mini online."));

  randomSeed(analogRead(0));

  //Set volume value (From 0 to 30)
  myMP3Player.volume(30);
  
  myMP3Player.loop(7);
  
}

void findDistance() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance = duration * 0.034 / 2;
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("[Exit] Ultrasonic Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(50);
}

void loop() {
  
  pirSensor = digitalRead(pirPin);
  findDistance();
  
  if(pirSensor == HIGH){
    Serial.println("Masuk");
    randomNumber = random(0, 3);
    myMP3Player.advertise(oddNumberList[randomNumber]);
    switch (oddNumberList[randomNumber]) {
      case 1:
        delay(18000);
        break;
      case 3:
        delay(11000);
        break;
      case 5:
        delay(10000);
        break;
    }
  }
  
  if (distance < 9) {
    Serial.println("Keluar");
    myMP3Player.advertise(evenNumberList[random(0, 3)]);
    delay(5000);
  }

}
