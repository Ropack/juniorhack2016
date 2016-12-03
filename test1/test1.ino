int sensorPin = 0;
int period = 100;

void setup ()
{
  Serial.begin (9600);
}

void loop ()
{
  int rawValue = analogRead (sensorPin);
  Serial.println(rawValue);
  delay (period);
}


