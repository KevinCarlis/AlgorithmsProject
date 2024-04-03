Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

[Windows.Forms.Application]::EnableVisualStyles()

class SelectForm : System.Windows.Forms.Form {
    hidden [scriptblock]$ShowEvent = {
        Start-Sleep -Seconds 1
        $this.TopMost = $false
        $this.ActiveControl = $null
    }
    [string[]]$SortOptions = @('Insertion','Selection','Bubble','Merge','Heap','Count','Radix','Quick')
    [string[]]$SizeOptions = @(1000,10000,100000,1000000,'Custom')

    hidden [System.Windows.Forms.FlowLayoutPanel]$CLBSort
    hidden [System.Windows.Forms.FlowLayoutPanel]$CLBSize

    SelectForm() {
        $this.Text = 'CS115 Project'
        $this.Size = New-Object System.Drawing.Size(310,420)
        $this.TopMost = $true
        $this.BackColor = [System.Drawing.Color]::AliceBlue
        $this.Icon = [System.Drawing.SystemIcons]::Application

        $this.Add_Shown($this.ShowEvent)
        $this.AddControls()
    }

    [void] AddControls() {
        $sortLabel = New-Object System.Windows.Forms.Label -Property @{
            #Location = New-Object System.Drawing.Point(10,10) 
            Text = 'Sort'
            BackColor = [System.Drawing.Color]::Transparent
            Font = [System.Drawing.Font]::new('Segoe UI', 16)
            AutoSize = $true
        }

        $this.CLBSort = New-Object System.Windows.Forms.FlowLayoutPanel -Property @{
            Location = New-Object System.Drawing.Point(30,30)
            Size = New-Object System.Drawing.Size(100,280)
            BackColor = [System.Drawing.Color]::White
            #FlowDirection = [System.Windows.Forms.FlowDirection]::TopDown
        }
        $this.CLBSort.Controls.Add($sortLabel)
        $this.CLBSort.SetFlowBreak($sortLabel, $true)
        $this.SortOptions | ForEach-Object {
            $this.CLBSort.Controls.Add((New-Object System.Windows.Forms.CheckBox -Property @{
                Text = $_
                Checked = $true
            }))
        }
        $this.Controls.Add($this.CLBSort)


        $sizeLabel = New-Object System.Windows.Forms.Label -Property @{
            #Location = New-Object System.Drawing.Point(10,10) 
            Text = 'Size'
            BackColor = [System.Drawing.Color]::Transparent
            Font = [System.Drawing.Font]::new('Segoe UI', 16)
            AutoSize = $true
        }

        $this.CLBSize = New-Object System.Windows.Forms.FlowLayoutPanel -Property @{
            Location = New-Object System.Drawing.Point(160,30)
            Size = New-Object System.Drawing.Size(100,280)
            BackColor = [System.Drawing.Color]::White
        }
        $this.CLBSize.Controls.Add($sizeLabel)
        $this.CLBSize.SetFlowBreak($sizeLabel, $true)
        $this.SizeOptions | ForEach-Object {
            $this.CLBSize.Controls.Add((New-Object System.Windows.Forms.CheckBox -Property @{
                Text = $_
                Checked = $true
            }))
        }
        $this.Controls.Add($this.CLBSize)

        $runButton = New-Object System.Windows.Forms.Button -Property @{
            Location = New-Object System.Drawing.Point(95,320)
            Font = [System.Drawing.Font]::new('Segoe UI', 16)
            Text = 'Run'
            Size = New-Object System.Drawing.Size(100,35)
            BackColor = [System.Drawing.Color]::Gainsboro
        }
        $this.Controls.Add($runButton)
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