// ------------------------------------------------------------------
// PROJET PI² : Jeu d'échec KAIROS
// Par Marçal Thomas, Kermel Aurore
// Janvier 2023
// ------------------------------------------------------------------

// BOUTON POUSSOIR
// ------------------------------------------------------------------
int boutonPin = 2;
int etat[2][8];

bool jeveuxchanger=false;
int positionavant;
int positionapres;

// MULTIPLEXER 1 - Lignes
// ------------------------------------------------------------------
//Mux_1 control pins
int MUX1_s0 = 9;
int MUX1_s1 = 10;
int MUX1_s2 = 11;
int MUX1_s3 = 12;
//Mux_1 in "SIG" pin
int MUX1_SIG_pin = 7;
// ------------------------------------------------------------------


int MUX[5]  = {MUX1_s0, MUX1_s1, MUX1_s2, MUX1_s3, MUX1_SIG_pin};
  
void setup() {

// BOUTON POUSSOIR
// ------------------------------------------------------------------
  pinMode(boutonPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(boutonPin), changement , RISING); // attache l’interruption externe n°0 à la fonction blink
  
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

  Serial.begin(9600);
  
}

void loop() {

  //Loop through and read all 16 values
  //Serial.println("A B C D E F G H");
  //Serial.println("---------------");
    for (int i = 0; i < 16; i ++) 
    {
      if (i < 8)
      {
        if (readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]) < 4.95) {etat[0][i]=0;}
        else {etat[0][i]=1;}    
      }
      else
      {
        if (readMux(i, MUX[0], MUX[1], MUX[2], MUX[3], MUX[4]) < 4.95) {etat[1][i]=0;}
        else {etat[1][i]=1;}    
      }
    }
  delay(3000);
  
  Serial.println();  
  Serial.println();
  Serial.println();
  affiche(etat);
  if(jeveuxchanger){Serial.println("CHANGE !");}
  
}

float readMux(int channel, int MUX_s0, int MUX_s1, int MUX_s2, int MUX_s3, int MUX_SIG_pin) {
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
  for (int i = 0; i < 4; i ++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  //read the value at the SIG pin
  int val = analogRead(MUX_SIG_pin); //return the value

  float voltage = (val*5.0)/1024;
  return voltage;
}
void affiche(int objet[2][8])
{
  for (int i = 0; i < 2; i ++) 
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
  jeveuxchanger=true;
}
