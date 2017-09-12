static int irPin = A0;

void setup() {

  pinMode(irPin, INPUT);
  
  Serial.begin(9600);

}

void loop() {

  Serial.println(analogRead(irPin));

}
