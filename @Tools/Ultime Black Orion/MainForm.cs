

#region Namespaces
using System; 
using System.IO; 
using System.IO.Compression;
using System.Text;
using System.Text.RegularExpressions; 
using System.Drawing; // Windows Form Manager
using System.Windows.Forms; // Windows Form Manager
using System.Security.Cryptography;
using Microsoft.Win32; 
using UBO.Editoren;
#endregion

namespace UBO
{
	public partial class MainForm : Form
	{
		#region Varriablen
		#region Strukturen
		public struct Mob // Struct Mob ==> Mobs aus der Liste speichern
		{
			public int MobID; // Mob ID (zB 20)
			public string MobName; // Mob Name (zB Small Aibat)
		}

		public struct Item // Struct Item  ==> Items aus der Liste speichern
		{
			public int ItemID; // Item ID (zB 127)
			public string AnzeigeName; // Anzeige Name (zB Lichiky Axe)
			public string InternName; // Interner Name (zB II_WEA_AXE_LICHIKY)
		}

		struct DataStruct // Data struct ==> Dateimanager - File Path speichern
		{
			public string Data; // Daten der Listbox
			public string DataPath; // Path zu der Datei
		}
		#endregion
		public UBO.MainForm.Mob[] MobIDsArr = new Mob[500];
		public UBO.MainForm.Item[] ItemsArr;
		
		#region LoadData Varriablen
		string LoadDateiPath; // Path zur aktuell geladenen Datei
		string LoadedData; // Der geladene Datei-Typ (Spawn, Drop, NPC)
		UBO.MainForm.DataStruct[] Datas = new DataStruct[1000];
		#endregion
		
		#region Spheron und App dir
		string ComstomDir; // Varriable für ein Eigenes Verzeichniss (Spheron-Verzeichniss nicht gefunden)
		string dir; // Path zum Spheron-Verzeichniss
		string AppPath = Application.StartupPath;
		#endregion
		
		bool LadenFertig = false; // Listen laden fertig (Item-, Mob-Liste,..)
		const string ErrorFilePath = @"\Errors.log"; // Name des Error Files
		string[] Args; // Die der exe übergeben Argumente
		#endregion
		
		#region Konstruktor und FormLoad
		public MainForm(string[] Args)
		{
			InitializeComponent(); // Windows Form Designer
			this.Args = Args;
		}
		
		void MainFormLoad(object sender, EventArgs e)
		{
			tabControl1.Height = 416;
			this.Height = 472;
			
			try
			{
				LoadMobIDs();
				LoadItemIDs();
				CheckFileErweiterrungen();
				
				for(int x = 0; x <= 444; x++)
				{
					list_MoverIDs.Items.Add("ID: " + MobIDsArr[x].MobID + new string(' ', (6 - MobIDsArr[x].MobID.ToString().Length) / 2) + "-" + new string(' ', (6 - MobIDsArr[x].MobID.ToString().Length) / 2) + "MobName: " + MobIDsArr[x].MobName);
					Combo_Mover_MoverIDs.Items.Add(MobIDsArr[x].MobName);
				}
				
				for(int i = 0; i < ItemsArr.Length; i++)
				{
					combo_item_Name_Anzeige.Items.Add(ItemsArr[i].AnzeigeName);
					combo_item_Name_Intern.Items.Add(ItemsArr[i].InternName);
					
					list_items.Items.Add("ID: " + ItemsArr[i].ItemID.ToString() + " - Name 1: " + ItemsArr[i].AnzeigeName + " - Name 2: " + ItemsArr[i].InternName);
					lv_Items.Items.Add(ItemsArr[i].ItemID.ToString());
					lv_Items.Items[lv_Items.Items.Count - 1].SubItems.Add(ItemsArr[i].AnzeigeName);
					lv_Items.Items[lv_Items.Items.Count - 1].SubItems.Add(ItemsArr[i].InternName);
				}
				
				combo_item_Name_Anzeige.Text = "";
				combo_item_Name_Intern.Text = "";
				
				LadenFertig = true;
				
				dir = AppPath;
				for(int i = dir.Length - 1;i >= 0; i--)
				{
					if(dir.Substring(i,1) == "\\")
					{
					   	dir = dir.Remove(i) + @"\Spheron\";				   	
					   	break;
					}
				}	
				
				if(Args.Length != 0)
				{
					if (System.IO.Directory.Exists(dir) == false)
					{
						tabControl1.TabPages[0].Enabled = false;
					}
					
					if(Args[0] == "--Open")
					{
						switch(new FileInfo(Args[1]).Extension)
						{
							case ".npc":
								tc_NPCs.TabPages.Add(new UBO.Editoren.NPC.NPC(Args[1], this));
							break;
							
							case ".spawn":
								tc_spawns.TabPages.Add(new UBO.Editoren.Spawn.Spawn(Args[1], this));
							break;
							
							case ".drop":
							break;
							
							case ".udb":
							break;
						}
					}					
				}
				
				if (System.IO.Directory.Exists(dir) == false)
				{
					bool Fertig = false;
					DialogResult Dialog;
					Dialog = MessageBox.Show("Spheron Verzeichniss nicht gefunden!\nMöchten sie es suchen?","Error", MessageBoxButtons.YesNo);
					if (Dialog == DialogResult.Yes)
					{
						while(Fertig == false)
						{
							ComstomDir = "ja";
							MessageBox.Show("ACHTUNG Diese Funktion ist NICHT ausgereift und auch noch NICHT ganz fertig gestellt! Die Gefar von Daten Verlusten besteht! Benutzung auf eigene Gefar!", "ACHTUNG!", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
							folderBrowserDialog.Description = @"Bitte wählen sie jetzt das Spheron Verzeichniss!(zB C:\Programme\Spheron\Spheron)";
							folderBrowserDialog.ShowDialog();
		
							if (System.IO.Directory.Exists(folderBrowserDialog.SelectedPath + @"\data"))
							{
								Fertig = true;
								dir = folderBrowserDialog.SelectedPath;
							}
							else 
							{
								MessageBox.Show("Das ist nicht das Spheron Verzeichniss!");
							}
							folderBrowserDialog.Description = "";
						}
					}
					else
					{
						ComstomDir = "KeineDa";
						list_Datas.Enabled = false;
						list_Datas.Items[4].Text = "Das Spheron Verzeichniss konnte nicht gefunden werden!,";
						list_Datas.Items[5].Text = "Sie können mittels \"Direkt Eingabe\" eine Datei auswählen!";
						cmd_LoadDrops.Enabled = false;
						cmd_LoadNPCs.Enabled= false;
						cmd_LoadSpawns.Enabled = false;
					}	
				} 
				else 
				{
					ComstomDir = "nein";
				}
			}
			catch (Exception ex)
			{
				LoggIt(ex.Message, ex.StackTrace);
			} 
			finally{}
		}
		#endregion
		
		// ==============================================================
		// LoadData und Zubehör Region Anfang
		// ==============================================================
		#region LoadData und Zubehör
		
		void Cmd_npc_loadClick(object sender, EventArgs e)
		{
			LoadData("npcs");
			tabControl1.SelectTab(0);
		}
				
		void Cmd_DropLoadClick(object sender, EventArgs e)
		{
			LoadData("drops");
			tabControl1.SelectTab(0);
		}
				
		void Cmd_NPCLoadClick(object sender, EventArgs e)
		{
			LoadData("npcs");
			tabControl1.SelectTab(0);
		}
		
		void List_DatasSelectedIndexChanged(object sender, EventArgs e)
		{
			//try
			//{
				bool HALT = false;
				for (int i = 0; i <= 998; i++)
				{
					if(Datas[i].Data == Datas[999].Data || HALT == true)
					{
						break;
					}
					
					if (list_Datas.SelectedItems[0].ToString().Remove(0, 15) == Datas[i].Data + "}")
					{
						LoadDateiPath = Datas[i].DataPath;
						
						switch(LoadedData)
						{
							case "spawns":
								tc_spawns.TabPages.Add(new UBO.Editoren.Spawn.Spawn(Datas[i].DataPath, this));
								LoadData("spawns");
								tabControl1.SelectTab(1);
								HALT = true;
								break;
								
								
							case "drops":
								tc_drops.TabPages.Add(new UBO.Editoren.Drop.Drop(this, Datas[i].DataPath));
								
								tabControl1.SelectTab(2);
								LoadData("drops");
								HALT = true;
								break;
								
								
							case "npcs":
								tc_NPCs.TabPages.Add(new Editoren.NPC.NPC(Datas[i].DataPath , this));
								tabControl1.SelectTab(3);
								LoadData("npcs");
								HALT = true;
								break;		
						}					
					}			
				}
			//}
			//catch ( Exception ex )
			//{
			//	LoggIt(ex.Message, ex.StackTrace);
			//}
		}
		
		void Cmd_LoadDropsClick(object sender, EventArgs e)
		{
			LoadData("drops"); // Daten Laden ==> Drops
		}
		
		void Cmd_LoadSpawnsClick(object sender, EventArgs e)
		{
			LoadData("spawns"); // Daten Laden ==> Spawns
		}
		
		void Cmd_LoadNPCsClick(object sender, EventArgs e)
		{
			LoadData("npcs"); // Daten Laden ==> NPCs
			
		}
		
		void LoadItemIDs() // Function um die ItemIDs zu laden
		{
			//try
			//{
				string ItemFileInhalt = string.Empty; // Inahlt des Files
				string tmp_str; // Aktuelles Zeichen
				
				string[] Items = new string[499]; // Vorhandene Items
				string[] AktItem = new string[10]; // Aktuelles Item

				ItemFileInhalt = System.IO.File.ReadAllText(AppPath + @"\MyItemList.dat");
				// Item Datei einlesen in ItemFileInhalt(string)
				
				Items = ItemFileInhalt.Split('\n');
				// Inhalt des Item Files splitten und in das String-Array Items geben
				
				ItemsArr = new Item[Items.Length];
				
				for(int i = 0; i < Items.Length; i++) // For Schleife
				{
					tmp_str = Items[i]; // Aktuelles Item in tmp_str füllen
					
					AktItem = tmp_str.Split(char.Parse("|")); 
					// Aktuelles Item durch "|" splitten und in das String-Array AktItem füllen
		
					ItemsArr[i].ItemID = int.Parse(AktItem[1]); // Item ID in das Item-Struckt-Array eintragen
					ItemsArr[i].AnzeigeName = AktItem[5]; // Anzeige Namen in das Item-Struckt-Array eintragen
					ItemsArr[i].InternName = AktItem[0]; // Iternen Namen in das Item-Struckt-Array eintragen
					
					AktItem[0] = string.Empty; // Array für das Aktuelle Item auslöschen
					AktItem[1] = string.Empty; // Array für das Aktuelle Item auslöschen
					AktItem[2] = string.Empty; // Array für das Aktuelle Item auslöschen
				}
			//}
			//catch ( Exception ex )
			//{
			//	LoggIt(ex.Message, ex.StackTrace);
			//} 
		}
		
		void LoadMobIDs()
		{
			try
			{
				string MobFileInhalt = string.Empty;
				string tmp_str;
				
				string[] MobFileZeilenArr = new string[499];
				string[] AktMob = new string[10];
				
				MobFileInhalt = System.IO.File.ReadAllText(AppPath + @"\MonsterList.dat");
	
				MobFileZeilenArr = MobFileInhalt.Split(char.Parse(""));
	
				for(int i = 0; i <= 444; i++)
				{
					tmp_str = MobFileZeilenArr[i];
					
					AktMob = tmp_str.Split(char.Parse("|"));
					
					MobIDsArr[i].MobID = int.Parse(AktMob[0]);
					MobIDsArr[i].MobName = AktMob[1];
					
					AktMob[0] = string.Empty;
					AktMob[1] = string.Empty;
					
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			}
		}
		
		private string GetMoverName(string File)
		{
			string FileInhalt;
			string MobName = String.Empty;
			int MobID;
			
			FileInhalt = System.IO.File.ReadAllText(File);
			
			Regex MoverRegEx = new Regex("[0-9]+");
				
			MobID = int.Parse(MoverRegEx.Matches(FileInhalt)[0].ToString());
				
			for(int i = 0; i <= 444; i++)
			{
				if(MobID == MobIDsArr[i].MobID) 
				{
					MobName = MobIDsArr[i].MobName;
				}
			}
			return MobName;
		}	
	
		private string[] GetNPCName(string File)
		{
			// Varriis Deklarieren
			string FileInhalt; // für den Datei-Inhalt
			string NPC_Full_Name = string.Empty; // Den Vollen NPC namen ("MaSa_Hallo")
			string[] ReturnArray = new string[2]; // Array das zurück gegeben wird.
			
			FileInhalt = System.IO.File.ReadAllText(File);
			
			Regex NPCNameRegEx = new Regex("[a-zA-Z]+[_][a-zA-Z]+");
			
			NPC_Full_Name = NPCNameRegEx.Matches(FileInhalt)[0].ToString();
			
			ReturnArray = NPC_Full_Name.Split(char.Parse("_"));
			
			return ReturnArray;			
		}	

		void LoadData(string data)
		{
			string tmp;
			string TmpDir;	

			string[] Files;
			int FilesAnzahl;			

			TmpDir = dir + @"data\" + data;
			
			list_Datas.Clear();	
			Files = System.IO.Directory.GetFiles(TmpDir);
			FilesAnzahl = Files.Length;	
			//try
			//{
				for (int i = 0; i < FilesAnzahl; i++)
				{
					tmp = Files[i];
					
					if (data == "spawns" || data == "drops")
					{
						System.IO.FileInfo f = new System.IO.FileInfo(tmp); 
						list_Datas.Items.Add(f.Name + "    -->    Mob: " + GetMoverName(tmp), 0);
						list_Datas.Items[list_Datas.Items.Count - 1].ToolTipText = System.IO.File.ReadAllText(f.FullName);
						Datas[i].Data = f.Name + "    -->    Mob: " + GetMoverName(tmp);
						Datas[i].DataPath = f.FullName;
					}
					else if ( data == "npcs" )
					{
						System.IO.FileInfo f = new System.IO.FileInfo(tmp); 
						
						list_Datas.Items.Add(f.Name + "   -->   " + GetNPCName(tmp)[1] + " (" + GetNPCName(tmp)[0] + ")");
						list_Datas.Items[list_Datas.Items.Count - 1].ToolTipText = System.IO.File.ReadAllText(f.FullName);
						Datas[i].Data = f.Name + "   -->   " + GetNPCName(tmp)[1] + " (" + GetNPCName(tmp)[0] + ")";
						Datas[i].DataPath = f.FullName;
					}
					LoadedData = data;
				}
			//}
			//catch ( Exception ex )
			//{
			//	LoggIt(ex.Message, ex.StackTrace);
			//}
		}	
		#endregion
		// ==============================================================
		// LoadData und Zubehör Region Ende
		// ==============================================================	
		
		// ==============================================================
		// DateiErrweiterrungen Anfang
		// ==============================================================
		#region DateiErweiterrungen
		void CheckFileErweiterrungen()
		{
			if(Registry.ClassesRoot.OpenSubKey(".drop", false) != null)
			{
				check_drop.Checked = true;
			}
			
			if(Registry.ClassesRoot.OpenSubKey(".npc", false) != null)
			{
				check_drop.Checked = true;
			}
			
			if(Registry.ClassesRoot.OpenSubKey(".spawn", false) != null)
			{
				check_drop.Checked = true;
			}

			if(Registry.ClassesRoot.OpenSubKey(".udb", false) != null)
			{
				check_drop.Checked = true;
			}
		}
				
		void Cmd_erweiter_uebernemenClick(object sender, EventArgs e)
		{
			try
			{
				if(check_drop.Checked == true)
				{
					CreateFileAssoc(".drop", @"%SystemRoot%\system32\shell32.dll,-157");
				}
				else if(Registry.ClassesRoot.OpenSubKey(".drop", false) != null)
				{
					Registry.ClassesRoot.DeleteSubKeyTree(".drop");
				}
				
				if(check_npc.Checked == true)
				{
					CreateFileAssoc(".npc", @"%SystemRoot%\system32\shell32.dll,-157");
				}
				else if(Registry.ClassesRoot.OpenSubKey(".npc", false) != null)
				{
					Registry.ClassesRoot.DeleteSubKeyTree(".npc");
				}
				
				if(check_Spawn.Checked == true)
				{
					CreateFileAssoc(".spawn", @"%SystemRoot%\system32\shell32.dll,-157");
				}
				else if(Registry.ClassesRoot.OpenSubKey(".spawn", false) != null)
				{
					Registry.ClassesRoot.DeleteSubKeyTree(".spawn");
				}
				
				if(check_udb.Checked == true)
				{
					CreateFileAssoc(".udb", @"%SystemRoot%\system32\shell32.dll,-157");
				}
				else if(Registry.ClassesRoot.OpenSubKey(".udb", false) != null)
				{
					Registry.ClassesRoot.DeleteSubKeyTree(".udb");
				}
			}
			catch(Exception ex)
			{
				LoggIt(ex.Message, ex.StackTrace);
			}
		}
		
		void CreateFileAssoc(string Endung, string DefaultIconPath)
		{
			Registry.ClassesRoot.CreateSubKey(Endung + @"\shell");
			Registry.ClassesRoot.CreateSubKey(Endung + @"\shell\DefaultIcon").SetValue("", DefaultIconPath);
			
			RegistryKey RegKey = Registry.ClassesRoot.OpenSubKey(Endung, true);
			
			RegKey = Registry.ClassesRoot.OpenSubKey(Endung + @"\shell", true);
			RegKey.CreateSubKey("open")
						.CreateSubKey("command")
						    .SetValue("", Application.ExecutablePath + " --Open %1");

			RegKey.CreateSubKey("print")
						  .CreateSubKey("command")
							  .SetValue("", @"%SystemRoot%\system32\NOTEPAD.EXE /p %1");
		}
		
		#endregion
		// ==============================================================
		// DateiErrweiterrungen Ende
		// ==============================================================

		void cmd_optClick(object sender, EventArgs e)
		{
			tabControl1.SelectTab(5);
			tabCont_Allgemein.SelectTab(5);
		}
		
		void tabControl1SelectedIndexChange(object sender, EventArgs e)
		{
			int SelIndex = tabControl1.SelectedIndex;
			switch(SelIndex)
			{
				case 0:
					tabControl1.Height = 416;
					this.Height = 472;	
				break;
				
				case 1:
					tabControl1.Height = 268;
					this.Height = 318;
				break;
					
				case 2:
					tabControl1.Height = 379;
					this.Height = 389;
				break;
				
				case 3:
					tabControl1.Height = 416;
					this.Height = 472;	
				break;
				
				case 5:
					tabCont_Allgemein.Height = 295;
					tabControl1.Height = 327;
					this.Height = 373;
				break;
				
				default:
				//	tabControl1.Height = 276;
				//	this.Height = 330;
				break;
			}			
		}
		
		// ==============================================================
		// Save Data Region Anfang
		// ==============================================================
		#region SaveData

        public static string CompressString(string text)
        {
            byte[] buffer = Encoding.UTF8.GetBytes(text);
            var memoryStream = new MemoryStream();
            using (var gZipStream = new GZipStream(memoryStream, CompressionMode.Compress, true))
            {
                gZipStream.Write(buffer, 0, buffer.Length);
            }

            memoryStream.Position = 0;

            var compressedData = new byte[memoryStream.Length];
            memoryStream.Read(compressedData, 0, compressedData.Length);

            var gZipBuffer = new byte[compressedData.Length + 4];
            Buffer.BlockCopy(compressedData, 0, gZipBuffer, 4, compressedData.Length);
            Buffer.BlockCopy(BitConverter.GetBytes(buffer.Length), 0, gZipBuffer, 0, 4);
            return Convert.ToBase64String(gZipBuffer);
        }
        public static string DecompressString(string compressedText)
        {
            byte[] gZipBuffer = Convert.FromBase64String(compressedText);
            using (var memoryStream = new MemoryStream())
            {
                int dataLength = BitConverter.ToInt32(gZipBuffer, 0);
                memoryStream.Write(gZipBuffer, 4, gZipBuffer.Length - 4);

                var buffer = new byte[dataLength];

                memoryStream.Position = 0;
                using (var gZipStream = new GZipStream(memoryStream, CompressionMode.Decompress))
                {
                    gZipStream.Read(buffer, 0, buffer.Length);
                }

                return Encoding.UTF8.GetString(buffer);
            }
        }

		
		string[] Data_Drop;
		string[] Data_NPC;
		string[] Data_Spawn;
		
		string[] Path_Drop;
		string[] Path_NPC;
		string[] Path_Spawn;
		
		const string Split1 = ""; // FF
		const string Split2 = ""; // BS
		const string Split3 = ""; // SI
		
		void cmd_udb_packClick(object sender, EventArgs e)
		{
			ReadData();
			saveFileDialog.Filter = "UBO DatenBank|*.udb";
			saveFileDialog.InitialDirectory = AppPath;
			saveFileDialog.ShowDialog();
			if(saveFileDialog.FileName != "") MakeUBODB(saveFileDialog.FileName);
			saveFileDialog.Filter = "";
		}
				
		void cmd_udb_depackClick(object sender, EventArgs e)
		{
			openFileDialog.Filter = "UBO DatenBank|*.udb";
			openFileDialog.InitialDirectory = AppPath;
			openFileDialog.ShowDialog();
			if(openFileDialog.FileName != "") DeMakeUBODB(openFileDialog.FileName);
			openFileDialog.Filter = "";
		}
		
		void DeMakeUBODB(string Path)
		{
			string Path1 = AppPath + @"\EntpackteDBs\";
			string UBOdb;
			
			string DropDB;
			string NPCDB;
			string SpawnDB;
			
			string[] SI_Split = new string[10];
			string[] BS_Split_Paths = new string[10];
			string[] BS_Split_Datas = new string[10];
			
			UBOdb = DecompressString(System.IO.File.ReadAllText(Path));
			
			DropDB = UBOdb.Split(char.Parse(Split1))[1];
			NPCDB = UBOdb.Split(char.Parse(Split1))[2];
			SpawnDB = UBOdb.Split(char.Parse(Split1))[3];
			
			listBox1.Items.Clear();
							
			System.IO.FileInfo f = new System.IO.FileInfo(Path);
			
			System.IO.Directory.CreateDirectory(Path1 + f.Name);
			
			System.IO.Directory.CreateDirectory(Path1 + f.Name + @"\drops");
			System.IO.Directory.CreateDirectory(Path1 + f.Name + @"\npcs");
			System.IO.Directory.CreateDirectory(Path1 + f.Name + @"\spawns");
			
			// Drops Anfang
			listBox1.Items.Add("------Drop-----");
			SI_Split = DropDB.Split(char.Parse(Split3));
			BS_Split_Paths = SI_Split[0].Split(char.Parse(Split2));
			BS_Split_Datas = SI_Split[1].Split(char.Parse(Split2));
			
			for(int i = 0; i <= BS_Split_Paths.Length - 2; i++)
			{
				System.IO.File.WriteAllText(Path1 + f.Name + @"\drops\" + BS_Split_Paths[i], BS_Split_Datas[i]);
				listBox1.Items.Add(BS_Split_Paths[i] + "  -->  " + BS_Split_Datas[i]);
			}
			// Drops Ende

			// NPCs Anfang
			listBox1.Items.Add("------NPC-----");
			SI_Split = NPCDB.Split(char.Parse(Split3));
			BS_Split_Paths = SI_Split[0].Split(char.Parse(Split2));
			BS_Split_Datas = SI_Split[1].Split(char.Parse(Split2));
			
			for(int i = 0; i <= BS_Split_Paths.Length - 2; i++)
			{
				System.IO.File.WriteAllText(Path1 +  f.Name + @"\npcs\" + BS_Split_Paths[i], BS_Split_Datas[i]);
				listBox1.Items.Add(BS_Split_Paths[i] + "  -->  " + BS_Split_Datas[i]);
			}
			// NPCs Ende
			
			// Spawns Anfang
			listBox1.Items.Add("------Spawn-----");
			SI_Split = SpawnDB.Split(char.Parse(Split3));
			BS_Split_Paths = SI_Split[0].Split(char.Parse(Split2));
			BS_Split_Datas = SI_Split[1].Split(char.Parse(Split2));
			
			for(int i = 0; i <= BS_Split_Paths.Length - 2; i++)
			{
				System.IO.File.WriteAllText(Path1 + f.Name + @"\spawns\" + BS_Split_Paths[i], BS_Split_Datas[i]);
				listBox1.Items.Add(BS_Split_Paths[i] + "  -->  " + BS_Split_Datas[i]);
			}
			// Spawns Ende
		}
		
		int MakeUBODB(string Path)
		{
			string DropDB;
			string NPCDB;
			string SpawnDB;
						
			string UDBtext = string.Empty;				
			System.IO.FileInfo f;
			
			string UBODB;
			
				// Drop DB erzeugen
				for(int i = 0; i < Path_Drop.Length; i++)
				{
					f = new System.IO.FileInfo(Path_Drop[i]);
					UDBtext += f.Name + Split2;
				}
				
				UDBtext += Split3;
				
				for(int i = 0; i < Path_Drop.Length; i++)
				{
					f = new System.IO.FileInfo(Path_Drop[i]);
					UDBtext += Data_Drop[i] + Split2;
				}
				DropDB = UDBtext;
				// Drop DB ende				
			
				// NPC DB erzeugen
			
				for(int i = 0; i < Path_NPC.Length; i++)
				{
					f = new System.IO.FileInfo(Path_NPC[i]);
					UDBtext += f.Name + Split2;
				}
				
				UDBtext += Split3;
				
				for(int i = 0; i < Path_NPC.Length; i++)
				{
					f = new System.IO.FileInfo(Path_NPC[i]);
					UDBtext += Data_NPC[i] + Split2;
				}
				NPCDB = UDBtext;
				// NPC DB ende			
						
				// SpawnDB erzeugen
				for(int i = 0; i < Path_NPC.Length; i++)
				{
					f = new System.IO.FileInfo(Path_Spawn[i]);
					UDBtext += f.Name + Split2;
				}
				
				UDBtext += Split3;
				
				for(int i = 0; i < Path_Spawn.Length; i++)
				{
					f = new System.IO.FileInfo(Path_Spawn[i]);
					UDBtext += Data_Spawn[i] + Split2;
				}
				SpawnDB = UDBtext;
				// Spawn DB ende
			
			UBODB = "UBODB" + Split1 + DropDB + Split1 + NPCDB + Split1 + SpawnDB + Split1;
			
			System.IO.File.WriteAllText(Path, CompressString(UBODB));
			return 0;
		}
		
		
		int ReadData()
		{
			try 
			{	
				Path_Drop = System.IO.Directory.GetFiles(dir + @"data\drops");
				
				Path_NPC = System.IO.Directory.GetFiles(dir + @"data\npcs");
				
				Path_Spawn = System.IO.Directory.GetFiles(dir + @"data\spawns");
				listBox1.Items.Clear();
							
				listBox1.Items.Add("------Drop-----");
				for(int i = 0; i < Path_Drop.Length; i++)
				{
					if(Path_Drop[i] == string.Empty) { break; };
					Data_Drop[i] = System.IO.File.ReadAllText(Path_Drop[i]);
					listBox1.Items.Add(Path_Drop[i] + "  -->  " + Data_Drop[i]);
				}
							
				listBox1.Items.Add("------NPC-----");
				for(int i = 0; i < Path_NPC.Length; i++)
				{
					if(Path_NPC[i] == string.Empty) { break; };
					Data_NPC[i] = System.IO.File.ReadAllText(Path_NPC[i]);
					listBox1.Items.Add(Path_NPC[i] + "  -->  " + Data_NPC[i]);
				}
						
				listBox1.Items.Add("------Spawn-----");
				for(int i = 0; i < Path_Spawn.Length; i++)
				{
					if(Path_Spawn[i] == string.Empty) { break; };
					Data_Spawn[i] = System.IO.File.ReadAllText(Path_Spawn[i]);
					listBox1.Items.Add(Path_Spawn[i] + "  -->  " + Data_Spawn[i]);
				}
				
				return 0;	
			}
			catch (Exception ex)
			{
				LoggIt(ex.Message, ex.StackTrace);
				return 1;
			}
		}
		#endregion
		// ==============================================================
		// Save Data Region Ende
		// ==============================================================
		
		// ==============================================================
		// Allgemeines Region Anfang
		// ==============================================================
		#region Allgemeines
		
		void tabCont_AllgemeinSelectedIndexChanged(object sender, EventArgs e)
		{
			switch(tabCont_Allgemein.SelectedIndex)
			{
				case 0:
				case 1:
					tabCont_Allgemein.Height = 295;
					tabControl1.Height = 327;
					this.Height = 373;
					break;
				case 2:
					tabCont_Allgemein.Height = 351;
					tabControl1.Height = 386;
					this.Height = 434;
					break;
				case 3:
					tabCont_Allgemein.Height = 344;
					tabControl1.Height = 378;
					this.Height = 427;
					break;				
				case 4:
					tabCont_Allgemein.Height = 344;
					tabControl1.Height = 378;
					this.Height = 427;
					break;
			}
			
		}
		
		#endregion
		// ==============================================================
		// Allgemeines Region Ende
		// ==============================================================
		
		// ==============================================================
		// MobList Region Anfang
		// ==============================================================
		#region MobList
				
		void Combo_Mover_MoverIDsSelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				Txt_Mover_MoverID.Text = MobIDsArr[Combo_Mover_MoverIDs.SelectedIndex].MobID.ToString();
				
				for(int x = 0; x < 445; x++)
				{
					if (Txt_Mover_MoverID.Text == MobIDsArr[x].MobID.ToString()) {
						list_MoverIDs.SetSelected(x, true);
						break;
					}
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			} 
		}
				
		void Txt_Mover_MoverIDTextChanged(object sender, EventArgs e)
		{
			try
			{
				Combo_Mover_MoverIDs.Text = string.Empty;
				for(int x = 0; x < 445; x++)
				{
					if (Txt_Mover_MoverID.Text == MobIDsArr[x].MobID.ToString()) {
						Combo_Mover_MoverIDs.Text = MobIDsArr[x].MobName;
						list_MoverIDs.SetSelected(x, true);
						break;
					}
				}
				if(Combo_Mover_MoverIDs.Text == string.Empty)
				{
					list_MoverIDs.ClearSelected();
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			} 
		}
		
		
		void list_MoverIDsSelectedIndexChanged(object sender, EventArgs e)
		{
			string SelString;
			string SollString;

			try
			{
				Combo_Mover_MoverIDs.Text = string.Empty;
				
				if(list_MoverIDs.SelectedIndex != -1)
				{				
					for(int x = 0; x < 445; x++)
					{
						SelString = list_MoverIDs.Items[list_MoverIDs.SelectedIndex].ToString();
						SollString = "ID: " + MobIDsArr[x].MobID + " - MobName: " + MobIDsArr[x].MobName;
						if (SelString == SollString) {
							Combo_Mover_MoverIDs.Text = MobIDsArr[x].MobName;
							Txt_Mover_MoverID.Text = MobIDsArr[x].MobID.ToString();
							break;
						}
					}
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			} 
		}	
		
		void Cmd_mover_suche_hideClick(object sender, EventArgs e)
		{
			if(cmd_mover_suche_hide.Text == "Suche zeigen")
			{
				cmd_mover_suche_hide.Text = "Suche verstecken";
				tabCont_Allgemein.Height = 460;
				tabControl1.Height = 492;
				this.Height = 540;
			}
			else
			{
				cmd_mover_suche_hide.Text = "Suche zeigen";
				tabCont_Allgemein.Height = 344;
				tabControl1.Height = 378;
				this.Height = 427;
			}
		}
		
		void txt_mover_suche_eingabeKeyPress(object sender, KeyPressEventArgs e)
		{
			FindeMob();
		}
		
		void FindeMob()
		{
			Regex MyRegex = new Regex("(" + txt_mover_suche_eingabe.Text + ")");
			tabCont_Allgemein.Height = 460;
			tabControl1.Height = 492;
			this.Height = 540;
						
			list_mover_suche_ergebiss.Items.Clear();
			
			for(int x = 0; x < 445; x++)
			{
				if(MyRegex.IsMatch(list_MoverIDs.Items[x].ToString()))
				{
					list_mover_suche_ergebiss.Items.Add("ID: " + MobIDsArr[x].MobID + " - MobName: " + MobIDsArr[x].MobName);
				}
			}
		}
		
		void List_mover_suche_ergebissSelectedIndexChanged(object sender, EventArgs e)
		{
			string SelString;
			string SollString;

			try
			{
				Combo_Mover_MoverIDs.Text = string.Empty;
				Txt_Mover_MoverID.Text = string.Empty;
				list_MoverIDs.ClearSelected();
				
				if(list_mover_suche_ergebiss.SelectedIndex != -1)
				{				
					for(int x = 0; x < 445; x++)
					{
						SelString = list_mover_suche_ergebiss.Items[list_mover_suche_ergebiss.SelectedIndex].ToString();
						SollString = "ID: " + MobIDsArr[x].MobID + " - MobName: " + MobIDsArr[x].MobName;
						
						if (Txt_Mover_MoverID.Text == MobIDsArr[x].MobID.ToString()) 
						{
							list_MoverIDs.SetSelected(x, true);
							break;
						}

						if (SelString == SollString) {
							Combo_Mover_MoverIDs.Text = MobIDsArr[x].MobName;
							Txt_Mover_MoverID.Text = MobIDsArr[x].MobID.ToString();
							break;
						}
					}
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			} 
		}
		
		#endregion
		// ==============================================================
		// MobList Region Ende
		// ==============================================================
		
		// ==============================================================
		// ItemList Region Anfang
		// ==============================================================
		#region ItemList
		
		void Txt_item_suche_hideClick(object sender, EventArgs e)
		{
			if(txt_item_suche_hide.Text == "Suche zeigen")
			{
				txt_item_suche_hide.Text = "Suche verstecken";
				tabCont_Allgemein.Height = 460;
				tabControl1.Height = 492;
				this.Height = 540;
			}
			else
			{
				txt_item_suche_hide.Text = "Suche zeigen";
				tabCont_Allgemein.Height = 344;
				tabControl1.Height = 378;
				this.Height = 427;
			}
		}
		
		void List_itemsSelectedIndexChanged(object sender, EventArgs e)
		{
			string SelString;
			string SollString;

			try
			{
				if(LadenFertig == true)
				{
					Combo_Mover_MoverIDs.Text = string.Empty;
					
					if(list_items.SelectedIndex != -1)
					{				
						for(int x = 0; x <= ItemsArr.Length; x++)
						{
							SelString = list_items.Items[list_items.SelectedIndex].ToString();
							SollString = "ID: " + ItemsArr[x].ItemID.ToString() + " - Name 1: " + ItemsArr[x].AnzeigeName + " - Name 2: " + ItemsArr[x].InternName;
							if (SelString == SollString) {
								combo_item_Name_Anzeige.Text = ItemsArr[x].AnzeigeName;
								combo_item_Name_Intern.Text = ItemsArr[x].InternName;
								txt_item_ID.Text = ItemsArr[x].ItemID.ToString();
								break;
							}
						}
					}
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			} 
		}
		
		void Combo_item_Name_AnzeigeSelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				if(LadenFertig == true)
				{
					txt_item_ID.Text = ItemsArr[combo_item_Name_Anzeige.SelectedIndex].ItemID.ToString();
					
					for(int x = 0; x < ItemsArr.Length; x++)
					{
						if (txt_item_ID.Text == ItemsArr[x].ItemID.ToString()) {
							//list_items.SetSelected(x, true);
							lv_Items.Items[x].Selected = true;
							break;
						}
					}
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			} 
		}
		
		void Combo_item_Name_InternSelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{	
				if(LadenFertig == true)
				{
					txt_item_ID.Text = ItemsArr[combo_item_Name_Intern.SelectedIndex].ItemID.ToString();
					
					for(int x = 0; x < ItemsArr.Length; x++)
					{
						if (txt_item_ID.Text == ItemsArr[x].ItemID.ToString()) {
							//list_items.SetSelected(x, true);
							lv_Items.Items[x].Selected = true;
							break;
						}
					}
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			} 
		}
		
		void Txt_item_IDTextChanged(object sender, EventArgs e)
		{
			try
			{
				if(LadenFertig == true)
				{
					combo_item_Name_Anzeige.Text = string.Empty;
					combo_item_Name_Intern.Text = string.Empty;
					
					for(int x = 0; x < ItemsArr.Length; x++)
					{
						if (txt_item_ID.Text == ItemsArr[x].ItemID.ToString())
						{
							combo_item_Name_Anzeige.Text = ItemsArr[x].AnzeigeName;
							combo_item_Name_Intern.Text = ItemsArr[x].InternName;
							break;
						}
					}
					if(Combo_Mover_MoverIDs.Text == string.Empty)
					{
						list_MoverIDs.ClearSelected();
					}
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			}
		}
				
		void txt_item_suche_eingabeKeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
			{
				FindeItem();
			}
		}
		
		void FindeItem()
		{
			try
			{
				Regex MyRegex = new Regex("(" + txt_item_suche_eingabe.Text.Replace("?", @"\?") + ")");
				tabCont_Allgemein.Height = 460;
				tabControl1.Height = 492;
				this.Height = 540;
							
				lv_mover_suche_ergebniss.Items.Clear();
				
				for(int x = 0; x < 4098; x++)
				{
					/*
					MessageBox.Show(lv_Items.Items[x].Text + " = " + MyRegex.IsMatch(lv_Items.Items[x].Text));
					MessageBox.Show(lv_Items.Items[x].SubItems[1].Text + " = " + MyRegex.IsMatch(lv_Items.Items[x].SubItems[1].Text));
					MessageBox.Show(lv_Items.Items[x].SubItems[2].Text + " = " + MyRegex.IsMatch(lv_Items.Items[x].SubItems[2].Text));
					*/
					
					if(MyRegex.IsMatch(lv_Items.Items[x].Text) | MyRegex.IsMatch(lv_Items.Items[x].SubItems[1].Text) | MyRegex.IsMatch(lv_Items.Items[x].SubItems[2].Text))
					{
						lv_mover_suche_ergebniss.Items.Add(lv_Items.Items[x].Text);
						lv_mover_suche_ergebniss.Items[lv_mover_suche_ergebniss.Items.Count - 1].SubItems.Add(ItemsArr[x].AnzeigeName);
						lv_mover_suche_ergebniss.Items[lv_mover_suche_ergebniss.Items.Count - 1].SubItems.Add(ItemsArr[x].InternName);
					}
				}
			}
			catch
			{
				MessageBox.Show("Ungültige Eingabe!");
			}
		}
			
		void Lv_ItemsSelectedIndexChanged(object sender, EventArgs e)
		{
			string SelString;
			string SollString;

			try
			{
				if(LadenFertig == true)
				{
					Combo_Mover_MoverIDs.Text = string.Empty;
					
					if(lv_Items.SelectedItems.Count != 0)
					{				
						for(int x = 0; x <= ItemsArr.Length; x++)
						{
							SelString = lv_Items.SelectedItems[0].Text;
							SollString = ItemsArr[x].ItemID.ToString();
							if (SelString == SollString) {
								combo_item_Name_Anzeige.Text = ItemsArr[x].AnzeigeName;
								combo_item_Name_Intern.Text = ItemsArr[x].InternName;
								txt_item_ID.Text = ItemsArr[x].ItemID.ToString();
								break;
							}
						}
					}
				}
			}
			catch ( Exception ex )
			{
				LoggIt(ex.Message, ex.StackTrace);
			}  
		}
		
		#endregion
		// ==============================================================
		// ItemList Region Ende
		// ==============================================================
		
		public void LoggIt(string Error_Message, string Error_StackTrace)
		{
			string ErrorFileInahlt = System.IO.File.ReadAllText(AppPath + ErrorFilePath);
			System.IO.StreamWriter ErrorFile = new System.IO.StreamWriter(AppPath + ErrorFilePath);
			ErrorFile.Write(ErrorFileInahlt);
			ErrorFile.Write("\r\n\r\n<-------->\r\nError" + Error_StackTrace + "\r\nMessage: " + Error_Message + "\r\n<-------->\r\n");
			ErrorFile.Close();
			MessageBox.Show("Achtung! Ein Fehler ist aufgetreten (" + Error_Message + ").Er wurde in \"Errors.log\" abgespeichert.\nSie können wie gewohnt weiterarbeiten, doch es währe nett wenn sie mir, mike1010, den Fehler mitteilen könnten.\nDazu einfach den gasamten Inahlt der Datei an mich schicken, Danke!");
		}
		
		void Button3Click(object sender, EventArgs e)
		{
			DialogResult DiaResult;
			
			while(true)
			{
				ComstomDir = "ja";
				MessageBox.Show("ACHTUNG Diese Funktion ist NICHT ausgereift und auch noch NICHT ganz fertig gestellt! Die Gefar von Daten Verlusten besteht! Benutzung auf eigene Gefar!", "ACHTUNG!", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
				folderBrowserDialog.Description = @"Bitte wählen sie jetzt das Spheron Verzeichniss!(zB C:\Programme\Spheron\Spheron)";
				DiaResult = folderBrowserDialog.ShowDialog();
				
				if (DiaResult == DialogResult.Cancel) { ComstomDir = "nein"; break; };
				
				if (System.IO.Directory.Exists(folderBrowserDialog.SelectedPath + @"\data\spawns"))
				{
					dir = folderBrowserDialog.SelectedPath;
					break;
				}
				else 
				{
					MessageBox.Show("Das ist nicht das Spheron Verzeichniss!");
				}
				folderBrowserDialog.Description = "";
			}
		}
		
		void Cmd_aboutClick(object sender, EventArgs e)
		{
			MessageBox.Show("*  Spheron UBO\n" +
							"*  Version 3.2\n" +
							"*  \n" +
							"*  Coded by Mike1010\n" +
							"*  Kontakt: Spheron Forum (www.iserver.pytalhost.de) ---> Mike1010\n" +
							"*  \n" +
							"*  Credits:\n" +
							"*  		Datei Browser:           Mike1010, Diverse Verbesserrungen: TyRoXx\n" +
							"*  		Drop, NPC, Spawn Editor: Mike1010, Diverse Verbesserrungen: TyRoXx\n" +
							"*  \n" +
							"*  THX 2:\n" +
							"*         TyRoXx (Beta-Testen, Code Verbeserrungen, Ideen, Listen)");
		}
		
		void Cmd_toolstrip_saveClick(object sender, EventArgs e)
		{
			UBO.Editoren.Spawn.Spawn MySpawn = (UBO.Editoren.Spawn.Spawn)tc_spawns.SelectedTab;
			if(MySpawn != null) MySpawn.WriteSpawn();
		}
		
		void Cmd_toolstrip_saveAllClick(object sender, EventArgs e)
		{
			foreach(TabPage page in tc_spawns.TabPages)
			{
				((UBO.Editoren.Spawn.Spawn)tc_spawns.SelectedTab).WriteSpawn();
			}
		}
		
		void Cmd_toolstrip_newFileClick(object sender, EventArgs e)
		{
			SaveFileDialog SaveDialog = new SaveFileDialog();
			
			string DialogFile = SaveDialog.FileName;
			if(DialogFile == string.Empty) return;
			
			File.WriteAllText(DialogFile, "MOB 0\n" + "COUNT 0\n" + "MOVING 1\n" + "MOVINGINTERVAL 5000\n\n" + "POS 0 0 0\n" + "WORLD 0\n" + "RANGE 0\n");
			
			tc_spawns.TabPages.Add(new UBO.Editoren.Spawn.Spawn(DialogFile, this));
		}
		
		void Cmd_toolstrip_closeClick(object sender, EventArgs e)
		{
			UBO.Editoren.Spawn.Spawn MySpawn = (UBO.Editoren.Spawn.Spawn)tc_spawns.SelectedTab;
			if(MySpawn != null) MySpawn.close();
		}
		
		void Cmd_toolstrip_openClick(object sender, EventArgs e)
		{
			OpenFileDialog OpenDialog = new OpenFileDialog();
			if(OpenDialog.ShowDialog() == DialogResult.Cancel) return;
			
			string DialogFile = OpenDialog.FileName;
			
			tc_spawns.TabPages.Add(new UBO.Editoren.Spawn.Spawn(DialogFile, this));
		}
		
		void Cmd_NPC_saveClick(object sender, EventArgs e)
		{
			UBO.Editoren.NPC.NPC MyNPC = (UBO.Editoren.NPC.NPC)tc_NPCs.SelectedTab;
			if(MyNPC != null) MyNPC.WriteNPC();
		}
		
		public string InputBox(string prompt, string title, string defaultValue)
		{
			InputBoxDialog ib = new InputBoxDialog();
			ib.FormPrompt = prompt;
			ib.FormCaption = title;
			ib.DefaultValue = defaultValue;
			ib.ShowDialog();
			string s = ib.InputResponse;
			ib.Close();
			return s;
		}
		
		void Cmd_npc_closeClick(object sender, EventArgs e)
		{
			UBO.Editoren.NPC.NPC MyNPC = (UBO.Editoren.NPC.NPC)tc_NPCs.SelectedTab;
			if(MyNPC != null) MyNPC.close();
		}
		
		void ToolStripButton5Click(object sender, EventArgs e)
		{
			OpenFileDialog OpenDialog = new OpenFileDialog();
			if(OpenDialog.ShowDialog() == DialogResult.Cancel) return;
			
			string DialogFile = OpenDialog.FileName;
			
			tc_spawns.TabPages.Add(new UBO.Editoren.Spawn.Spawn(DialogFile, this));
		}
		
		void Cmd_NPC_saveAllClick(object sender, EventArgs e)
		{
			foreach(TabPage page in tc_spawns.TabPages)
			{
				((UBO.Editoren.NPC.NPC)tc_NPCs.SelectedTab).WriteNPC();
			}
		}
		
		void Cmd_NPC_newClick(object sender, EventArgs e)
		{
			
		}
	}
}