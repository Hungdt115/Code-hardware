int infrared = 4;
int led = 2;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(infrared, INPUT_PULLUP);
}
void loop() 
{
  if(digitalRead(infrared) == 0)
  {
    digitalWrite(led, HIGH);
    delay (100);    
        digitalWrite(led, LOW);
    delay (100); 
  }
  else
  {   
    digitalWrite(led, LOW);
  }
}
