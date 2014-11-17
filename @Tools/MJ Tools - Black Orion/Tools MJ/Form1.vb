Imports System
Imports System.Drawing
Imports System.Windows.Forms
Imports System.IO
Imports System.Text.RegularExpressions
Class Form1



    Private Sub Button21_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button21.Click
        TextBox5.Text = ""
        If ComboBox9.Text = "Aucun" Then
            TextBox5.Text = "#item " & TextBox1.Text & " " & TextBox3.Text & " " & TrackBar5.Value & " 0 " & TrackBar4.Value & " " & ComboBox10.Text
        ElseIf ComboBox9.Text = "Feu" Then
            TextBox5.Text = "#item " & TextBox1.Text & " " & TextBox3.Text & " " & TrackBar5.Value & " 1 " & TrackBar4.Value & " " & ComboBox10.Text
        ElseIf ComboBox9.Text = "Eau" Then
            TextBox5.Text = "#item " & TextBox1.Text & " " & TextBox3.Text & " " & TrackBar5.Value & " 2 " & TrackBar4.Value & " " & ComboBox10.Text
        ElseIf ComboBox9.Text = "Eclair" Then
            TextBox5.Text = "#item " & TextBox1.Text & " " & TextBox3.Text & " " & TrackBar5.Value & " 3 " & TrackBar4.Value & " " & ComboBox10.Text
        ElseIf ComboBox9.Text = "Vent" Then
            TextBox5.Text = "#item " & TextBox1.Text & " " & TextBox3.Text & " " & TrackBar5.Value & " 4 " & TrackBar4.Value & " " & ComboBox10.Text
        ElseIf ComboBox9.Text = "Terre" Then
            TextBox5.Text = "#item " & TextBox1.Text & " " & TextBox3.Text & " " & TrackBar5.Value & " 5 " & TrackBar4.Value & " " & ComboBox10.Text
        End If
    End Sub

    Private Sub TextBox5_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox5.TextChanged
        If TextBox5.TextLength > 0 Then Button22.Enabled = True
        If TextBox5.TextLength <= 0 Then Button22.Enabled = False

    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Dim List As New StreamReader("Item.txt")
        Dim Notice As New StreamReader("Notice.txt")
        Dim Config As New StreamReader("Config.ini")
        Dim Text As New StreamReader("data.txt")
        Config.ReadLine()
        TrackBar3.Value = Config.ReadLine()
        If TrackBar3.Value <= 24 Then TrackBar3.Value = 25
        Config.ReadLine()
        ComboBox6.Text = Config.ReadLine
        Config.ReadLine()
        TextBox36.Text = Config.ReadLine
        Config.ReadLine()
        CheckBox2.Checked = Config.ReadLine
        Config.ReadLine()
        CheckBox3.Checked = Config.ReadLine
        RichTextBox7.Text = Text.ReadToEnd
        RichTextBox6.Text = Notice.ReadToEnd
        RichTextBox8.Text = List.ReadToEnd
        List.Close()
        Notice.Close()
        Text.Close()
        TrackBar3.Minimum = 25

    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        TextBox7.Text = ""
        TextBox7.Select()
        My.Computer.Keyboard.SendKeys(".setjob ")
        My.Computer.Keyboard.SendKeys(TextBox9.Text)
        My.Computer.Keyboard.SendKeys(" ")
        My.Computer.Keyboard.SendKeys(TextBox8.Text)
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        TextBox7.Text = ""
        TextBox7.Select()
        My.Computer.Keyboard.SendKeys("#job ")
        My.Computer.Keyboard.SendKeys(TextBox8.Text)
    End Sub

    Private Sub TextBox7_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox7.TextChanged
        If TextBox7.TextLength > 0 Then Button7.Enabled = True
        If TextBox7.TextLength <= 0 Then Button7.Enabled = False
    End Sub

    Private Sub Button22_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button22.Click
        Clipboard.SetText(TextBox5.Text)
    End Sub

    Private Sub Button7_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button7.Click
        Clipboard.SetText(TextBox7.Text)
    End Sub

    Private Sub Button20_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button20.Click
        Timer1.Enabled = True
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Call AppActivate(TextBox10.Text)
        Timer1.Enabled = False
        Timer2.Enabled = True
    End Sub

    Private Sub ComboBox9_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ComboBox9.SelectedIndexChanged
        If ComboBox9.Text = "Aucun" Then
            TrackBar4.Enabled = False
            TrackBar4.Value = "0"
        End If
        If ComboBox9.Text = "Feu" Then TrackBar4.Enabled = True
        If ComboBox9.Text = "Eau" Then TrackBar4.Enabled = True
        If ComboBox9.Text = "Eclair" Then TrackBar4.Enabled = True
        If ComboBox9.Text = "Vent" Then TrackBar4.Enabled = True
        If ComboBox9.Text = "Terre" Then TrackBar4.Enabled = True
    End Sub

    Private Sub GroupBox7_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles GroupBox7.Enter

    End Sub

    Private Sub Button8_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button8.Click
        TextBox19.Text = ""
        TextBox19.Select()
        My.Computer.Keyboard.SendKeys("#teleplace ")
        My.Computer.Keyboard.SendKeys(TextBox18.Text)
        My.Computer.Keyboard.SendKeys(" ")
        My.Computer.Keyboard.SendKeys(TextBox17.Text)
        My.Computer.Keyboard.SendKeys(" ")
        My.Computer.Keyboard.SendKeys(TextBox16.Text)
        My.Computer.Keyboard.SendKeys(" ")
        My.Computer.Keyboard.SendKeys(TextBox15.Text)
        My.Computer.Keyboard.SendKeys(" ")
    End Sub

    Private Sub TextBox19_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox19.TextChanged
        If TextBox19.TextLength > 0 Then Button10.Enabled = True
        If TextBox19.TextLength <= 0 Then Button10.Enabled = False
    End Sub

    Private Sub TextBox21_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox21.TextChanged
        If TextBox21.TextLength > 0 Then Button16.Enabled = True
        If TextBox21.TextLength <= 0 Then Button16.Enabled = False
    End Sub

    Private Sub TextBox23_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox23.TextChanged
        If TextBox23.TextLength > 0 Then Button23.Enabled = True
        If TextBox23.TextLength <= 0 Then Button23.Enabled = False
    End Sub

    Private Sub TextBox24_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox24.TextChanged
        If TextBox24.TextLength > 0 Then Button25.Enabled = True
        If TextBox24.TextLength <= 0 Then Button25.Enabled = False
    End Sub

    Private Sub TextBox25_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox25.TextChanged
        If TextBox25.TextLength > 0 Then Button27.Enabled = True
        If TextBox25.TextLength <= 0 Then Button27.Enabled = False
    End Sub

    Private Sub Button10_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button10.Click
        Clipboard.SetText(TextBox19.Text)
    End Sub

    Private Sub Button16_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button16.Click
        Clipboard.SetText(TextBox21.Text)
    End Sub

    Private Sub Button23_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button23.Click
        Clipboard.SetText(TextBox23.Text)
    End Sub

    Private Sub Button25_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button25.Click
        Clipboard.SetText(TextBox24.Text)
    End Sub

    Private Sub Button27_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button27.Click
        Clipboard.SetText(TextBox25.Text)
    End Sub

    Private Sub Button11_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button11.Click
        TextBox21.Text = ""
        TextBox21.Select()
        My.Computer.Keyboard.SendKeys("#lvl ")
        My.Computer.Keyboard.SendKeys(TextBox20.Text)
    End Sub

    Private Sub Button13_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button13.Click
        TextBox23.Text = ""
        TextBox23.Select()
        My.Computer.Keyboard.SendKeys(".sizemod ")
        My.Computer.Keyboard.SendKeys(TextBox27.Text)
    End Sub

    Private Sub Button14_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button14.Click
        TextBox24.Text = ""
        TextBox24.Select()
        My.Computer.Keyboard.SendKeys("#name ")
        My.Computer.Keyboard.SendKeys(TextBox28.Text)
    End Sub

    Private Sub Button15_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button15.Click
        TextBox25.Text = ""
        TextBox25.Select()
        My.Computer.Keyboard.SendKeys(".transform ")
        My.Computer.Keyboard.SendKeys(TextBox29.Text)
    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        Timer3.Enabled = True
    End Sub

    Private Sub Button9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button9.Click
        Timer5.Enabled = True
    End Sub

    Private Sub Button17_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button17.Click
        Timer7.Enabled = True
    End Sub

    Private Sub Button19_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        Timer9.Enabled = True
    End Sub

    Private Sub Button24_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button24.Click
        Timer11.Enabled = True
    End Sub

    Private Sub Button26_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button26.Click
        Timer13.Enabled = True
    End Sub

    Private Sub Button28_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button28.Click
        Timer15.Enabled = True
    End Sub

    Private Sub Button30_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)



    End Sub

    Private Sub Button33_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button33.Click
        Clipboard.SetText(TextBox32.Text)
    End Sub

    Private Sub Button36_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button36.Click
        Clipboard.SetText(TextBox34.Text)
    End Sub

    Private Sub Button39_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button39.Click
        Clipboard.SetText(TextBox33.Text)
    End Sub

    Private Sub Button42_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button42.Click
        Clipboard.SetText(TextBox35.Text)
    End Sub

    Private Sub TextBox32_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox32.TextChanged
        If TextBox32.TextLength > 0 Then Button33.Enabled = True
        If TextBox32.TextLength <= 0 Then Button33.Enabled = False
    End Sub

    Private Sub TextBox34_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox34.TextChanged
        If TextBox34.TextLength > 0 Then Button36.Enabled = True
        If TextBox34.TextLength <= 0 Then Button36.Enabled = False
    End Sub

    Private Sub TextBox33_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox33.TextChanged
        If TextBox33.TextLength > 0 Then Button39.Enabled = True
        If TextBox33.TextLength <= 0 Then Button39.Enabled = False
    End Sub

    Private Sub TextBox35_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox35.TextChanged
        If TextBox35.TextLength > 0 Then Button42.Enabled = True
        If TextBox35.TextLength <= 0 Then Button42.Enabled = False
    End Sub

    Private Sub Button31_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button31.Click
        TextBox32.Text = ""
        TextBox32.Select()
        My.Computer.Keyboard.SendKeys("#kill ")
        My.Computer.Keyboard.SendKeys(TextBox31.Text)
    End Sub

    Private Sub Button34_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button34.Click
        TextBox34.Text = ""
        TextBox34.Select()
        My.Computer.Keyboard.SendKeys("#weather ")
        My.Computer.Keyboard.SendKeys(ComboBox1.Text)
    End Sub

    Private Sub Button37_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button37.Click
        TextBox33.Text = ""
        TextBox33.Select()
        My.Computer.Keyboard.SendKeys("#stat ")
        My.Computer.Keyboard.SendKeys(ComboBox2.Text)
    End Sub

    Private Sub Button40_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button40.Click
        TextBox35.Text = ""
        TextBox35.Select()
        My.Computer.Keyboard.SendKeys(".abp ")
        My.Computer.Keyboard.SendKeys(ComboBox3.Text)
    End Sub

    Private Sub ToolStripStatusLabel7_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ToolStripStatusLabel7.Click

    End Sub

    Private Sub Button32_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button32.Click
        Timer17.Enabled = True
    End Sub

    Private Sub Button35_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button35.Click
        Timer19.Enabled = True
    End Sub

    Private Sub Button38_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button38.Click
        Timer21.Enabled = True
    End Sub

    Private Sub Button41_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button41.Click
        Timer24.Enabled = True
    End Sub

    Private Sub TrackBar3_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TrackBar3.Scroll

    End Sub

    Private Sub TrackBar3_ValueChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles TrackBar3.ValueChanged

        Me.Opacity = TrackBar3.Value / 100
    End Sub

    Private Sub ComboBox6_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ComboBox6.SelectedIndexChanged
        If ComboBox6.Text = "Vide" Then Me.FormBorderStyle = Windows.Forms.FormBorderStyle.None
        If ComboBox6.Text = "FixedSingle" Then Me.FormBorderStyle = Windows.Forms.FormBorderStyle.FixedSingle
        If ComboBox6.Text = "Fixed3D" Then Me.FormBorderStyle = Windows.Forms.FormBorderStyle.Fixed3D
        If ComboBox6.Text = "FixedDialog" Then Me.FormBorderStyle = Windows.Forms.FormBorderStyle.FixedDialog
        If ComboBox6.Text = "Sizable" Then Me.FormBorderStyle = Windows.Forms.FormBorderStyle.Sizable
        If ComboBox6.Text = "FixedToolWindow" Then Me.FormBorderStyle = Windows.Forms.FormBorderStyle.FixedToolWindow
        If ComboBox6.Text = "SizableToolWindow" Then Me.FormBorderStyle = Windows.Forms.FormBorderStyle.SizableToolWindow

    End Sub

    Private Sub CheckBox2_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckBox2.CheckedChanged
        If CheckBox2.Checked Then Me.ShowIcon = True
        If CheckBox2.Checked = False Then Me.ShowIcon = False

    End Sub
    Private Sub CheckBox3_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckBox3.CheckedChanged
        If CheckBox3.Checked = True Then Me.ShowInTaskbar = True
        If CheckBox3.Checked = False Then Me.ShowInTaskbar = False

    End Sub

    Private Sub TextBox36_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox36.TextChanged
        Me.Text = TextBox36.Text

    End Sub

    Private Sub Timer2_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer2.Tick
        SendKeys.Send(TextBox5.Text)
        SendKeys.Send("{ENTER}")
        Timer2.Enabled = False
    End Sub

    Private Sub ComboBox4_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs)

    End Sub

    Private Sub Timer3_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer3.Tick
        Call AppActivate(TextBox10.Text)
        Timer4.Enabled = True
        Timer3.Enabled = False
    End Sub

    Private Sub Timer4_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer4.Tick
        SendKeys.Send(TextBox7.Text)
        SendKeys.Send("{ENTER}")
        Timer4.Enabled = False
    End Sub

    Private Sub Timer5_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer5.Tick
        Call AppActivate(TextBox10.Text)
        Timer6.Enabled = True
        Timer5.Enabled = False
    End Sub

    Private Sub Timer6_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer6.Tick

        SendKeys.Send(TextBox19.Text)
        SendKeys.Send("{ENTER}")
        Timer6.Enabled = False
    End Sub

    Private Sub Timer7_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer7.Tick
        Call AppActivate(TextBox10.Text)
        Timer8.Enabled = True
        Timer7.Enabled = False
    End Sub

    Private Sub Timer8_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer8.Tick
        SendKeys.Send(TextBox21.Text)
        SendKeys.Send("{ENTER}")
        Timer8.Enabled = False
    End Sub

    Private Sub Timer9_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer9.Tick
        Call AppActivate(TextBox10.Text)
        Timer10.Enabled = True
        Timer9.Enabled = False
    End Sub

    Private Sub Timer11_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer11.Tick
        Call AppActivate(TextBox10.Text)
        Timer12.Enabled = True
        Timer11.Enabled = False
    End Sub

    Private Sub Timer12_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer12.Tick

        SendKeys.Send(TextBox23.Text)
        SendKeys.Send("{ENTER}")
        Timer12.Enabled = False
    End Sub

    Private Sub Timer13_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer13.Tick
        Call AppActivate(TextBox10.Text)
        Timer14.Enabled = True
        Timer13.Enabled = False
    End Sub

    Private Sub Timer14_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer14.Tick

        SendKeys.Send(TextBox24.Text)
        SendKeys.Send("{ENTER}")
        Timer14.Enabled = False
    End Sub

    Private Sub Timer15_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer15.Tick
        Call AppActivate(TextBox10.Text)
        Timer16.Enabled = True
        Timer15.Enabled = False
    End Sub

    Private Sub Timer16_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer16.Tick

        SendKeys.Send(TextBox25.Text)
        SendKeys.Send("{ENTER}")
        Timer16.Enabled = False
    End Sub

    Private Sub Timer17_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer17.Tick
        Call AppActivate(TextBox10.Text)
        Timer18.Enabled = True
        Timer17.Enabled = False
    End Sub

    Private Sub Timer18_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer18.Tick

        SendKeys.Send(TextBox32.Text)
        SendKeys.Send("{ENTER}")
        Timer18.Enabled = False
    End Sub

    Private Sub Timer19_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer19.Tick
        Call AppActivate(TextBox10.Text)
        Timer20.Enabled = True
        Timer19.Enabled = False
    End Sub

    Private Sub Timer20_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer20.Tick
        SendKeys.Send(TextBox34.Text)
        SendKeys.Send("{ENTER}")
        Timer20.Enabled = False
    End Sub

    Private Sub Timer21_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer21.Tick
        Call AppActivate(TextBox10.Text)
        Timer22.Enabled = True
        Timer21.Enabled = False
    End Sub

    Private Sub Timer22_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer22.Tick

        SendKeys.Send(TextBox33.Text)
        SendKeys.Send("{ENTER}")
        Timer22.Enabled = False
    End Sub

    Private Sub Timer23_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer23.Tick
        Call AppActivate(TextBox10.Text)
        Timer24.Enabled = True
        Timer23.Enabled = False
    End Sub

    Private Sub Timer24_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer24.Tick
        SendKeys.Send(TextBox35.Text)
        SendKeys.Send("{ENTER}")
        Timer24.Enabled = False
    End Sub

    Private Sub Timer31_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer7.Tick
        Call AppActivate(TextBox10.Text)
        Timer8.Enabled = True
        Timer7.Enabled = False
    End Sub

    Private Sub Button30_Click_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button30.Click
        Dim Speichern As New StreamWriter("Notice.txt")
        RichTextBox6.Select()
        My.Computer.Keyboard.SendKeys(TimeOfDay)
        My.Computer.Keyboard.SendKeys(" ")
        My.Computer.Keyboard.SendKeys(TextBox30.Text)
        SendKeys.SendWait(vbNewLine)
        TextBox30.Text = ""
        TextBox30.Select()
        Speichern.Write(RichTextBox6.Text)
        Speichern.Close()
    End Sub

    Private Sub Button43_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button43.Click
        RichTextBox6.Text = ""
        Dim Speichern As New StreamWriter("Notice.txt")
        Speichern.Write(RichTextBox6.Text)
        Speichern.Close()
    End Sub

    Private Sub TextBox30_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles TextBox30.KeyPress
        Select Case e.KeyChar
            Case "ä"c, "Ä"c, "ö"c, "Ö"c, "^"c, ":"c, "#"c, "'"c, "+"c, "-"c, "."c, ","c, ";"c, "*"c, "~"c, "^"c
                e.Handled = True
        End Select
    End Sub

    Private Sub TextBox30_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox30.TextChanged

    End Sub

    Private Sub Button44_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)

    End Sub

    Private Sub Button45_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button45.Click
        Dim Save As New StreamWriter("Config.ini")
        Save.WriteLine("[Transparent]")
        Save.WriteLine(TrackBar3.Value)
        Save.WriteLine("[Window Style]")
        Save.WriteLine(ComboBox6.Text)
        Save.WriteLine("[Titre]")
        Save.WriteLine(TextBox36.Text)
        Save.WriteLine("[Voir Icone]")
        Save.WriteLine(CheckBox2.Checked)
        Save.WriteLine("[Barre de tache ]")
        Save.WriteLine(CheckBox3.Checked)
        Save.Close()
        MsgBox("Config OK!", MsgBoxStyle.OkOnly)
    End Sub

    Private Sub RadioButton1_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RadioButton1.CheckedChanged
        If RadioButton1.Checked = True Then TrackBar5.Maximum = 20
        If RadioButton1.Checked = True Then Label5.Text = "0 2 4 6 8 10  12  14  16  18  20"
    End Sub

    Private Sub RadioButton2_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RadioButton2.CheckedChanged
        If RadioButton2.Checked = True Then TrackBar5.Maximum = 10
        If RadioButton2.Checked = True Then Label5.Text = "0   1  2  3  4   5  6  7   8   9  10"
    End Sub

    Private Sub TextBox9_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox9.TextChanged

    End Sub

    Private Sub RichTextBox7_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RichTextBox7.TextChanged

    End Sub

    Private Sub Button44_Click_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button44.Click
        Dim Text As New StreamWriter("Text.txt")
        Text.Write(RichTextBox7.Text)
        Text.Close()
        MsgBox("Sauvgarde avec Succes!", MsgBoxStyle.OkOnly)
    End Sub

    Private Sub Button46_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button46.Click
        Timer25.Enabled = True
    End Sub

    Private Sub Timer25_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer25.Tick
        Call AppActivate(TextBox10.Text)
        Timer26.Enabled = True
        Timer25.Enabled = False
    End Sub

    Private Sub Timer26_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer26.Tick
        My.Computer.Keyboard.SendKeys(".telealltome")
        My.Computer.Keyboard.SendKeys("{ENTER}")
        Timer26.Enabled = False
    End Sub

    Private Sub Button47_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button47.Click
        Timer27.Enabled = True
    End Sub

    Private Sub Timer27_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer27.Tick
        Call AppActivate(TextBox10.Text)
        Timer28.Enabled = True
        Timer27.Enabled = False
    End Sub

    Private Sub Timer28_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer28.Tick
        My.Computer.Keyboard.SendKeys(".telemeto " & TextBox37.Text)
        My.Computer.Keyboard.SendKeys("{ENTER}")
        Timer28.Enabled = False
    End Sub

    Private Sub Button48_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button48.Click
        Timer29.Enabled = True
    End Sub

    Private Sub Timer29_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer29.Tick
        Call AppActivate(TextBox10.Text)
        Timer30.Enabled = True
        Timer29.Enabled = False
    End Sub

    Private Sub Timer30_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer30.Tick
        If RadioButton3.Checked = True Then
            My.Computer.Keyboard.SendKeys("#n " & TextBox38.Text)
            My.Computer.Keyboard.SendKeys("{ENTER}")
        End If
        If RadioButton4.Checked = True Then
            My.Computer.Keyboard.SendKeys("#notice " & TextBox38.Text)
            My.Computer.Keyboard.SendKeys("{ENTER}")
        End If
        Timer30.Enabled = False
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        RichTextBox7.Text = ""
    End Sub

    Private Sub ToolStripStatusLabel1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ToolStripStatusLabel1.Click

    End Sub

    Private Sub GroupBox1_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles GroupBox1.Enter

    End Sub

    Private Sub QuitterToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles QuitterToolStripMenuItem.Click
        Application.Exit()
    End Sub

    Private Sub StatusStrip1_ItemClicked(ByVal sender As System.Object, ByVal e As System.Windows.Forms.ToolStripItemClickedEventArgs) Handles StatusStrip1.ItemClicked

    End Sub

    Private Sub Label45_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Label45.Click

    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Clipboard.SetText(TextBox2.Text)
    End Sub
    Private Sub Button888_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button38.Click
        Timer33.Enabled = True
    End Sub

    Private Sub Button12_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button12.Click
        TextBox2.Text = ""
        TextBox2.Select()
        My.Computer.Keyboard.SendKeys("#penya ")
        My.Computer.Keyboard.SendKeys(TextBox44.Text)
    End Sub
    Private Sub Timer33_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer23.Tick
        Call AppActivate(TextBox44.Text)
        Timer24.Enabled = True
        Button2.Enabled = True

        Timer31.Enabled = False
    End Sub
    Private Sub Timer32_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer24.Tick
        SendKeys.Send(TextBox2.Text)
        SendKeys.Send("{ENTER}")
        Timer24.Enabled = False
    End Sub

    Private Sub TabPage10_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TabPage10.Click

    End Sub
End Class