// Buttons
#define BUTTON_RESTART 8
#define BUTTON_LEFT 2
#define BUTTON_RIGHT 3
#define BUTTON_SHOOT 4


// Commands
char restart[15] = "RESTART\n";
char left[15] = "LEFT\n";
char right[15] = "RIGHT\n";
char shoot[15] = "SHOOT\n";

void setup() {
  Serial.begin(115200);  

  // Buttons
  pinMode(BUTTON_RESTART,INPUT);
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_SHOOT, INPUT);
}

void loop() {
  int restartPressed = digitalRead(BUTTON_RESTART);
  int leftPressed = digitalRead(BUTTON_LEFT);
  int rightPressed = digitalRead(BUTTON_RIGHT);
  int shootPressed = digitalRead(BUTTON_SHOOT);
  
  if (restartPressed == HIGH && Serial.availableForWrite()) {
    Serial.println(restart);
    delay(1000);
  }
  
  if (leftPressed == HIGH && Serial.availableForWrite()) {
    Serial.println(left);
    delay(1000);
  }
  
  if (rightPressed == HIGH && Serial.availableForWrite()) {
    Serial.println(right);
    delay(1000);
  }
  
  if (shootPressed == HIGH && Serial.availableForWrite()) {
    Serial.println(shoot);
    delay(1000);
  }
}
