#include <LiquidCrystal.h>

// ---------------- LCD CONNECTIONS ----------------
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// ---------------- SENSOR CONNECTIONS ----------------
#define IN_SENSOR  A0
#define OUT_SENSOR A5

// ---------------- RELAY CONNECTION ----------------
#define RELAY 2

// ---------------- VARIABLES ----------------
int count = 0;

int lastInState = LOW;
int lastOutState = LOW;


// ==================================================
// DISPLAY FUNCTION
// ==================================================

void updateDisplay()
{
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Count: ");
  lcd.print(count);

  lcd.setCursor(0, 1);

  if (count > 0)
  {
    lcd.print("Relay: ON");
  }
  else
  {
    lcd.print("Relay: OFF");
  }
}


// ==================================================
// SETUP
// ==================================================

void setup()
{
  lcd.begin(16, 2);

  pinMode(IN_SENSOR, INPUT);
  pinMode(OUT_SENSOR, INPUT);

  pinMode(RELAY, OUTPUT);

  // Start with relay OFF
  digitalWrite(RELAY, LOW);

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("Smart Classroom");

  lcd.setCursor(0, 1);
  lcd.print("Occupancy System");

  delay(2000);

  updateDisplay();
}


// ==================================================
// MAIN LOOP
// ==================================================

void loop()
{
  int inState = digitalRead(IN_SENSOR);
  int outState = digitalRead(OUT_SENSOR);


  // ----------------------------------------------
  // PERSON ENTERING
  // ----------------------------------------------

  if (inState == HIGH && lastInState == LOW)
  {
    count++;

    updateDisplay();

    delay(300);
  }


  // ----------------------------------------------
  // PERSON LEAVING
  // ----------------------------------------------

  if (outState == HIGH && lastOutState == LOW)
  {
    // Prevent negative count
    if (count > 0)
    {
      count--;

      updateDisplay();
    }

    delay(300);
  }


  // Store previous sensor states
  lastInState = inState;
  lastOutState = outState;


  // ----------------------------------------------
  // AUTOMATIC LIGHT CONTROL
  // ----------------------------------------------

  if (count > 0)
  {
    digitalWrite(RELAY, HIGH);
  }
  else
  {
    digitalWrite(RELAY, LOW);
  }


  delay(50);
}
