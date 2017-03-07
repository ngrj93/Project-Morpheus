namespace Client
{
    partial class MasterNode
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.CalculatePiBtn = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.ResultTextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // CalculatePiBtn
            // 
            this.CalculatePiBtn.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CalculatePiBtn.ForeColor = System.Drawing.Color.Red;
            this.CalculatePiBtn.Location = new System.Drawing.Point(13, 96);
            this.CalculatePiBtn.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.CalculatePiBtn.Name = "CalculatePiBtn";
            this.CalculatePiBtn.Size = new System.Drawing.Size(289, 48);
            this.CalculatePiBtn.TabIndex = 2;
            this.CalculatePiBtn.Text = "Calculate PI";
            this.CalculatePiBtn.UseVisualStyleBackColor = true;
            this.CalculatePiBtn.Click += new System.EventHandler(this.CalculatePiBtn_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Navy;
            this.label2.Location = new System.Drawing.Point(13, 29);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(54, 19);
            this.label2.TabIndex = 3;
            this.label2.Text = "Result:";
            // 
            // ResultTextBox
            // 
            this.ResultTextBox.Location = new System.Drawing.Point(75, 26);
            this.ResultTextBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.ResultTextBox.Name = "ResultTextBox";
            this.ResultTextBox.ReadOnly = true;
            this.ResultTextBox.Size = new System.Drawing.Size(227, 27);
            this.ResultTextBox.TabIndex = 4;
            // 
            // MasterNode
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 19F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(315, 174);
            this.Controls.Add(this.ResultTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.CalculatePiBtn);
            this.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "MasterNode";
            this.Text = "Master Node";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button CalculatePiBtn;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox ResultTextBox;
    }
}

