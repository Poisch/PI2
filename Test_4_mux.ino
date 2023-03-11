// ------------------------------------------------------------------
// PROJET PI² : Jeu d'échec KAIROS
// Par Marçal Thomas, Kermel Aurore
// Janvier 2023
// ------------------------------------------------------------------

// BOUTON POUSSOIR
// ------------------------------------------------------------------
int boutonPin = 2;
int etat[4][8];

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


// MULTIPLEXER 2 - Lignes
// ------------------------------------------------------------------
//Mux_2 control pins
int MUX2_s0 = 22;
int MUX2_s1 = 24;
int MUX2_s2 = 26;
int MUX2_s3 = 28;
//Mux_2 in "SIG" pin
int MUX2_SIG_pin = 30;

int MUX[2][5]  = {{MUX1_s0, MUX1_s1, MUX1_s2, MUX1_s3, MUX1_SIG_pin},{MUX2_s0, MUX2_s1, MUX2_s2, MUX2_s3, MUX2_SIG_pin}};
  
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

  Serial.begin(9600);
  
}

void loop() 
{

  //Loop through and read all 16 values
  //Serial.println("A B C D E F G H");
  //Serial.println("---------------");
  for (int j=0; j<2; j++)
  {
    for (int i = 0; i < 16; i ++) 
    {
      if (i < 8)
      {
        etat[j*2][i]=readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]);
      }
      else
      {
        etat[j*2+1][i-8]=readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]);
      }
    }
  }
  delay(1000);
  
  affiche(etat);
  Serial.println();  
  //Serial.println();
  //Serial.println();
  
 if(jeveuxchanger)
    {
      positionavant=changementPiece();
      delay(100);
      positionapres=changementPiece();
      Serial.println("Vous pouvez poser la piece");
    }
    delay(1000);
  
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
void affiche(int objet[4][8])
{
  for (int i = 0; i < 4; i ++) 
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
  if(jeveuxchanger){jeveuxchanger=false;}
  else{jeveuxchanger=true;}
}

int changementPiece()
{
  // fonction qui retourne la postion de la pièce qui a bougé
  int etatBougerPiece1[2][8];
  int positionPieceQuiBouge[2];
  bool change=false;
  Serial.println("Change la piece de place");
  delay(3000);
  Serial.println("Enregistre les positions");
  //enregistrement du nouvel etat du plateau
  for (int j=0; j<2; j++)
  {
    for (int i = 0; i < 16; i ++) 
    {
      if (i < 8)
      {
        etatBougerPiece1[j*2][i]=readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]);
        if(etatBougerPiece1[j*2][i]!=etat[j*2][i])
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
        if(etatBougerPiece1[j*2+1][i-8]!=etat[j*2+1][i-8])
        {
          positionPieceQuiBouge[0]=j*2+1;
          positionPieceQuiBouge[1]=i-8;
          change=true;
          etat[j*2+1][i-8]=etatBougerPiece1[j*2+1][i-8];
        }
      }
    }
  }
  //comparaison avec l'ancien etat

  if(change)
  {
    //on peut allumer la led verte
    Serial.println("Il y a eu un changement de position");
    Serial.println("La piece qui a bouge etait en ligne : "+ String(positionPieceQuiBouge[0]+1)+"\nEn colonne : "+ String(positionPieceQuiBouge[1]+1)); //parce que sur arduino les positions sont numérotés de 0 à 3 mais en vrai elles vont de 1 à 4 
    jeveuxchanger=false;
  }
  return positionPieceQuiBouge;
}
