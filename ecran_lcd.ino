#include <LiquidCrystal_I2C.h> // pour télécharger la librairie: croquis - include library - manage libraries - LiquidCrystal_I2C.h de Frank de Brabander
LiquidCrystal_I2C lcd(0x27, 16, 2); //écran LCD 0x27 avec 16 colonnes et 2 lignes (ligne 0 et ligne 1)



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // initialise la connexion série
  lcd.init(); //initialisation de l'écran LCD
  lcd.cursor_on();
  lcd.blink_on();
  lcd.backlight();
  lcd.print("Jeu d'Echec");

  while (!Serial) {
    ; // attendre la connexion série
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear(); // Efface l'écran LCD
  lcd.print("Mode Rail"); // Affiche le mode
  delay(1000);
}
