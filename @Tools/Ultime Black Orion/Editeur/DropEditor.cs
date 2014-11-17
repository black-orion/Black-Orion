using System;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.IO;
using System.Collections;
using UBO.Editoren.Public;

namespace UBO.Editoren.Drop
{
	public partial class Drop : TabPage
	{
		public struct Penya
		{
			public int Max;
			public int Min;
		}
		
		public struct StructDrop
		{
			public ListView.ListViewItemCollection DropItems;
			public ListView.ListViewItemCollection DropKinds;
			public ListView.ListViewItemCollection DropSPCs;
			
			public ListBox.ObjectCollection RemoveItems;
			
			public ListView.ListViewItemCollection MobIDs;
			
			public Penya penya;
		}
		
		StructDrop OpenDrop;
		MainForm Main;
		string DropFile;
		
		public Drop(MainForm Main, string DropFilePath)
		{
			this.Main = Main;
			this.DropFile = DropFilePath;
			
			this.Text = new FileInfo(DropFile).Name;
			
			InitializeComponent();
			
			OpenDrop.DropItems   = new System.Windows.Forms.ListView.ListViewItemCollection(lv_dropItem);
			OpenDrop.DropKinds   = new System.Windows.Forms.ListView.ListViewItemCollection(lv_dropKind);
			OpenDrop.DropSPCs    = new System.Windows.Forms.ListView.ListViewItemCollection(lv_dropSPC);
			OpenDrop.RemoveItems = new System.Windows.Forms.ListBox.ObjectCollection(lb_nichtDrop);
			OpenDrop.MobIDs      = new System.Windows.Forms.ListView.ListViewItemCollection(lv_movers);
			
			OpenDrop = ReadSpawn();
		}		
		
		string findeMob(int ID)
		{
			for(int x = 0; x <= 444; x++)
			{
				if (ID == Main.MobIDsArr[x].MobID) 
				{
					return Main.MobIDsArr[x].MobName;
				}
			}
			return "null";
		}
		
		/// <summary>
		/// Function um die Drop Dateien zu lesen.
		/// </summary>
		public StructDrop ReadSpawn()
		{
			string DropFileText = File.ReadAllText(DropFile).Replace('.', ',').Replace("\r", string.Empty);
			
			string[] lines = DropFileText.Split('\n');
			
			StructDrop returnDrop = new StructDrop();
			returnDrop.DropItems   = new System.Windows.Forms.ListView.ListViewItemCollection(lv_dropItem);
			returnDrop.DropKinds   = new System.Windows.Forms.ListView.ListViewItemCollection(lv_dropKind);
			returnDrop.DropSPCs    = new System.Windows.Forms.ListView.ListViewItemCollection(lv_dropSPC);
			returnDrop.RemoveItems = new System.Windows.Forms.ListBox.ObjectCollection(lb_nichtDrop);
			returnDrop.MobIDs      = new System.Windows.Forms.ListView.ListViewItemCollection(lv_movers);
			
			Regex zahl      = new Regex(@"[\d]+");
			Regex floatZahl = new Regex(@"[\d]+[,]?[\d]*");
			
			Regex[] DropCMDs = new Regex[] {new Regex(@"MOB " + zahl.ToString()),
											new Regex(@"PENYA " + zahl.ToString() + " "  + zahl.ToString()),
											new Regex(@"DROPITEM " + zahl.ToString() + " "  + floatZahl.ToString()),
											new Regex(@"DROPKIND [\w]+ " + zahl.ToString() + zahl.ToString() + " "  + floatZahl.ToString()),
											new Regex(@"DROPSPC " + zahl.ToString() + " "  + floatZahl.ToString() + " "  + zahl.ToString() + " "  + zahl.ToString() + " "  + zahl.ToString()),
											new Regex(@"REMOVE " + zahl.ToString())};
			
			try
			{
				foreach(string line in lines)
				{
					if(!line.StartsWith("//"))
					{
						for(int i = 0; i < DropCMDs.Length; i++)
						{
							if(DropCMDs[i].IsMatch(line))
							{
								if(i == 0) // Mob-ID
								{
									ListViewItem lvItem = new ListViewItem(zahl.Matches(line)[0].ToString());
									lvItem.SubItems.Add(findeMob(int.Parse(zahl.Matches(line)[0].ToString())));
									
									returnDrop.MobIDs.Add(lvItem);
								}
								else if(i == 1)
								{
									returnDrop.penya.Min = int.Parse(zahl.Matches(line)[0].ToString());
									returnDrop.penya.Max = int.Parse(zahl.Matches(line)[1].ToString());
								}
								else if(i == 2)
								{
									ListViewItem lvItem = new ListViewItem(zahl.Matches(line)[0].ToString());
									lvItem.SubItems.Add(floatZahl.Matches(line)[1].ToString());
									
									returnDrop.DropItems.Add(lvItem);
								}
								else if(i == 3)
								{
									string tmpLine = line;
									tmpLine = tmpLine.Remove(0, 9); // "DROPKIND "
									
									ListViewItem lvItem = new ListViewItem(new Regex(@"[\w]+").Matches(tmpLine)[0].ToString());
									lvItem.SubItems.Add(zahl.Matches(tmpLine)[0].ToString());
									lvItem.SubItems.Add(zahl.Matches(tmpLine)[1].ToString());
									lvItem.SubItems.Add(floatZahl.Matches(tmpLine)[2].ToString());
									
									returnDrop.DropKinds.Add(lvItem);
								}
								else if(i == 4)
								{
									string tmpLine = line.Remove(0, 8); // "DROPSPC "
									
									ListViewItem lvItem = new ListViewItem(zahl.Matches(line)[0].ToString());
									lvItem.SubItems.Add(floatZahl.Matches(line)[1].ToString());
									lvItem.SubItems.Add(zahl.Matches(line)[2].ToString());
									lvItem.SubItems.Add(zahl.Matches(line)[3].ToString());
									lvItem.SubItems.Add(zahl.Matches(line)[4].ToString());
									
									returnDrop.DropSPCs.Add(lvItem);
								}
								else if(i == 5)
								{
									lb_nichtDrop.Items.Add(zahl.Matches(line)[0].ToString());
								}
							}
						}
					}
				}
			}
	 		catch ( Exception ex )
			{
				Main.LoggIt(ex.Message, ex.StackTrace);
			}
			
			return returnDrop;
		}
	}
}