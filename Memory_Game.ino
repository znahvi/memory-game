#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

int correct = 0;

// Buttons
const int red_button = 2;
const int blue_button = 3;
const int yellow_button = 4;
const int green_button = 5;
const int start_button = 6;

bool pressed = false;

// LEDs
const int red_led = 12;
const int blue_led = 11;
const int yellow_led = 10;
const int green_led = 9;

// Servo motor
Servo servo;
int pos = 90;

// Game state variables
int start = false;
int presses[4];
int button_count = 0;
int games = 0;
int speed = 500; // speed of LED blinking
int playing = false;

int highscore = 0;


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  // LCD
  lcd.init();
  lcd.backlight();
  
  // Buttons 
  pinMode(red_button, INPUT_PULLUP);
  pinMode(blue_button, INPUT_PULLUP);
  pinMode(yellow_button, INPUT_PULLUP);
  pinMode(green_button, INPUT_PULLUP);
  
  pinMode(start_button, INPUT_PULLUP);
  
  // LEDs
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  
  // Servo Motor
  servo.attach(7); // digital pin 7
  
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Press to start->");
  lcd.setCursor(0, 1);
  lcd.print("Highscore: ");
  lcd.print(highscore);
  lcd.setCursor(0, 0);
  while (!start) {
    delay(200);
    if (read_start_button(start_button)) {
      start = true;
        games = 0;    // Reset game count
      correct = 0;  // Reset score
      speed = 500;  // Reset speed
        playing = true;
        lcd.clear();
        delay(500);
    }
  }
  
  
  while (playing && start) {
    button_count = 0;
    
    // Pattern for LED blinking
    int pattern[4] = {random(9, 13), random(9, 13), random(9, 13), random(9, 13)};
    
    // Four blinks
    for (int i = 0; i < 4; i++) {
      digitalWrite(pattern[i], HIGH);
      delay(speed);
      digitalWrite(pattern[i], LOW);
      delay(speed);
    }
    
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("YOUR TURN!");
    lcd.setCursor(0, 0);
    
    delay(200); // make sure the player isn't holding a button down
    
    // Read buttons until player presses 4 buttons
    while(button_count < 4) {
      read_button(red_button);
      read_button(blue_button);
      read_button(yellow_button);
      read_button(green_button);
    }
    
    // Was the combination correct?
    if (arraysEqual(pattern, presses)) {
      lcd.print("Yes, you got it!");
      correct += 1;
      delay(500);
      lcd.clear();
      games += 1;
      speed -= 50;
      if (speed < 300) {
        speed = 500;
      }
      delay(1000);
    }
    else {
      lcd.print("Sorry, that's wrong!");
      delay(300);
      lcd.clear();
      playing = false;
    }

  }
  
  if (!playing) {
    if (correct > highscore) {

      for (int i = 90; i >= 0; i-=5) {
        pos -= 5;
        servo.write(pos);
        delay(7);
      }
      delay(3000);
      for (int i = 0; i <= 90; i+=5) {
        pos += 5;
        servo.write(pos);
        delay(7);
      }
      
      lcd.setCursor(0, 0);
      lcd.print("You beat the");
      lcd.setCursor(0, 1);
      lcd.print("highscore!");
      highscore = correct;
      delay(500);
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Total Score: ");
    lcd.print(correct);
    lcd.setCursor(0, 1);
    lcd.print("Goodbye!");
    delay(2000);
    
    start = false;
  }
  
}

void read_button(int button) {
  bool currentState = digitalRead(button);
  
  if (currentState == pressed && button_count < 4) {
    delay(50);
    while(digitalRead(button) == pressed) {
      delay(10);
    }
    appendElement(button);
  }
}

bool read_start_button(int button) {
  bool currentState = digitalRead(button);
  
  if (currentState == pressed) {
    delay(50);
    while(digitalRead(button) == pressed) {
      delay(10);
    }
    return true;
  }
  return false;
}

void appendElement(int button) {
  int match = map(button, 5, 2, 9, 12);
  presses[button_count] = match;
  button_count += 1;
}

bool arraysEqual(int array1[], int array2[]) {
  for (int i = 0; i < 4; i++) {
    if (array1[i] != array2[i]) {
      return false;
    }
  }
  return true;
}
