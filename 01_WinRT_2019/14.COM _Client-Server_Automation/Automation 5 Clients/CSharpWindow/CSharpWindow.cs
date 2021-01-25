using System;
using System.Drawing;
using System.Windows.Forms;

public class CSharpWindow:Form
{
	public static void Main()
	{
		Application.Run(new CSharpWindow());
	}
	
	public CSharpWindow()
	{
//		Icon = new Icon("MyIcon.ico");
		Text = " c# Windows";
		Width = 800;
		Height = 500;
		BackColor = Color.Black;
		ResizeRedraw = true;
		
		this.KeyDown += new KeyEventHandler(MyKeyDown);
		this.MouseDown += new MouseEventHandler(MyMouseDown);
	}
	protected override void OnPaint(PaintEventArgs par)
	{
		
		Graphics grfs = par.Graphics;
		StringFormat strfmt = new StringFormat();
		strfmt.Alignment = StringAlignment.Center;
		strfmt.LineAlignment = 	StringAlignment.Center;
		grfs.DrawString("Hellow Sir !!!",Font,new SolidBrush(System.Drawing.Color.Green),ClientRectangle,strfmt);
	}
	void MyKeyDown(Object Sender,KeyEventArgs e)
	{
		MessageBox.Show("A Kew Is Pressed");
	}
	void MyMouseDown(Object Sender,MouseEventArgs e)
	{
		MessageBox.Show("A Kew Is Pressed");
	}
}

