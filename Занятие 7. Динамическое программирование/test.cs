using System.Drawing;
using System.Windows.Forms;

public class DrawingExample : Form
{
    public DrawingExample()
    {
        this.ClientSize = new Size(800, 600);
        this.Paint += new PaintEventHandler(DrawingExample_Paint);
        this.DoubleBuffered = true; // Avoid flickering
    }

    private void DrawingExample_Paint(object sender, PaintEventArgs e)
    {
        Graphics g = e.Graphics;

        // Background
        g.Clear(Color.White);
        g.FillRectangle(Brushes.SkyBlue, 0, 0, ClientSize.Width, ClientSize.Height / 2);
        g.FillRectangle(Brushes.Green, 0, ClientSize.Height / 2, ClientSize.Width, ClientSize.Height / 2);

        // Mountains
        DrawMountain(g, 50, 100, 80, Color.Black);
        DrawMountain(g, 150, 50, 120, Color.LightGray);
        DrawMountain(g, 280, 120, 60, Color.DarkGray);
        DrawMountain(g, 350, 80, 90, Color.White);
        DrawMountain(g, 500, 100, 70, Color.White);
        DrawMountain(g, 600, 60, 110, Color.LightGray);
        DrawMountain(g, 720, 130, 50, Color.Black);

        // Trees
        DrawTree(g, 80, 350);
        DrawTree(g, 180, 400);
        DrawTree(g, 280, 370);
        DrawTree(g, 380, 420);
        DrawTree(g, 480, 380);
        DrawTree(g, 580, 410);
        DrawTree(g, 680, 360);
        DrawTree(g, 150, 480);
        DrawTree(g, 250, 500);
        DrawTree(g, 700, 470);

        // Clouds
        DrawCloud(g, 150, 50);
        DrawCloud(g, 400, 70);
        DrawCloud(g, 650, 40);

        // White Patches
        g.FillEllipse(Brushes.White, 150, 520, 50, 30);
        g.FillEllipse(Brushes.White, 350, 550, 80, 40);
        g.FillEllipse(Brushes.White, 580, 450, 60, 35);
        g.FillEllipse(Brushes.White, 250, 300, 30, 15);
        g.FillEllipse(Brushes.White, 450, 280, 20, 10);
    }

    private void DrawMountain(Graphics g, int x, int y, int height, Color color)
    {
        Point[] points = {
            new Point(x, ClientSize.Height / 2),
            new Point(x + height / 2, y),
            new Point(x + height, ClientSize.Height / 2)
        };

        using (Brush brush = new SolidBrush(color))
        {
            g.FillPolygon(brush, points);
            g.DrawPolygon(Pens.Black, points); // Outline
        }
    }

    private void DrawTree(Graphics g, int x, int y)
    {
        // Trunk
        g.FillRectangle(Brushes.Brown, x - 10, y, 20, 40);
        g.DrawRectangle(Pens.Black, x - 10, y, 20, 40);

        // Leaves
        g.FillEllipse(Brushes.LimeGreen, x - 30, y - 50, 60, 50);
        g.DrawEllipse(Pens.Black, x - 30, y - 50, 60, 50);
       
        // Spots
        g.FillEllipse(Brushes.White, x - 15, y - 40, 15, 15);
        g.FillEllipse(Brushes.White, x + 5, y - 35, 10, 10);
        g.FillEllipse(Brushes.White, x - 20, y - 25, 12, 12);
    }

    private void DrawCloud(Graphics g, int x, int y)
    {
        g.FillEllipse(Brushes.White, x, y, 50, 30);
        g.FillEllipse(Brushes.White, x + 20, y - 10, 40, 30);
        g.FillEllipse(Brushes.White, x + 50, y, 50, 30);
        g.DrawEllipse(Pens.Black, x, y, 50, 30);
        g.DrawEllipse(Pens.Black, x + 20, y - 10, 40, 30);
        g.DrawEllipse(Pens.Black, x + 50, y, 50, 30);
    }

    public static void Main()
    {
        Application.Run(new DrawingExample());
    }
}