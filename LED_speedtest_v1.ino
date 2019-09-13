  const int x = 5;    //Amount of LEDs
  int i = 0;          //Loop iteration, equals the number of times LEDs have flashed
  int bi = 0;         //Number of button pushes
  int button = 0;
  int r = 0;          //Random seed from analogread
  int t0 = 1500;      //Initial length of LED flash
  int t00 = t0;       //For testing purposes, restart the loop
  long t1 = 0;        //Time base value
  long t2 = 0;        //Time elapsed
  int tdelta = 50;    //How much the time is shortened 
  int offset = 8;     //Offset due to the pin numbers

  //Create arrays for random LEDs and pushed buttons
  const int arrel = 300;
  int randomarray[arrel];
  int buttonarray[arrel];

void setup() {

  Serial.begin(9600);

  //Declare which pins are used for LEDs
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  //Declare which pins are used for buttons
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  //Use one analog input for random seed
  pinMode(A2, INPUT);
  randomSeed(analogRead(A2));
}




//Start of loop
void loop() {

  //Get the first loop basetime
  if(i == 0){
    
    t1 = millis();
    t0 = t00;
  }


  //Get a random LED number to blink
  randomarray[i] = random(x);
  digitalWrite(randomarray[i] + offset, HIGH);

  //Polling loop
  while(t2 - t1 < t0){

    //Poll buttons
    button = buttons();
    if(button >= 0){
      buttonarray[bi] = button;
      Serial.print("Random array index ");
      Serial.print(bi);
      Serial.print(" is ");
      Serial.println(randomarray[bi]);
      Serial.print("Button array index ");
      Serial.print(bi);
      Serial.print(" is ");
      Serial.println(buttonarray[bi]);

      //Compare pressed button to flashed LED number
      if(buttonarray[bi] == randomarray[bi]){
        Serial.println("Yay, correct press!");
        //TODO: delays are not acceptable in this code, replace with something better
        delay(100);
    }
    
    else{
      lostcase();
    }
      
      bi++;
    }
    
    t2 = millis();
    
  }
  
  digitalWrite(randomarray[i] + offset, LOW);

  //Set new basetime and increment array index
  t1 = t2;
  i = i + 1;
  delay(100);
  

  //For testing purpose
  //Start from the beginning
  if(i > arrel){
    i = 0;
  }


  //Increase LED blinking speed
  if(i > 0 && i % 15 == 0){
    if(t0 > arrel){
      t0 = t00 - ( i / 15 ) * tdelta;
    }
  }

  if( i == 0 && t0 < 1500){
    t0 = t00;
  }

}


//Declare functions to be used

int buttons(){

  int val = 0;

  if(digitalRead(3)){
    val = 0;
  }
  else if(digitalRead(4)){
    val = 1;
  }
  else if(digitalRead(5)){
    val = 2;
  }
  else if(digitalRead(6)){
    val = 3;
  }
  else if(digitalRead(7)){
    val = 4;
  }
  else{
      val = -1;
  }

  return val;
  
}


//If player presses wrong button, flash all LEDs
void lostcase(){
  
  digitalWrite(8, HIGH);
  delay(50);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(50);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(50);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(50);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  delay(50);
  digitalWrite(12, LOW);
}
