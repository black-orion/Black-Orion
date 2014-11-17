/*
 * Created by SharpDevelop.
 * User: biggy
 * Date: 04/10/2007
 * Time: 10:32
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace picBoxApp
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
			System.Diagnostics.Process tabapp1 = new System.Diagnostics.Process();
					tabapp1.StartInfo.UseShellExecute = true;
					tabapp1.StartInfo.Arguments += " /K TITLE Command Prompt1";
					tabapp1.StartInfo.FileName = "CMD";
					tabapp1.Start();
			System.Diagnostics.Process tabapp2 = new System.Diagnostics.Process();
					tabapp2.StartInfo.UseShellExecute = true;
					tabapp2.StartInfo.Arguments += " /K TITLE Command Prompt2";
					tabapp2.StartInfo.FileName = "CMD";
					tabapp2.Start();
			this.timer1.Enabled = true;
			
			//
			// TODO: Add constructor code after the InitializeComponent() call.
			//
		}
		
		void Timer1Tick(object sender, EventArgs e)
		{
			System.IntPtr winParent;
			System.IntPtr x;
			System.IntPtr winHandle = Usr32.FindWin("ConsoleWindowClass", "Command Prompt1");
			if(winHandle != System.IntPtr.Zero)
			{
				winParent = Usr32.GetParent(winHandle);
				x = Usr32.SetParent(winHandle, this.tabPage1.Handle);
				x = Usr32.SetWindowPos(winHandle, 1, 10, 10, 500, 300, 0);
				this.timer1.Enabled = false;
			}
			winHandle = Usr32.FindWin("ConsoleWindowClass", "Command Prompt2");
			if(winHandle != System.IntPtr.Zero)
			{
				winParent = Usr32.GetParent(winHandle);
				x = Usr32.SetParent(winHandle, this.tabPage2.Handle);
				x = Usr32.SetWindowPos(winHandle, 1, 10, 10, 500, 300, 0);
				this.timer1.Enabled = false;
			}
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
