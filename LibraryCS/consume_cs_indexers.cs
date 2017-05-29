using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibraryCS
{
    public class IndexerClass
    {
        private int[] myArray = new int[100];
        public int this[int index]
        {
            get 
            {
                if (index < 0 || index >= 100)
                    return 0;
                else
                    return myArray[index];
            }
            set
            {
                if (!(index < 0 || index >= 100))
                    myArray[index] = value;
            }
        }
    }

    public class MainClass
    {
        public static void Main()
        {
            IndexerClass b = new IndexerClass();
            
            b[3] = 256;
            b[5] = 1024;
            for (int i = 0; i <= 10; i++)
            {
                Console.WriteLine("Element #{0} = {1}", i, b[i]);
            }
        }
    }
}
