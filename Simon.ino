int LENGTH = 400;
int notes[4] = {100, 350, 600, 850};
int gamepattern[30];
//int idle = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  Serial.begin(9600);
}

void loop() {
  for (int i=2; i<10; i++) {digitalWrite(i, HIGH);}
  main_menu();
}

void main_menu()
{
  while (1 == 1)
  {
    //if (idle == 0){play_note(1, 100);}
    //if (idle == 1){play_note(2, 100);}
    //if (idle == 2){play_note(3, 100);}
    //if (idle == 3){play_note(4, 100);}
    if ((digitalRead(6) == LOW) | (digitalRead(7) == LOW) | (digitalRead(8) == LOW) | (digitalRead(9) == LOW))
    {
      generate_game();
      play_game();
    }
    idle++;
    if (idle == 4){idle = 0;}
  }
}

void play_game()
{
  int roundCount = 0;
  int playerTurn = 1;
  bool buttonPress = false;
  int currentNote;
  int userInput = 0;
  bool loss = false;
  //play_note(1, 100);
  //play_note(2, 100);
  //play_note(3, 100);
  //play_note(4, 100);
  delay(5000);
  for (int currentRound=1; (currentRound - 1)<=(30); currentRound++)
    {
      roundCount += 1;
      playerTurn = 1;
      buttonPress = false;
      userInput = 0;
      for (int j = 1; j != currentRound; j++) {play_note(gamepattern[j - 1], LENGTH);}
      while (playerTurn < currentRound) {
        currentNote = gamepattern[playerTurn - 1];
        while (buttonPress == false) {
           if (digitalRead(6) == LOW)
           {
             buttonPress = true;
             userInput = 1;
           }
           if (digitalRead(7) == LOW)
           {
             buttonPress = true;
             userInput = 2;
           }
           if (digitalRead(8) == LOW)
           {
             buttonPress = true;
             userInput = 3;
           }
           if (digitalRead(9) == LOW)
           {
             buttonPress = true;
             userInput = 4;
           }
           if (buttonPress == true)
           {
             play_note(userInput, LENGTH);
             if (currentNote == userInput) {playerTurn++;}
             else {game_over(false,userInput);}
           }
    }
    buttonPress = false;
   }
  }
  if (loss == false){
    game_over(true,userInput);
  }
 }

void generate_game() {
  randomSeed(analogRead(1));
  for (int i=0; i<(30); i++) {gamepattern[i] = random(1, 5);}
}

void play_note(int index, int notespeed) {
  digitalWrite(index + 1, LOW);
  tone(11, notes[ index - 1 ], notespeed);
  delay(notespeed * 2);
  digitalWrite(index + 1, HIGH);
}

void game_over(bool win, int userInput) {
  if (win) {
    for (int i = 0; i < 10; i++){
      play_note(1, 50);
      play_note(2, 50);
      play_note(3, 50);
      play_note(4, 50);
    }
  }
  else {
    for (int i = 0; i < 1; i++){
      //play_note(4, 100);
      //play_note(3, 100);
      //play_note(2, 100);
      play_note(userInput, 3000);
    }
  }
  main_menu();
}
