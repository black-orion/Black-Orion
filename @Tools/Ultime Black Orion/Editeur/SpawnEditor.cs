using System;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;
using System.Collections;
using UBO.Editoren.Public;

namespace UBO.Editoren.Public
{
	public struct Position
	{
		public float X;
		public float Y;
		public float Z;
		public int World;
	}
}

namespace UBO.Editoren.Spawn
{
	public partial class Spawn : TabPage
	{
		public struct StructSpawn
		{
			public ListView.ListViewItemCollection MoverIDs;
			
			public int Count;
			
			public int Size;
			
			public bool Move;
			public int MovingInterval;
			
			public float Range;
			public float Aggro;
			public int ReTime;
			
			public float Penya;
			public float Drop;
			public float Exp;
			
			public Position Pos;
		}
		
		string SpawnFile;
		StructSpawn OpenSpawn;
		MainForm Main;
		bool save = true;
		
		public Spawn(string Datei, MainForm Main)
		{
			InitializeComponent();
			this.SpawnFile = Datei;
			this.Main = Main;
			
			OpenSpawn = ReadSpawn();
			SpawnAnzeigen(OpenSpawn);
			
			this.Text = new FileInfo(Datei).Name;
			
			for(int x = 0; x <= 444; x++)
			{
				//combo_MoverIDs.Items.Add(Main.MobIDsArr[x].MobName);
			}
		}
		
		public void close()
		{
			if(save == true)
			{
				Main.tc_spawns.TabPages.Remove(this);
				this.Dispose();
			}
			else
			{
				if(MessageBox.Show("Du hast nicht gespeichert! Jetzt Speichern?", "Speichern?", MessageBoxButtons.YesNo) == DialogResult.Yes)
				{
					WriteSpawn();
				}
				
				Main.tc_spawns.TabPages.Remove(this);
				this.Dispose();
			}
		}
		
		void SpawnAnzeigen(StructSpawn spawn)
		{
			txt_AggroChance.Text    = spawn.Aggro.ToString();
			txt_Gebiet.Text         = spawn.Range.ToString();
			txt_MaxMobs.Text        = spawn.Count.ToString();
			txt_RespawnZeit.Text    = spawn.ReTime.ToString();
			txt_World.Text          = spawn.Pos.World.ToString();
			txt_X.Text              = spawn.Pos.X.ToString();
			txt_Y.Text              = spawn.Pos.Y.ToString();
			txt_Z.Text              = spawn.Pos.Z.ToString();
			txt_exp.Text            = spawn.Exp.ToString();
			txt_drop.Text           = spawn.Drop.ToString();
			txt_penya.Text          = spawn.Penya.ToString();
			cb_move.Checked         = spawn.Move;
			txt_MovingInterval.Text = spawn.MovingInterval.ToString();
			txt_size.Text           = spawn.Size.ToString();
		}
				
		void NamenErneuern()
		{
			try
			{
				foreach(ListViewItem lvItem in lv_movers.Items)
				{
					lvItem.SubItems[1].Text = findeMob(int.Parse(lvItem.Text));
				}
			}
			catch (Exception ex)
			{
				Main.LoggIt(ex.Message, ex.StackTrace);
			}
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
		
		void DatenEinlesen()
		{
			try
			{
				OpenSpawn.Aggro = float.Parse(txt_AggroChance.Text);
				OpenSpawn.Count = int.Parse(txt_MaxMobs.Text);
				
				OpenSpawn.Size      = int.Parse(txt_size.Text);
				
				OpenSpawn.Pos.X     = float.Parse(txt_X.Text);
				OpenSpawn.Pos.Y     = float.Parse(txt_Y.Text);
				OpenSpawn.Pos.Z     = float.Parse(txt_Z.Text);
				OpenSpawn.Pos.World = int.Parse(txt_World.Text);
				OpenSpawn.Range     = float.Parse(txt_Gebiet.Text);
				
				OpenSpawn.ReTime         = int.Parse(txt_RespawnZeit.Text);
				OpenSpawn.Move           = cb_move.Checked;
				OpenSpawn.MovingInterval = int.Parse(txt_MovingInterval.Text);
				
				if(txt_drop.Text  != string.Empty) OpenSpawn.Drop  = float.Parse(txt_drop.Text);
				if(txt_exp.Text   != string.Empty) OpenSpawn.Exp   = float.Parse(txt_exp.Text);
				if(txt_penya.Text != string.Empty) OpenSpawn.Penya = float.Parse(txt_penya.Text);
			}
			catch (Exception ex)
			{
				Main.LoggIt(ex.Message, ex.StackTrace);
			}
		}
		
		public void WriteSpawn()
		{
			try
			{
				DatenEinlesen();
				
				File.Delete(SpawnFile);
				
				StreamWriter SpawnStream = new StreamWriter(SpawnFile);
				
				for(int i = 0; i < OpenSpawn.MoverIDs.Count; i++)
				{
					SpawnStream.WriteLine("MOB "   + OpenSpawn.MoverIDs[i].Text);
				}
				SpawnStream.WriteLine("COUNT " + OpenSpawn.Count.ToString());
				if(OpenSpawn.Move) SpawnStream.WriteLine("MOVING 1");
				else SpawnStream.WriteLine("MOVING 0");
				SpawnStream.WriteLine("MOVINGINTERVAL " + OpenSpawn.MovingInterval.ToString());
				
				if(OpenSpawn.Exp.ToString().Contains(",")) SpawnStream.WriteLine("EXP " + OpenSpawn.Exp.ToString().Replace(',', '.'));
				else SpawnStream.WriteLine("EXP " + OpenSpawn.Exp.ToString() + ".0");
				
				if(OpenSpawn.Penya.ToString().Contains(",")) SpawnStream.WriteLine("PENYA " + OpenSpawn.Penya.ToString().Replace(',', '.'));
				else SpawnStream.WriteLine("PENYA " + OpenSpawn.Penya.ToString() + ".0");
				
				if(OpenSpawn.Drop.ToString().Contains(",")) SpawnStream.WriteLine("DROP " + OpenSpawn.Drop.ToString().Replace(',', '.'));
				else SpawnStream.WriteLine("DROP " + OpenSpawn.Drop.ToString() + ".0");
				
				SpawnStream.WriteLine("POS "         + OpenSpawn.Pos.X.ToString().Replace(',', '.') + " " 
				                  				 	 + OpenSpawn.Pos.Y.ToString().Replace(',', '.') + " " 
				                  					 + OpenSpawn.Pos.Z.ToString().Replace(',', '.'));
				
				SpawnStream.WriteLine("WORLD "       + OpenSpawn.Pos.World.ToString());
				SpawnStream.WriteLine("SIZE "        + OpenSpawn.Size.ToString());
				
				SpawnStream.WriteLine("RANGE "       + OpenSpawn.Range.ToString().Replace(',', '.'));
				SpawnStream.WriteLine("AGGRO "       + OpenSpawn.Aggro.ToString().Replace(',', '.'));
				SpawnStream.WriteLine("RESPAWNTIME " + OpenSpawn.ReTime.ToString());
				
				SpawnStream.Flush();
				SpawnStream.Close();
				
			}
			catch (Exception ex)
			{
				Main.LoggIt(ex.Message, ex.StackTrace);
			}
		}
		
		/// <summary>
		/// Function um die Spawn Dateien zu lesen.
		/// </summary>
		public StructSpawn ReadSpawn()
		{
			string SpawnFileText = File.ReadAllText(SpawnFile).Replace('.', ',');
			StructSpawn returnSpawn = new StructSpawn();
			returnSpawn.MoverIDs = new System.Windows.Forms.ListView.ListViewItemCollection(lv_movers);
			
			SpawnFileText = SpawnFileText.Replace("\r", string.Empty);
			
			Regex zahl      = new Regex(@"[\d]+");
			Regex floatZahl = new Regex(@"[\d]+[,]?[\d]*");
			
			Regex[] spawnCMDs = new Regex[] {new Regex(@"MOB " + zahl.ToString()), 
											 new Regex(@"COUNT " + zahl.ToString()), 
											 new Regex(@"MOVING " + zahl.ToString()),
											 new Regex(@"PENYA " + floatZahl.ToString()),
											 new Regex(@"EXP " + floatZahl.ToString()), 
											 new Regex(@"DROP " + floatZahl.ToString()), 
											 new Regex(@"POS " + floatZahl.ToString() + " " + floatZahl.ToString() + " " + floatZahl.ToString()), 
											 new Regex(@"WORLD " + floatZahl.ToString()), 
											 new Regex(@"RANGE " + floatZahl.ToString()),
											 new Regex(@"AGGRO " + floatZahl.ToString()), 
											 new Regex(@"RESPAWNTIME " + zahl.ToString()),
											 new Regex(@"MOVINGINTERVAL " + floatZahl.ToString()),
											 new Regex(@"SIZE " + zahl.ToString())};
			
			string[] lines = SpawnFileText.Split('\n');
			
			try
			{
				foreach(string line in lines)
				{
					if(!line.StartsWith("//"))
					{
						for(int i = 0; i < spawnCMDs.Length; i++)
						{
							if(spawnCMDs[i].IsMatch(line))
							{
								if(i == 0) // Mob-ID
								{
									ListViewItem lvItem = new ListViewItem(zahl.Matches(line)[0].ToString());
									lvItem.SubItems.Add(findeMob(int.Parse(zahl.Matches(line)[0].ToString())));
									
									returnSpawn.MoverIDs.Add(lvItem);
									break;
								}
								else if(i == 1) // Mob Count
								{
									returnSpawn.Count = int.Parse(zahl.Matches(line)[0].ToString());
									break;
								}
								else if(i == 2) // Move
								{
									returnSpawn.Move = line.Contains("1");
									break;
								}
								else if(i == 3) // Penya
								{
									returnSpawn.Penya = float.Parse(floatZahl.Matches(line.Replace('.', ','))[0].ToString());
									break;
								}
								else if(i == 4) // EXP-Rate
								{
									returnSpawn.Exp   = float.Parse(floatZahl.Matches(line.Replace('.', ','))[0].ToString());
									break;
								}
								else if(i == 5) // Drop
								{
									returnSpawn.Drop  = float.Parse(floatZahl.Matches(line.Replace('.', ','))[0].ToString());
									break;
								}
								else if(i == 6) // Position
								{
									returnSpawn.Pos.X  = float.Parse(floatZahl.Matches(line)[0].ToString());
									returnSpawn.Pos.Y  = float.Parse(floatZahl.Matches(line)[1].ToString());
									returnSpawn.Pos.Z  = float.Parse(floatZahl.Matches(line)[2].ToString());
									break;
								}
								else if(i == 7) // Position.World
								{
									returnSpawn.Pos.World = int.Parse(zahl.Matches(line)[0].ToString());
									break;
								}
								else if(i == 8) // Angriff Range
								{
									returnSpawn.Range  = float.Parse(floatZahl.Matches(line)[0].ToString());
									break;
								}
								else if(i == 9) // Aggro Chance
								{
									returnSpawn.Aggro  = float.Parse(floatZahl.Matches(line)[0].ToString());
									break;
								}
								else if(i == 10) // Respwan Time
								{
									returnSpawn.ReTime = int.Parse(zahl.Matches(line)[0].ToString());
									break;
								}
								else if(i == 11) // Moving Interval
								{
									returnSpawn.MovingInterval = int.Parse(zahl.Matches(line)[0].ToString());
									break;
								}
								else if(i == 12) // Size
								{
									returnSpawn.Size = int.Parse(zahl.Matches(line)[0].ToString());
									break;
								}
							}
						}
					}
				}
			}
			catch (Exception ex)
			{
				Main.LoggIt(ex.Message, ex.StackTrace);
			}
			
			return returnSpawn;
		}
		
		void lv_moversAfterLabelEdit(object sender, LabelEditEventArgs e)
		{
			NamenErneuern();
		}
	}
}
