int boutonPin=2;

void setup() {
  // put your setup code here, to run once:
  pinMode(boutonPin,INPUT);
  attachInterrupt(0, changement , RISING); // attache l’interruption externe n°0 à la fonction blink
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(2));
  delay(1000);
}

void changement()
{
  Serial.println("Hello");
}
