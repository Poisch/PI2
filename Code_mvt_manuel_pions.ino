// C++ code
// Par KERMEL Aurore
// Mars 2023



//Definifition des cases et numéro des pin associées aux cases
int c11=4; //numéro de la pin associée à la case en ligne 1 colonne 1
int c12=5; // même fonctionnement
int c13=6;
int c14=7;
int etat[4];


//Definition du bouton changement
int pinBouton=3;
bool jeveuxchanger=false;
int positionavant;
int positionapres;


//definition des pin de la led RGB

int pinRouge=10;
int pinBleu=9;
int pinVert=11;


void setup()
{
  //la detection
  pinMode(c11,INPUT); 
  pinMode(c12,INPUT);
  pinMode(c13,INPUT);
  pinMode(c14,INPUT);

  //LED pour afficher les étapes
  pinMode(pinRouge,OUTPUT);
  pinMode(pinBleu,OUTPUT);
  pinMode(pinVert,OUTPUT);
  //bouton changement
  pinMode(pinBouton,INPUT);
  attachInterrupt(digitalPinToInterrupt(pinBouton),changement,RISING);
  //attachInterrupt(digitalPinToInterrupt(pinBouton),changement2,FALLING);
  //affichage dans le moniteur
  Serial.begin(9600);
}




void loop()
{
  //affichage des etats
    for (int j=4; j<8 && !jeveuxchanger;j++)
    {
      Serial.print(digitalRead(j));
      etat[j-4]=digitalRead(j);
    }
    Serial.println();
    Serial.println();

    if(jeveuxchanger)
    {
      positionavant=changementPiece();
      delay(100);
      positionapres=changementPiece();
      Serial.println("Vous pouvez poser la pièce");
    }
    delay(1000);
}


void changement () 
{
  if(!jeveuxchanger)
  {
    jeveuxchanger=true;
  }
  
} 


void couleur(int rouge,int vert, int bleu)
{
  analogWrite(pinRouge, rouge);
  analogWrite(pinVert,vert);
  analogWrite(pinBleu,bleu);
}

int changementPiece()
{
  // fonction qui retourne la postion de la pièce qui a bougé
  int etatBougerPiece1[4];
  int positionPieceQuiBouge;
  bool change=false;
  Serial.println("Change la piece de place");
  couleur(0,0,250);  
  delay(3000);
  Serial.println("Enregistre les positions");
  couleur(250,0,0);
  for (int j=4; j<12 && !change;j++)
  {
  etatBougerPiece1[j-4]=digitalRead(j);
    if(etatBougerPiece1[j-4]!=etat[j-4])
    {
      positionPieceQuiBouge=j-4;
      change=true;
      etat[j-4]=etatBougerPiece1[j-4];
      
    }
  Serial.print(digitalRead(j)+" ");
  }
  if(change)
  {
    //on peut allumer la led verte
    Serial.println("Il y a eu un changement de position");
    Serial.println("La piece qui a bougé était en "+ String(positionPieceQuiBouge+1)); //parce que sur arduino les positions sont numérotés de 0 à 3 mais en vrai elles vont de 1 à 4 
    jeveuxchanger=false;
  }
  return positionPieceQuiBouge;
}
