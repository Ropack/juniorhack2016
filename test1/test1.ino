// Pulse Monitor Test Script
int sensorPin = 0;
double alpha = 0.75;
int period = 50;
double change = 0.0;
double minval = 0.0;
void setup ()
{
  Serial.begin (9600);
}
void loop ()
{
    static double oldValue = 0;
    static double oldChange = 0;
 
    int rawValue = analogRead (sensorPin);
    double value = alpha * oldValue + (1 - alpha) * rawValue;
 
    Serial.print (rawValue);
    Serial.print (";");
    Serial.println(String((int)value) + "," + String((int)((value - (double)((int)value))*100)));
    oldValue = value;
 
    delay (period);
}
