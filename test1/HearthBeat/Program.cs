using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace HearthBeat
{
    class Program
    {
        static void Main(string[] args)
        {
            double alpha = 0.75;
            int period = 100;


            double delta = 3.5;
            double oldValue = 0;
            int counter = 0, sumCount = 0;
            //int sum = 0;
            double oldMin = 1023, oldMax = 0;
            bool isHigh = false;
            int[] field = new int[15];
            const int avgcount = 5;
            double[] avg = new double[avgcount];
            int oldest = 0;


            SerialPort sp = new SerialPort()
            {
                BaudRate = 9600,
                PortName = "COM3"
            };
            sp.Open();

            while(true)
            {
                int data;
                if(int.TryParse(sp.ReadLine(), out data))
                {
                    double value1 = alpha * oldValue + (1 - alpha) * data;

                    //Console.Write(string.Format("{0:N2}", value1));
                    /*Serial.print (rawValue);
                    Serial.print (";");*/
                    //Serial.println(String((int)value) + "," + String((int)((value - (double)((int)value))*100)));
                    //Serial.print(";");
                    avg[oldest] = value1;
                    if (oldest < avgcount - 1)
                    {
                        oldest++;
                    }
                    else
                    {
                        oldest = 0;
                    }
                    double sum = 0;
                    for (int i = 0; i < avgcount; i++)
                    {
                        sum += avg[i];
                    }
                    double value = sum / avgcount;
                    sum = 0;
                    //Serial.println(String((int)avgvalue) + "," + String((int)((avgvalue - (double)((int)avgvalue))*100)));
                    //Console.Write(string.Format("{0:N2}", value));
                    //Console.WriteLine("\t" + DateTime.Now.Minute + ":" + DateTime.Now.Second + "," + DateTime.Now.Millisecond);

                    if (!isHigh)
                    {
                        //Serial.print("Jsme dole");
                        
                        if (oldMin > value)
                        {
                            oldMin = value;
                        }
                        
                        if (value - oldMin > delta)
                        {
                            //Serial.print("Presli jsme nahoru, oldMin=");
                            Console.WriteLine("Presli jsme nahoru");
                            //Serial.print(oldMin);
                            //Serial.print("counter=");
                            //Serial.print(counter);
                            isHigh = true;

                            Console.WriteLine("counter = " + counter);
                            field[sumCount] = counter * period;
                            sumCount++;
                            int x = 15;
                            if (sumCount == x)
                            {
                                double med = median(field);
                                /*Serial.print(value);
                                Serial.print(", ");
                                Serial.print(oldMin);
                                Serial.print(";");
                                Serial.print(med);*/
                                Console.WriteLine(med + ";" + 60000 / med * 8);
                                //Serial.print(";");
                                //Serial.println(60000 / med);
                                sumCount = 0;
                            }
                            else
                            {
                                //Serial.println();
                            }
                            counter = 0;
                        }
                        else
                        {
                            //Serial.println();
                            counter++;
                        }
                    }
                    else
                    {
                        if (oldMax < value)
                        {
                            oldMax = value;
                        }

                        //Serial.print("Jsme nahore");
                        if (oldMax - value > delta)
                        {
                            //Serial.println("Presli jsme dolu");
                            Console.WriteLine("Presli jsme dolu");
                            isHigh = false;
                            oldMax = 0;
                            oldMin = 1023;
                        }
                        else
                        {
                            

                            //Serial.println();
                        }
                        counter++;
                    }


                    oldValue = value;
                }
                
                
            }

            
        }
        static double median(int[] a)
        {
            int size = 15;
            //Serial.println(size);
            for (int i = 0; i < (size - 1); i++)
            {
                for (int o = 0; o < (size - (i + 1)); o++)
                {
                    if (a[o] > a[o + 1])
                    {
                        int t = a[o];
                        a[o] = a[o + 1];
                        a[o + 1] = t;
                    }
                }

            }
            //for(int i = 0; i < size; i++) {
            //Serial.println(a[i]);
            //}
            if (size % 2 == 0)
            {
                return ((a[size / 2] + a[size / 2 - 1]) / 2.0);
            }
            return (double)a[size / 2];
        }
    }
    
}
