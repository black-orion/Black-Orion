

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace GBO
{
	/// <summary>
	/// Description of MainForm.
	/// </summary>
	public partial class MainForm : Form
	{
		public MainForm()
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();

           
			
			//
			// TODO: Add constructor code after the InitializeComponent() call.
			//
		}

		
		void Timer1Tick(object sender, EventArgs e)
		{

			System.IntPtr winParent;
			System.IntPtr x;
            System.IntPtr y;
            System.IntPtr z;
			System.IntPtr winHandle = Usr32.FindWin("ConsoleWindowClass", "Black-Orion  Login Serveur v14.0");
			if(winHandle != System.IntPtr.Zero)
			{
				winParent = Usr32.GetParent(winHandle);
				x = Usr32.SetParent(winHandle, this.tabPage1.Handle);
				x = Usr32.SetWindowPos(winHandle, 1, 10, 10, 500, 300, 0);
				this.timer1.Enabled = false;
			}
            winHandle = Usr32.FindWin("ConsoleWindowClass", "Black-Orion Char-Serveur v14.0");
			if(winHandle != System.IntPtr.Zero)
			{
				winParent = Usr32.GetParent(winHandle);
				y = Usr32.SetParent(winHandle, this.tabPage2.Handle);
				y = Usr32.SetWindowPos(winHandle, 1, 10, 10, 500, 300, 0);
				this.timer1.Enabled = false;
			}
            winHandle = Usr32.FindWin("ConsoleWindowClass", "Black-Orion  Monde-Serveur v14.0");
            if (winHandle != System.IntPtr.Zero)
            {
                winParent = Usr32.GetParent(winHandle);
                z = Usr32.SetParent(winHandle, this.tabPage3.Handle);
                z = Usr32.SetWindowPos(winHandle, 1, 10, 10, 500, 300, 0);
                this.timer1.Enabled = false;
            }
		}

        void Timer2Tick(object sender, EventArgs e)
        {


           
            this.timer2.Enabled = false;

        }
        private void tabPage1_Click(object sender, EventArgs e)
        {

        }

        private void tabPage3_Click(object sender, EventArgs e)
        {

        }

        private void toolStripStatusLabel3_Click(object sender, EventArgs e)
        {

        }

        private void lancerLeServeurToolStripMenuItem_Click(object sender, EventArgs e)
        {


            System.Diagnostics.Process tabapp1 = new System.Diagnostics.Process();
            tabapp1.StartInfo.UseShellExecute = true;
            tabapp1.StartInfo.Arguments += " /login";
            tabapp1.StartInfo.FileName = "black-orion.exe";
            tabapp1.StartInfo.CreateNoWindow = true;
            System.Diagnostics.Process tabapp2 = new System.Diagnostics.Process();
            tabapp2.StartInfo.UseShellExecute = true;
            tabapp2.StartInfo.Arguments += " /char";
            tabapp2.StartInfo.FileName = "black-orion.exe";
            tabapp2.StartInfo.CreateNoWindow = true;
            System.Diagnostics.Process tabapp3 = new System.Diagnostics.Process();
            tabapp3.StartInfo.UseShellExecute = true;
            tabapp3.StartInfo.Arguments += " /world";
            tabapp3.StartInfo.FileName = "black-orion.exe";
            tabapp3.StartInfo.CreateNoWindow = true;

            tabapp1.Start();
            System.Threading.Thread.Sleep(1000);
            tabapp2.Start();
            System.Threading.Thread.Sleep(1000);
            tabapp3.Start();
            System.Threading.Thread.Sleep(2000);
            this.timer1.Enabled = true;
        }

        private void arreterLeServeurToolStripMenuItem_Click(object sender,  EventArgs e)
        {

            this.timer2.Enabled = true;
                

        }

        private void quitterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
            Application.Exit(); 
        }
	}
		public class Usr32
  	{
    	#region Class Variables
    	public  const int SM_CXSCREEN=0;
    	public  const int SM_CYSCREEN=1;
    	#endregion    
    
    	#region Class Functions
    	[DllImport("user32.dll", EntryPoint="FindWindow")]
    	public static extern IntPtr FindWin(string lpClassName, string lpWindowName);
    
    	[DllImport("user32.dll", EntryPoint="SetParent")]
    	public static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);
    
    	[DllImport("user32.dll", EntryPoint="GetParent")]
    	public static extern IntPtr GetParent(IntPtr hWnd);
    
    	[DllImport("user32.dll", EntryPoint="SetWindowPos")]
    	public static extern IntPtr SetWindowPos(IntPtr hWnd, int hWndInsertAfter , int x , int Y , int cx , int cy , int wFlags);
    
    	[DllImport("user32.dll", EntryPoint="ShowWindow")]
    	public static extern IntPtr ShowWindow(IntPtr hWnd, long nCmdShow);
    
    	[DllImport("user32.dll", EntryPoint="CloseWindow")]
    	public static extern IntPtr CloseWindow(IntPtr hWnd);
    
    	[DllImport("user32.dll", EntryPoint="DestroyWindow")]
    	public static extern IntPtr DestroyWindow(IntPtr hWnd);
    
    	#endregion
  	}
}
