/*
 * PROJEKT: LED-STEUERUNG MIT TASTER (ACTIVE LOW)
 * * --- HARDWARE-AUFBAU (DETAIL) ---
 * 1. LED (Pin 9):
 * - Grünes Kabel von Pin 9 -> Widerstand 220 -> Anode LED.
 * - Kathode LED -> Minus-Reihe (-) Breadboard -> Zu GND Arduino.
 * * 2. TASTER (Pin 2):
 * - Oranges Kabel von Pin 2 -> Widerstand 1000 (1k) -> Ein Bein des Tasters.
 * - Anderes Bein des Tasters -> Minus-Reihe (-) Breadboard -> Zu GND Arduino.
 * * --- FUNKTIONSLOGIK ---
 * - Normal (Taster losgelassen): Pin 2 ist offen. Wir nutzen INPUT_PULLUP.
 * Der Chip zieht das Signal intern auf 5V (HIGH).
 * - Wenn gedrückt: Pin 2 ist mit GND verbunden (durch die Minus-Reihe).
 * Die Spannung fällt auf 0V (LOW).
 */

// --- VARIABLEN DEKLARIEREN ---

// Benenne Pin 9 als LED_PIN für bessere Lesbarkeit
const int LED_PIN = 9; 

// Benenne Pin 2 als BUTTON_PIN
const int BUTTON_PIN = 2; 

// Variable speichert den Status (0 oder 1)
int buttonState = 0; 

// --- EINSTELLUNGEN (SETUP) ---
void setup() {
  // Konfiguriere LED-Pin als Ausgang (Strom für das Licht)
  pinMode(LED_PIN, OUTPUT);
  
  // Konfiguriere Taster-Pin als Eingang mit Pull-up-Widerstand (WICHTIG)
  // Dieser Befehl gibt Pin 2 schwache 5V, wenn niemand drückt.
  // Ohne dies ist das Signal instabil (Rauschen), wenn der Taster offen ist.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
}

// --- HAUPTSCHLEIFE (LOOP) ---
void loop() {
  
  // S1: Lese Spannung an Pin 2
  // Wenn 5V -> gibt 1 zurück (HIGH)
  // Wenn 0V -> gibt 0 zurück (LOW)
  buttonState = digitalRead(BUTTON_PIN);

  // S2: Logik prüfen (Achtung: umgekehrte Logik)
  // Da der Taster mit GND verbunden ist: Drücken = LOW (0)
  
  if (buttonState == LOW) {
    // ---> FALL: TASTER WIRD GEDRÜCKT
    
    // Nachricht an den Bildschirm senden
    Serial.println("Taster gedrueckt -> LED AN");
    
    // 5V an Pin 9 senden -> LED leuchtet
    digitalWrite(LED_PIN, HIGH);
  } 
  else {
    // ---> FALL: TASTER IST LOSGELASSEN (buttonState == HIGH)
    
    // Nachricht an den Bildschirm (auskommentiert)
    // Serial.println("Taster losgelassen -> LED AUS");
    
    // Strom an Pin 9 abschalten -> LED aus
    digitalWrite(LED_PIN, LOW);
  }

  // S3: Kurz warten (Entprellen / Debounce)
  // Mechanische Kontakte vibrieren beim Drücken.
  // "delay(50)" ignoriert dieses Vibrieren für stabile Signale.
  delay(50);
}