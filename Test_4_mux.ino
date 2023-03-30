// ------------------------------------------------------------------
// PROJET PI² : Jeu d'échec KAIROS
// Par Marçal Thomas, Kermel Aurore
// Janvier 2023
// ------------------------------------------------------------------

// BOUTON POUSSOIR
// ------------------------------------------------------------------
int boutonPin = 19;
int etat[8][8];

bool jeveuxchanger=false;
String positionavant;
String positionapres;
String correspondance[8] = {"a","b","c","d","e","f","g","h"}; //permet de transcrire le numéro de colonne en lettre pour etre compatible avec l'API

// AFFICHAGE ECRAN LCD 

#include <LiquidCrystal_I2C.h> // pour télécharger la librairie: croquis - include library - manage libraries - LiquidCrystal_I2C.h de Frank de Brabander
LiquidCrystal_I2C lcd(0x27, 16, 2); //écran LCD 0x27 avec 16 colonnes et 2 lignes (ligne 0 et ligne 1)


// MULTIPLEXER 1 - Lignes
// ------------------------------------------------------------------
//Mux_1 control pins
int MUX1_s0 = 53;
int MUX1_s1 = 52;
int MUX1_s2 = 51;
int MUX1_s3 = 50;
//Mux_1 in "SIG" pin
int MUX1_SIG_pin = 22;

// MULTIPLEXER 2
// ------------------------------------------------------------------
//Mux_2 control pins
int MUX2_s0 = 48;
int MUX2_s1 = 46;
int MUX2_s2 = 49;
int MUX2_s3 = 47;
//Mux_2 in "SIG" pin
int MUX2_SIG_pin = 23;
// ------------------------------------------------------------------

// MULTIPLEXER 3
// ------------------------------------------------------------------
//Mux_3 control pins
int MUX3_s0 = 30;
int MUX3_s1 = 31;
int MUX3_s2 = 32;
int MUX3_s3 = 33;
//Mux_3 in "SIG" pin
int MUX3_SIG_pin = 25;
// ------------------------------------------------------------------

// MULTIPLEXER 4
// ------------------------------------------------------------------
//Mux_4 control pins
int MUX4_s0 = 38;
int MUX4_s1 = 39;
int MUX4_s2 = 40;
int MUX4_s3 = 41;
//Mux_4 in "SIG" pin 
int MUX4_SIG_pin = 24;
// ------------------------------------------------------------------

int MUX[4][5]  = {{MUX1_s0, MUX1_s1, MUX1_s2, MUX1_s3, MUX1_SIG_pin}, {MUX2_s0, MUX2_s1, MUX2_s2, MUX2_s3, MUX2_SIG_pin}, {MUX3_s0, MUX3_s1, MUX3_s2, MUX3_s3, MUX3_SIG_pin}, {MUX4_s0, MUX4_s1, MUX4_s2, MUX4_s3, MUX4_SIG_pin}};
  
void setup() {

  Serial.begin(9600);
  
// BOUTON POUSSOIR
// ------------------------------------------------------------------
  pinMode(boutonPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(boutonPin), changement , RISING); // attache l’interruption externe n°0 à la fonction blink

// AFFICHAGE ECRAN
// ------------------------------------------------------------------

  lcd.init(); //initialisation de l'écran LCD
  lcd.cursor_on();
  lcd.blink_on();
  lcd.backlight();
  lcd.print("Jeu d'Echec");

  while (!Serial) {
    ; // attendre la connexion série
  }
// MULTIPLEXER 1
// ------------------------------------------------------------------
  pinMode(MUX1_s0, OUTPUT);
  pinMode(MUX1_s1, OUTPUT);
  pinMode(MUX1_s2, OUTPUT);
  pinMode(MUX1_s3, OUTPUT);

  pinMode(MUX1_SIG_pin,INPUT);

  digitalWrite(MUX1_s0, LOW);
  digitalWrite(MUX1_s1, LOW);
  digitalWrite(MUX1_s2, LOW);
  digitalWrite(MUX1_s3, LOW);
// ------------------------------------------------------------------
  
// MULTIPLEXER 2
// ------------------------------------------------------------------
  pinMode(MUX2_s0, OUTPUT);
  pinMode(MUX2_s1, OUTPUT);
  pinMode(MUX2_s2, OUTPUT);
  pinMode(MUX2_s3, OUTPUT);

  pinMode(MUX2_SIG_pin,INPUT);

  digitalWrite(MUX2_s0, LOW);
  digitalWrite(MUX2_s1, LOW);
  digitalWrite(MUX2_s2, LOW);
  digitalWrite(MUX2_s3, LOW);
// ------------------------------------------------------------------
// MULTIPLEXER 3
// ------------------------------------------------------------------
  pinMode(MUX3_s0, OUTPUT);
  pinMode(MUX3_s1, OUTPUT);
  pinMode(MUX3_s2, OUTPUT);
  pinMode(MUX3_s3, OUTPUT);

  pinMode(MUX3_SIG_pin,INPUT);

  digitalWrite(MUX3_s0, LOW);
  digitalWrite(MUX3_s1, LOW);
  digitalWrite(MUX3_s2, LOW);
  digitalWrite(MUX3_s3, LOW);
// ------------------------------------------------------------------

// MULTIPLEXER 4
// ------------------------------------------------------------------
  pinMode(MUX4_s0, OUTPUT);
  pinMode(MUX4_s1, OUTPUT);
  pinMode(MUX4_s2, OUTPUT);
  pinMode(MUX4_s3, OUTPUT);

  pinMode(MUX4_SIG_pin,INPUT);

  digitalWrite(MUX4_s0, LOW);
  digitalWrite(MUX4_s1, LOW);
  digitalWrite(MUX4_s2, LOW);
  digitalWrite(MUX4_s3, LOW);
// ------------------------------------------------------------------
  
  
}

void loop() {

  //Affichage pour faciliter la lecture des valeurs du plateau quand on les affiche dans le moniteur série pour faire des tests
  //Loop through and read all 16 values
  //Serial.println("ABCDEFGH");
  //Serial.println("---------------");
  
  
  //Regarde l'état du plateau en regardant chaque valeur reçue par les multiplexeurs
  for (int j=0; j<4; j++)
  {
    //Parcours les multiplexeurs 1 à 4
    
    for (int i = 0; i < 16; i ++) 
    {
      //Parcours les pin c0 à c15 du multiplexeur
      if (i < 8) //Si la case concernée appartient à la première ligne gérée par le multiplexeur
      {
        etat[j*2][i]=readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]);
      }
      else // Si la case concernée appartient à la deuxième ligne gérée par le multiplexeur
      {
        etat[j*2+1][i-8]=readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]);
      }
    }
  }
  delay(1000);
  
  //affichage du plateau et de son etat atuel
 // affiche(etat);
  //Serial.println();   /retour à la ligne pour faciliter la lecture des valeurs
  //Serial.println();
  //Serial.println();
  
 if(jeveuxchanger) //Si j'ai appuyé sur le bouton poussoir
  { 
      positionavant=changementPiece(); // Détermine la position initiale de la pièce qui a été bougée
      delay(100); // Pas forcément utile
      positionapres=changementPiece(); // Même chose mais pour la position finale
      affichepositions(positionavant,positionapres);
  }
  delay(1000);
  
}

float readMux(int channel, int MUX_s0, int MUX_s1, int MUX_s2, int MUX_s3, int MUX_SIG_pin) 
{
  //Permet de lire la valeur du channel du MUX (Multiplexeur) désiré
  int controlPin[] = {MUX_s0, MUX_s1, MUX_s2, MUX_s3};
  int muxChannel[16][4] = { {0, 0, 0, 0},
                            {1, 0, 0, 0},
                            {0, 1, 0, 0},
                            {1, 1, 0, 0},
                            {0, 0, 1, 0},
                            {1, 0, 1, 0},
                            {0, 1, 1, 0},
                            {1, 1, 1, 0},
                            {0, 0, 0, 1},
                            {1, 0, 0, 1},
                            {0, 1, 0, 1},
                            {1, 1, 0, 1},
                            {0, 0, 1, 1},
                            {1, 0, 1, 1},
                            {0, 1, 1, 1},
                            {1, 1, 1, 1}
                          };
  //loop through the 4 sig
  for (int i = 0; i < 4; i ++) 
  {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  
  return digitalRead(MUX_SIG_pin); //Renvoie 1 ou 0 en fonction de si l'interrupteur est fermé ou non
}
void affiche(int objet[8][8])
{
  //Fonction d'affichage du plateau
  for (int i = 0; i < 8; i ++) 
  {
      for (int j=0; j<8;j++)
      {
        Serial.print(objet[i][j]);
      }
      Serial.println();
  }
}
void changement()
{
  //Fonction liée à l'interrupt pour interrompre la fonction loop et changer la valeur de jeveuxchanger immédiatement après une pression sur le bouton poussoir
  if(jeveuxchanger){jeveuxchanger=false;}
  else{jeveuxchanger=true;}
}

void affichepositions(String avant, String apres)
{
  //Fonction affichant l'information destinée à l'API dans le moniteur série et qui transcrit cette information sur l'écran LCD
  Serial.println(avant+apres);
  lcd.clear(); // Efface l'écran LCD
  lcd.print("De :"+ avant+ " a :" +apres); // Affiche le mode
}

String changementPiece()
{
  // fonction qui retourne la postion de la pièce qui a bougé
  int etatBougerPiece1[8][8]; //variable qui va contenir les valeurs du plateau après le mouvement d'une pièce
  int positionPieceQuiBouge[2]={0,0};
  bool change=false;
  //Affichage des action
  //--------------------------------------------------------
  //Serial.println("Change la piece de place");
  lcd.clear(); // Efface l'écran LCD
  lcd.print("Mouvement du pion"); 
  delay(6000);
  //Serial.println("Enregistre les positions");
  lcd.clear(); // Efface l'écran LCD
  lcd.print("Enregistrement"); 
  delay(1000);
  //enregistrement du nouvel etat du plateau
  //---------------------------------------------------
  for (int j=0; j<4 && !change; j++)
  {
    for (int i = 0; i < 16 && !change; i ++) 
    {
      if (i < 8)
      {
        etatBougerPiece1[j*2][i]=readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]);
        if(etatBougerPiece1[j*2][i]!=etat[j*2][i]) //comparaison avec l'ancien etat
        {
          positionPieceQuiBouge[0]=j*2;
          positionPieceQuiBouge[1]=i;
          change=true;
          etat[j*2][i]=etatBougerPiece1[j*2][i];
        }
      }
      else
      {
        etatBougerPiece1[j*2+1][i-8]=readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]);
        if(etatBougerPiece1[j*2+1][i-8]!=etat[j*2+1][i-8]) //comparaison avec l'ancien etat
        {
          positionPieceQuiBouge[0]=j*2+1;
          positionPieceQuiBouge[1]=i-8;
          change=true;
          etat[j*2+1][i-8]=etatBougerPiece1[j*2+1][i-8];
        }
      }
    }
  }
  
  if(change)
  {
    
    //Serial.println("Il y a eu un changement de position");
    //Serial.println(correspondance[positionPieceQuiBouge[0]]+String(positionPieceQuiBouge[1]+1)); //parce que sur arduino les positions sont numérotés de 0 à 3 mais en vrai elles vont de 1 à 4 
    jeveuxchanger=false;
  }
  //Serial.println(positionPieceQuiBouge[0]);
  //Serial.println(positionPieceQuiBouge[1]);
  return String(correspondance[positionPieceQuiBouge[1]]+String(positionPieceQuiBouge[0]+1));
}
