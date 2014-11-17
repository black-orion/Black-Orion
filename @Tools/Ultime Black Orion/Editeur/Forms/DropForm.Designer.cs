
namespace UBO
{
	public partial class DropForm
	{
		/// <summary>
		/// Designer variable UBOd to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources UBOd by the form.
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
			this.components = new System.ComponentModel.Container();
			System.Windows.Forms.Label lbl_nDrop;
			System.Windows.Forms.Label label13;
			System.Windows.Forms.Label label12;
			System.Windows.Forms.Label label11;
			System.Windows.Forms.Label label4;
			System.Windows.Forms.Label label2;
			System.Windows.Forms.Label label1;
			this.lb_nichtDrop = new System.Windows.Forms.ListBox();
			this.txt_penyaMax = new System.Windows.Forms.TextBox();
			this.txt_penyaMin = new System.Windows.Forms.TextBox();
			this.lv_dropSPC = new System.Windows.Forms.ListView();
			this.lv_dropKind = new System.Windows.Forms.ListView();
			this.lv_dropItem = new System.Windows.Forms.ListView();
			this.lv_movers = new System.Windows.Forms.ListView();
			this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
			this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.neuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.löschenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.column_id = new System.Windows.Forms.ColumnHeader();
			this.column_warschein = new System.Windows.Forms.ColumnHeader();
			this.column_spc_id = new System.Windows.Forms.ColumnHeader();
			this.column_spc_warschei = new System.Windows.Forms.ColumnHeader();
			this.column_spc_upgrade = new System.Windows.Forms.ColumnHeader();
			this.column_spc_erweck = new System.Windows.Forms.ColumnHeader();
			this.column_spc_statting = new System.Windows.Forms.ColumnHeader();
			this.column_kind_name = new System.Windows.Forms.ColumnHeader();
			this.column_kind_minLvl = new System.Windows.Forms.ColumnHeader();
			this.column_kind_maxLvl = new System.Windows.Forms.ColumnHeader();
			this.column_kind_warschei = new System.Windows.Forms.ColumnHeader();
			lbl_nDrop = new System.Windows.Forms.Label();
			label13 = new System.Windows.Forms.Label();
			label12 = new System.Windows.Forms.Label();
			label11 = new System.Windows.Forms.Label();
			label4 = new System.Windows.Forms.Label();
			label2 = new System.Windows.Forms.Label();
			label1 = new System.Windows.Forms.Label();
			this.contextMenuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// lbl_nDrop
			// 
			lbl_nDrop.Location = new System.Drawing.Point(267, 10);
			lbl_nDrop.Name = "lbl_nDrop";
			lbl_nDrop.Size = new System.Drawing.Size(80, 17);
			lbl_nDrop.TabIndex = 33;
			lbl_nDrop.Text = "Nicht Droppen:";
			// 
			// label13
			// 
			label13.Location = new System.Drawing.Point(192, 9);
			label13.Name = "label13";
			label13.Size = new System.Drawing.Size(32, 20);
			label13.TabIndex = 31;
			label13.Text = "Max:";
			// 
			// label12
			// 
			label12.Location = new System.Drawing.Point(195, 32);
			label12.Name = "label12";
			label12.Size = new System.Drawing.Size(27, 20);
			label12.TabIndex = 30;
			label12.Text = "Min:";
			// 
			// label11
			// 
			label11.Location = new System.Drawing.Point(147, 9);
			label11.Name = "label11";
			label11.Size = new System.Drawing.Size(42, 20);
			label11.TabIndex = 29;
			label11.Text = "Penya:";
			// 
			// label4
			// 
			label4.Location = new System.Drawing.Point(2, 168);
			label4.Name = "label4";
			label4.Size = new System.Drawing.Size(480, 14);
			label4.TabIndex = 27;
			label4.Text = "Drop SPC";
			label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// label2
			// 
			label2.Location = new System.Drawing.Point(248, 55);
			label2.Name = "label2";
			label2.Size = new System.Drawing.Size(234, 14);
			label2.TabIndex = 26;
			label2.Text = "Drop Kind";
			label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// label1
			// 
			label1.Location = new System.Drawing.Point(3, 52);
			label1.Name = "label1";
			label1.Size = new System.Drawing.Size(233, 14);
			label1.TabIndex = 25;
			label1.Text = "Drop Item";
			label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// lb_nichtDrop
			// 
			this.lb_nichtDrop.FormattingEnabled = true;
			this.lb_nichtDrop.Location = new System.Drawing.Point(353, 6);
			this.lb_nichtDrop.Name = "lb_nichtDrop";
			this.lb_nichtDrop.Size = new System.Drawing.Size(125, 43);
			this.lb_nichtDrop.TabIndex = 34;
			// 
			// txt_penyaMax
			// 
			this.txt_penyaMax.Location = new System.Drawing.Point(225, 6);
			this.txt_penyaMax.Name = "txt_penyaMax";
			this.txt_penyaMax.Size = new System.Drawing.Size(42, 20);
			this.txt_penyaMax.TabIndex = 32;
			// 
			// txt_penyaMin
			// 
			this.txt_penyaMin.Location = new System.Drawing.Point(225, 29);
			this.txt_penyaMin.Name = "txt_penyaMin";
			this.txt_penyaMin.Size = new System.Drawing.Size(42, 20);
			this.txt_penyaMin.TabIndex = 28;
			// 
			// lv_dropSPC
			// 
			this.lv_dropSPC.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.column_spc_id,
									this.column_spc_warschei,
									this.column_spc_upgrade,
									this.column_spc_erweck,
									this.column_spc_statting});
			this.lv_dropSPC.Location = new System.Drawing.Point(6, 186);
			this.lv_dropSPC.Name = "lv_dropSPC";
			this.lv_dropSPC.Size = new System.Drawing.Size(472, 97);
			this.lv_dropSPC.TabIndex = 24;
			this.lv_dropSPC.UBOCompatibleStateImageBehavior = false;
			this.lv_dropSPC.View = System.Windows.Forms.View.Details;
			// 
			// lv_dropKind
			// 
			this.lv_dropKind.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.column_kind_name,
									this.column_kind_minLvl,
									this.column_kind_maxLvl,
									this.column_kind_warschei});
			this.lv_dropKind.Location = new System.Drawing.Point(248, 69);
			this.lv_dropKind.Name = "lv_dropKind";
			this.lv_dropKind.Size = new System.Drawing.Size(230, 97);
			this.lv_dropKind.TabIndex = 23;
			this.lv_dropKind.UBOCompatibleStateImageBehavior = false;
			this.lv_dropKind.View = System.Windows.Forms.View.Details;
			// 
			// lv_dropItem
			// 
			this.lv_dropItem.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.column_id,
									this.column_warschein});
			this.lv_dropItem.Location = new System.Drawing.Point(6, 69);
			this.lv_dropItem.Name = "lv_dropItem";
			this.lv_dropItem.Size = new System.Drawing.Size(230, 97);
			this.lv_dropItem.TabIndex = 35;
			this.lv_dropItem.UBOCompatibleStateImageBehavior = false;
			this.lv_dropItem.View = System.Windows.Forms.View.Details;
			// 
			// lv_movers
			// 
			this.lv_movers.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.columnHeader1,
									this.columnHeader2});
			this.lv_movers.FullRowSelect = true;
			this.lv_movers.GridLines = true;
			this.lv_movers.LabelEdit = true;
			this.lv_movers.Location = new System.Drawing.Point(12, 2);
			this.lv_movers.Name = "lv_movers";
			this.lv_movers.Size = new System.Drawing.Size(135, 50);
			this.lv_movers.TabIndex = 36;
			this.lv_movers.UBOCompatibleStateImageBehavior = false;
			this.lv_movers.View = System.Windows.Forms.View.Details;
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "ID";
			this.columnHeader1.Width = 32;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "Nom";
			this.columnHeader2.Width = 98;
			// 
			// contextMenuStrip1
			// 
			this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.neuToolStripMenuItem,
									this.löschenToolStripMenuItem});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new System.Drawing.Size(125, 48);
			// 
			// neuToolStripMenuItem
			// 
			this.neuToolStripMenuItem.Name = "neuToolStripMenuItem";
			this.neuToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
			this.neuToolStripMenuItem.Text = "Neu";
			// 
			// löschenToolStripMenuItem
			// 
			this.löschenToolStripMenuItem.Name = "löschenToolStripMenuItem";
			this.löschenToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
			this.löschenToolStripMenuItem.Text = "Löschen";
			// 
			// column_id
			// 
			this.column_id.Text = "ID";
			this.column_id.Width = 51;
			// 
			// column_warschein
			// 
			this.column_warschein.Text = "%";
			this.column_warschein.Width = 36;
			// 
			// column_spc_id
			// 
			this.column_spc_id.Text = "ID";
			this.column_spc_id.Width = 83;
			// 
			// column_spc_warschei
			// 
			this.column_spc_warschei.Text = "%";
			this.column_spc_warschei.Width = 36;
			// 
			// column_spc_upgrade
			// 
			this.column_spc_upgrade.Text = "Upgrade";
			this.column_spc_upgrade.Width = 80;
			// 
			// column_spc_erweck
			// 
			this.column_spc_erweck.Text = "Erweckung";
			this.column_spc_erweck.Width = 92;
			// 
			// column_spc_statting
			// 
			this.column_spc_statting.Text = "Statting";
			this.column_spc_statting.Width = 83;
			// 
			// column_kind_name
			// 
			this.column_kind_name.Text = "Nom";
			this.column_kind_name.Width = 79;
			// 
			// column_kind_minLvl
			// 
			this.column_kind_minLvl.Text = "Min Lvl";
			this.column_kind_minLvl.Width = 50;
			// 
			// column_kind_maxLvl
			// 
			this.column_kind_maxLvl.Text = "Max Lvl";
			this.column_kind_maxLvl.Width = 57;
			// 
			// column_kind_warschei
			// 
			this.column_kind_warschei.Text = "%";
			this.column_kind_warschei.Width = 39;
			// 
			// DropForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(484, 291);
			this.Controls.Add(this.lv_dropItem);
			this.Controls.Add(this.lb_nichtDrop);
			this.Controls.Add(this.lv_movers);
			this.Controls.Add(lbl_nDrop);
			this.Controls.Add(this.txt_penyaMax);
			this.Controls.Add(label13);
			this.Controls.Add(label12);
			this.Controls.Add(this.txt_penyaMin);
			this.Controls.Add(label11);
			this.Controls.Add(label4);
			this.Controls.Add(label2);
			this.Controls.Add(label1);
			this.Controls.Add(this.lv_dropSPC);
			this.Controls.Add(this.lv_dropKind);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.Name = "DropForm";
			this.Text = "DropForm";
			this.contextMenuStrip1.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private System.Windows.Forms.ColumnHeader column_spc_statting;
		private System.Windows.Forms.ColumnHeader column_spc_erweck;
		private System.Windows.Forms.ColumnHeader column_spc_upgrade;
		private System.Windows.Forms.ColumnHeader column_spc_warschei;
		private System.Windows.Forms.ColumnHeader column_spc_id;
		private System.Windows.Forms.ColumnHeader column_kind_warschei;
		private System.Windows.Forms.ColumnHeader column_kind_maxLvl;
		private System.Windows.Forms.ColumnHeader column_kind_minLvl;
		private System.Windows.Forms.ColumnHeader column_kind_name;
		private System.Windows.Forms.ColumnHeader column_warschein;
		private System.Windows.Forms.ColumnHeader column_id;
		private System.Windows.Forms.ToolStripMenuItem löschenToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem neuToolStripMenuItem;
		private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.ListView lv_movers;
		private System.Windows.Forms.ListView lv_dropSPC;
		private System.Windows.Forms.ListBox lb_nichtDrop;
		private System.Windows.Forms.ListView lv_dropItem;
		private System.Windows.Forms.TextBox txt_penyaMax;
		private System.Windows.Forms.TextBox txt_penyaMin;
		private System.Windows.Forms.ListView lv_dropKind;
	}
}
