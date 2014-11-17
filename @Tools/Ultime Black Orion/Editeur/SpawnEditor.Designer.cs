
namespace UBO.Editoren.Spawn
{
	partial class Spawn
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
			System.Windows.Forms.Label label9;
			System.Windows.Forms.Label label8;
			System.Windows.Forms.Label lbl_AggroChance;
			System.Windows.Forms.Label lbl_RespawnZeit;
			System.Windows.Forms.Label lbl_Gebiet;
			System.Windows.Forms.Label lbl_World;
			System.Windows.Forms.Label lbl_Z;
			System.Windows.Forms.Label lbl_Y;
			System.Windows.Forms.Label lbl_X;
			System.Windows.Forms.Label lbl1;
			System.Windows.Forms.Label lbl2;
			System.Windows.Forms.Label lbl3;
			System.Windows.Forms.Label lbl_MaxMobs;
			System.Windows.Forms.Label label1;
			System.Windows.Forms.Label label2;
			this.group_angriff = new System.Windows.Forms.GroupBox();
			this.txt_AggroChance = new System.Windows.Forms.NumericUpDown();
			this.textBox6 = new System.Windows.Forms.TextBox();
			this.textBox5 = new System.Windows.Forms.TextBox();
			this.group_MoverData = new System.Windows.Forms.GroupBox();
			this.cb_move = new System.Windows.Forms.CheckBox();
			this.txt_RespawnZeit = new System.Windows.Forms.TextBox();
			this.groupData = new System.Windows.Forms.GroupBox();
			this.txt_MaxMobs = new System.Windows.Forms.NumericUpDown();
			this.txt_World = new System.Windows.Forms.NumericUpDown();
			this.txt_Gebiet = new System.Windows.Forms.NumericUpDown();
			this.txt_Z = new System.Windows.Forms.NumericUpDown();
			this.txt_Y = new System.Windows.Forms.NumericUpDown();
			this.txt_X = new System.Windows.Forms.NumericUpDown();
			this.group_multi = new System.Windows.Forms.GroupBox();
			this.txt_drop = new System.Windows.Forms.NumericUpDown();
			this.txt_exp = new System.Windows.Forms.NumericUpDown();
			this.txt_penya = new System.Windows.Forms.NumericUpDown();
			this.txt_MovingInterval = new System.Windows.Forms.TextBox();
			this.txt_size = new System.Windows.Forms.NumericUpDown();
			this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
			this.lv_movers = new System.Windows.Forms.ListView();
			label9 = new System.Windows.Forms.Label();
			label8 = new System.Windows.Forms.Label();
			lbl_AggroChance = new System.Windows.Forms.Label();
			lbl_RespawnZeit = new System.Windows.Forms.Label();
			lbl_Gebiet = new System.Windows.Forms.Label();
			lbl_World = new System.Windows.Forms.Label();
			lbl_Z = new System.Windows.Forms.Label();
			lbl_Y = new System.Windows.Forms.Label();
			lbl_X = new System.Windows.Forms.Label();
			lbl1 = new System.Windows.Forms.Label();
			lbl2 = new System.Windows.Forms.Label();
			lbl3 = new System.Windows.Forms.Label();
			lbl_MaxMobs = new System.Windows.Forms.Label();
			label1 = new System.Windows.Forms.Label();
			label2 = new System.Windows.Forms.Label();
			this.group_angriff.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.txt_AggroChance)).BeginInit();
			this.group_MoverData.SuspendLayout();
			this.groupData.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.txt_MaxMobs)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_World)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Gebiet)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Z)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Y)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_X)).BeginInit();
			this.group_multi.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.txt_drop)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_exp)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_penya)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_size)).BeginInit();
			this.SuspendLayout();
			// 
			// label9
			// 
			label9.Enabled = false;
			label9.Location = new System.Drawing.Point(11, 71);
			label9.Name = "label9";
			label9.Size = new System.Drawing.Size(81, 20);
			label9.TabIndex = 23;
			label9.Text = "Radius Max";
			// 
			// label8
			// 
			label8.Enabled = false;
			label8.Location = new System.Drawing.Point(11, 45);
			label8.Name = "label8";
			label8.Size = new System.Drawing.Size(81, 20);
			label8.TabIndex = 21;
			label8.Text = "Radius Min";
			// 
			// lbl_AggroChance
			// 
			lbl_AggroChance.Location = new System.Drawing.Point(11, 19);
			lbl_AggroChance.Name = "lbl_AggroChance";
			lbl_AggroChance.Size = new System.Drawing.Size(81, 20);
			lbl_AggroChance.TabIndex = 19;
			lbl_AggroChance.Text = "Aggro";
			// 
			// lbl_RespawnZeit
			// 
			lbl_RespawnZeit.Location = new System.Drawing.Point(257, 164);
			lbl_RespawnZeit.Name = "lbl_RespawnZeit";
			lbl_RespawnZeit.Size = new System.Drawing.Size(81, 20);
			lbl_RespawnZeit.TabIndex = 17;
			lbl_RespawnZeit.Text = "Temps Respawn :";
			// 
			// lbl_Gebiet
			// 
			lbl_Gebiet.Location = new System.Drawing.Point(136, 23);
			lbl_Gebiet.Name = "lbl_Gebiet";
			lbl_Gebiet.Size = new System.Drawing.Size(66, 20);
			lbl_Gebiet.TabIndex = 27;
			lbl_Gebiet.Text = "Radius";
			// 
			// lbl_World
			// 
			lbl_World.Location = new System.Drawing.Point(137, 49);
			lbl_World.Name = "lbl_World";
			lbl_World.Size = new System.Drawing.Size(65, 20);
			lbl_World.TabIndex = 22;
			lbl_World.Text = "World ID";
			// 
			// lbl_Z
			// 
			lbl_Z.Location = new System.Drawing.Point(8, 75);
			lbl_Z.Name = "lbl_Z";
			lbl_Z.Size = new System.Drawing.Size(65, 20);
			lbl_Z.TabIndex = 20;
			lbl_Z.Text = "Positon Z";
			// 
			// lbl_Y
			// 
			lbl_Y.Location = new System.Drawing.Point(8, 49);
			lbl_Y.Name = "lbl_Y";
			lbl_Y.Size = new System.Drawing.Size(65, 20);
			lbl_Y.TabIndex = 19;
			lbl_Y.Text = "Positon Y";
			// 
			// lbl_X
			// 
			lbl_X.Location = new System.Drawing.Point(8, 23);
			lbl_X.Name = "lbl_X";
			lbl_X.Size = new System.Drawing.Size(65, 20);
			lbl_X.TabIndex = 18;
			lbl_X.Text = "Positon X";
			// 
			// lbl1
			// 
			lbl1.Location = new System.Drawing.Point(10, 20);
			lbl1.Name = "lbl1";
			lbl1.Size = new System.Drawing.Size(43, 17);
			lbl1.TabIndex = 4;
			lbl1.Text = "Penyas :";
			// 
			// lbl2
			// 
			lbl2.Location = new System.Drawing.Point(95, 19);
			lbl2.Name = "lbl2";
			lbl2.Size = new System.Drawing.Size(34, 17);
			lbl2.TabIndex = 2;
			lbl2.Text = "Drops :";
			// 
			// lbl3
			// 
			lbl3.Location = new System.Drawing.Point(182, 18);
			lbl3.Name = "lbl3";
			lbl3.Size = new System.Drawing.Size(34, 17);
			lbl3.TabIndex = 0;
			lbl3.Text = "EXP :";
			// 
			// lbl_MaxMobs
			// 
			lbl_MaxMobs.Location = new System.Drawing.Point(137, 75);
			lbl_MaxMobs.Name = "lbl_MaxMobs";
			lbl_MaxMobs.Size = new System.Drawing.Size(65, 20);
			lbl_MaxMobs.TabIndex = 54;
			lbl_MaxMobs.Text = "Monstres";
			// 
			// label1
			// 
			label1.Location = new System.Drawing.Point(132, 164);
			label1.Name = "label1";
			label1.Size = new System.Drawing.Size(87, 20);
			label1.TabIndex = 46;
			label1.Text = "Temps de mouvements :";
			// 
			// label2
			// 
			label2.Location = new System.Drawing.Point(11, 75);
			label2.Name = "label2";
			label2.Size = new System.Drawing.Size(36, 17);
			label2.TabIndex = 55;
			label2.Text = "Size:";
			// 
			// group_angriff
			// 
			this.group_angriff.Controls.Add(this.txt_AggroChance);
			this.group_angriff.Controls.Add(this.textBox6);
			this.group_angriff.Controls.Add(label9);
			this.group_angriff.Controls.Add(this.textBox5);
			this.group_angriff.Controls.Add(label8);
			this.group_angriff.Controls.Add(lbl_AggroChance);
			this.group_angriff.Location = new System.Drawing.Point(21, 117);
			this.group_angriff.Name = "group_angriff";
			this.group_angriff.Size = new System.Drawing.Size(159, 40);
			this.group_angriff.TabIndex = 43;
			this.group_angriff.TabStop = false;
			this.group_angriff.Text = "Aggro";
			// 
			// txt_AggroChance
			// 
			this.txt_AggroChance.DecimalPlaces = 2;
			this.txt_AggroChance.Increment = new decimal(new int[] {
									1,
									0,
									0,
									131072});
			this.txt_AggroChance.Location = new System.Drawing.Point(95, 16);
			this.txt_AggroChance.Maximum = new decimal(new int[] {
									1,
									0,
									0,
									0});
			this.txt_AggroChance.Name = "txt_AggroChance";
			this.txt_AggroChance.Size = new System.Drawing.Size(60, 20);
			this.txt_AggroChance.TabIndex = 53;
			// 
			// textBox6
			// 
			this.textBox6.Enabled = false;
			this.textBox6.Location = new System.Drawing.Point(99, 71);
			this.textBox6.Name = "textBox6";
			this.textBox6.Size = new System.Drawing.Size(60, 20);
			this.textBox6.TabIndex = 22;
			// 
			// textBox5
			// 
			this.textBox5.Enabled = false;
			this.textBox5.Location = new System.Drawing.Point(99, 45);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new System.Drawing.Size(60, 20);
			this.textBox5.TabIndex = 20;
			// 
			// group_MoverData
			// 
			this.group_MoverData.Controls.Add(this.txt_size);
			this.group_MoverData.Controls.Add(label2);
			this.group_MoverData.Controls.Add(this.cb_move);
			this.group_MoverData.Controls.Add(this.lv_movers);
			this.group_MoverData.Location = new System.Drawing.Point(289, 12);
			this.group_MoverData.Name = "group_MoverData";
			this.group_MoverData.Size = new System.Drawing.Size(182, 100);
			this.group_MoverData.TabIndex = 40;
			this.group_MoverData.TabStop = false;
			this.group_MoverData.Text = "Mobs";
			// 
			// cb_move
			// 
			this.cb_move.Location = new System.Drawing.Point(123, 75);
			this.cb_move.Name = "cb_move";
			this.cb_move.Size = new System.Drawing.Size(53, 20);
			this.cb_move.TabIndex = 19;
			this.cb_move.Text = "Mouvement";
			this.cb_move.UseVisualStyleBackColor = true;
			// 
			// txt_RespawnZeit
			// 
			this.txt_RespawnZeit.Location = new System.Drawing.Point(334, 164);
			this.txt_RespawnZeit.Name = "txt_RespawnZeit";
			this.txt_RespawnZeit.Size = new System.Drawing.Size(36, 20);
			this.txt_RespawnZeit.TabIndex = 8;
			// 
			// groupData
			// 
			this.groupData.Controls.Add(this.txt_MaxMobs);
			this.groupData.Controls.Add(lbl_MaxMobs);
			this.groupData.Controls.Add(this.txt_World);
			this.groupData.Controls.Add(this.txt_Gebiet);
			this.groupData.Controls.Add(this.txt_Z);
			this.groupData.Controls.Add(this.txt_Y);
			this.groupData.Controls.Add(this.txt_X);
			this.groupData.Controls.Add(lbl_Gebiet);
			this.groupData.Controls.Add(lbl_World);
			this.groupData.Controls.Add(lbl_Z);
			this.groupData.Controls.Add(lbl_Y);
			this.groupData.Controls.Add(lbl_X);
			this.groupData.Location = new System.Drawing.Point(5, 12);
			this.groupData.Name = "groupData";
			this.groupData.Size = new System.Drawing.Size(268, 100);
			this.groupData.TabIndex = 41;
			this.groupData.TabStop = false;
			this.groupData.Text = "Position en jeu";
			// 
			// txt_MaxMobs
			// 
			this.txt_MaxMobs.Location = new System.Drawing.Point(208, 73);
			this.txt_MaxMobs.Name = "txt_MaxMobs";
			this.txt_MaxMobs.Size = new System.Drawing.Size(52, 20);
			this.txt_MaxMobs.TabIndex = 55;
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
			// txt_Gebiet
			// 
			this.txt_Gebiet.DecimalPlaces = 2;
			this.txt_Gebiet.Location = new System.Drawing.Point(208, 21);
			this.txt_Gebiet.Name = "txt_Gebiet";
			this.txt_Gebiet.Size = new System.Drawing.Size(52, 20);
			this.txt_Gebiet.TabIndex = 49;
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
			// group_multi
			// 
			this.group_multi.Controls.Add(this.txt_drop);
			this.group_multi.Controls.Add(this.txt_exp);
			this.group_multi.Controls.Add(this.txt_penya);
			this.group_multi.Controls.Add(lbl1);
			this.group_multi.Controls.Add(lbl2);
			this.group_multi.Controls.Add(lbl3);
			this.group_multi.Location = new System.Drawing.Point(199, 117);
			this.group_multi.Name = "group_multi";
			this.group_multi.Size = new System.Drawing.Size(272, 40);
			this.group_multi.TabIndex = 44;
			this.group_multi.TabStop = false;
			this.group_multi.Text = "Multiplicateur";
			// 
			// txt_drop
			// 
			this.txt_drop.DecimalPlaces = 1;
			this.txt_drop.Increment = new decimal(new int[] {
									5,
									0,
									0,
									65536});
			this.txt_drop.Location = new System.Drawing.Point(134, 16);
			this.txt_drop.Name = "txt_drop";
			this.txt_drop.Size = new System.Drawing.Size(42, 20);
			this.txt_drop.TabIndex = 54;
			// 
			// txt_exp
			// 
			this.txt_exp.DecimalPlaces = 1;
			this.txt_exp.Increment = new decimal(new int[] {
									5,
									0,
									0,
									65536});
			this.txt_exp.Location = new System.Drawing.Point(213, 16);
			this.txt_exp.Name = "txt_exp";
			this.txt_exp.Size = new System.Drawing.Size(42, 20);
			this.txt_exp.TabIndex = 53;
			// 
			// txt_penya
			// 
			this.txt_penya.DecimalPlaces = 1;
			this.txt_penya.Increment = new decimal(new int[] {
									5,
									0,
									0,
									65536});
			this.txt_penya.Location = new System.Drawing.Point(52, 18);
			this.txt_penya.Name = "txt_penya";
			this.txt_penya.Size = new System.Drawing.Size(42, 20);
			this.txt_penya.TabIndex = 52;
			// 
			// txt_MovingInterval
			// 
			this.txt_MovingInterval.Location = new System.Drawing.Point(215, 164);
			this.txt_MovingInterval.Name = "txt_MovingInterval";
			this.txt_MovingInterval.Size = new System.Drawing.Size(36, 20);
			this.txt_MovingInterval.TabIndex = 45;
			// 
			// txt_size
			// 
			this.txt_size.Increment = new decimal(new int[] {
									50,
									0,
									0,
									0});
			this.txt_size.Location = new System.Drawing.Point(43, 73);
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
			this.txt_size.TabIndex = 56;
			this.txt_size.Value = new decimal(new int[] {
									100,
									0,
									0,
									0});
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "ID";
			this.columnHeader1.Width = 32;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "Nom";
			this.columnHeader2.Width = 130;
			// 
			// lv_movers
			// 
			this.lv_movers.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.columnHeader1,
									this.columnHeader2});
			this.lv_movers.FullRowSelect = true;
			this.lv_movers.GridLines = true;
			this.lv_movers.LabelEdit = true;
			this.lv_movers.Location = new System.Drawing.Point(11, 19);
			this.lv_movers.Name = "lv_movers";
			this.lv_movers.Size = new System.Drawing.Size(166, 50);
			this.lv_movers.TabIndex = 0;
			this.lv_movers.UseCompatibleStateImageBehavior = false;
			this.lv_movers.View = System.Windows.Forms.View.Details;
			this.lv_movers.AfterLabelEdit += new System.Windows.Forms.LabelEditEventHandler(this.lv_moversAfterLabelEdit);
			// 
			// SpawnForm
			// 
			this.Controls.Add(this.txt_MovingInterval);
			this.Controls.Add(label1);
			this.Controls.Add(this.txt_RespawnZeit);
			this.Controls.Add(this.group_angriff);
			this.Controls.Add(lbl_RespawnZeit);
			this.Controls.Add(this.group_MoverData);
			this.Controls.Add(this.groupData);
			this.Controls.Add(this.group_multi);
			this.group_angriff.ResumeLayout(false);
			this.group_angriff.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.txt_AggroChance)).EndInit();
			this.group_MoverData.ResumeLayout(false);
			this.groupData.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.txt_MaxMobs)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_World)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Gebiet)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Z)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_Y)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_X)).EndInit();
			this.group_multi.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.txt_drop)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_exp)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_penya)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.txt_size)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private System.Windows.Forms.NumericUpDown txt_size;
		private System.Windows.Forms.TextBox txt_MovingInterval;
		private System.Windows.Forms.ListView lv_movers;
		private System.Windows.Forms.NumericUpDown txt_AggroChance;
		private System.Windows.Forms.NumericUpDown txt_penya;
		private System.Windows.Forms.NumericUpDown txt_drop;
		private System.Windows.Forms.NumericUpDown txt_exp;
		private System.Windows.Forms.NumericUpDown txt_MaxMobs;
		private System.Windows.Forms.NumericUpDown txt_World;
		private System.Windows.Forms.NumericUpDown txt_Gebiet;
		private System.Windows.Forms.NumericUpDown txt_Z;
		private System.Windows.Forms.NumericUpDown txt_Y;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.CheckBox cb_move;
		private System.Windows.Forms.GroupBox group_multi;
		private System.Windows.Forms.NumericUpDown txt_X;
		private System.Windows.Forms.GroupBox groupData;
		private System.Windows.Forms.TextBox txt_RespawnZeit;
		private System.Windows.Forms.GroupBox group_MoverData;
		private System.Windows.Forms.TextBox textBox5;
		private System.Windows.Forms.TextBox textBox6;
		private System.Windows.Forms.GroupBox group_angriff;
	}
}
