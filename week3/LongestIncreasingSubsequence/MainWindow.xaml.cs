using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Collections;   

namespace LongestIncreasingSubsequence
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {

        const int MAX = 1000;

        ArrayList x = new ArrayList(); //array to deal with

        ArrayList LIS = new ArrayList(); //subscript(s) in array x
        int length = -1; //length of LIS
        
        Random ra = new Random();

        public MainWindow()
        {
            InitializeComponent();
        }
        
        //ref: http://blog.csdn.net/joylnwang/article/details/6766317
        int doLIS(int[] array, int length, int[] result)  
        {            
            
  
            int[] lis = new int[length];  
  
            int[] pre = new int[length];  
  
            lis[0] = 0;  
            int max = 1;  

            for(int i = 0; i < length; ++i)  
            {  
                pre[i] = i;  
            }  

            //initialization done
  
            for(int i = 1; i < length; ++i)  
            {  
                
                int j = 0; int k = max - 1;  
        
                //binary search
                int m;
                while(k - j > 1)  
                {  
                    m = (j + k) / 2;  
                    if(array[lis[m]] < array[i])  
                    {  
                        j = m;  
                    }  
                    else  
                    {  
                        k = m;  
                    }  
                }  
  
                if(array[lis[j]] < array[i])  
                {  
                    j = k;  
                }  
  
                
                if(j == 0)  
                {  
                    if(array[lis[0]] >= array[i])  
                    {  
                        lis[0] = i;  
                        continue;  
                    }  
                }  

                if(j == max - 1)  
                {  
                    if(array[lis[j]] < array[i])  
                    {  
                        pre[i] = lis[j];  
                        lis[max++] = i;  
                        continue;  
                    }  
                }  
  
                pre[i] = lis[j - 1];  
                lis[j] = i;  
            }  
  
            //generate the subsequence
            int a = max - 1;  
            int b = lis[max - 1];  
  
            while(pre[b] != b)  
            {  
                result[a--] = b;  
                b = pre[b];  
            }  
  
            result[a] = b;

            return max;  
        }  


        void calc()
        {
            int n = x.Count;
            int[] arr = new int[n];
            int[] result = new int[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = (int)x[i];
            }
            length = doLIS(arr, n, result);

            LIS.Clear();
            for (int i = 0; i < length; i++)
            {
                LIS.Add(result[i]);
            }
        }

        void update() //update UI
        {
            int n = x.Count;
            
            this.label.Content = "Length: " + length;
            
            this.list.Items.Clear();
            for (int i = 0; i < n; i++)
            {
                ListBoxItem item = new ListBoxItem();
                
                item.Content = x[i];
                int r_, g_, b_;

                double k = (double)(int)x[i] / (double)MAX;

                HsvToRgb(180, k, 1, out r_, out g_, out b_);
                foreach (int ___ in LIS)
                {
                    if (___ == i)
                    {
                        HsvToRgb(0, .2 + k * .8, 1, out r_, out g_, out b_);
                        break;
                    }
                }

                byte r__ = System.BitConverter.GetBytes(r_)[0];
                byte g__ = System.BitConverter.GetBytes(g_)[0];
                byte b__ = System.BitConverter.GetBytes(b_)[0];
                item.Background = new LinearGradientBrush(Colors.White, Color.FromRgb(r__, g__, b__), 90);

                this.list.Items.Add(item);
            }
        }
        void insert()
        {
            int r = ra.Next() % MAX;
            x.Add(r); 
        }

        void clear()
        {
            x.Clear();
            this.list.Items.Clear();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            insert();
            calc();
            update();
        }
        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < 10; i++)
            {
                insert();
            }
            calc();
            update();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            clear();
        }

        //ref: http://stackoverflow.com/questions/1335426/is-there-a-built-in-c-net-system-api-for-hsv-to-rgb
        void HsvToRgb(double h, double S, double V, out int r, out int g, out int b)
        {
            double H = h;
            while (H < 0) { H += 360; };
            while (H >= 360) { H -= 360; };
            double R, G, B;
            if (V <= 0)
            { R = G = B = 0; }
            else if (S <= 0)
            {
                R = G = B = V;
            }
            else
            {
                double hf = H / 60.0;
                int i = (int)Math.Floor(hf);
                double f = hf - i;
                double pv = V * (1 - S);
                double qv = V * (1 - S * f);
                double tv = V * (1 - S * (1 - f));
                switch (i)
                {

                    // Red is the dominant color

                    case 0:
                        R = V;
                        G = tv;
                        B = pv;
                        break;

                    // Green is the dominant color

                    case 1:
                        R = qv;
                        G = V;
                        B = pv;
                        break;
                    case 2:
                        R = pv;
                        G = V;
                        B = tv;
                        break;

                    // Blue is the dominant color

                    case 3:
                        R = pv;
                        G = qv;
                        B = V;
                        break;
                    case 4:
                        R = tv;
                        G = pv;
                        B = V;
                        break;

                    // Red is the dominant color

                    case 5:
                        R = V;
                        G = pv;
                        B = qv;
                        break;

                    // Just in case we overshoot on our math by a little, we put these here. Since its a switch it won't slow us down at all to put these here.

                    case 6:
                        R = V;
                        G = tv;
                        B = pv;
                        break;
                    case -1:
                        R = V;
                        G = pv;
                        B = qv;
                        break;

                    // The color is not defined, we should throw an error.

                    default:
                        //LFATAL("i Value error in Pixel conversion, Value is %d", i);
                        R = G = B = V; // Just pretend its black/white
                        break;
                }
            }
            r = Clamp((int)(R * 255.0));
            g = Clamp((int)(G * 255.0));
            b = Clamp((int)(B * 255.0));
        }

        int Clamp(int i)
        {
            if (i < 0) return 0;
            if (i > 255) return 255;
            return i;
        }
        
    }
}
