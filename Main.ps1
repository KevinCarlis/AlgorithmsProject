Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

[Windows.Forms.Application]::EnableVisualStyles()

class SelectForm : System.Windows.Forms.Form {
    hidden [scriptblock]$ShowEvent = {
        Start-Sleep -Seconds 1
        $this.TopMost = $false
        $this.ActiveControl = $null
    }
    [string[]]$SortOptions = @('Insertion','Selection','Bubble','Merge','Quick','Heap','Count','Radix')

    hidden [System.Windows.Forms.FlowLayoutPanel]$CLBSort
    hidden [System.Windows.Forms.CheckedListBox]$CLBSize

    SelectForm() {
        $this.Text = 'CS115 Project'
        $this.Size = New-Object System.Drawing.Size(1280,720)
        $this.TopMost = $true
        $this.BackColor = [System.Drawing.Color]::AliceBlue
        $this.Icon = [System.Drawing.SystemIcons]::WinLogo

        $this.Add_Shown($this.ShowEvent)
        $this.AddControls()
    }

    [void] AddControls() {
        $SortLabel = New-Object System.Windows.Forms.Label -Property @{
            #Location = New-Object System.Drawing.Point(10,10) 
            Text = 'Sort'
            BackColor = [System.Drawing.Color]::Transparent
            Font = [System.Drawing.Font]::new('Segoe UI', 16)
            AutoSize = $true
        }

        $this.CLBSort = New-Object System.Windows.Forms.FlowLayoutPanel -Property @{
            Location = New-Object System.Drawing.Point(10,10)
            Size = New-Object System.Drawing.Size(100,280)
            BackColor = [System.Drawing.Color]::White
            #FlowDirection = [System.Windows.Forms.FlowDirection]::TopDown
        }
        $this.CLBSort.Controls.Add($SortLabel)
        $this.CLBSort.SetFlowBreak($SortLabel, $true)
        $this.SortOptions | ForEach-Object {
            $this.CLBSort.Controls.Add((New-Object System.Windows.Forms.CheckBox -Property @{
                Text = $_
                Checked = $true
            }))
        }
        $this.Controls.Add($this.CLBSort)

        $this.CLBSize = New-Object System.Windows.Forms.CheckedListBox -Property @{

        }

    }
}

try {
    $form = [SelectForm]::new()
    [System.Windows.Forms.Application]::Run($form)
} catch {
    throw
} finally {
    if ($form) {
        $form.Dispose()
    }
}