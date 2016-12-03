// Pulse Monitor Test Script
int sensorPin = 0;
double alpha = 0.75;
int period = 50;


double delta = 3.5;
double oldValue = 0, oldChange = 0;
int counter = 0, sumCount = 0;
//int sum = 0;
double oldMin = 1023, oldMax = 0;
bool isHigh = false;
int field[15];
const int avgcount = 5;
double avg[avgcount];
int oldest = 0;


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
    double value1 = alpha * oldValue + (1 - alpha) * rawValue;

 
    /*Serial.print (rawValue);
    Serial.print (";");*/
    //Serial.println(String((int)value) + "," + String((int)((value - (double)((int)value))*100)));
    //Serial.print(";");
    avg[oldest] = value1;
    if(oldest < avgcount-1) {
      oldest++;
    }
    else {
      oldest = 0;
    }
    double sum;
    for(int i = 0; i < avgcount; i++) {
      sum += avg[i];
    }
    double value = sum / avgcount;
    sum = 0;
    //Serial.println(String((int)avgvalue) + "," + String((int)((avgvalue - (double)((int)avgvalue))*100)));

    if(!isHigh) {
      //Serial.print("Jsme dole");
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
        Serial.print(oldMin);
        isHigh = true;
        

        field[sumCount] = counter * period;
        sumCount++;
        int x = 15;
        if(sumCount == x) {
          double med = median(field);
          /*Serial.print(value);
          Serial.print(", ");
          Serial.print(oldMin);
          Serial.print(";");*/
          Serial.print(med);
          Serial.print(";");
          Serial.println(60000 / med);
          sumCount = 0;
        }
        else {
          Serial.println();
        }
        counter = 0;
      }
      else {
        //Serial.println();
      }
    }
    else {
      //Serial.print("Jsme nahore");
      if (value < oldMin + 1.5) {
        Serial.println("Presli jsme dolu");
        isHigh = false;
        oldMin = 1023;
      }
      else {
        counter++;
        //Serial.println();
      }
    }
    
    
    oldValue = value;
    
    delay (period);
}

double median(int a[]) {
    int size = 15;
    //Serial.println(size);
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) {
                    int t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
        
    }
    //for(int i = 0; i < size; i++) {
      //Serial.println(a[i]);
    //}
    if (size % 2 == 0) {
      return ((a[size/2] + a[size/2-1]) / 2.0);
    }
    return (double)a[size/2];
}
