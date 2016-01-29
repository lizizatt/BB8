//very simple dc motor driver through l298 controller
//liz izatt

//REMINDER:  power lines to white motor cable + motor body for best results

int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 9;

bool fwd = false;
bool back = false;

void setup() { 
  Serial.begin(9600);

  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);

}

int state1 = 0;

void loop() {
  digitalWrite(speedPinA, state1 == 0? LOW : HIGH);
  digitalWrite(dir1PinA, fwd? HIGH : LOW);
  digitalWrite(dir2PinA, back? HIGH : LOW);
  
  if (Serial.available() > 0) {
    int inc = Serial.read();

    if (inc == 49) {
      state1 = (state1 + 1) % 2;
      Serial.println(String(state1));
    }
    
    else if (inc == 119) {
      fwd = !fwd;
      back = false;
        Serial.println(fwd? "Fwd" : "Stop");
    }
    else if (inc == 115) {
        fwd = false;
        back = !back;
        Serial.println(back? "Back" : "Stop");
    }
  }
}
