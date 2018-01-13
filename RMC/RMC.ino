int ch1 = 11;
int ch2 = 10;

void setup() {
  Serial.begin(9600);
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
}

void loop() {
  int CH1 = pulseIn(ch1, HIGH);
  Serial.print(CH1);
  Serial.print("\t");
  int CH2 = pulseIn(ch2, HIGH);
  Serial.println(CH2);
  delay(100);
}



