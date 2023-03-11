// ------------------------------------------------------------------
// PROJET PI² : Jeu d'échec KAIROS
// Par Marçal Thomas, Kermel Aurore
// Janvier 2023
// ------------------------------------------------------------------

// BOUTON POUSSOIR
// ------------------------------------------------------------------
int boutonPin = 2;
int etat[8][8]={};

bool jeveuxchanger=false;
int positionavant;
int positionapres;

// MULTIPLEXER 1 - Lignes
// ------------------------------------------------------------------
//Mux_1 control pins
int MUX1_s0 = 52;
int MUX1_s1 = 50;
int MUX1_s2 = 53;
int MUX1_s3 = 51;
//Mux_1 in "SIG" pin
int MUX1_SIG_pin = 15;
// ------------------------------------------------------------------

// MULTIPLEXER 2
// ------------------------------------------------------------------
//Mux_2 control pins
int MUX2_s0 = 48;
int MUX2_s1 = 46;
int MUX2_s2 = 49;
int MUX2_s3 = 47;
//Mux_2 in "SIG" pin
int MUX2_SIG_pin = 14;
// ------------------------------------------------------------------

// MULTIPLEXER 3
// ------------------------------------------------------------------
//Mux_3 control pins
int MUX3_s0 = 44;
int MUX3_s1 = 42;
int MUX3_s2 = 45;
int MUX3_s3 = 43;
//Mux_3 in "SIG" pin
int MUX3_SIG_pin = 13;
// ------------------------------------------------------------------

// MULTIPLEXER 4
// ------------------------------------------------------------------
//Mux_4 control pins
int MUX4_s0 = 40;
int MUX4_s1 = 38;
int MUX4_s2 = 41;
int MUX4_s3 = 39;
//Mux_4 in "SIG" pin
int MUX4_SIG_pin = 12;
// ------------------------------------------------------------------

int MUX[4][5]  = {{MUX1_s0, MUX1_s1, MUX1_s2, MUX1_s3, MUX1_SIG_pin}, {MUX2_s0, MUX2_s1, MUX2_s2, MUX2_s3, MUX2_SIG_pin}, {MUX3_s0, MUX3_s1, MUX3_s2, MUX3_s3, MUX3_SIG_pin}, {MUX4_s0, MUX4_s1, MUX4_s2, MUX4_s3, MUX4_SIG_pin}};
  
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

  Serial.begin(9600);
  
}

void loop() {

  //Loop through and read all 16 values
  //Serial.println("A B C D E F G H");
  //Serial.println("---------------");
  
  for (int j = 0; j < 4; j++){
    for (int i = 0; i < 16; i ++) {
      if (i < 8){
        if (readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]) < 4.95){
          //Serial.print("0 ");
          if(j%2==0){etat[j][i]=0;}

        }
        else{
          //Serial.print("1 ");
          if(j%2==0){etat[j][i]=1;}
        }    
      }
      else if (i == 8){
        //Serial.println();
        if (readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]) < 4.95){
          //Serial.print("0 ");
          if(j%2==1){etat[j][i]=0;}
        }
        else{
          //Serial.print("1 ");
          if(j%2==1){etat[j][i]=1;}
        }     
      }
      else if (i == 15){
        if (readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]) < 4.95){
          //Serial.print("0 ");
          if(j%2==1){etat[j][i]=0;}
        }
        else{
          //Serial.print("1 ");
          if(j%2==1){etat[j][i]=1;}
        }   
        //Serial.println();
      }
      else {
        if (readMux(i, MUX[j][0], MUX[j][1], MUX[j][2], MUX[j][3], MUX[j][4]) < 4.95){
          //Serial.print("0 ");
          if(j%2==1){etat[j][i]=0;}
        }
        else{
          //Serial.print("1 ");
          if(j%2==1){etat[j][i]=1;}
        }   
      }
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
void affiche(int objet[8][8])
{
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
  jeveuxchanger=true;
}
