// GENESIS BOARD MINI SUMO ROBOT PROGRAM 
//FOR 3 OPPONENT SENSOR, 2 EDGE SENSOR
// JSUMO 12/2015
///////////////////////////////////////

//MOTOR CONTROL
int RPwm = 11;
int RDir = 13;

int LPwm = 3;
int LDir = 12;

//LED & BUZZER
int Buzzer = 9;
int ArduLed = 8;

//EDGE & CONTRAST SENSORS
int Redge = A0;
int Ledge = A1;

//TRIMPOTS
int SPD = A7;
int TRN = A6;

//OPPONENT SENSORS
int LSens = A2;
int RSens = A4;
int MSens = A3;

int LFSens = A5;
int RFSens = 4;

// DIPSWITCH & BUTTON
int Button = 10; // Can be used as start pin too.
int DS1 = 5;
int DS2 = 6;
int DS3 = 7;

//VALUES
int Speed =50;
int MaxSpeed = 30; // Idle Speed while no sensor giving data.
int TurnSpeed = 80; // Left and Right Forward Turning Speed
int EdgeTurn = 75; // Turning Time variable when minisumo sees white line
int Duration; // Turning Time at minisumo starting.
int LastValue = 5; // Last Value Variable for remembering last Opponent sensor sense.

void setup()
{
  pinMode(LSens, INPUT);    // Left Opponent Sensor Input
  pinMode(RSens, INPUT);    // Right Opponent Sensor Input
  pinMode(MSens, INPUT);    // Middle Opponent Sensor Input

  pinMode(Buzzer, OUTPUT);  // Buzzer Declared as Output
  pinMode(ArduLed, OUTPUT); // Buzzer Declared as Output
  pinMode(Button, INPUT); // Buzzer Declared as Output

  pinMode(RPwm, OUTPUT);  // Four PWM Channel Declared as Output
  pinMode(RDir, OUTPUT); 
  pinMode(LPwm, OUTPUT); 
  pinMode(LDir, OUTPUT); 

  digitalWrite(Buzzer, LOW); // Buzzer Pin Made Low for Silence :)
  digitalWrite(ArduLed, LOW);  // Arduino Mode Led Made Low
  digitalWrite(DS1, HIGH); // 3 Dipswitch Pin Pullups Made
  digitalWrite(DS2, HIGH);
  digitalWrite(DS3, HIGH);

  digitalWrite(LSens, HIGH); // Opponent Sensor Pullups Made
  digitalWrite(RSens, HIGH); 
  digitalWrite(LFSens, HIGH); 
  digitalWrite(RFSens, HIGH); 
  digitalWrite(MSens, HIGH); 
  Serial.begin(9600);
}

//Motor Control Function
void Set_Motor (float Lval, float Rval, int timex){
  Lval = Lval*2.5;
  Rval = Rval*2.5; 
  if (Lval >=0) { 
      analogWrite(LPwm, Lval);  
      digitalWrite(LDir, LOW);       
      } else {
      Lval=abs(Lval); 
      digitalWrite(LDir, HIGH);  
      analogWrite(LPwm, Lval); 
      }
   if (Rval >=0) {    
      analogWrite(RPwm, Rval);  
      digitalWrite(RDir, HIGH);       
      } else {
      Rval=abs(Rval);     
      digitalWrite(RDir, LOW);  
      analogWrite(RPwm, Rval); 
      }   
     // Serial.print(Rval); Serial.print("-"); Serial.println(Lval);
   delay(timex);  
}

void check()
 { delay(10);
       if (digitalRead(DS1)==0 && digitalRead(DS2)==1 && digitalRead(DS3)==1){
           Serial.print("LEFT TURN");            
           Set_Motor(-100,100,Duration); //                 
       }
          else if (digitalRead(DS1)==0 && digitalRead(DS2)==0 && digitalRead(DS3)==0) {
               Serial.print("MIDDLE DIRECT");
               Set_Motor(100,100,2);
       }
           else if (digitalRead(DS1)==1 && digitalRead(DS2)==1 && digitalRead(DS3)==0){
           Serial.print("Sag");
           Set_Motor(100,-100,Duration);           
       }       
         else if (digitalRead(DS1)==1 && digitalRead(DS2)==0 && digitalRead(DS3)==0){
            Serial.print("Left Circle");
           Set_Motor(100,36,650); 
       }       
       else if (digitalRead(DS1)==0 && digitalRead(DS2)==0 && digitalRead(DS3)==1){
           Serial.print("Right Circle");
           Set_Motor(36,100,650); 
       }       
        else if (digitalRead(DS1)==0 && digitalRead(DS2)==1 && digitalRead(DS3)==0){
           Serial.print("Reverse 180"); 
           Set_Motor(-100,100,Duration); 
          delay(Duration);  
       }

}
  
void loop() {

  digitalWrite(RPwm, LOW);
  digitalWrite(LPwm, LOW);
  if (digitalRead(Button) == 1) { // If button is pressed at beginning.
    //tone(Buzzer, 18, 100); // Pin, Frequency, Duration
    while (1) {
      if (digitalRead(DS1) == 0 && digitalRead(DS2) == 0 && digitalRead(DS3) == 0) {
        Serial.print("Board Test");
        Set_Motor(100, 100, 1000);
        Set_Motor(0, 0, 1000);
        Set_Motor(-90, -90, 1000);
        Set_Motor(0, 0, 1000);
        // tone(Buzzer, 18, 300);
        // tone(ArduLed, 18, 300);            
      }
    }
  }
  //////////////////////////////////////////////
  //tone(Buzzer, 18, 100); // Pin, Frequency, Duration
  Wait:
    Serial.println("Button Press Waited");
  Set_Motor(0, 0, 1);
  /// Sensor Control While Waiting The Button Press ///
  if (digitalRead(MSens) == LOW || digitalRead(RSens) == LOW || digitalRead(LSens) == LOW || digitalRead(RFSens) == LOW || digitalRead(LFSens) == LOW || analogRead(Redge) < 500 || analogRead(Ledge) < 500) {
    digitalWrite(ArduLed, HIGH);
  } else {
    digitalWrite(ArduLed, LOW);
  }
  ///////////////////////////////////////////////
  if (digitalRead(Button) == 1) {
    Duration = (analogRead(TRN) / 4); // Duration variable based on TRN (A6) trimpot
    Serial.println("5 Sec Routine Started");
    for (int i = 0; i < 5; i++) {
      digitalWrite(Buzzer, HIGH);
      digitalWrite(ArduLed, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);
      digitalWrite(ArduLed, LOW);
      delay(900);
    }

    if (digitalRead(DS1) == 0 && digitalRead(DS2) == 1 && digitalRead(DS3) == 1) {
      Serial.print("LEFT TURN");
      Set_Motor(-100, 100, Duration); //                 
    } else if (digitalRead(DS1) == 0 && digitalRead(DS2) == 0 && digitalRead(DS3) == 0) {
      Serial.print("MIDDLE DIRECT");
      Set_Motor(100, 100, 2);
    } else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 1 && digitalRead(DS3) == 0) {
      Serial.print("Sag");
      Set_Motor(100, -100, Duration);
    } else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 0 && digitalRead(DS3) == 0) {
      Serial.print("Left Circle");
      Set_Motor(100, 36, 650);
    } else if (digitalRead(DS1) == 0 && digitalRead(DS2) == 0 && digitalRead(DS3) == 1) {
      Serial.print("Right Circle");
      Set_Motor(36, 100, 650);
    } else if (digitalRead(DS1) == 0 && digitalRead(DS2) == 1 && digitalRead(DS3) == 0) {
      Serial.print("Reverse 180");
      Set_Motor(-100, 100, Duration);
      delay(Duration);
    }
    Serial.print("OK");
    // digitalWrite(Buzzer, LOW);
    // EdgeTurn=(analogRead(TRN)/5); EdgeTurn=205-EdgeTurn; 
    goto Start;
  }
  goto Wait;

  //Main Loop scanning the lines on the ring
  Start:

    //--------
    /// Edge Sensor Control Routine ///
    digitalWrite(ArduLed, LOW);
  //delay (10);

  if (analogRead(Ledge) < 150 && analogRead(Redge) < 150) {
    digitalWrite(Buzzer, LOW);
    digitalWrite(ArduLed, HIGH);

    Set_Motor(-1000, -1000, 200);

    delay(20);
    //Set_Motor(100, -100, EdgeTurn); // Right Backward, Left Forward, Turning Time Based on ETRN Trimpot
    LastValue = 5;
    check();

  } else if (analogRead(Ledge) < 150 && analogRead(Redge) > 150) {
    digitalWrite(Buzzer, LOW);
    digitalWrite(ArduLed, HIGH);

    Set_Motor(-1000, -1000, 200);
    delay(20);
    //Set_Motor(-100, 100, EdgeTurn); // Left Backward, Right Forward, Turning Time Based on ETRN Trimpot
    LastValue = 5;
    check();
  } else if (analogRead(Ledge) > 150 && analogRead(Redge) < 150) {
    digitalWrite(Buzzer, LOW);
    digitalWrite(ArduLed, HIGH);

    Set_Motor(-1000, -1000, 200);

    delay(20);
    //Set_Motor(100, -100, EdgeTurn); // Right Backward, Left Forward, Turning Time Based on ETRN Trimpot
    LastValue = 5;
    check();
  } else
    /// Opponent Sensor Control Routine ///
    //if (digitalRead(Button)==LOW) {Set_Motor(0, 0,5000); digitalWrite(Buzzer, HIGH); LastValue=3;} else

    if (digitalRead(MSens) == LOW) {
      Set_Motor(MaxSpeed, MaxSpeed, 1);
      digitalWrite(Buzzer, HIGH);
      LastValue = 5;
    } else
  if (digitalRead(LSens) == LOW) {
    Set_Motor(-40, TurnSpeed, 1);
    digitalWrite(Buzzer, HIGH);
    LastValue = 7;
  } else
  if (digitalRead(RSens) == LOW) {
    Set_Motor(TurnSpeed, -40, 1);
    digitalWrite(Buzzer, HIGH);
    LastValue = 3;
  } else

  //if (digitalRead(LFSens)== LOW) {Set_Motor(-40, TurnSpeed,1); digitalWrite(Buzzer, HIGH); LastValue=7;} else
  //if (digitalRead(RFSens)==LOW) {Set_Motor(TurnSpeed, -40,1); digitalWrite(Buzzer, HIGH); LastValue=3;} else
  {
    digitalWrite(Buzzer, LOW);
    //Speed=(analogRead(SPD)/10.3); Speed=100-Speed; 

    if (LastValue == 5) {
      Set_Motor(35, 35, 1);
    } else // Forward, Based on SPD (A7) Trimpot
      if (LastValue == 7) {
        Set_Motor(-20, Speed, 2);
      } else // Left Turning Based on SPD (A7) Trimpot
        if (LastValue == 3) {
          Set_Motor(Speed, -20, 2);
        } // Right Turning Based on SPD (A7) Trimpot
  }
  goto Start;
}
