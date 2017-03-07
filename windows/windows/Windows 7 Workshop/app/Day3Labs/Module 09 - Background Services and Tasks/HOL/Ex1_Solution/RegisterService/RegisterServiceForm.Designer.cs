namespace RegisterService
{
    partial class RegisterServiceForm
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
            this.btnRegisterDemandStart = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.btnRegisterTriggerStart = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.txtLog = new System.Windows.Forms.TextBox();
            this.btnRemovePrivileges = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnRegisterDemandStart
            // 
            this.btnRegisterDemandStart.Location = new System.Drawing.Point(13, 13);
            this.btnRegisterDemandStart.Name = "btnRegisterDemandStart";
            this.btnRegisterDemandStart.Size = new System.Drawing.Size(195, 23);
            this.btnRegisterDemandStart.TabIndex = 0;
            this.btnRegisterDemandStart.Text = "Register Demand-Start";
            this.btnRegisterDemandStart.UseVisualStyleBackColor = true;
            this.btnRegisterDemandStart.Click += new System.EventHandler(this.btnRegisterDemandStart_Click);
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(12, 42);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(196, 23);
            this.btnStart.TabIndex = 0;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // btnRegisterTriggerStart
            // 
            this.btnRegisterTriggerStart.Location = new System.Drawing.Point(13, 100);
            this.btnRegisterTriggerStart.Name = "btnRegisterTriggerStart";
            this.btnRegisterTriggerStart.Size = new System.Drawing.Size(195, 23);
            this.btnRegisterTriggerStart.TabIndex = 0;
            this.btnRegisterTriggerStart.Text = "Register Trigger-Start";
            this.btnRegisterTriggerStart.UseVisualStyleBackColor = true;
            this.btnRegisterTriggerStart.Click += new System.EventHandler(this.btnRegisterTriggerStart_Click);
            // 
            // btnStop
            // 
            this.btnStop.Location = new System.Drawing.Point(12, 71);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(196, 23);
            this.btnStop.TabIndex = 0;
            this.btnStop.Text = "Stop";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.Location = new System.Drawing.Point(12, 129);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(196, 23);
            this.btnDelete.TabIndex = 0;
            this.btnDelete.Text = "Delete";
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // txtLog
            // 
            this.txtLog.Location = new System.Drawing.Point(215, 13);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtLog.Size = new System.Drawing.Size(310, 167);
            this.txtLog.TabIndex = 1;
            // 
            // btnRemovePrivileges
            // 
            this.btnRemovePrivileges.Location = new System.Drawing.Point(12, 157);
            this.btnRemovePrivileges.Name = "btnRemovePrivileges";
            this.btnRemovePrivileges.Size = new System.Drawing.Size(196, 23);
            this.btnRemovePrivileges.TabIndex = 0;
            this.btnRemovePrivileges.Text = "Remove Privileges";
            this.btnRemovePrivileges.UseVisualStyleBackColor = true;
            this.btnRemovePrivileges.Click += new System.EventHandler(this.btnRemovePrivileges_Click);
            // 
            // RegisterServiceForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(537, 192);
            this.Controls.Add(this.txtLog);
            this.Controls.Add(this.btnRemovePrivileges);
            this.Controls.Add(this.btnDelete);
            this.Controls.Add(this.btnRegisterTriggerStart);
            this.Controls.Add(this.btnStop);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.btnRegisterDemandStart);
            this.Name = "RegisterServiceForm";
            this.Text = "Register Service";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnRegisterDemandStart;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button btnRegisterTriggerStart;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.TextBox txtLog;
        private System.Windows.Forms.Button btnRemovePrivileges;
    }
}