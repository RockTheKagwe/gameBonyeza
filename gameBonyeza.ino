/*  This code is authored by:
 *      Peter Kagwe Kagunyi
 *      School of Engineering and Technology
 *      Kenyatta University
 *  This is an interactive game by use of pushButtons. Two players play against each other. 
 *  The pushbuttons are pressed and the player with the highest presses takes the win. 
 *  The main aim of this exercise is to ensure that the IEEE learners in the Arduino series think outside the box.
 *       The game is to be played within a given time. After that, the players will have to reset.
 *       Each press is accompanied by a count for the given player, and the respective LED flickers.
 *       The Serial monitor is used to display the game progress.
 */
 
const int buzzerPin = 8;      //Variable to store the pin to be used by the buzzer oncethe game is over.
const int pushButton1 =  12;  //Variable to store the pin for player1's button.
const int pushButton2 = 4;    //Variable to store the pin for player2's button.
const int led1 = 10;          //Variable to store the pin for player1's LED.
const int led2 = 6;           //Variable to store the pin for player2's LED.

unsigned long timeToFinal = 20000; //Variable to store the set time for the game.
unsigned long timeTaken;           //Variable to store the time taken since the program started to run.
unsigned long timeRemaining;       //Variable to store the time difference of the above two.

int count1 = 0, count2 = 0;        //variables to store the counts of the presses/pushes.
int pushed1, pushed2; //Variables to store the states of the pins.
void setup()
{
  //Initialize the pins, and serial communication.
  pinMode(buzzerPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(pushButton2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() 
{
  String returnMessage;  //Variable to store message after game is complete
  int playScore;         //Variable to store score of the winner
  
  timeTaken = millis(); //millis() is an inbuilt Arduino function to obtain the time taken since the curent proram started to run
  
  timeRemaining = (timeToFinal - timeTaken)/1000;

  //If there is still time to game, let them game.
  if (timeTaken <= timeToFinal)
  {
    Serial.print("Time remaining: ");
    Serial.print(timeRemaining);
    Serial.println(" seconds");
    
    pushed1 = digitalRead(pushButton1);  //Store the state of the button
    if (pushed1 == LOW)  //Check whether the button is pressed/
    {
      count1 = count1 + 1;  //Increment the count
      //Flicker the LED
      digitalWrite(led1, HIGH);
      delay(10);
      digitalWrite(led1, LOW);
    }
    
    pushed2 = digitalRead(pushButton2); //Store the state of the button
    if (pushed2 == LOW) //Check whether the button is pressed
    {
      count2 = count2 + 1;  //Increment the count
      //Flicker the LED
      digitalWrite(led2, HIGH);
      delay(10);
      digitalWrite(led2, LOW);
    }
    //Print current game scores.
    Serial.print("Player1 Score: ");
    Serial.print(count1);
    Serial.print("\tPlayer2 Score: ");
    Serial.println(count2);

  }
  else
  {
    //Gauge the players.
    if (count1 > count2)
    {
      returnMessage = "Player 1 wins. Hurray";
      playScore = count1;
    }
    else if (count1 <count2)
    {
      returnMessage = "Player 2 wins. Hurray";
      playScore = count2;
    }
    else
    {
      returnMessage = "Both players draw. What a competition!!!";
      playScore = count1;
      //playScore = count2;
    }

    //Check the states of the pins.
    pushed1 = digitalRead(pushButton1);
    pushed2 = digitalRead(pushButton2);
    if ((pushed1 == LOW) || (pushed2 == LOW))
    {
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      Serial.println("Game Over!!!");
      Serial.println(returnMessage);
      Serial.print("Score: ");
      Serial.print(playScore);
      Serial.println(" points.");
    }
  }
}
