static int readings[][4] = {
  {10, 20, 30, 40},
  {20, 30, 40, 30},
  {30, 40, 30, 20},
  {40, 30, 20, 10},
  {30, 20, 10,  0}
  };
static int xcount = 5, ycount = 4;

void setup() {

  Serial.begin(9600);

}

void loop() {

  while(Serial.read() != '1') delay(50);
  
  for (int y = 0; y < ycount; y++) {
    for (int x = 0; x < xcount; x++) {
      Serial.println(String(x) + "," + String(y) + "," + String(readings[x][y]));
      delay(50);
    }
  }

  Serial.println("-1,-1,-1");

  delay(500);

}
