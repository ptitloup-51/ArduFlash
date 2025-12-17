/*
  Flash Trigger pour Godox V1C
  Compatible Arduino Due
  
  Déclenche le flash en shuntant les contacts du hot shoe
  via un optocoupleur PC817 pour isolation galvanique.
  
*/

// Configuration des pins
const int FLASH_PIN = 7;           // Pin de commande du flash
const int PULSE_DURATION = 10;     // Durée de l'impulsion en ms
const int RECYCLE_TIME = 2000;     // Temps de recyclage du flash en ms

void setup() {
  // Initialisation du pin de commande
  pinMode(FLASH_PIN, OUTPUT);
  digitalWrite(FLASH_PIN, LOW);
  
  // Communication série pour debug
  Serial.begin(115200);
  Serial.println("=================================");
  Serial.println("Flash Trigger - Godox V1C");
  Serial.println("=================================");
  Serial.println("Pret a declencher !");
  Serial.println();
}

void loop() {
  // Déclenche le flash
  triggerFlash();
  
  // Affiche le statut
  Serial.println("Flash declenche !");
  
  // Attend le temps de recyclage
  delay(RECYCLE_TIME);
}

/**
 * Fonction de déclenchement du flash
 * Envoie une impulsion courte pour shunter les contacts
 */
void triggerFlash() {
  digitalWrite(FLASH_PIN, HIGH);   // Active le circuit
  delay(PULSE_DURATION);           // Maintient 10ms
  digitalWrite(FLASH_PIN, LOW);    // Désactive
}