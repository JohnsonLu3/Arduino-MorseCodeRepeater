#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <vector>;
using namespace std;

// LEDs
int RedLED = 12;
int GrnLED = 11;

// Buzzers
int Buzzer = 13;

// Buttons
int dotButton = 6;
int dshButton = 7;
int spcButton = 2;
int plyButton = 3;
int rstButton = 10;

// Delays and Frequencies
int buttonDelay = 200;
int dotDelay = 300;
int dotFreq = 450;
int dashDelay = 600;
int dashFreq = 450;
int spaceDelay = 200;

// Data
bool isPlaying = false;
vector<char> morseSeqence;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RedLED, OUTPUT);
  pinMode(GrnLED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(dotButton, OUTPUT);
  pinMode(dshButton, OUTPUT);
  pinMode(spcButton, OUTPUT);
  pinMode(plyButton, OUTPUT);
  pinMode(rstButton, OUTPUT);

  digitalWrite(RedLED, LOW);
  digitalWrite(GrnLED, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!isPlaying) {
    if (digitalRead(rstButton) == HIGH) {
      reset();
    }
    morseButtonCheck();
  }
  playButtonCheck(); 
}
void playButtonCheck() {
  if (digitalRead(plyButton) == HIGH) {
    Serial.println("Play Button Pressed");
    isPlaying = true;
    for (vector<char>::const_iterator i = morseSeqence.begin(); i != morseSeqence.end(); ++i) {
      switch (*i) {
        case '.':
          tone(Buzzer, dotFreq);
          digitalWrite(RedLED, HIGH);
          delay(dotDelay);
          digitalWrite(RedLED, LOW);
          noTone(Buzzer);
          break;
        case '-':
          tone(Buzzer, dashFreq);
          digitalWrite(GrnLED, HIGH);
          delay(dashDelay);
          digitalWrite(GrnLED, LOW);
          noTone(Buzzer);
          break;
        case ' ':
          delay(spaceDelay);
          break;
        default:
          break;

      }
      delay(50);
    }
    isPlaying = false;
    delay(buttonDelay);
  }
}

void reset() {
  morseSeqence.clear();
}

void morseButtonCheck() {
  if (digitalRead(dotButton) == HIGH) {
    Serial.println("Dot Button Pressed");
    morseSeqence.push_back('.');
    digitalWrite(RedLED, HIGH);
    delay(buttonDelay);
    digitalWrite(RedLED, LOW);
  } else {
    if (digitalRead(dshButton) == HIGH) {
      Serial.println("Dash Button Pressed");
      morseSeqence.push_back('-');
      digitalWrite(GrnLED, HIGH);
      delay(buttonDelay);
      digitalWrite(GrnLED, LOW);
    } else {
      if (digitalRead(spcButton) == HIGH) {
        Serial.println("Space Button Pressed");
        morseSeqence.push_back(' ');
        digitalWrite(GrnLED, HIGH);
        digitalWrite(RedLED, HIGH);
        delay(buttonDelay);
        digitalWrite(GrnLED, LOW);
        digitalWrite(RedLED, LOW);
      }
    }
  }
}
