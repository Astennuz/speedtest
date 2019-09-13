  int x = 5;          //Amount of LEDs
  int i = 0;          //Loop iteration, equals the number of times LEDs have flashed
  int r = 0;          //Random seed from analogread
  int t0 = 1500;      //Initial length of LED flash
  int t1 = 0;         //Time base value
  int t2 = 0;         //Time elapsed
  int tdelta = 50;   //How much the time is shortened 

  int randomarray[300];

void setup() {

  Serial.begin(9600);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  pinMode(A2, INPUT);

  randomSeed(analogRead(A2));
}

void loop() {

  //Get the first loop basetime
  if(t1 == 0){
    t1 = millis();
  }

  //Get a ra
  randomarray[i] = random(5) + 8;
  Serial.println(randomarray[i]);
  digitalWrite(randomarray[i], HIGH);
  delay(t0);
  digitalWrite(randomarray[i], LOW);
  delay(100);
  i = i + 1;

  if(i > 299){
    i = 0;
  }

  if(i > 0 && i % 15 == 0){
    if(t0 > 300){
      t0 = t0 - ( i / 15 ) * tdelta;
    }
  }

  if( i == 0 && t0 < 1500){
    t0 = 1500;
  }

}
