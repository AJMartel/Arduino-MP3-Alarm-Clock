#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <XantoTM1637.h>


//20x4 I2C LCD Start
int i2cAddressLCD = 0x3F;
int lcdCOLS = 20;
int lcdROWS = 4;

LiquidCrystal_I2C lcd(i2cAddressLCD,lcdCOLS,lcdROWS);
//20x4 I2C LCD End

//4x4 I2C Keypap Start
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = {0,1,2,3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4,5,6,7}; //connect to the column pinouts of the keypad

int i2cAddressKeypad = 0x38;

Keypad_I2C keypad = Keypad_I2C( makeKeymap(keys), rowPins, colPins, ROWS, COLS, i2cAddressKeypad );
//4x4 I2C Keypap End

//TM1637 Start
// each "event" (LED) gets their own tracking variable
unsigned long previousMillisDISPLAY_DIO1=0;
unsigned long previousMillisDISPLAY_DIO2=0;

// different intervals for each LED
size_t intervalDISPLAY_DIO1 = 500;
size_t intervalDISPLAY_DIO2 = 250;

// each LED gets a state varaible
boolean DIO2state = false;     // the LED will turn ON in the first iteration of loop()
boolean DIO1state = false;     // need to seed the light to be OFF

const uint8_t PIN_DISPLAY_CLK = 6;
const uint8_t PIN_DISPLAY_DIO1 = 5;
const uint8_t PIN_DISPLAY_DIO2 = 7;

XantoTM1637 displays[] {
  {PIN_DISPLAY_CLK, PIN_DISPLAY_DIO1},
  {PIN_DISPLAY_CLK, PIN_DISPLAY_DIO2}
};

int i = 0; //For Demo clock
int j = 0; //For Demo clock X2

//TM1637 End

void setup(){
//  Serial.begin(9600);
  keypad.begin();
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Fixed Library");
  lcd.setCursor(0,1);
  lcd.print("Arduino Nano v3!");
  lcd.setCursor(0,2);
  lcd.print("Arduino LCM IIC 2004");
  lcd.setCursor(0,3);
  lcd.print("Power By 3DFabXYZ!");  
}

void loop(){
   // get current time stamp
   // only need one for both if-statements
   unsigned long currentMillis = millis();

   // time to toggle LED on DIO1?
   if ((unsigned long)(currentMillis - previousMillisDISPLAY_DIO1) >= intervalDISPLAY_DIO1) {
      DIO1state = !DIO1state;
      displays[0].displayTime(i++, DIO1state);  //digitalWrite(12, DIO1state);
      // save current time to DISPLAY_DIO1's previousMillis
      previousMillisDISPLAY_DIO1 = currentMillis;
   }

// time to toggle LED on DIO2?
  if ((unsigned long)(currentMillis - previousMillisDISPLAY_DIO2) >= intervalDISPLAY_DIO2) {
      DIO2state = !DIO2state;
      displays[1].displayTime(j++, DIO2state);  //digitalWrite(13, DIO2state);
      // save current time to DISPLAY_DIO2's previousMillis
      previousMillisDISPLAY_DIO2 = currentMillis;
  }
  
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print(key);
  }
}

