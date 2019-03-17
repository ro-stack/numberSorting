// Task 3 Number Sorting
int Array[50]; // initialising the array size
int incomingByte; // initialising the data to be read by the serial monitor

int pinArray[] = {   6, 7, 8, 9, 10, 11, 12, 13  }; // initialising an array for the LED pins
int pinCount = 8; // number of pins being used on the arduino

int highArray; // the value of the highest value in the array once sorted
int lowArray; // the value of the lowest value in the array once sorted


void setup() {
  Serial.begin(9600); // Loads serial port
  for (int thisPin = 0; thisPin <= pinCount; thisPin++) //initialize the LED pins as an output
  {
    pinMode(pinArray[thisPin], OUTPUT); // the pins in the array are set to output
  }

  randomSeed(analogRead(0));
  for (int i = 0; i < 50; i++) // // adds random numbers to the array 50 times
  {
    int n = random(256); // ensures the numbers in the array are between 0 and 255
    Array[i] = n;
  }

  Serial.print("Unsorted Array: "); //
  for (int i = 0; i < 50; i++) {
    Serial.print(Array[i]);
    Serial.print(","); // these 4 lines will display the unsorted array on the serial monitor
  }
  Serial.println(""); // creates new line
  Serial.println("Type 'S' to sort"); // instruction for user on serial monitor on how to sort the numbers
}

void loop() {

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 'S') { // these 3 lines declares what needs to be input to the serial monitor to execute the if statement
      sort(Array, 50); // this is now the array sorted

      Serial.print("Sorted Array: ");
      for (int i = 0; i < 50; i++) {
        Serial.print(Array[i]);
        Serial.print(","); // these 4 lines will prin the array from lowest to highest in order on the serial monitor
      }
      Serial.println(""); // new line

      Serial.print("Lowest Number = ");
      lowArray = Array[0];
      Serial.print(Array[0]);
      Serial.println(""); // these 4 lines will find the lowest number in the array and display it on the serial monitor

      Serial.print("Highest Number = ");
      highArray = Array[49];
      Serial.print(Array[49]);
      Serial.println(""); // these 4 lines will find the highest number in the array and display it on the serial monitor

      Serial.println("The lowest number will now appear on the 8 LED's in binary."); // tells the user on the serial monitor what the LED is displaying
      binaryLowesttNumber();    //calls binaryLowesttNumber function
      delay(10000); // delay 10 seconds
      turnLedsOff();     //turns all LEDs off

      Serial.println("The highest number will now appear on the 8 LED's in binary."); // tells the user on the serial monitor what the LED is displaying
      delay(2000); // delay 2 seconds
      binaryHighestNumber();       //calls binaryHighestNumber function
      delay(10000); // delay 10 seconds
      turnLedsOff();     //turns all LEDs off

    }
  }
}

// number sort function
void sort (int a[], int size) {
  for (int i = 0; i < (size - 1); i++) {
    for (int b = 0; b < (size - (i + 1)); b++) {
      if (a[b] > a[b + 1]) {
        int t = a[b];
        a[b] = a[b + 1];
        a[b + 1] = t;
        /* this is the number/bubble sorting algorithm.
           it will compare the first two numbers and will swap them if the first number is larger than the second.
           it will not swap the numbers if the  the previous is lower
           it will keep looping through until no more position swaps happen and the numbers are in order */
      }
    }
  }
}

void binaryLowesttNumber()
{
  int remainder = lowArray; /* remainder is what I am going to be left with after taking away the value of the pins,
    sets remainder as the lowest sorted number */
  int j = 128;  // value of pins in binary
  int i = 7;    // index of current pin
  while (i >= 0)
  {
    if (remainder >= j) //if remainder is larger or equal to the value of the current pin
    {
      digitalWrite(pinArray[i], HIGH);
      remainder = remainder - j;   // takes value of pin away from remainder
      j = j >> 1;   // halves the value of j
      i--;   // moves to next pin
    }
    else
    {
      j = j >> 1;   // halves the value of j
      i--;   // moves to next pin
    }
  }
}

void binaryHighestNumber()
{
  int remainder = highArray; // same as binaryLowestNumber function except the remainder will be the highest sorted number
  int i = 128;
  int thisPin = 7;

  while (remainder > 0)
  {
    while (remainder >= i)
    {
      double j = i / 2;
      digitalWrite(pinArray[thisPin], HIGH);
      remainder = remainder - i;
      i = i - j;
      thisPin--;
    }
    while (remainder < i)
    {
      int j = i / 2;
      if (j >= 1)
      {
        i = i - j;
        thisPin--;
      }
      else
      {
        i = 0;
      }
    }
  }
}

void turnLedsOff()
{
  for (int thisPin = 0; thisPin < pinCount; thisPin++) // initializes all of the LED pins
  {
    digitalWrite(pinArray[thisPin], LOW); // this will turn all of the LED's yo Low, maning they are off
  }
}
