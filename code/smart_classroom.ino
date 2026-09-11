#include <LiquidCrystal.h>

// ---------------- PIN CONNECTIONS ----------------

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// IR sensors
#define IN_SENSOR  A0
#define OUT_SENSOR A5

// Relay
#define RELAY 2

// ---------------- VARIABLES ----------------

int count = 0;

int lastInState = LOW;
int lastOutState = LOW;

// ---------------- DISPLAY ----------------

void updateDisplay()
{
  lcd.clear();

  if (count <= 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("Nobody In Room");

    lcd.setCursor(0, 1);
    lcd.print("Light Is Off");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Person In Room:");

    lcd.setCursor(0, 1);
    lcd.print(count);

    lcd.print("  Light ON");
  }
}

// ---------------- SETUP ----------------

void setup()
{
  lcd.begin(16, 2);

  pinMode(IN_SENSOR, INPUT);
  pinMode(OUT_SENSOR, INPUT);

  pinMode(RELAY, OUTPUT);

  // Start with light OFF
  digitalWrite(RELAY, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Visitor Counter");

  delay(2000);

  updateDisplay();
}

// ---------------- MAIN LOOP ----------------

void loop()
{
  int inState = digitalRead(IN_SENSOR);
  int outState = digitalRead(OUT_SENSOR);

  // -------- PERSON ENTERING --------
  if (inState == HIGH && lastInState == LOW)
  {
    count++;

    updateDisplay();

    delay(200);
  }

  // -------- PERSON LEAVING --------
  if (outState == HIGH && lastOutState == LOW)
  {
    // Prevent negative occupancy
    if (count > 0)
    {
      count--;

      updateDisplay();
    }

    delay(200);
  }

  // Save current sensor states
  lastInState = inState;
  lastOutState = outState;

  // -------- AUTOMATIC LIGHT CONTROL --------

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
