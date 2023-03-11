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

void loop() 
{

  //Loop through and read all 16 values
  //Serial.println("A B C D E F G H");
  //Serial.println("---------------");
  for (int i = 0; i < 16; i ++) 
  {
    if (i < 8)
    {
      etat[0][i]=readMux(i, MUX[0], MUX[1], MUX[2], MUX[3], MUX[4]);
    }
    else
    {
      etat[1][i-8]=readMux(i, MUX[0], MUX[1], MUX[2], MUX[3], MUX[4]);
      //Serial.println(readMux(i, MUX[0], MUX[1], MUX[2], MUX[3], MUX[4]));  
    }
  }
  delay(1000);
  
  affiche(etat);
  Serial.println();  
  Serial.println();
  Serial.println();
  
  if(jeveuxchanger)
  {
    Serial.println("CHANGE !");
    jeveuxchanger=false;
    
  }
  
}

float readMux(int channel, int MUX_s0, int MUX_s1, int MUX_s2, int MUX_s3, int MUX_SIG_pin) 
{
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
  
  return digitalRead(MUX_SIG_pin);
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
