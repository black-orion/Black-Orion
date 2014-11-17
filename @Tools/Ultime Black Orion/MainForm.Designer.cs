
namespace UBO
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable Used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources Used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
            System.Windows.Forms.Label lbl_RespawnZeit;
            System.Windows.Forms.Label lbl_MoverID;
            System.Windows.Forms.Label lbl_Gebiet;
            System.Windows.Forms.Label lbl_MaxMobs;
            System.Windows.Forms.Label lbl_World;
            System.Windows.Forms.Label lbl_Z;
            System.Windows.Forms.Label lbl_Y;
            System.Windows.Forms.Label lbl_X;
            System.Windows.Forms.Label label8;
            System.Windows.Forms.Label label9;
            System.Windows.Forms.Label lbl_AggroChance;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            System.Windows.Forms.ListViewItem listViewItem13 = new System.Windows.Forms.ListViewItem("");
            System.Windows.Forms.ListViewItem listViewItem14 = new System.Windows.Forms.ListViewItem("");
            System.Windows.Forms.ListViewItem listViewItem15 = new System.Windows.Forms.ListViewItem("");
            System.Windows.Forms.ListViewItem listViewItem16 = new System.Windows.Forms.ListViewItem("");
            System.Windows.Forms.ListViewItem listViewItem17 = new System.Windows.Forms.ListViewItem("");
            System.Windows.Forms.ListViewItem listViewItem18 = new System.Windows.Forms.ListViewItem("                        Um Dateien zu laden klicken sie bitte auf einen der obrig" +
                    "en Buttons!");
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.tab_Infos = new System.Windows.Forms.TabPage();
            this.tabCont_Allgemein = new System.Windows.Forms.TabControl();
            this.tab_format_Spawn = new System.Windows.Forms.TabPage();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.tab_format_Drop = new System.Windows.Forms.TabPage();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.tab_format_NPC = new System.Windows.Forms.TabPage();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.tab_MoverList = new System.Windows.Forms.TabPage();
            this.cmd_mover_suche_hide = new System.Windows.Forms.Button();
            this.list_mover_suche_ergebiss = new System.Windows.Forms.ListBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txt_mover_suche_eingabe = new System.Windows.Forms.TextBox();
            this.list_MoverIDs = new System.Windows.Forms.ListBox();
            this.label3 = new System.Windows.Forms.Label();
            this.Txt_Mover_MoverID = new System.Windows.Forms.TextBox();
            this.Combo_Mover_MoverIDs = new System.Windows.Forms.ComboBox();
            this.tab_ItemList = new System.Windows.Forms.TabPage();
            this.lv_mover_suche_ergebniss = new System.Windows.Forms.ListView();
            this.colum_ItemID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.colum_NameAnzeige = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.colum_InternName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.lv_Items = new System.Windows.Forms.ListView();
            this.colum_ID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.colum_AnzeigeName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.colum_NameIntern = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.combo_item_Name_Intern = new System.Windows.Forms.ComboBox();
            this.txt_item_suche_hide = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.txt_item_suche_eingabe = new System.Windows.Forms.TextBox();
            this.list_items = new System.Windows.Forms.ListBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txt_item_ID = new System.Windows.Forms.TextBox();
            this.combo_item_Name_Anzeige = new System.Windows.Forms.ComboBox();
            this.tab_einstell = new System.Windows.Forms.TabPage();
            this.cmd_about = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button3 = new System.Windows.Forms.Button();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.group_datei = new System.Windows.Forms.GroupBox();
            this.cmd_erweiter_uebernemen = new System.Windows.Forms.Button();
            this.check_udb = new System.Windows.Forms.CheckBox();
            this.check_npc = new System.Windows.Forms.CheckBox();
            this.check_drop = new System.Windows.Forms.CheckBox();
            this.check_Spawn = new System.Windows.Forms.CheckBox();
            this.tab_Usedb = new System.Windows.Forms.TabPage();
            this.cmd_udb_depack = new System.Windows.Forms.Button();
            this.label21 = new System.Windows.Forms.Label();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.cmd_udb_pack = new System.Windows.Forms.Button();
            this.tab_NPC = new System.Windows.Forms.TabPage();
            this.tc_NPCs = new System.Windows.Forms.TabControl();
            this.toolStrip2 = new System.Windows.Forms.ToolStrip();
            this.cmd_NPC_new = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator7 = new System.Windows.Forms.ToolStripSeparator();
            this.cmd_NPC_save = new System.Windows.Forms.ToolStripButton();
            this.cmd_NPC_saveAll = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator8 = new System.Windows.Forms.ToolStripSeparator();
            this.cmd_npc_close = new System.Windows.Forms.ToolStripButton();
            this.cmd_npc_open = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator9 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton14 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton15 = new System.Windows.Forms.ToolStripButton();
            this.tab_Drop = new System.Windows.Forms.TabPage();
            this.tc_drops = new System.Windows.Forms.TabControl();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton_drop_save = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton5 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton6 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton7 = new System.Windows.Forms.ToolStripButton();
            this.tab_Browser = new System.Windows.Forms.TabPage();
            this.cmd_opt = new System.Windows.Forms.Button();
            this.cmd_LoadNPCs = new System.Windows.Forms.Button();
            this.cmd_LoadDrops = new System.Windows.Forms.Button();
            this.cmd_LoadSpawns = new System.Windows.Forms.Button();
            this.list_Datas = new System.Windows.Forms.ListView();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tab_Spawn = new System.Windows.Forms.TabPage();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.cmd_toolstrip_newFile = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.cmd_toolstrip_save = new System.Windows.Forms.ToolStripButton();
            this.cmd_toolstrip_saveAll = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.cmd_toolstrip_close = new System.Windows.Forms.ToolStripButton();
            this.cmd_toolstrip_open = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.cmd_toolstrip_redo = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton9 = new System.Windows.Forms.ToolStripButton();
            this.tc_spawns = new System.Windows.Forms.TabControl();
            this.panel1 = new System.Windows.Forms.Panel();
            this.txt_Spawn_RespawnZeit = new System.Windows.Forms.TextBox();
            this.txt_Spawn_MoverID = new System.Windows.Forms.TextBox();
            this.txt_Spawn_MaxMobs = new System.Windows.Forms.TextBox();
            this.combo_Spawn_MoverIDs = new System.Windows.Forms.ComboBox();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.txt_Spawn_Gebiet = new System.Windows.Forms.TextBox();
            this.txt_Spawn_World = new System.Windows.Forms.TextBox();
            this.txt_Spawn_Z = new System.Windows.Forms.TextBox();
            this.txt_Spawn_Y = new System.Windows.Forms.TextBox();
            this.txt_Spawn_X = new System.Windows.Forms.TextBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.txt_Spawn_AggroChance = new System.Windows.Forms.TextBox();
            lbl_RespawnZeit = new System.Windows.Forms.Label();
            lbl_MoverID = new System.Windows.Forms.Label();
            lbl_Gebiet = new System.Windows.Forms.Label();
            lbl_MaxMobs = new System.Windows.Forms.Label();
            lbl_World = new System.Windows.Forms.Label();
            lbl_Z = new System.Windows.Forms.Label();
            lbl_Y = new System.Windows.Forms.Label();
            lbl_X = new System.Windows.Forms.Label();
            label8 = new System.Windows.Forms.Label();
            label9 = new System.Windows.Forms.Label();
            lbl_AggroChance = new System.Windows.Forms.Label();
            this.tab_Infos.SuspendLayout();
            this.tabCont_Allgemein.SuspendLayout();
            this.tab_format_Spawn.SuspendLayout();
            this.tab_format_Drop.SuspendLayout();
            this.tab_format_NPC.SuspendLayout();
            this.tab_MoverList.SuspendLayout();
            this.tab_ItemList.SuspendLayout();
            this.tab_einstell.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.group_datei.SuspendLayout();
            this.tab_Usedb.SuspendLayout();
            this.tab_NPC.SuspendLayout();
            this.toolStrip2.SuspendLayout();
            this.tab_Drop.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.tab_Browser.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tab_Spawn.SuspendLayout();
            this.toolStrip.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lbl_RespawnZeit
            // 
            lbl_RespawnZeit.Location = new System.Drawing.Point(10, 73);
            lbl_RespawnZeit.Name = "lbl_RespawnZeit";
            lbl_RespawnZeit.Size = new System.Drawing.Size(81, 20);
            lbl_RespawnZeit.TabIndex = 17;
            lbl_RespawnZeit.Text = "Respawn Zeit";
            // 
            // lbl_MoverID
            // 
            lbl_MoverID.Location = new System.Drawing.Point(7, 20);
            lbl_MoverID.Name = "lbl_MoverID";
            lbl_MoverID.Size = new System.Drawing.Size(179, 20);
            lbl_MoverID.TabIndex = 2;
            lbl_MoverID.Text = "Mover Name                                 ID";
            // 
            // lbl_Gebiet
            // 
            lbl_Gebiet.Location = new System.Drawing.Point(6, 75);
            lbl_Gebiet.Name = "lbl_Gebiet";
            lbl_Gebiet.Size = new System.Drawing.Size(76, 20);
            lbl_Gebiet.TabIndex = 27;
            lbl_Gebiet.Text = "Spawn Radius";
            // 
            // lbl_MaxMobs
            // 
            lbl_MaxMobs.Location = new System.Drawing.Point(135, 75);
            lbl_MaxMobs.Name = "lbl_MaxMobs";
            lbl_MaxMobs.Size = new System.Drawing.Size(65, 20);
            lbl_MaxMobs.TabIndex = 24;
            lbl_MaxMobs.Text = "Max Mobs";
            // 
            // lbl_World
            // 
            lbl_World.Location = new System.Drawing.Point(135, 49);
            lbl_World.Name = "lbl_World";
            lbl_World.Size = new System.Drawing.Size(65, 20);
            lbl_World.TabIndex = 22;
            lbl_World.Text = "World ID";
            // 
            // lbl_Z
            // 
            lbl_Z.Location = new System.Drawing.Point(135, 23);
            lbl_Z.Name = "lbl_Z";
            lbl_Z.Size = new System.Drawing.Size(65, 20);
            lbl_Z.TabIndex = 20;
            lbl_Z.Text = "Positon Z";
            // 
            // lbl_Y
            // 
            lbl_Y.Location = new System.Drawing.Point(6, 49);
            lbl_Y.Name = "lbl_Y";
            lbl_Y.Size = new System.Drawing.Size(65, 20);
            lbl_Y.TabIndex = 19;
            lbl_Y.Text = "Positon Y";
            // 
            // lbl_X
            // 
            lbl_X.Location = new System.Drawing.Point(6, 23);
            lbl_X.Name = "lbl_X";
            lbl_X.Size = new System.Drawing.Size(65, 20);
            lbl_X.TabIndex = 18;
            lbl_X.Text = "Positon X";
            // 
            // label8
            // 
            label8.Location = new System.Drawing.Point(9, 45);
            label8.Name = "label8";
            label8.Size = new System.Drawing.Size(81, 20);
            label8.TabIndex = 21;
            label8.Text = "Beginn Radius";
            // 
            // label9
            // 
            label9.Location = new System.Drawing.Point(9, 71);
            label9.Name = "label9";
            label9.Size = new System.Drawing.Size(81, 20);
            label9.TabIndex = 23;
            label9.Text = "Halten Radius";
            // 
            // lbl_AggroChance
            // 
            lbl_AggroChance.Location = new System.Drawing.Point(9, 19);
            lbl_AggroChance.Name = "lbl_AggroChance";
            lbl_AggroChance.Size = new System.Drawing.Size(81, 20);
            lbl_AggroChance.TabIndex = 19;
            lbl_AggroChance.Text = "Aggro Chance";
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "Alle Dateien|*.*|Spawn Dateien|*.spawn|Drop Dateien|*.drop|NPC Dateien|*.npc";
            // 
            // tab_Infos
            // 
            this.tab_Infos.Controls.Add(this.tabCont_Allgemein);
            this.tab_Infos.Location = new System.Drawing.Point(4, 22);
            this.tab_Infos.Name = "tab_Infos";
            this.tab_Infos.Size = new System.Drawing.Size(492, 392);
            this.tab_Infos.TabIndex = 7;
            this.tab_Infos.Text = "Autres";
            this.tab_Infos.UseVisualStyleBackColor = true;
            // 
            // tabCont_Allgemein
            // 
            this.tabCont_Allgemein.Controls.Add(this.tab_format_Spawn);
            this.tabCont_Allgemein.Controls.Add(this.tab_format_Drop);
            this.tabCont_Allgemein.Controls.Add(this.tab_format_NPC);
            this.tabCont_Allgemein.Controls.Add(this.tab_MoverList);
            this.tabCont_Allgemein.Controls.Add(this.tab_ItemList);
            this.tabCont_Allgemein.Controls.Add(this.tab_einstell);
            this.tabCont_Allgemein.Location = new System.Drawing.Point(3, 3);
            this.tabCont_Allgemein.Name = "tabCont_Allgemein";
            this.tabCont_Allgemein.SelectedIndex = 0;
            this.tabCont_Allgemein.Size = new System.Drawing.Size(483, 463);
            this.tabCont_Allgemein.TabIndex = 2;
            this.tabCont_Allgemein.SelectedIndexChanged += new System.EventHandler(this.tabCont_AllgemeinSelectedIndexChanged);
            // 
            // tab_format_Spawn
            // 
            this.tab_format_Spawn.Controls.Add(this.textBox1);
            this.tab_format_Spawn.Location = new System.Drawing.Point(4, 22);
            this.tab_format_Spawn.Name = "tab_format_Spawn";
            this.tab_format_Spawn.Padding = new System.Windows.Forms.Padding(3);
            this.tab_format_Spawn.Size = new System.Drawing.Size(475, 437);
            this.tab_format_Spawn.TabIndex = 0;
            this.tab_format_Spawn.Text = "Spawn Format";
            this.tab_format_Spawn.UseVisualStyleBackColor = true;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(6, 6);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox1.Size = new System.Drawing.Size(463, 257);
            this.textBox1.TabIndex = 3;
            this.textBox1.Text = resources.GetString("textBox1.Text");
            // 
            // tab_format_Drop
            // 
            this.tab_format_Drop.Controls.Add(this.textBox2);
            this.tab_format_Drop.Location = new System.Drawing.Point(4, 22);
            this.tab_format_Drop.Name = "tab_format_Drop";
            this.tab_format_Drop.Padding = new System.Windows.Forms.Padding(3);
            this.tab_format_Drop.Size = new System.Drawing.Size(475, 437);
            this.tab_format_Drop.TabIndex = 1;
            this.tab_format_Drop.Text = "Drop Format";
            this.tab_format_Drop.UseVisualStyleBackColor = true;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(6, 6);
            this.textBox2.Multiline = true;
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.Size = new System.Drawing.Size(463, 257);
            this.textBox2.TabIndex = 0;
            this.textBox2.Text = resources.GetString("textBox2.Text");
            // 
            // tab_format_NPC
            // 
            this.tab_format_NPC.Controls.Add(this.textBox3);
            this.tab_format_NPC.Location = new System.Drawing.Point(4, 22);
            this.tab_format_NPC.Name = "tab_format_NPC";
            this.tab_format_NPC.Size = new System.Drawing.Size(475, 437);
            this.tab_format_NPC.TabIndex = 2;
            this.tab_format_NPC.Text = "NPC Format";
            this.tab_format_NPC.UseVisualStyleBackColor = true;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(3, 3);
            this.textBox3.Multiline = true;
            this.textBox3.Name = "textBox3";
            this.textBox3.ReadOnly = true;
            this.textBox3.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox3.Size = new System.Drawing.Size(469, 313);
            this.textBox3.TabIndex = 0;
            this.textBox3.Text = resources.GetString("textBox3.Text");
            // 
            // tab_MoverList
            // 
            this.tab_MoverList.Controls.Add(this.cmd_mover_suche_hide);
            this.tab_MoverList.Controls.Add(this.list_mover_suche_ergebiss);
            this.tab_MoverList.Controls.Add(this.label5);
            this.tab_MoverList.Controls.Add(this.txt_mover_suche_eingabe);
            this.tab_MoverList.Controls.Add(this.list_MoverIDs);
            this.tab_MoverList.Controls.Add(this.label3);
            this.tab_MoverList.Controls.Add(this.Txt_Mover_MoverID);
            this.tab_MoverList.Controls.Add(this.Combo_Mover_MoverIDs);
            this.tab_MoverList.Location = new System.Drawing.Point(4, 22);
            this.tab_MoverList.Name = "tab_MoverList";
            this.tab_MoverList.Size = new System.Drawing.Size(475, 437);
            this.tab_MoverList.TabIndex = 3;
            this.tab_MoverList.Text = "Mover Liste";
            this.tab_MoverList.UseVisualStyleBackColor = true;
            // 
            // cmd_mover_suche_hide
            // 
            this.cmd_mover_suche_hide.Location = new System.Drawing.Point(366, 295);
            this.cmd_mover_suche_hide.Name = "cmd_mover_suche_hide";
            this.cmd_mover_suche_hide.Size = new System.Drawing.Size(106, 20);
            this.cmd_mover_suche_hide.TabIndex = 27;
            this.cmd_mover_suche_hide.Text = "Suche zeigen";
            this.cmd_mover_suche_hide.UseVisualStyleBackColor = true;
            this.cmd_mover_suche_hide.Click += new System.EventHandler(this.Cmd_mover_suche_hideClick);
            // 
            // list_mover_suche_ergebiss
            // 
            this.list_mover_suche_ergebiss.FormattingEnabled = true;
            this.list_mover_suche_ergebiss.Location = new System.Drawing.Point(9, 321);
            this.list_mover_suche_ergebiss.Name = "list_mover_suche_ergebiss";
            this.list_mover_suche_ergebiss.Size = new System.Drawing.Size(463, 108);
            this.list_mover_suche_ergebiss.TabIndex = 26;
            this.list_mover_suche_ergebiss.SelectedIndexChanged += new System.EventHandler(this.List_mover_suche_ergebissSelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(9, 295);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(51, 20);
            this.label5.TabIndex = 25;
            this.label5.Text = "Suchen:";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // txt_mover_suche_eingabe
            // 
            this.txt_mover_suche_eingabe.Location = new System.Drawing.Point(66, 295);
            this.txt_mover_suche_eingabe.Name = "txt_mover_suche_eingabe";
            this.txt_mover_suche_eingabe.Size = new System.Drawing.Size(294, 20);
            this.txt_mover_suche_eingabe.TabIndex = 23;
            this.txt_mover_suche_eingabe.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txt_mover_suche_eingabeKeyPress);
            // 
            // list_MoverIDs
            // 
            this.list_MoverIDs.FormattingEnabled = true;
            this.list_MoverIDs.Location = new System.Drawing.Point(9, 54);
            this.list_MoverIDs.Name = "list_MoverIDs";
            this.list_MoverIDs.Size = new System.Drawing.Size(463, 238);
            this.list_MoverIDs.TabIndex = 22;
            this.list_MoverIDs.SelectedIndexChanged += new System.EventHandler(this.list_MoverIDsSelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(9, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(463, 15);
            this.label3.TabIndex = 19;
            this.label3.Text = "Mover Name                                                                       " +
                "                                                     ID";
            // 
            // Txt_Mover_MoverID
            // 
            this.Txt_Mover_MoverID.Location = new System.Drawing.Point(429, 28);
            this.Txt_Mover_MoverID.Name = "Txt_Mover_MoverID";
            this.Txt_Mover_MoverID.Size = new System.Drawing.Size(43, 20);
            this.Txt_Mover_MoverID.TabIndex = 20;
            this.Txt_Mover_MoverID.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Txt_Mover_MoverID.TextChanged += new System.EventHandler(this.Txt_Mover_MoverIDTextChanged);
            // 
            // Combo_Mover_MoverIDs
            // 
            this.Combo_Mover_MoverIDs.FormattingEnabled = true;
            this.Combo_Mover_MoverIDs.Location = new System.Drawing.Point(9, 27);
            this.Combo_Mover_MoverIDs.Name = "Combo_Mover_MoverIDs";
            this.Combo_Mover_MoverIDs.Size = new System.Drawing.Size(414, 21);
            this.Combo_Mover_MoverIDs.TabIndex = 21;
            this.Combo_Mover_MoverIDs.SelectedIndexChanged += new System.EventHandler(this.Combo_Mover_MoverIDsSelectedIndexChanged);
            // 
            // tab_ItemList
            // 
            this.tab_ItemList.Controls.Add(this.lv_mover_suche_ergebniss);
            this.tab_ItemList.Controls.Add(this.lv_Items);
            this.tab_ItemList.Controls.Add(this.combo_item_Name_Intern);
            this.tab_ItemList.Controls.Add(this.txt_item_suche_hide);
            this.tab_ItemList.Controls.Add(this.label6);
            this.tab_ItemList.Controls.Add(this.txt_item_suche_eingabe);
            this.tab_ItemList.Controls.Add(this.list_items);
            this.tab_ItemList.Controls.Add(this.label7);
            this.tab_ItemList.Controls.Add(this.txt_item_ID);
            this.tab_ItemList.Controls.Add(this.combo_item_Name_Anzeige);
            this.tab_ItemList.Location = new System.Drawing.Point(4, 22);
            this.tab_ItemList.Name = "tab_ItemList";
            this.tab_ItemList.Size = new System.Drawing.Size(475, 437);
            this.tab_ItemList.TabIndex = 4;
            this.tab_ItemList.Text = "Item Liste";
            this.tab_ItemList.UseVisualStyleBackColor = true;
            // 
            // lv_mover_suche_ergebniss
            // 
            this.lv_mover_suche_ergebniss.Activation = System.Windows.Forms.ItemActivation.OneClick;
            this.lv_mover_suche_ergebniss.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.colum_ItemID,
            this.colum_NameAnzeige,
            this.colum_InternName});
            this.lv_mover_suche_ergebniss.FullRowSelect = true;
            this.lv_mover_suche_ergebniss.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.lv_mover_suche_ergebniss.Location = new System.Drawing.Point(6, 320);
            this.lv_mover_suche_ergebniss.Name = "lv_mover_suche_ergebniss";
            this.lv_mover_suche_ergebniss.Size = new System.Drawing.Size(463, 114);
            this.lv_mover_suche_ergebniss.TabIndex = 39;
            this.lv_mover_suche_ergebniss.UseCompatibleStateImageBehavior = false;
            this.lv_mover_suche_ergebniss.View = System.Windows.Forms.View.Details;
            // 
            // colum_ItemID
            // 
            this.colum_ItemID.Text = "Item ID";
            this.colum_ItemID.Width = 73;
            // 
            // colum_NameAnzeige
            // 
            this.colum_NameAnzeige.Text = "Anzeige Name";
            this.colum_NameAnzeige.Width = 151;
            // 
            // colum_InternName
            // 
            this.colum_InternName.Text = "Interner Name";
            this.colum_InternName.Width = 181;
            // 
            // lv_Items
            // 
            this.lv_Items.Activation = System.Windows.Forms.ItemActivation.OneClick;
            this.lv_Items.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.colum_ID,
            this.colum_AnzeigeName,
            this.colum_NameIntern});
            this.lv_Items.FullRowSelect = true;
            this.lv_Items.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.lv_Items.Location = new System.Drawing.Point(6, 54);
            this.lv_Items.MultiSelect = false;
            this.lv_Items.Name = "lv_Items";
            this.lv_Items.Size = new System.Drawing.Size(463, 234);
            this.lv_Items.TabIndex = 38;
            this.lv_Items.UseCompatibleStateImageBehavior = false;
            this.lv_Items.View = System.Windows.Forms.View.Details;
            this.lv_Items.SelectedIndexChanged += new System.EventHandler(this.Lv_ItemsSelectedIndexChanged);
            // 
            // colum_ID
            // 
            this.colum_ID.Text = "Item ID";
            this.colum_ID.Width = 58;
            // 
            // colum_AnzeigeName
            // 
            this.colum_AnzeigeName.Text = "Anzeige Name";
            this.colum_AnzeigeName.Width = 160;
            // 
            // colum_NameIntern
            // 
            this.colum_NameIntern.Text = "Interner Name";
            this.colum_NameIntern.Width = 233;
            // 
            // combo_item_Name_Intern
            // 
            this.combo_item_Name_Intern.FormattingEnabled = true;
            this.combo_item_Name_Intern.Location = new System.Drawing.Point(214, 27);
            this.combo_item_Name_Intern.Name = "combo_item_Name_Intern";
            this.combo_item_Name_Intern.Size = new System.Drawing.Size(202, 21);
            this.combo_item_Name_Intern.TabIndex = 37;
            this.combo_item_Name_Intern.SelectedIndexChanged += new System.EventHandler(this.Combo_item_Name_InternSelectedIndexChanged);
            // 
            // txt_item_suche_hide
            // 
            this.txt_item_suche_hide.Location = new System.Drawing.Point(363, 294);
            this.txt_item_suche_hide.Name = "txt_item_suche_hide";
            this.txt_item_suche_hide.Size = new System.Drawing.Size(106, 20);
            this.txt_item_suche_hide.TabIndex = 36;
            this.txt_item_suche_hide.Text = "Suche zeigen";
            this.txt_item_suche_hide.UseVisualStyleBackColor = true;
            this.txt_item_suche_hide.Click += new System.EventHandler(this.Txt_item_suche_hideClick);
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(6, 294);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(51, 20);
            this.label6.TabIndex = 34;
            this.label6.Text = "Suchen:";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // txt_item_suche_eingabe
            // 
            this.txt_item_suche_eingabe.Location = new System.Drawing.Point(63, 294);
            this.txt_item_suche_eingabe.Name = "txt_item_suche_eingabe";
            this.txt_item_suche_eingabe.Size = new System.Drawing.Size(294, 20);
            this.txt_item_suche_eingabe.TabIndex = 32;
            this.txt_item_suche_eingabe.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txt_item_suche_eingabeKeyDown);
            // 
            // list_items
            // 
            this.list_items.FormattingEnabled = true;
            this.list_items.Location = new System.Drawing.Point(6, 294);
            this.list_items.Name = "list_items";
            this.list_items.Size = new System.Drawing.Size(10, 4);
            this.list_items.TabIndex = 31;
            this.list_items.SelectedIndexChanged += new System.EventHandler(this.List_itemsSelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(6, 8);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(463, 15);
            this.label7.TabIndex = 28;
            this.label7.Text = "Anzeige Name                                              Interner Name          " +
                "                                          ID";
            // 
            // txt_item_ID
            // 
            this.txt_item_ID.Location = new System.Drawing.Point(422, 27);
            this.txt_item_ID.Name = "txt_item_ID";
            this.txt_item_ID.Size = new System.Drawing.Size(47, 20);
            this.txt_item_ID.TabIndex = 29;
            this.txt_item_ID.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txt_item_ID.TextChanged += new System.EventHandler(this.Txt_item_IDTextChanged);
            // 
            // combo_item_Name_Anzeige
            // 
            this.combo_item_Name_Anzeige.FormattingEnabled = true;
            this.combo_item_Name_Anzeige.Location = new System.Drawing.Point(6, 26);
            this.combo_item_Name_Anzeige.Name = "combo_item_Name_Anzeige";
            this.combo_item_Name_Anzeige.Size = new System.Drawing.Size(202, 21);
            this.combo_item_Name_Anzeige.TabIndex = 30;
            this.combo_item_Name_Anzeige.SelectedIndexChanged += new System.EventHandler(this.Combo_item_Name_AnzeigeSelectedIndexChanged);
            // 
            // tab_einstell
            // 
            this.tab_einstell.Controls.Add(this.cmd_about);
            this.tab_einstell.Controls.Add(this.groupBox1);
            this.tab_einstell.Controls.Add(this.group_datei);
            this.tab_einstell.Location = new System.Drawing.Point(4, 22);
            this.tab_einstell.Name = "tab_einstell";
            this.tab_einstell.Size = new System.Drawing.Size(475, 437);
            this.tab_einstell.TabIndex = 5;
            this.tab_einstell.Text = "Einstellungen";
            this.tab_einstell.UseVisualStyleBackColor = true;
            // 
            // cmd_about
            // 
            this.cmd_about.Location = new System.Drawing.Point(204, 90);
            this.cmd_about.Name = "cmd_about";
            this.cmd_about.Size = new System.Drawing.Size(268, 38);
            this.cmd_about.TabIndex = 2;
            this.cmd_about.Text = "About";
            this.cmd_about.UseVisualStyleBackColor = true;
            this.cmd_about.Click += new System.EventHandler(this.Cmd_aboutClick);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button3);
            this.groupBox1.Controls.Add(this.textBox4);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Enabled = false;
            this.groupBox1.Location = new System.Drawing.Point(204, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(268, 78);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Dauerhaft ein eigenes Spheron Verzeichniss wählen";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(11, 44);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 2;
            this.button3.Text = "...";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.Button3Click);
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(11, 19);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(251, 20);
            this.textBox4.TabIndex = 1;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(179, 44);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(83, 23);
            this.button2.TabIndex = 0;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // group_datei
            // 
            this.group_datei.Controls.Add(this.cmd_erweiter_uebernemen);
            this.group_datei.Controls.Add(this.check_udb);
            this.group_datei.Controls.Add(this.check_npc);
            this.group_datei.Controls.Add(this.check_drop);
            this.group_datei.Controls.Add(this.check_Spawn);
            this.group_datei.Location = new System.Drawing.Point(3, 6);
            this.group_datei.Name = "group_datei";
            this.group_datei.Size = new System.Drawing.Size(197, 122);
            this.group_datei.TabIndex = 0;
            this.group_datei.TabStop = false;
            this.group_datei.Text = "Datei Verknüpfungen";
            // 
            // cmd_erweiter_uebernemen
            // 
            this.cmd_erweiter_uebernemen.Location = new System.Drawing.Point(6, 84);
            this.cmd_erweiter_uebernemen.Name = "cmd_erweiter_uebernemen";
            this.cmd_erweiter_uebernemen.Size = new System.Drawing.Size(185, 29);
            this.cmd_erweiter_uebernemen.TabIndex = 4;
            this.cmd_erweiter_uebernemen.Text = "Übernemen";
            this.cmd_erweiter_uebernemen.UseVisualStyleBackColor = true;
            this.cmd_erweiter_uebernemen.Click += new System.EventHandler(this.Cmd_erweiter_uebernemenClick);
            // 
            // check_udb
            // 
            this.check_udb.Location = new System.Drawing.Point(102, 44);
            this.check_udb.Name = "check_udb";
            this.check_udb.Size = new System.Drawing.Size(93, 34);
            this.check_udb.TabIndex = 3;
            this.check_udb.Text = "Use Datenbanken";
            this.check_udb.UseVisualStyleBackColor = true;
            // 
            // check_npc
            // 
            this.check_npc.Location = new System.Drawing.Point(6, 49);
            this.check_npc.Name = "check_npc";
            this.check_npc.Size = new System.Drawing.Size(104, 24);
            this.check_npc.TabIndex = 2;
            this.check_npc.Text = "NPC Dateien";
            this.check_npc.UseVisualStyleBackColor = true;
            // 
            // check_drop
            // 
            this.check_drop.Location = new System.Drawing.Point(102, 19);
            this.check_drop.Name = "check_drop";
            this.check_drop.Size = new System.Drawing.Size(104, 24);
            this.check_drop.TabIndex = 1;
            this.check_drop.Text = "Drop Dateien";
            this.check_drop.UseVisualStyleBackColor = true;
            // 
            // check_Spawn
            // 
            this.check_Spawn.Location = new System.Drawing.Point(6, 19);
            this.check_Spawn.Name = "check_Spawn";
            this.check_Spawn.Size = new System.Drawing.Size(104, 24);
            this.check_Spawn.TabIndex = 0;
            this.check_Spawn.Text = "Spawn Dateien";
            this.check_Spawn.UseVisualStyleBackColor = true;
            // 
            // tab_Usedb
            // 
            this.tab_Usedb.Controls.Add(this.cmd_udb_depack);
            this.tab_Usedb.Controls.Add(this.label21);
            this.tab_Usedb.Controls.Add(this.listBox1);
            this.tab_Usedb.Controls.Add(this.cmd_udb_pack);
            this.tab_Usedb.Location = new System.Drawing.Point(4, 22);
            this.tab_Usedb.Name = "tab_Usedb";
            this.tab_Usedb.Size = new System.Drawing.Size(492, 392);
            this.tab_Usedb.TabIndex = 6;
            this.tab_Usedb.Text = "Base de données";
            this.tab_Usedb.UseVisualStyleBackColor = true;
            // 
            // cmd_udb_depack
            // 
            this.cmd_udb_depack.Enabled = false;
            this.cmd_udb_depack.Location = new System.Drawing.Point(270, 3);
            this.cmd_udb_depack.Name = "cmd_udb_depack";
            this.cmd_udb_depack.Size = new System.Drawing.Size(219, 28);
            this.cmd_udb_depack.TabIndex = 6;
            this.cmd_udb_depack.Text = "DB Entpacken";
            this.cmd_udb_depack.UseVisualStyleBackColor = true;
            this.cmd_udb_depack.Click += new System.EventHandler(this.cmd_udb_depackClick);
            // 
            // label21
            // 
            this.label21.Enabled = false;
            this.label21.Location = new System.Drawing.Point(3, 34);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(275, 13);
            this.label21.TabIndex = 5;
            this.label21.Text = "Ein/Aus-gelesene Daten: (Dateiname \"--->\" Datei Inhalt)";
            // 
            // listBox1
            // 
            this.listBox1.Enabled = false;
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(3, 52);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(483, 329);
            this.listBox1.TabIndex = 3;
            // 
            // cmd_udb_pack
            // 
            this.cmd_udb_pack.Enabled = false;
            this.cmd_udb_pack.Location = new System.Drawing.Point(3, 3);
            this.cmd_udb_pack.Name = "cmd_udb_pack";
            this.cmd_udb_pack.Size = new System.Drawing.Size(219, 28);
            this.cmd_udb_pack.TabIndex = 0;
            this.cmd_udb_pack.Text = "DB Erzeugen";
            this.cmd_udb_pack.UseVisualStyleBackColor = true;
            this.cmd_udb_pack.Click += new System.EventHandler(this.cmd_udb_packClick);
            // 
            // tab_NPC
            // 
            this.tab_NPC.Controls.Add(this.tc_NPCs);
            this.tab_NPC.Controls.Add(this.toolStrip2);
            this.tab_NPC.Location = new System.Drawing.Point(4, 22);
            this.tab_NPC.Name = "tab_NPC";
            this.tab_NPC.Size = new System.Drawing.Size(492, 392);
            this.tab_NPC.TabIndex = 3;
            this.tab_NPC.Text = "Editeur de PNJ";
            this.tab_NPC.UseVisualStyleBackColor = true;
            // 
            // tc_NPCs
            // 
            this.tc_NPCs.Location = new System.Drawing.Point(3, 28);
            this.tc_NPCs.Name = "tc_NPCs";
            this.tc_NPCs.SelectedIndex = 0;
            this.tc_NPCs.Size = new System.Drawing.Size(486, 360);
            this.tc_NPCs.TabIndex = 11;
            // 
            // toolStrip2
            // 
            this.toolStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmd_NPC_new,
            this.toolStripSeparator7,
            this.cmd_NPC_save,
            this.cmd_NPC_saveAll,
            this.toolStripSeparator8,
            this.cmd_npc_close,
            this.cmd_npc_open,
            this.toolStripSeparator9,
            this.toolStripButton14,
            this.toolStripButton15});
            this.toolStrip2.Location = new System.Drawing.Point(0, 0);
            this.toolStrip2.Name = "toolStrip2";
            this.toolStrip2.Size = new System.Drawing.Size(492, 25);
            this.toolStrip2.TabIndex = 10;
            this.toolStrip2.Text = "toolStrip2";
            // 
            // cmd_NPC_new
            // 
            this.cmd_NPC_new.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_NPC_new.Image = ((System.Drawing.Image)(resources.GetObject("cmd_NPC_new.Image")));
            this.cmd_NPC_new.Name = "cmd_NPC_new";
            this.cmd_NPC_new.Size = new System.Drawing.Size(23, 22);
            this.cmd_NPC_new.ToolTipText = "Neu";
            this.cmd_NPC_new.Click += new System.EventHandler(this.Cmd_NPC_newClick);
            // 
            // toolStripSeparator7
            // 
            this.toolStripSeparator7.Name = "toolStripSeparator7";
            this.toolStripSeparator7.Size = new System.Drawing.Size(6, 25);
            // 
            // cmd_NPC_save
            // 
            this.cmd_NPC_save.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_NPC_save.Image = ((System.Drawing.Image)(resources.GetObject("cmd_NPC_save.Image")));
            this.cmd_NPC_save.Name = "cmd_NPC_save";
            this.cmd_NPC_save.Size = new System.Drawing.Size(23, 22);
            this.cmd_NPC_save.ToolTipText = "Speichern";
            this.cmd_NPC_save.Click += new System.EventHandler(this.Cmd_NPC_saveClick);
            // 
            // cmd_NPC_saveAll
            // 
            this.cmd_NPC_saveAll.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_NPC_saveAll.Image = ((System.Drawing.Image)(resources.GetObject("cmd_NPC_saveAll.Image")));
            this.cmd_NPC_saveAll.Name = "cmd_NPC_saveAll";
            this.cmd_NPC_saveAll.Size = new System.Drawing.Size(23, 22);
            this.cmd_NPC_saveAll.ToolTipText = "Alle Speichern";
            this.cmd_NPC_saveAll.Click += new System.EventHandler(this.Cmd_NPC_saveAllClick);
            // 
            // toolStripSeparator8
            // 
            this.toolStripSeparator8.Name = "toolStripSeparator8";
            this.toolStripSeparator8.Size = new System.Drawing.Size(6, 25);
            // 
            // cmd_npc_close
            // 
            this.cmd_npc_close.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_npc_close.Image = ((System.Drawing.Image)(resources.GetObject("cmd_npc_close.Image")));
            this.cmd_npc_close.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmd_npc_close.Name = "cmd_npc_close";
            this.cmd_npc_close.Size = new System.Drawing.Size(23, 22);
            this.cmd_npc_close.Text = "toolStripButton1";
            this.cmd_npc_close.ToolTipText = "Schliessen";
            this.cmd_npc_close.Click += new System.EventHandler(this.Cmd_npc_closeClick);
            // 
            // cmd_npc_open
            // 
            this.cmd_npc_open.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_npc_open.Image = ((System.Drawing.Image)(resources.GetObject("cmd_npc_open.Image")));
            this.cmd_npc_open.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmd_npc_open.Name = "cmd_npc_open";
            this.cmd_npc_open.Size = new System.Drawing.Size(23, 22);
            this.cmd_npc_open.Text = "toolStripButton2";
            this.cmd_npc_open.ToolTipText = "Öffnen";
            // 
            // toolStripSeparator9
            // 
            this.toolStripSeparator9.Name = "toolStripSeparator9";
            this.toolStripSeparator9.Size = new System.Drawing.Size(6, 25);
            this.toolStripSeparator9.Visible = false;
            // 
            // toolStripButton14
            // 
            this.toolStripButton14.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton14.Enabled = false;
            this.toolStripButton14.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton14.Image")));
            this.toolStripButton14.Name = "toolStripButton14";
            this.toolStripButton14.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton14.ToolTipText = "Wiederherstellen";
            this.toolStripButton14.Visible = false;
            // 
            // toolStripButton15
            // 
            this.toolStripButton15.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton15.Enabled = false;
            this.toolStripButton15.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton15.Image")));
            this.toolStripButton15.Name = "toolStripButton15";
            this.toolStripButton15.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton15.ToolTipText = "Rückgengig";
            this.toolStripButton15.Visible = false;
            // 
            // tab_Drop
            // 
            this.tab_Drop.Controls.Add(this.tc_drops);
            this.tab_Drop.Controls.Add(this.toolStrip1);
            this.tab_Drop.Location = new System.Drawing.Point(4, 22);
            this.tab_Drop.Name = "tab_Drop";
            this.tab_Drop.Size = new System.Drawing.Size(492, 392);
            this.tab_Drop.TabIndex = 2;
            this.tab_Drop.Text = "Editeur de drops";
            this.tab_Drop.UseVisualStyleBackColor = true;
            // 
            // tc_drops
            // 
            this.tc_drops.Enabled = false;
            this.tc_drops.Location = new System.Drawing.Point(3, 28);
            this.tc_drops.Name = "tc_drops";
            this.tc_drops.SelectedIndex = 0;
            this.tc_drops.Size = new System.Drawing.Size(486, 360);
            this.tc_drops.TabIndex = 10;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Enabled = false;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton1,
            this.toolStripSeparator4,
            this.toolStripButton_drop_save,
            this.toolStripButton3,
            this.toolStripSeparator5,
            this.toolStripButton4,
            this.toolStripButton5,
            this.toolStripSeparator6,
            this.toolStripButton6,
            this.toolStripButton7});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(492, 25);
            this.toolStrip1.TabIndex = 9;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton1.ToolTipText = "Neu";
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton_drop_save
            // 
            this.toolStripButton_drop_save.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_drop_save.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton_drop_save.Image")));
            this.toolStripButton_drop_save.Name = "toolStripButton_drop_save";
            this.toolStripButton_drop_save.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton_drop_save.ToolTipText = "Speichern";
            // 
            // toolStripButton3
            // 
            this.toolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton3.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton3.Image")));
            this.toolStripButton3.Name = "toolStripButton3";
            this.toolStripButton3.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton3.ToolTipText = "Alle Speichern";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton4.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton4.Image")));
            this.toolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton4.Text = "toolStripButton1";
            this.toolStripButton4.ToolTipText = "Schliessen";
            // 
            // toolStripButton5
            // 
            this.toolStripButton5.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton5.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton5.Image")));
            this.toolStripButton5.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton5.Name = "toolStripButton5";
            this.toolStripButton5.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton5.Text = "toolStripButton2";
            this.toolStripButton5.ToolTipText = "Öffnen";
            this.toolStripButton5.Click += new System.EventHandler(this.ToolStripButton5Click);
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(6, 25);
            this.toolStripSeparator6.Visible = false;
            // 
            // toolStripButton6
            // 
            this.toolStripButton6.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton6.Enabled = false;
            this.toolStripButton6.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton6.Image")));
            this.toolStripButton6.Name = "toolStripButton6";
            this.toolStripButton6.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton6.ToolTipText = "Wiederherstellen";
            this.toolStripButton6.Visible = false;
            // 
            // toolStripButton7
            // 
            this.toolStripButton7.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton7.Enabled = false;
            this.toolStripButton7.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton7.Image")));
            this.toolStripButton7.Name = "toolStripButton7";
            this.toolStripButton7.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton7.ToolTipText = "Rückgengig";
            this.toolStripButton7.Visible = false;
            // 
            // tab_Browser
            // 
            this.tab_Browser.Controls.Add(this.cmd_opt);
            this.tab_Browser.Controls.Add(this.cmd_LoadNPCs);
            this.tab_Browser.Controls.Add(this.cmd_LoadDrops);
            this.tab_Browser.Controls.Add(this.cmd_LoadSpawns);
            this.tab_Browser.Controls.Add(this.list_Datas);
            this.tab_Browser.Location = new System.Drawing.Point(4, 22);
            this.tab_Browser.Name = "tab_Browser";
            this.tab_Browser.Padding = new System.Windows.Forms.Padding(3);
            this.tab_Browser.Size = new System.Drawing.Size(492, 392);
            this.tab_Browser.TabIndex = 0;
            this.tab_Browser.Text = "Accueil";
            this.tab_Browser.UseVisualStyleBackColor = true;
            // 
            // cmd_opt
            // 
            this.cmd_opt.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmd_opt.Location = new System.Drawing.Point(369, 6);
            this.cmd_opt.Name = "cmd_opt";
            this.cmd_opt.Size = new System.Drawing.Size(115, 42);
            this.cmd_opt.TabIndex = 20;
            this.cmd_opt.Text = "Options et configurations";
            this.cmd_opt.UseVisualStyleBackColor = true;
            this.cmd_opt.Click += new System.EventHandler(this.cmd_optClick);
            // 
            // cmd_LoadNPCs
            // 
            this.cmd_LoadNPCs.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmd_LoadNPCs.Location = new System.Drawing.Point(248, 6);
            this.cmd_LoadNPCs.Name = "cmd_LoadNPCs";
            this.cmd_LoadNPCs.Size = new System.Drawing.Size(115, 42);
            this.cmd_LoadNPCs.TabIndex = 14;
            this.cmd_LoadNPCs.Text = "NPC Data";
            this.cmd_LoadNPCs.UseVisualStyleBackColor = true;
            this.cmd_LoadNPCs.Click += new System.EventHandler(this.Cmd_LoadNPCsClick);
            // 
            // cmd_LoadDrops
            // 
            this.cmd_LoadDrops.Enabled = false;
            this.cmd_LoadDrops.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmd_LoadDrops.Location = new System.Drawing.Point(127, 6);
            this.cmd_LoadDrops.Name = "cmd_LoadDrops";
            this.cmd_LoadDrops.Size = new System.Drawing.Size(115, 42);
            this.cmd_LoadDrops.TabIndex = 13;
            this.cmd_LoadDrops.Text = "Drops Data";
            this.cmd_LoadDrops.UseVisualStyleBackColor = true;
            this.cmd_LoadDrops.Click += new System.EventHandler(this.Cmd_LoadDropsClick);
            // 
            // cmd_LoadSpawns
            // 
            this.cmd_LoadSpawns.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmd_LoadSpawns.Location = new System.Drawing.Point(6, 6);
            this.cmd_LoadSpawns.Name = "cmd_LoadSpawns";
            this.cmd_LoadSpawns.Size = new System.Drawing.Size(115, 42);
            this.cmd_LoadSpawns.TabIndex = 12;
            this.cmd_LoadSpawns.Text = "Spawn Data";
            this.cmd_LoadSpawns.UseVisualStyleBackColor = true;
            this.cmd_LoadSpawns.Click += new System.EventHandler(this.Cmd_LoadSpawnsClick);
            // 
            // list_Datas
            // 
            this.list_Datas.AllowDrop = true;
            this.list_Datas.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.list_Datas.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem13,
            listViewItem14,
            listViewItem15,
            listViewItem16,
            listViewItem17,
            listViewItem18});
            this.list_Datas.Location = new System.Drawing.Point(6, 54);
            this.list_Datas.MultiSelect = false;
            this.list_Datas.Name = "list_Datas";
            this.list_Datas.ShowItemToolTips = true;
            this.list_Datas.Size = new System.Drawing.Size(477, 329);
            this.list_Datas.TabIndex = 11;
            this.list_Datas.UseCompatibleStateImageBehavior = false;
            this.list_Datas.View = System.Windows.Forms.View.List;
            this.list_Datas.SelectedIndexChanged += new System.EventHandler(this.List_DatasSelectedIndexChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tab_Browser);
            this.tabControl1.Controls.Add(this.tab_Spawn);
            this.tabControl1.Controls.Add(this.tab_Drop);
            this.tabControl1.Controls.Add(this.tab_NPC);
            this.tabControl1.Controls.Add(this.tab_Usedb);
            this.tabControl1.Controls.Add(this.tab_Infos);
            this.tabControl1.Location = new System.Drawing.Point(5, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(500, 418);
            this.tabControl1.TabIndex = 0;
            this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1SelectedIndexChange);
            // 
            // tab_Spawn
            // 
            this.tab_Spawn.Controls.Add(this.toolStrip);
            this.tab_Spawn.Controls.Add(this.tc_spawns);
            this.tab_Spawn.Location = new System.Drawing.Point(4, 22);
            this.tab_Spawn.Name = "tab_Spawn";
            this.tab_Spawn.Padding = new System.Windows.Forms.Padding(3);
            this.tab_Spawn.Size = new System.Drawing.Size(492, 392);
            this.tab_Spawn.TabIndex = 1;
            this.tab_Spawn.Text = "Editeur de spawns";
            this.tab_Spawn.UseVisualStyleBackColor = true;
            // 
            // toolStrip
            // 
            this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmd_toolstrip_newFile,
            this.toolStripSeparator1,
            this.cmd_toolstrip_save,
            this.cmd_toolstrip_saveAll,
            this.toolStripSeparator3,
            this.cmd_toolstrip_close,
            this.cmd_toolstrip_open,
            this.toolStripSeparator2,
            this.cmd_toolstrip_redo,
            this.toolStripButton9});
            this.toolStrip.Location = new System.Drawing.Point(3, 3);
            this.toolStrip.Name = "toolStrip";
            this.toolStrip.Size = new System.Drawing.Size(486, 25);
            this.toolStrip.TabIndex = 1;
            this.toolStrip.Text = "toolStrip1";
            // 
            // cmd_toolstrip_newFile
            // 
            this.cmd_toolstrip_newFile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_toolstrip_newFile.Image = ((System.Drawing.Image)(resources.GetObject("cmd_toolstrip_newFile.Image")));
            this.cmd_toolstrip_newFile.Name = "cmd_toolstrip_newFile";
            this.cmd_toolstrip_newFile.Size = new System.Drawing.Size(23, 22);
            this.cmd_toolstrip_newFile.ToolTipText = "Neu";
            this.cmd_toolstrip_newFile.Click += new System.EventHandler(this.Cmd_toolstrip_newFileClick);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // cmd_toolstrip_save
            // 
            this.cmd_toolstrip_save.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_toolstrip_save.Image = ((System.Drawing.Image)(resources.GetObject("cmd_toolstrip_save.Image")));
            this.cmd_toolstrip_save.Name = "cmd_toolstrip_save";
            this.cmd_toolstrip_save.Size = new System.Drawing.Size(23, 22);
            this.cmd_toolstrip_save.ToolTipText = "Speichern";
            this.cmd_toolstrip_save.Click += new System.EventHandler(this.Cmd_toolstrip_saveClick);
            // 
            // cmd_toolstrip_saveAll
            // 
            this.cmd_toolstrip_saveAll.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_toolstrip_saveAll.Image = ((System.Drawing.Image)(resources.GetObject("cmd_toolstrip_saveAll.Image")));
            this.cmd_toolstrip_saveAll.Name = "cmd_toolstrip_saveAll";
            this.cmd_toolstrip_saveAll.Size = new System.Drawing.Size(23, 22);
            this.cmd_toolstrip_saveAll.ToolTipText = "Alle Speichern";
            this.cmd_toolstrip_saveAll.Click += new System.EventHandler(this.Cmd_toolstrip_saveAllClick);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // cmd_toolstrip_close
            // 
            this.cmd_toolstrip_close.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_toolstrip_close.Image = ((System.Drawing.Image)(resources.GetObject("cmd_toolstrip_close.Image")));
            this.cmd_toolstrip_close.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmd_toolstrip_close.Name = "cmd_toolstrip_close";
            this.cmd_toolstrip_close.Size = new System.Drawing.Size(23, 22);
            this.cmd_toolstrip_close.Text = "toolStripButton1";
            this.cmd_toolstrip_close.ToolTipText = "Schliessen";
            this.cmd_toolstrip_close.Click += new System.EventHandler(this.Cmd_toolstrip_closeClick);
            // 
            // cmd_toolstrip_open
            // 
            this.cmd_toolstrip_open.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_toolstrip_open.Image = ((System.Drawing.Image)(resources.GetObject("cmd_toolstrip_open.Image")));
            this.cmd_toolstrip_open.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmd_toolstrip_open.Name = "cmd_toolstrip_open";
            this.cmd_toolstrip_open.Size = new System.Drawing.Size(23, 22);
            this.cmd_toolstrip_open.Text = "toolStripButton2";
            this.cmd_toolstrip_open.ToolTipText = "Öffnen";
            this.cmd_toolstrip_open.Click += new System.EventHandler(this.Cmd_toolstrip_openClick);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            this.toolStripSeparator2.Visible = false;
            // 
            // cmd_toolstrip_redo
            // 
            this.cmd_toolstrip_redo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cmd_toolstrip_redo.Enabled = false;
            this.cmd_toolstrip_redo.Image = ((System.Drawing.Image)(resources.GetObject("cmd_toolstrip_redo.Image")));
            this.cmd_toolstrip_redo.Name = "cmd_toolstrip_redo";
            this.cmd_toolstrip_redo.Size = new System.Drawing.Size(23, 22);
            this.cmd_toolstrip_redo.ToolTipText = "Wiederherstellen";
            this.cmd_toolstrip_redo.Visible = false;
            // 
            // toolStripButton9
            // 
            this.toolStripButton9.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton9.Enabled = false;
            this.toolStripButton9.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton9.Image")));
            this.toolStripButton9.Name = "toolStripButton9";
            this.toolStripButton9.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton9.ToolTipText = "Rückgengig";
            this.toolStripButton9.Visible = false;
            // 
            // tc_spawns
            // 
            this.tc_spawns.Location = new System.Drawing.Point(3, 28);
            this.tc_spawns.Name = "tc_spawns";
            this.tc_spawns.SelectedIndex = 0;
            this.tc_spawns.Size = new System.Drawing.Size(486, 219);
            this.tc_spawns.TabIndex = 0;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.tabControl1);
            this.panel1.Location = new System.Drawing.Point(12, 8);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(508, 432);
            this.panel1.TabIndex = 1;
            // 
            // txt_Spawn_RespawnZeit
            // 
            this.txt_Spawn_RespawnZeit.Location = new System.Drawing.Point(97, 70);
            this.txt_Spawn_RespawnZeit.Name = "txt_Spawn_RespawnZeit";
            this.txt_Spawn_RespawnZeit.Size = new System.Drawing.Size(36, 20);
            this.txt_Spawn_RespawnZeit.TabIndex = 8;
            // 
            // txt_Spawn_MoverID
            // 
            this.txt_Spawn_MoverID.Location = new System.Drawing.Point(162, 43);
            this.txt_Spawn_MoverID.Name = "txt_Spawn_MoverID";
            this.txt_Spawn_MoverID.Size = new System.Drawing.Size(24, 20);
            this.txt_Spawn_MoverID.TabIndex = 3;
            this.txt_Spawn_MoverID.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txt_Spawn_MaxMobs
            // 
            this.txt_Spawn_MaxMobs.Location = new System.Drawing.Point(206, 75);
            this.txt_Spawn_MaxMobs.Name = "txt_Spawn_MaxMobs";
            this.txt_Spawn_MaxMobs.Size = new System.Drawing.Size(51, 20);
            this.txt_Spawn_MaxMobs.TabIndex = 26;
            // 
            // combo_Spawn_MoverIDs
            // 
            this.combo_Spawn_MoverIDs.FormattingEnabled = true;
            this.combo_Spawn_MoverIDs.Location = new System.Drawing.Point(8, 43);
            this.combo_Spawn_MoverIDs.Name = "combo_Spawn_MoverIDs";
            this.combo_Spawn_MoverIDs.Size = new System.Drawing.Size(148, 21);
            this.combo_Spawn_MoverIDs.TabIndex = 18;
            // 
            // textBox6
            // 
            this.textBox6.Location = new System.Drawing.Point(97, 71);
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(60, 20);
            this.textBox6.TabIndex = 22;
            // 
            // txt_Spawn_Gebiet
            // 
            this.txt_Spawn_Gebiet.Location = new System.Drawing.Point(88, 75);
            this.txt_Spawn_Gebiet.Name = "txt_Spawn_Gebiet";
            this.txt_Spawn_Gebiet.Size = new System.Drawing.Size(41, 20);
            this.txt_Spawn_Gebiet.TabIndex = 25;
            // 
            // txt_Spawn_World
            // 
            this.txt_Spawn_World.Location = new System.Drawing.Point(206, 49);
            this.txt_Spawn_World.Name = "txt_Spawn_World";
            this.txt_Spawn_World.Size = new System.Drawing.Size(52, 20);
            this.txt_Spawn_World.TabIndex = 23;
            // 
            // txt_Spawn_Z
            // 
            this.txt_Spawn_Z.Location = new System.Drawing.Point(206, 23);
            this.txt_Spawn_Z.Name = "txt_Spawn_Z";
            this.txt_Spawn_Z.Size = new System.Drawing.Size(52, 20);
            this.txt_Spawn_Z.TabIndex = 17;
            // 
            // txt_Spawn_Y
            // 
            this.txt_Spawn_Y.Location = new System.Drawing.Point(77, 49);
            this.txt_Spawn_Y.Name = "txt_Spawn_Y";
            this.txt_Spawn_Y.Size = new System.Drawing.Size(52, 20);
            this.txt_Spawn_Y.TabIndex = 16;
            // 
            // txt_Spawn_X
            // 
            this.txt_Spawn_X.Location = new System.Drawing.Point(77, 23);
            this.txt_Spawn_X.Name = "txt_Spawn_X";
            this.txt_Spawn_X.Size = new System.Drawing.Size(52, 20);
            this.txt_Spawn_X.TabIndex = 15;
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(97, 45);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(60, 20);
            this.textBox5.TabIndex = 20;
            // 
            // txt_Spawn_AggroChance
            // 
            this.txt_Spawn_AggroChance.Location = new System.Drawing.Point(97, 19);
            this.txt_Spawn_AggroChance.Name = "txt_Spawn_AggroChance";
            this.txt_Spawn_AggroChance.Size = new System.Drawing.Size(60, 20);
            this.txt_Spawn_AggroChance.TabIndex = 18;
            // 
            // MainForm
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(529, 433);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Use   -   Ultime Black Orion   -   2011";
            this.Load += new System.EventHandler(this.MainFormLoad);
            this.tab_Infos.ResumeLayout(false);
            this.tabCont_Allgemein.ResumeLayout(false);
            this.tab_format_Spawn.ResumeLayout(false);
            this.tab_format_Spawn.PerformLayout();
            this.tab_format_Drop.ResumeLayout(false);
            this.tab_format_Drop.PerformLayout();
            this.tab_format_NPC.ResumeLayout(false);
            this.tab_format_NPC.PerformLayout();
            this.tab_MoverList.ResumeLayout(false);
            this.tab_MoverList.PerformLayout();
            this.tab_ItemList.ResumeLayout(false);
            this.tab_ItemList.PerformLayout();
            this.tab_einstell.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.group_datei.ResumeLayout(false);
            this.tab_Usedb.ResumeLayout(false);
            this.tab_NPC.ResumeLayout(false);
            this.tab_NPC.PerformLayout();
            this.toolStrip2.ResumeLayout(false);
            this.toolStrip2.PerformLayout();
            this.tab_Drop.ResumeLayout(false);
            this.tab_Drop.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.tab_Browser.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tab_Spawn.ResumeLayout(false);
            this.tab_Spawn.PerformLayout();
            this.toolStrip.ResumeLayout(false);
            this.toolStrip.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);

		}
		private System.Windows.Forms.ToolStripButton cmd_NPC_new;
		private System.Windows.Forms.ToolStripButton cmd_NPC_save;
		private System.Windows.Forms.ToolStripButton cmd_NPC_saveAll;
		private System.Windows.Forms.ToolStripButton cmd_npc_close;
		private System.Windows.Forms.ToolStripButton cmd_npc_open;
		private System.Windows.Forms.ToolStripButton toolStripButton_drop_save;
		private System.Windows.Forms.ToolStripButton toolStripButton15;
		private System.Windows.Forms.ToolStripButton toolStripButton14;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator9;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator8;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator7;
		private System.Windows.Forms.ToolStrip toolStrip2;
		public System.Windows.Forms.TabControl tc_NPCs;
		private System.Windows.Forms.ToolStripButton toolStripButton9;
		public System.Windows.Forms.TabControl tc_drops;
		private System.Windows.Forms.ToolStripButton toolStripButton7;
		private System.Windows.Forms.ToolStripButton toolStripButton6;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
		private System.Windows.Forms.ToolStripButton toolStripButton5;
		private System.Windows.Forms.ToolStripButton toolStripButton4;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
		private System.Windows.Forms.ToolStripButton toolStripButton3;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
		private System.Windows.Forms.ToolStripButton toolStripButton1;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStrip toolStrip;
		private System.Windows.Forms.ToolStripButton cmd_toolstrip_open;
		private System.Windows.Forms.ToolStripButton cmd_toolstrip_close;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
		private System.Windows.Forms.ToolStripButton cmd_toolstrip_redo;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripButton cmd_toolstrip_saveAll;
		private System.Windows.Forms.ToolStripButton cmd_toolstrip_save;
		private System.Windows.Forms.ToolStripButton cmd_toolstrip_newFile;
		private System.Windows.Forms.TextBox txt_Spawn_AggroChance;
		private System.Windows.Forms.TextBox textBox5;
		private System.Windows.Forms.TextBox txt_Spawn_X;
		private System.Windows.Forms.TextBox txt_Spawn_Y;
		private System.Windows.Forms.TextBox txt_Spawn_Z;
		private System.Windows.Forms.TextBox txt_Spawn_World;
		private System.Windows.Forms.TextBox txt_Spawn_Gebiet;
		private System.Windows.Forms.TextBox textBox6;
		private System.Windows.Forms.ComboBox combo_Spawn_MoverIDs;
		private System.Windows.Forms.TextBox txt_Spawn_MaxMobs;
		private System.Windows.Forms.TextBox txt_Spawn_MoverID;
		private System.Windows.Forms.TextBox txt_Spawn_RespawnZeit;
		public System.Windows.Forms.TabControl tc_spawns;
		private System.Windows.Forms.Button cmd_about;
		private System.Windows.Forms.Button cmd_erweiter_uebernemen;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.TextBox textBox4;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.CheckBox check_drop;
		private System.Windows.Forms.CheckBox check_npc;
		private System.Windows.Forms.CheckBox check_udb;
		private System.Windows.Forms.CheckBox check_Spawn;
		private System.Windows.Forms.GroupBox group_datei;
		private System.Windows.Forms.Button cmd_opt;
		private System.Windows.Forms.TabPage tab_einstell;
		private System.Windows.Forms.ColumnHeader colum_InternName;
		private System.Windows.Forms.ColumnHeader colum_NameAnzeige;
		private System.Windows.Forms.ColumnHeader colum_ItemID;
		private System.Windows.Forms.ListView lv_mover_suche_ergebniss;
		private System.Windows.Forms.ListView lv_Items;
		private System.Windows.Forms.ColumnHeader colum_NameIntern;
		private System.Windows.Forms.ColumnHeader colum_AnzeigeName;
		private System.Windows.Forms.ColumnHeader colum_ID;
		private System.Windows.Forms.TextBox txt_mover_suche_eingabe;
		private System.Windows.Forms.TextBox txt_item_ID;
		private System.Windows.Forms.ComboBox combo_item_Name_Anzeige;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.ListBox list_items;
		private System.Windows.Forms.TextBox txt_item_suche_eingabe;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Button txt_item_suche_hide;
		private System.Windows.Forms.ComboBox combo_item_Name_Intern;
		private System.Windows.Forms.ListBox list_mover_suche_ergebiss;
		private System.Windows.Forms.TabPage tab_format_Spawn;
		private System.Windows.Forms.TabPage tab_format_Drop;
		private System.Windows.Forms.TabPage tab_format_NPC;
		private System.Windows.Forms.TabPage tab_MoverList;
		private System.Windows.Forms.TabPage tab_ItemList;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Button cmd_mover_suche_hide;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.ListBox list_MoverIDs;
		private System.Windows.Forms.ComboBox Combo_Mover_MoverIDs;
		private System.Windows.Forms.TextBox Txt_Mover_MoverID;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TabControl tabCont_Allgemein;
		private System.Windows.Forms.TextBox textBox3;
		private System.Windows.Forms.TextBox textBox2;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.TabPage tab_Infos;
		private System.Windows.Forms.Button cmd_udb_pack;
		private System.Windows.Forms.Button cmd_udb_depack;
		private System.Windows.Forms.SaveFileDialog saveFileDialog;
		private System.Windows.Forms.TabPage tab_Usedb;
		private System.Windows.Forms.Label label21;
		private System.Windows.Forms.ListBox listBox1;
		private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
		private System.Windows.Forms.OpenFileDialog openFileDialog;
		private System.Windows.Forms.TabPage tab_NPC;
		private System.Windows.Forms.TabPage tab_Drop;
		private System.Windows.Forms.TabPage tab_Spawn;
		private System.Windows.Forms.TabPage tab_Browser;
		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.ListView list_Datas;
		private System.Windows.Forms.Button cmd_LoadSpawns;
		private System.Windows.Forms.Button cmd_LoadDrops;
		private System.Windows.Forms.Button cmd_LoadNPCs;
	}
}
