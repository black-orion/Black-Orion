
using System;
using System.Drawing;
using System.Windows.Forms;

namespace UBO.Editoren.Forms
{
	/// <summary>
	/// Description of NPCForm.
	/// </summary>
	public partial class NPCForm : Form
	{
		UBO.MainForm Main;
		
		public NPCForm(UBO.MainForm Main)
		{
			InitializeComponent();
			

			
			group_items.Size = new Size(207, 48);
		}
		
		void Txt_newItemIDTextChanged(object sender, EventArgs e){}		
		void Combo_newItemNameSelectedIndexChanged(object sender, EventArgs e){}
		void Cmd_ItemAddClick(object sender, EventArgs e){}
		void Cmd_ItemRmClick(object sender, EventArgs e){}
		void Cmd_TextAddClick(object sender, EventArgs e){}
		void Cmd_TextRmClick(object sender, EventArgs e){}
		void Cmd_TextChangeClick(object sender, System.EventArgs e){}
	}
}
