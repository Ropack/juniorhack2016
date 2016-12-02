// Pulse Monitor Test Script
int sensorPin = 0;
double alpha = 0.75;
int period = 10;


double delta = 2.5;
double oldValue = 0, oldChange = 0;
int counter = 0, sumCount = 0;
//int sum = 0;
double oldMin = 1023;
bool isHigh = false;
int field[15];

void setup ()
{
  Serial.begin (9600);
  Serial.println("start");
}


void loop ()
{
    //static double oldValue = 0;
    //static double oldChange = 0;
    
 
    int rawValue = analogRead (sensorPin);
    double value = alpha * oldValue + (1 - alpha) * rawValue;

    
 
    /*Serial.print (rawValue);
    Serial.print (";");
    Serial.println(String((int)value) + "," + String((int)((value - (double)((int)value))*100)));*/
    
    

    if(!isHigh) {
      //Serial.println("Jsme dole");
      if(value - oldValue > 0) {
        if(oldMin > oldValue) {
          oldMin = oldValue;
        }
      }
      else {
        oldMin = 1023;
      }
      if(value - oldMin > delta) {
        Serial.print("Presli jsme nahoru, oldMin=");
        Serial.println(oldMin);
        isHigh = true;

        field[sumCount] = counter * period;
        //sum += counter * period;
        sumCount++;
        int x = 15;
        if(sumCount == x) {
          double med = median(field);
          Serial.print(value);
          Serial.print(", ");
          Serial.print(oldMin);
          Serial.print(", ");
          Serial.print(med);
          Serial.print(", ");
          Serial.println(60000 / med);
          //sum = 0;
          sumCount = 0;
          counter++;
        }

      }
    }
    else {
      //Serial.println("Jsme nahore");
      if (value < oldMin + 1.2) {
        Serial.println("Presli jsme dolu");
        isHigh = false;
        oldMin = 1023;
      }
      else {
        counter++;
      }
    }
    
    
    oldValue = value;
    
    delay (period);
}

double median(int a[]) {
    int size = 15;
    Serial.println(size);
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) {
                    int t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
    }
    if (size % 2 == 0) {
      return ((a[size/2] + a[size/2-1]) / 2.0);
    }
    return a[size/2] / 2.0;
}
