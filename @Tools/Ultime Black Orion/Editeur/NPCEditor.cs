using System;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.IO;
using UBO.Editoren.Public;

namespace UBO.Editoren.NPC
{
	public struct StructNPC
	{
		public ListView.ListViewItemCollection[] Items;
		public ListView.ListViewItemCollection Texte;
		public Position Pos;
		public int Size;
		public int Rotation;
		public int NPCID;
		public string Name;
	}
	
	public partial class NPC : TabPage
	{
		string NPCFile;
		MainForm Main;
		bool save = true;
		
		StructNPC openNPC;
		
		TabPage[]  tp_slots = new TabPage[4];
		ListView[] lv_slots = new ListView[4];
		
		public NPC(string Datei, MainForm Main)
		{
			InitializeComponent();
			
			this.Main = Main;
			NPCFile = Datei;
			
			this.Text = new FileInfo(NPCFile).Name;
			
			for(int i = 0; i < Main.ItemsArr.Length; i++)
			{
				combo_newItemName.Items.Add(Main.ItemsArr[i].AnzeigeName);
			}
			
			for(int i = 0; i < 4; i++)
			{
				lv_slots[i] = new ListView();
				lv_slots[i].Columns.Add("Item ID", 62);
				lv_slots[i].Columns.Add("Nom", 131);
				lv_slots[i].FullRowSelect = true;
				lv_slots[i].View = View.Details;
				lv_slots[i].Dock = DockStyle.Fill;
				
				tp_slots[i] = new TabPage("Slot " + i.ToString());
				tp_slots[i].Controls.Add(lv_slots[i]);
				
				tc_slots.TabPages.Add(tp_slots[i]);
			}
			
			openNPC = ReadNPC();
			NPCAnzeigen(openNPC);
		}
		
		public void close()
		{
			if(save == true)
			{
				Main.tc_NPCs.TabPages.Remove(this);
				this.Dispose();
			}
			else
			{
				if(MessageBox.Show("Du hast nicht gespeichert! Jetzt Speichern?", "Speichern?", MessageBoxButtons.YesNo) == DialogResult.Yes)
				{
					WriteNPC();
				}
				
				Main.tc_NPCs.TabPages.Remove(this);
				this.Dispose();
			}
		}
		
		void NPCAnzeigen(StructNPC zeigeNPC)
		{
			try
			{
				txt_id.Text   = zeigeNPC.NPCID.ToString();
				txt_name.Text = zeigeNPC.Name;
				txt_rotation.Text = zeigeNPC.Rotation.ToString();
				txt_size.Text = zeigeNPC .Size.ToString();
				txt_World.Text = zeigeNPC.Pos.World.ToString();
				txt_X.Text = zeigeNPC.Pos.X.ToString();
				txt_Y.Text = zeigeNPC.Pos.Y.ToString();
				txt_Z.Text = zeigeNPC.Pos.Z.ToString();
			}
			catch (Exception ex)
			{
				Main.LoggIt(ex.Message, ex.StackTrace);
			}
		}
		
		void NPCAktualisieren()
		{
			try
			{
				openNPC.NPCID = int.Parse(txt_id.Text);
				openNPC.Name = txt_name.Text;
				openNPC.Rotation = int.Parse(txt_rotation.Text);
				openNPC.Size = int.Parse(txt_size.Text);
				openNPC.Pos.World = int.Parse(txt_World.Text);
				openNPC.Pos.X = float.Parse(txt_X.Text);
				openNPC.Pos.Y = float.Parse(txt_Y.Text);
				openNPC.Pos.Z = float.Parse(txt_Z.Text);
			}
			catch (Exception ex)
			{
				Main.LoggIt(ex.Message, ex.StackTrace);
			}
		}
		
		public void WriteNPC()
		{
			try
			{
				NPCAktualisieren();
				
				File.Delete(NPCFile);
				StreamWriter NPCStream = new StreamWriter(new FileStream(NPCFile, FileMode.CreateNew));
				
				NPCStream.WriteLine("NAME \"" + openNPC.Name + "\"");
				NPCStream.WriteLine("MOVER " + openNPC.NPCID.ToString() + "\n");
				NPCStream.WriteLine("POS " + openNPC.Pos.X.ToString().Replace(',', '.') + " " + 
				                    		 openNPC.Pos.Y.ToString().Replace(',', '.')  + " " + 
				                    		 openNPC.Pos.Z.ToString().Replace(',', '.'));
				NPCStream.WriteLine("WORLD " + openNPC.Pos.World.ToString());
				NPCStream.WriteLine("ROTATION " + openNPC.Rotation.ToString());
				NPCStream.WriteLine("SIZE " + openNPC.Size + "\n");
				NPCStream.Flush();
				
				for(int i = 0; i < 4; i++)
				{
					if(openNPC.Items[i].Count != 0)
					{
						NPCStream.WriteLine("PAGE " + i.ToString());
						for(int x = 0; x < openNPC.Items[i].Count; x++)
						{
							NPCStream.WriteLine("\t" + openNPC.Items[i][x].Text);
						}
						NPCStream.WriteLine("END\n");
					}
				}
				NPCStream.Flush();
				
				for(int i = 0; i < openNPC.Texte.Count; i++)
				{
					NPCStream.WriteLine("TEXT " + openNPC.Texte[i].SubItems[1].Text + " \"" + openNPC.Texte[i].Text.Replace("%N", "\n") + "\"");
				}
				
				NPCStream.Flush();
				NPCStream.Close();
				
			}
			catch (Exception ex)
			{
				Main.LoggIt(ex.Message, ex.StackTrace);
			}
		}
		
		public StructNPC ReadNPC()
		{
			string NPCFileText = File.ReadAllText(NPCFile, System.Text.Encoding.UTF8);
			StructNPC returnNPC = new StructNPC();
			returnNPC.Items = new System.Windows.Forms.ListView.ListViewItemCollection[4];
			
			for(int i = 0; i < 4; i++)
			{
				returnNPC.Items[i] = new System.Windows.Forms.ListView.ListViewItemCollection(lv_slots[i]);
			}
			
			returnNPC.Texte = new System.Windows.Forms.ListView.ListViewItemCollection(lv_texte);
			
			NPCFileText = NPCFileText.Replace("\r", string.Empty);
			
			Regex zahl      = new Regex(@"[\d]+");
			Regex floatZahl = new Regex(@"[\d]+[.]?[\d]*");
			
			Regex[] spawnCMDs = new Regex[] {new Regex("NAME \"[\\w]+\""), 
											 new Regex(@"MOVER " + zahl.ToString()),
											 new Regex(@"POS " + floatZahl.ToString() + " " + floatZahl.ToString() + " " + floatZahl.ToString()), 
											 new Regex(@"WORLD " + floatZahl.ToString()), 
											 new Regex(@"ROTATION " + zahl.ToString()),
											 new Regex(@"SIZE " + zahl.ToString()),
											 new Regex(@"PAGE [0|1|2|3]"),
											 new Regex("TEXT " + zahl.ToString() + " \"[\\w]+[\"]?")};
			
			string[] lines = NPCFileText.Split('\n');
			
			try
			{
				for(int x = 0; x < lines.Length; x++)
				{
					if(!lines[x].StartsWith("//"))
					{
						for(int i = 0; i < spawnCMDs.Length; i++)
						{
							if(spawnCMDs[i].IsMatch(lines[x]))
							{
								if(i == 0) // Name
								{
									returnNPC.Name = lines[x].Split(' ')[1].Replace("\"", "");
									break;
								}
								else if(i == 1) // NPC-ID
								{
									returnNPC.NPCID = int.Parse(zahl.Matches(lines[x])[0].ToString());
									break;
								}
								else if(i == 2) // Position
								{
									returnNPC.Pos.X  = float.Parse(floatZahl.Matches(lines[x])[0].ToString().Replace('.', ','));
									returnNPC.Pos.Y  = float.Parse(floatZahl.Matches(lines[x])[1].ToString().Replace('.', ','));
									returnNPC.Pos.Z  = float.Parse(floatZahl.Matches(lines[x])[2].ToString().Replace('.', ','));
									break;
								}
								else if(i == 3) // Position.World
								{
									returnNPC.Pos.World = int.Parse(zahl.Matches(lines[x])[0].ToString());
									break;
								}
								else if(i == 4) // Rotation
								{
									returnNPC.Rotation = int.Parse(zahl.Matches(lines[x])[0].ToString());
									break;
								}
								else if(i == 5) // Size
								{
									returnNPC.Size = int.Parse(zahl.Matches(lines[x])[0].ToString());
									break;
								}
								else if(i == 6) // Items
								{
									Regex RegexSpace = new Regex(@"[\s]*");
										
									int o = x+1;
									int Slot = int.Parse(lines[x].Substring(5, 1));
										
									while(!lines[o].Contains("END") || lines[o].Contains("PAGE"))
									{
										
										returnNPC.Items[Slot].Add(RegexSpace.Replace(lines[o], ""));
										returnNPC.Items[Slot][returnNPC.Items[Slot].Count-1].SubItems.Add(findeItem(int.Parse(RegexSpace.Replace(lines[o], ""))));
										o++;
									}
									
									break;
								}
								else if(i == 7) // Texte
								{
									for(int y = 0; y < lines[x].Length; y++)
									{
										if(lines[x].Substring(y, 1) == "\"")
										{
											int o = x+1;
											string Text = string.Empty;
											Text += lines[x].Substring(y+1) + "%N";
												
											while(!lines[o-1].Contains("\"") || lines[o-1].Contains("TEXT"))
											{
												Text += lines[o] + "%N";
												o++;
											}
											Text = Text.Remove(Text.Length-2, 2);
											
											returnNPC.Texte.Add(Text.Replace("\"", "")).SubItems.Add(zahl.Matches(lines[x])[0].ToString());
											break;
										}
									}
									break;
								}
							}
						}
					}
				}
/*				foreach(ListView.ListViewItemCollection lv in returnNPC.Items)
				{
					foreach(ListViewItem lvItem in lv)
					{
						lvItem.SubItems[2].Text = findeItem(int.Parse(lvItem.SubItems[1].Text));
					}
				} */
			}
	 		catch ( Exception ex )
			{
				Main.LoggIt(ex.Message, ex.StackTrace);
			}
			
			return returnNPC;
		}
		
		string findeItem(int ID)
		{
			for(int x = 0; x < Main.ItemsArr.Length; x++)
			{
				if (ID == Main.ItemsArr[x].ItemID)
				{
					return Main.ItemsArr[x].AnzeigeName;
				}
			}
			return "null";
		}
		
		void Txt_newItemIDTextChanged(object sender, EventArgs e)
		{
			combo_newItemName.Text = string.Empty;
			for(int x = 0; x < Main.ItemsArr.Length; x++)
			{
				if (txt_newItemID.Text == Main.ItemsArr[x].ItemID.ToString())
				{
					combo_newItemName.Text = Main.ItemsArr[x].AnzeigeName;
					break;
				}
			}
		}
		
		void Combo_newItemNameSelectedIndexChanged(object sender, EventArgs e)
		{
			txt_newItemID.Text = Main.ItemsArr[combo_newItemName.SelectedIndex].ItemID.ToString();
		}
		
		void Cmd_ItemAddClick(object sender, EventArgs e)
		{
			openNPC.Items[tc_slots.SelectedIndex].Add(txt_newItemID.Text);
			openNPC.Items[tc_slots.SelectedIndex][openNPC.Items[tc_slots.SelectedIndex].Count-1].SubItems.Add(combo_newItemName.Text);
		}
		
		void Cmd_ItemRmClick(object sender, EventArgs e)
		{
			ListView RmListview = (ListView)tc_slots.SelectedTab.Controls[0];
			
			foreach(ListViewItem lvItem in RmListview.Items)
			{
				if(lvItem.Text == txt_newItemID.Text)
				{
					lvItem.Remove();
					return;
				}
			}
		}
		
		void Cmd_TextAddClick(object sender, EventArgs e)
		{
			string AddText = Main.InputBox("Bitte den Text eingeben! (Neue Zeile mit %N)", "Text eingabe", "");
			string AddTime = Main.InputBox("Bitte die Zeit eingeben!", "Text eingabe", "20");
			if(AddText == "" || AddTime == "") return;
			
			openNPC.Texte.Add(AddText);
			openNPC.Texte[openNPC.Texte.Count-1].SubItems.Add(AddTime);
		}
		
		void Cmd_TextRmClick(object sender, EventArgs e)
		{
			lv_texte.SelectedItems[0].Remove();
		}
		
		void Cmd_TextChangeClick(object sender, System.EventArgs e)
		{
			string AddText = Main.InputBox("Bitte den Text eingeben! (Neue Zeile mit %N)", "Text eingabe", lv_texte.SelectedItems[0].Text);
			string AddTime = Main.InputBox("Bitte die Zeit eingeben!", "Text eingabe", lv_texte.SelectedItems[0].SubItems[1].Text);
			if(AddText == "" || AddTime == "") return;
			
			lv_texte.SelectedItems[0].Text = AddText;
			lv_texte.SelectedItems[0].SubItems[1].Text = AddTime;
		}
	}
}
