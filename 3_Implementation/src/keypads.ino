//BY ARDUICREATE
//INCLUDE THESE LIBRARYS
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
#define Password_Lenght 7 // Give enough room for six chars + NULL char
char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "999999";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  mySerial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");

  customKey = myKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count, 1); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Passis");

    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
    {
      lcd.print("CORRECT");
    }

    else {
      lcd.print("INCORRECT");
      SendMessage();
    }
    delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
    lcd.clear();
    clearData();
  }
}

void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}
void SendMessage()
{
  mySerial.println("AT\r");
  delay(1000);
  mySerial.println("AT+CMGF=1\r");
  delay(1000);
  mySerial.println("AT+CMGS=\"country code + your number\"\r");
  delay(1000);
  mySerial.println("INTRUDER");
  delay(1000);
  mySerial.println((char)26);
  delay(100);
}