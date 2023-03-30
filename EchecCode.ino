#include <Wire.h>
#include <LiquidCrystal_I2C.h> // pour télécharger la librairie: croquis - include library - manage libraries - LiquidCrystal_I2C.h de Frank de Brabander
LiquidCrystal_I2C lcd(0x27, 16, 2); //écran LCD 0x27 avec 16 colonnes et 2 lignes (ligne 0 et ligne 1)

String mode = "";

bool moveMade = false; // variable pour stocker l'état du mouvement

// A supprimer
int button1Pin = 2; // Broche du premier bouton
int button2Pin = 3; // Broche du deuxième bouton
int button1State = 0; // Etat du premier bouton (0 = relâché, 1 = appuyé)
int button2State = 0; // Etat du deuxième bouton (0 = relâché, 1 = appuyé)




void setup() {
  Serial.begin(9600); // initialise la connexion série
  lcd.init(); //initialisation de l'écran LCD
  lcd.cursor_on();
  lcd.blink_on();
  lcd.backlight();
  lcd.print("Jeu d'Echec");

  while (!Serial) {
    ; // attendre la connexion série
  }


// A supprimer
  pinMode(button1Pin, INPUT); // Définit la broche du premier bouton comme une entrée
  pinMode(button2Pin, INPUT); // Définit la broche du deuxième bouton comme une entrée
}

void loop() {

  String x = "";
  if (Serial.available()>0) { // Vérifie si des données sont disponibles
    String x = Serial.readString();
    if (x == "R"){
      lcd.clear(); // Efface l'écran LCD
      lcd.print("Mode Rail"); // Affiche le mode
      mode = "R";
    }
    else if (x == "M"){
      lcd.clear(); // Efface l'écran LCD
      lcd.print("Mode Manuel"); // Affiche le mode
      mode = "M";
    }
    if (x != "R" && x != "M" && mode == "R"){ // Quand on joue avec les rails
      lcd.clear(); // Efface l'écran LCD
      lcd.print(x); // Affiche la valeur de x
    }
    else if (x != "R" && x != "M" && mode == "M"){ // Quand on joue en mode manuel
      if (checkInput(x) != ""){
        lcd.clear(); // Efface l'écran LCD
        lcd.print(x); // Affiche la valeur de x
      }
      else if (x == "move" && !moveMade){
        lcd.clear();
        lcd.print("Mouv en attente");
        button1State = digitalRead(button1Pin); // Lit l'état du premier bouton
        button2State = digitalRead(button2Pin); // Lit l'état du deuxième bouton
      
        if (button1State == HIGH) { // Si le premier bouton est appuyé
          Serial.println("a7a5"); // Envoie la chaîne de caractères "a2a4" sur le port série
          moveMade = true;
          delay(500);
        } 
        if (button2State == HIGH) { // Si le deuxième bouton est appuyé
          Serial.println("h7h6"); // Envoie la chaîne de caractères "h2h4" sur le port série
          moveMade = true;
          delay(500);
        }
        if (moveMade) {
          lcd.clear();
          lcd.print("Move effectue");
        }
      }
    }
  }
}


String checkInput(String input) {
  if(input.length() != 4) { // Vérifie que la chaîne d'entrée a une longueur de 4 caractères
    return ""; // Retourne une chaîne de caractères vide si elle ne respecte pas le format attendu
  }

  char c1 = input.charAt(0);
  char c2 = input.charAt(1);
  char c3 = input.charAt(2);
  char c4 = input.charAt(3);

  // Vérifie que les 4 caractères respectent les contraintes
  if(c1 < 'a' || c1 > 'h' || c2 < '1' || c2 > '8' || c3 < 'a' || c3 > 'h' || c4 < '1' || c4 > '8') {
    return ""; // Retourne une chaîne de caractères vide si elle ne respecte pas le format attendu
  }

  return input; // Retourne la chaîne d'origine si elle est dans le bon format
}
