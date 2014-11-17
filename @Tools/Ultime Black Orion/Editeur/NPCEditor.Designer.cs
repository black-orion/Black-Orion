
namespace UBO.Editoren.NPC
{
	partial class NPC
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
			System.Windows.Forms.Label lbl_rotation;
			System.Windows.Forms.Label lbl_size;
			System.Windows.Forms.Label label4;
			System.Windows.Forms.Label label10;
			System.Windows.Forms.Label label11;
			System.Windows.Forms.Label label12;
			this.group_npcDaten = new System.Windows.Forms.GroupBox();
			this.txt_id = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.txt_name = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.groupData = new System.Windows.Forms.GroupBox();
			this.txt_rotation = new System.Windows.Forms.NumericUpDown();
			this.txt_World = new System.Windows.Forms.NumericUpDown();
			this.txt_size = new System.Windows.Forms.NumericUpDown();
			this.txt_Z = new System.Windows.Forms.NumericUpDown();
			this.txt_Y = new System.Windows.Forms.NumericUpDown();
			this.txt_X = new System.Windows.Forms.NumericUpDown();
			this.tc_slots = new System.Windows.Forms.TabControl();
			this.group_items = new System.Windows.Forms.GroupBox();
			this.cmd_ItemAdd = new System.Windows.Forms.Button();
			this.cmd_ItemRm = new System.Windows.Forms.Button();
			this.txt_newItemID = new System.Windows.Forms.TextBox();
			this.combo_newItemName = new System.Windows.Forms.ComboBox();
			this.group_text = new System.Windows.Forms.GroupBox();
			this.cmd_TextAdd = new System.Windows.Forms.Button();
			this.cmd_TextRm = new System.Windows.Forms.Button();
			this.lv_texte = new System.Windows.Forms.ListView();
			this.column_text = new System.Windows.Forms.ColumnHeader();
			this.column_inverval = new System.Windows.Forms.ColumnHeader();
			this.cmd_TextChange = new System.Windows.Forms.Button();
			lbl_rotation = new System.Windows.Forms.Label();
			lbl_size = new System.Windows.Forms.Label();
			label4 = new System.Windows.Forms.Label();
			label10 = new System.Windows.Forms.Label();
			label11 = new System.Windows.Forms.Label();
			label12 = new System.Windows.Forms.Label();
			this.group_npcDaten.SuspendLayout();
			this.groupData.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.txt_rotation)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_World)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_size)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Z)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Y)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_X)).BeginInit();
			this.group_items.SuspendLayout();
			this.group_text.SuspendLayout();
			this.SuspendLayout();
			// 
			// lbl_rotation
			// 
			lbl_rotation.Location = new System.Drawing.Point(137, 75);
			lbl_rotation.Name = "lbl_rotation";
			lbl_rotation.Size = new System.Drawing.Size(65, 20);
			lbl_rotation.TabIndex = 54;
			lbl_rotation.Text = "Rotation";
			// 
			// lbl_size
			// 
			lbl_size.Location = new System.Drawing.Point(136, 23);
			lbl_size.Name = "lbl_size";
			lbl_size.Size = new System.Drawing.Size(66, 20);
			lbl_size.TabIndex = 27;
			lbl_size.Text = "Taille";
			// 
			// label4
			// 
			label4.Location = new System.Drawing.Point(137, 49);
			label4.Name = "label4";
			label4.Size = new System.Drawing.Size(65, 20);
			label4.TabIndex = 22;
			label4.Text = "World ID";
			// 
			// label10
			// 
			label10.Location = new System.Drawing.Point(8, 75);
			label10.Name = "label10";
			label10.Size = new System.Drawing.Size(65, 20);
			label10.TabIndex = 20;
			label10.Text = "Positon Z";
			// 
			// label11
			// 
			label11.Location = new System.Drawing.Point(8, 49);
			label11.Name = "label11";
			label11.Size = new System.Drawing.Size(65, 20);
			label11.TabIndex = 19;
			label11.Text = "Positon Y";
			// 
			// label12
			// 
			label12.Location = new System.Drawing.Point(8, 23);
			label12.Name = "label12";
			label12.Size = new System.Drawing.Size(65, 20);
			label12.TabIndex = 18;
			label12.Text = "Positon X";
			// 
			// group_npcDaten
			// 
			this.group_npcDaten.Controls.Add(this.txt_id);
			this.group_npcDaten.Controls.Add(this.label2);
			this.group_npcDaten.Controls.Add(this.txt_name);
			this.group_npcDaten.Controls.Add(this.label1);
			this.group_npcDaten.Location = new System.Drawing.Point(5, 109);
			this.group_npcDaten.Name = "group_npcDaten";
			this.group_npcDaten.Size = new System.Drawing.Size(268, 47);
			this.group_npcDaten.TabIndex = 53;
			this.group_npcDaten.TabStop = false;
			this.group_npcDaten.Text = "NPC Data";
			// 
			// txt_id
			// 
			this.txt_id.Location = new System.Drawing.Point(199, 17);
			this.txt_id.Name = "txt_id";
			this.txt_id.Size = new System.Drawing.Size(61, 20);
			this.txt_id.TabIndex = 5;
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(148, 20);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(54, 17);
			this.label2.TabIndex = 4;
			this.label2.Text = "NPC ID :";
			// 
			// txt_name
			// 
			this.txt_name.Location = new System.Drawing.Point(49, 17);
			this.txt_name.Name = "txt_name";
			this.txt_name.Size = new System.Drawing.Size(93, 20);
			this.txt_name.TabIndex = 3;
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(6, 20);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(44, 17);
			this.label1.TabIndex = 2;
			this.label1.Text = "Nom :";
			// 
			// groupData
			// 
			this.groupData.Controls.Add(this.txt_rotation);
			this.groupData.Controls.Add(lbl_rotation);
			this.groupData.Controls.Add(this.txt_World);
			this.groupData.Controls.Add(this.txt_size);
			this.groupData.Controls.Add(this.txt_Z);
			this.groupData.Controls.Add(this.txt_Y);
			this.groupData.Controls.Add(this.txt_X);
			this.groupData.Controls.Add(lbl_size);
			this.groupData.Controls.Add(label4);
			this.groupData.Controls.Add(label10);
			this.groupData.Controls.Add(label11);
			this.groupData.Controls.Add(label12);
			this.groupData.Location = new System.Drawing.Point(5, 3);
			this.groupData.Name = "groupData";
			this.groupData.Size = new System.Drawing.Size(268, 100);
			this.groupData.TabIndex = 52;
			this.groupData.TabStop = false;
			this.groupData.Text = "Position en jeu";
			// 
			// txt_rotation
			// 
			this.txt_rotation.Increment = new decimal(new int[] {
									100,
									0,
									0,
									0});
			this.txt_rotation.Location = new System.Drawing.Point(208, 73);
			this.txt_rotation.Maximum = new decimal(new int[] {
									3600,
									0,
									0,
									0});
			this.txt_rotation.Name = "txt_rotation";
			this.txt_rotation.Size = new System.Drawing.Size(52, 20);
			this.txt_rotation.TabIndex = 55;
			// 
			// txt_World
			// 
			this.txt_World.Location = new System.Drawing.Point(208, 47);
			this.txt_World.Maximum = new decimal(new int[] {
									10,
									0,
									0,
									0});
			this.txt_World.Name = "txt_World";
			this.txt_World.Size = new System.Drawing.Size(52, 20);
			this.txt_World.TabIndex = 50;
			// 
			// txt_size
			// 
			this.txt_size.Increment = new decimal(new int[] {
									50,
									0,
									0,
									0});
			this.txt_size.Location = new System.Drawing.Point(208, 21);
			this.txt_size.Maximum = new decimal(new int[] {
									1000,
									0,
									0,
									0});
			this.txt_size.Minimum = new decimal(new int[] {
									1,
									0,
									0,
									0});
			this.txt_size.Name = "txt_size";
			this.txt_size.Size = new System.Drawing.Size(52, 20);
			this.txt_size.TabIndex = 49;
			this.txt_size.Value = new decimal(new int[] {
									1,
									0,
									0,
									0});
			// 
			// txt_Z
			// 
			this.txt_Z.DecimalPlaces = 1;
			this.txt_Z.Increment = new decimal(new int[] {
									10,
									0,
									0,
									0});
			this.txt_Z.Location = new System.Drawing.Point(79, 73);
			this.txt_Z.Maximum = new decimal(new int[] {
									10000,
									0,
									0,
									0});
			this.txt_Z.Name = "txt_Z";
			this.txt_Z.Size = new System.Drawing.Size(52, 20);
			this.txt_Z.TabIndex = 48;
			// 
			// txt_Y
			// 
			this.txt_Y.DecimalPlaces = 1;
			this.txt_Y.Increment = new decimal(new int[] {
									10,
									0,
									0,
									0});
			this.txt_Y.Location = new System.Drawing.Point(79, 47);
			this.txt_Y.Maximum = new decimal(new int[] {
									10000,
									0,
									0,
									0});
			this.txt_Y.Name = "txt_Y";
			this.txt_Y.Size = new System.Drawing.Size(52, 20);
			this.txt_Y.TabIndex = 47;
			// 
			// txt_X
			// 
			this.txt_X.DecimalPlaces = 1;
			this.txt_X.Increment = new decimal(new int[] {
									10,
									0,
									0,
									0});
			this.txt_X.Location = new System.Drawing.Point(79, 21);
			this.txt_X.Maximum = new decimal(new int[] {
									10000,
									0,
									0,
									0});
			this.txt_X.Name = "txt_X";
			this.txt_X.Size = new System.Drawing.Size(52, 20);
			this.txt_X.TabIndex = 46;
			// 
			// tc_slots
			// 
			this.tc_slots.Location = new System.Drawing.Point(279, 3);
			this.tc_slots.Name = "tc_slots";
			this.tc_slots.SelectedIndex = 0;
			this.tc_slots.Size = new System.Drawing.Size(198, 328);
			this.tc_slots.TabIndex = 51;
			// 
			// group_items
			// 
			this.group_items.Controls.Add(this.cmd_ItemAdd);
			this.group_items.Controls.Add(this.cmd_ItemRm);
			this.group_items.Controls.Add(this.txt_newItemID);
			this.group_items.Controls.Add(this.combo_newItemName);
			this.group_items.Location = new System.Drawing.Point(38, 252);
			this.group_items.Name = "group_items";
			this.group_items.Size = new System.Drawing.Size(207, 79);
			this.group_items.TabIndex = 54;
			this.group_items.TabStop = false;
			this.group_items.Text = "Items";
			// 
			// cmd_ItemAdd
			// 
			this.cmd_ItemAdd.Location = new System.Drawing.Point(6, 19);
			this.cmd_ItemAdd.Name = "cmd_ItemAdd";
			this.cmd_ItemAdd.Size = new System.Drawing.Size(92, 23);
			this.cmd_ItemAdd.TabIndex = 6;
			this.cmd_ItemAdd.Text = "Ajouter";
			this.cmd_ItemAdd.UseVisualStyleBackColor = true;
			this.cmd_ItemAdd.Click += new System.EventHandler(this.Cmd_ItemAddClick);
			// 
			// cmd_ItemRm
			// 
			this.cmd_ItemRm.Location = new System.Drawing.Point(109, 19);
			this.cmd_ItemRm.Name = "cmd_ItemRm";
			this.cmd_ItemRm.Size = new System.Drawing.Size(92, 23);
			this.cmd_ItemRm.TabIndex = 7;
			this.cmd_ItemRm.Text = "Supprimer";
			this.cmd_ItemRm.UseVisualStyleBackColor = true;
			this.cmd_ItemRm.Click += new System.EventHandler(this.Cmd_ItemRmClick);
			// 
			// txt_newItemID
			// 
			this.txt_newItemID.Location = new System.Drawing.Point(128, 51);
			this.txt_newItemID.Name = "txt_newItemID";
			this.txt_newItemID.Size = new System.Drawing.Size(72, 20);
			this.txt_newItemID.TabIndex = 9;
			this.txt_newItemID.TextChanged += new System.EventHandler(this.Txt_newItemIDTextChanged);
			// 
			// combo_newItemName
			// 
			this.combo_newItemName.FormattingEnabled = true;
			this.combo_newItemName.Location = new System.Drawing.Point(6, 50);
			this.combo_newItemName.Name = "combo_newItemName";
			this.combo_newItemName.Size = new System.Drawing.Size(116, 21);
			this.combo_newItemName.TabIndex = 10;
			this.combo_newItemName.SelectedIndexChanged += new System.EventHandler(this.Combo_newItemNameSelectedIndexChanged);
			// 
			// group_text
			// 
			this.group_text.Controls.Add(this.cmd_TextChange);
			this.group_text.Controls.Add(this.cmd_TextAdd);
			this.group_text.Controls.Add(this.cmd_TextRm);
			this.group_text.Controls.Add(this.lv_texte);
			this.group_text.Location = new System.Drawing.Point(5, 162);
			this.group_text.Name = "group_text";
			this.group_text.Size = new System.Drawing.Size(268, 88);
			this.group_text.TabIndex = 55;
			this.group_text.TabStop = false;
			this.group_text.Text = "Texte dans la bulle";
			// 
			// cmd_TextAdd
			// 
			this.cmd_TextAdd.Location = new System.Drawing.Point(195, 13);
			this.cmd_TextAdd.Name = "cmd_TextAdd";
			this.cmd_TextAdd.Size = new System.Drawing.Size(67, 23);
			this.cmd_TextAdd.TabIndex = 8;
			this.cmd_TextAdd.Text = "Ajouter";
			this.cmd_TextAdd.UseVisualStyleBackColor = true;
			this.cmd_TextAdd.Click += new System.EventHandler(this.Cmd_TextAddClick);
			// 
			// cmd_TextRm
			// 
			this.cmd_TextRm.Location = new System.Drawing.Point(195, 37);
			this.cmd_TextRm.Name = "cmd_TextRm";
			this.cmd_TextRm.Size = new System.Drawing.Size(67, 23);
			this.cmd_TextRm.TabIndex = 9;
			this.cmd_TextRm.Text = "Supprimer";
			this.cmd_TextRm.UseVisualStyleBackColor = true;
			this.cmd_TextRm.Click += new System.EventHandler(this.Cmd_TextRmClick);
			// 
			// lv_texte
			// 
			this.lv_texte.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.column_text,
									this.column_inverval});
			this.lv_texte.Location = new System.Drawing.Point(6, 13);
			this.lv_texte.Name = "lv_texte";
			this.lv_texte.Size = new System.Drawing.Size(182, 67);
			this.lv_texte.TabIndex = 1;
			this.lv_texte.UseCompatibleStateImageBehavior = false;
			this.lv_texte.View = System.Windows.Forms.View.Details;
			// 
			// column_text
			// 
			this.column_text.Text = "Texte";
			this.column_text.Width = 138;
			// 
			// column_inverval
			// 
			this.column_inverval.Text = "Temps";
			this.column_inverval.Width = 40;
			// 
			// cmd_TextChange
			// 
			this.cmd_TextChange.Location = new System.Drawing.Point(195, 62);
			this.cmd_TextChange.Name = "cmd_TextChange";
			this.cmd_TextChange.Size = new System.Drawing.Size(67, 23);
			this.cmd_TextChange.TabIndex = 10;
			this.cmd_TextChange.Text = "Retour";
			this.cmd_TextChange.UseVisualStyleBackColor = true;
			this.cmd_TextChange.Click += new System.EventHandler(this.Cmd_TextChangeClick);
			// 
			// NPCForm
			// 
			this.Controls.Add(this.group_npcDaten);
			this.Controls.Add(this.groupData);
			this.Controls.Add(this.tc_slots);
			this.Controls.Add(this.group_items);
			this.Controls.Add(this.group_text);
			this.group_npcDaten.ResumeLayout(false);
			this.group_npcDaten.PerformLayout();
			this.groupData.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.txt_rotation)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_World)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_size)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Z)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Y)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_X)).EndInit();
			this.group_items.ResumeLayout(false);
			this.group_items.PerformLayout();
			this.group_text.ResumeLayout(false);
			this.ResumeLayout(false);
		}
		private System.Windows.Forms.Button cmd_TextChange;
		private System.Windows.Forms.Button cmd_TextAdd;
		private System.Windows.Forms.Button cmd_TextRm;
		private System.Windows.Forms.Button cmd_ItemRm;
		private System.Windows.Forms.Button cmd_ItemAdd;
		private System.Windows.Forms.ListView lv_texte;
		private System.Windows.Forms.NumericUpDown txt_rotation;
		private System.Windows.Forms.NumericUpDown txt_size;
		private System.Windows.Forms.GroupBox group_npcDaten;
		private System.Windows.Forms.TextBox txt_id;
		private System.Windows.Forms.TextBox txt_name;
		private System.Windows.Forms.TabControl tc_slots;
		private System.Windows.Forms.ColumnHeader column_inverval;
		private System.Windows.Forms.ColumnHeader column_text;
		private System.Windows.Forms.GroupBox group_text;
		private System.Windows.Forms.GroupBox group_items;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.NumericUpDown txt_X;
		private System.Windows.Forms.NumericUpDown txt_Y;
		private System.Windows.Forms.NumericUpDown txt_Z;
		private System.Windows.Forms.NumericUpDown txt_World;
		private System.Windows.Forms.GroupBox groupData;
		private System.Windows.Forms.ComboBox combo_newItemName;
		private System.Windows.Forms.TextBox txt_newItemID;
		
	}
}
