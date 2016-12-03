using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            const double count = 60;
            Random rand = new Random();
            DateTime pom = DateTime.Now - new TimeSpan(5,0,0);
            StreamWriter sw = new StreamWriter("data.csv", false);
            int maxValue = 60, minValue = 75, oldValue = 65;
            for (int i = 0; i < count; i++)
            {
                int perc = rand.Next(0, 101);
                

                if(i < 40)
                {
                    minValue = oldValue - 5;
                    maxValue = oldValue + 5;
                    if(minValue < 60)
                    {
                        minValue = 60;
                    }
                    if(maxValue > 75)
                    {
                        maxValue = 75;
                    }
                }
                else if (i == 40)
                {
                    minValue = 110;
                    maxValue = 125;
                }
                else if (i < 48)
                {
                    minValue -= 6;
                    maxValue -= 6;
                }
                else if(i == 48)
                {
                    minValue = 60;
                    maxValue = 75;
                }
                else
                {
                    minValue = oldValue - 5;
                    maxValue = oldValue + 5;
                    if (minValue < 60)
                    {
                        minValue = 60;
                    }
                    if (maxValue > 75)
                    {
                        maxValue = 75;
                    }
                }
                //id,datetime,tep
                int a = rand.Next(minValue, maxValue);
                string radek = i.ToString() + "," + pom.ToString() + "," + a.ToString();
                sw.WriteLine(radek);
                Console.WriteLine(radek);
                pom = pom.AddSeconds(20);
                oldValue = a;
            }
            sw.Close();
            Console.WriteLine("done");
            Console.ReadKey();
        }
    }
}
