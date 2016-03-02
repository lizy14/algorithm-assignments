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
using System.Runtime.InteropServices;
using System.Collections;   

namespace Gui
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        Canvas canv;
        Line _l;
        ArrayList points;
        const int RADIUS = 6;
        public MainWindow()
        {
            InitializeComponent();
            points = new ArrayList();  
 
            canv = new Canvas();
            this.Content = canv;
            canv.Margin = new Thickness(0, 0, 0, 0);
            canv.Background = new SolidColorBrush(Colors.White);

            _l = new Line();
            _l.X1 = 0;
            _l.Y1 = 0;
            _l.X2 = 0;
            _l.Y2 = 0;

            _l.Stroke = new SolidColorBrush(Colors.Blue);

            canv.Children.Add(_l);
            
        }
        
        [DllImport("Library.dll")]
        static extern void addPoint(int x, int y);
        [DllImport("Library.dll")]
        static extern int getA();
        [DllImport("Library.dll")]
        static extern int getB();


        protected override void OnMouseDown(MouseButtonEventArgs e)
        {
            Point p = e.GetPosition(this);

            points.Add(p);

            addPoint((int)p.X, (int)p.Y);

            int a = getA();
            int b = getB();


            //Ellipse

            Ellipse el = new Ellipse();
            el.Fill = new SolidColorBrush(Colors.Blue);
            el.Stroke = new SolidColorBrush(Colors.Blue);
            el.Width = RADIUS;
            el.Height = RADIUS;

            el.SetValue(Canvas.ZIndexProperty, 1);
            el.SetValue(Canvas.LeftProperty, p.X - RADIUS/2);
            el.SetValue(Canvas.TopProperty, p.Y - RADIUS/2);

            canv.Children.Add(el);

            
            if (a != 0 && b != 0)
            {
                _l.X1 = ((Point)(points[a - 1])).X;
                _l.Y1 = ((Point)(points[a - 1])).Y;

                _l.X2 = ((Point)(points[b - 1])).X;
                _l.Y2 = ((Point)(points[b - 1])).Y;

                canv.Children[0] = _l;
            }
       }
    }
}
