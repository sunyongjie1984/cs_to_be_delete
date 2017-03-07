namespace Ex1_Starter
{
    partial class MainForm
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
            System.Windows.Forms.Label label1;
            System.Windows.Forms.Label label2;
            this.txtSourceDirectory = new System.Windows.Forms.TextBox();
            this.txtDestinationDirectory = new System.Windows.Forms.TextBox();
            this.btnBrowseSource = new System.Windows.Forms.Button();
            this.btnBrowseDestination = new System.Windows.Forms.Button();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.lblProgress = new System.Windows.Forms.Label();
            this.btnCopy = new System.Windows.Forms.Button();
            label1 = new System.Windows.Forms.Label();
            label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new System.Drawing.Point(22, 17);
            label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            label1.Name = "label1";
            label1.Size = new System.Drawing.Size(154, 25);
            label1.TabIndex = 0;
            label1.Text = "Source directory:";
            // 
            // txtSourceDirectory
            // 
            this.txtSourceDirectory.Location = new System.Drawing.Point(224, 17);
            this.txtSourceDirectory.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.txtSourceDirectory.Name = "txtSourceDirectory";
            this.txtSourceDirectory.Size = new System.Drawing.Size(313, 33);
            this.txtSourceDirectory.TabIndex = 1;
            // 
            // txtDestinationDirectory
            // 
            this.txtDestinationDirectory.Location = new System.Drawing.Point(224, 81);
            this.txtDestinationDirectory.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.txtDestinationDirectory.Name = "txtDestinationDirectory";
            this.txtDestinationDirectory.Size = new System.Drawing.Size(313, 33);
            this.txtDestinationDirectory.TabIndex = 3;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new System.Drawing.Point(22, 81);
            label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            label2.Name = "label2";
            label2.Size = new System.Drawing.Size(192, 25);
            label2.TabIndex = 2;
            label2.Text = "Destination directory:";
            // 
            // btnBrowseSource
            // 
            this.btnBrowseSource.Location = new System.Drawing.Point(563, 17);
            this.btnBrowseSource.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.btnBrowseSource.Name = "btnBrowseSource";
            this.btnBrowseSource.Size = new System.Drawing.Size(138, 44);
            this.btnBrowseSource.TabIndex = 4;
            this.btnBrowseSource.Text = "Browse";
            this.btnBrowseSource.UseVisualStyleBackColor = true;
            this.btnBrowseSource.Click += new System.EventHandler(this.btnBrowseSource_Click);
            // 
            // btnBrowseDestination
            // 
            this.btnBrowseDestination.Location = new System.Drawing.Point(563, 71);
            this.btnBrowseDestination.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.btnBrowseDestination.Name = "btnBrowseDestination";
            this.btnBrowseDestination.Size = new System.Drawing.Size(138, 44);
            this.btnBrowseDestination.TabIndex = 5;
            this.btnBrowseDestination.Text = "Browse";
            this.btnBrowseDestination.UseVisualStyleBackColor = true;
            this.btnBrowseDestination.Click += new System.EventHandler(this.btnBrowseDestination_Click);
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(27, 222);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(674, 23);
            this.progressBar.TabIndex = 6;
            // 
            // lblProgress
            // 
            this.lblProgress.AutoSize = true;
            this.lblProgress.Location = new System.Drawing.Point(22, 194);
            this.lblProgress.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.lblProgress.Name = "lblProgress";
            this.lblProgress.Size = new System.Drawing.Size(89, 25);
            this.lblProgress.TabIndex = 7;
            this.lblProgress.Text = "Progress:";
            // 
            // btnCopy
            // 
            this.btnCopy.Location = new System.Drawing.Point(27, 144);
            this.btnCopy.Margin = new System.Windows.Forms.Padding(6);
            this.btnCopy.Name = "btnCopy";
            this.btnCopy.Size = new System.Drawing.Size(138, 44);
            this.btnCopy.TabIndex = 8;
            this.btnCopy.Text = "Copy";
            this.btnCopy.UseVisualStyleBackColor = true;
            this.btnCopy.Click += new System.EventHandler(this.btnCopy_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(718, 257);
            this.Controls.Add(this.btnCopy);
            this.Controls.Add(this.lblProgress);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.btnBrowseDestination);
            this.Controls.Add(this.btnBrowseSource);
            this.Controls.Add(this.txtDestinationDirectory);
            this.Controls.Add(label2);
            this.Controls.Add(this.txtSourceDirectory);
            this.Controls.Add(label1);
            this.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.Name = "MainForm";
            this.Text = "File Copier";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtSourceDirectory;
        private System.Windows.Forms.TextBox txtDestinationDirectory;
        private System.Windows.Forms.Button btnBrowseSource;
        private System.Windows.Forms.Button btnBrowseDestination;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Label lblProgress;
        private System.Windows.Forms.Button btnCopy;
    }
}

