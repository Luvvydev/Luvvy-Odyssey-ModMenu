$ErrorActionPreference = 'Stop'

$ExpectedHash = 'ac327dad2cbbdd72a3fda8e99cbeab9d12af328363e4f09bc5674bdd36b8c483'
$KnownProxyHashes = @(
    'b616f11f3fca61eef16d71301adb95ae4c5583dd612eb09eaa8c0db3e6c973a7',
    '251e861b06001e6747e15c31eaf7c2f83b4aa7a50ef16b6ec5d53e96a3d8ccf7'
)
$Root = Split-Path -Parent $PSScriptRoot
$Exe = Join-Path $Root 'ACOdyssey.exe'
$Bink = Join-Path $Root 'bink2w64.dll'
$OriginalBink = Join-Path $Root 'bink2w64_original.dll'
$ExternalSource = Join-Path $PSScriptRoot 'LuvvyOdysseyExternalMenu.exe'
$ExternalDest = Join-Path $Root 'LuvvyOdysseyExternalMenu.exe'
$StaleMod = Join-Path $Root 'LuvvyOdysseyMod.dll'
$StaleInjector = Join-Path $Root 'LuvvyOdysseyInjector.exe'

function Fail([string]$Message) {
    Write-Host ''
    Write-Host "ERROR: $Message" -ForegroundColor Red
    exit 1
}

if (!(Test-Path -LiteralPath $Exe)) {
    Fail 'ACOdyssey.exe was not found beside this launcher. Extract the ZIP contents into the Assassin''s Creed Odyssey game folder.'
}

if (Get-Process -Name 'ACOdyssey' -ErrorAction SilentlyContinue) {
    Fail 'ACOdyssey.exe is already running. Close the game and Ubisoft crash dialog first, then run Luvvy Odyssey.exe again.'
}

$ActualHash = (Get-FileHash -LiteralPath $Exe -Algorithm SHA256).Hash.ToLowerInvariant()
Write-Host "ACOdyssey.exe SHA256: $ActualHash"
if ($ActualHash -ne $ExpectedHash) {
    Fail 'Unsupported ACOdyssey.exe build. No files were changed.'
}

if (!(Test-Path -LiteralPath $ExternalSource)) {
    Fail 'LuvvyOdysseyExternalMenu.exe is missing from the v4 package.'
}

# v4 keeps the v3 external startup architecture and removes the v1/v2 Bink proxy from the Ubisoft startup path.
if (Test-Path -LiteralPath $Bink) {
    $CurrentBinkHash = (Get-FileHash -LiteralPath $Bink -Algorithm SHA256).Hash.ToLowerInvariant()
    if ($KnownProxyHashes -contains $CurrentBinkHash) {
        if (!(Test-Path -LiteralPath $OriginalBink)) {
            Fail 'A Luvvy Bink proxy is installed but bink2w64_original.dll is missing. Verify Odyssey files in Steam once, then rerun v4.'
        }
        Copy-Item -LiteralPath $OriginalBink -Destination $Bink -Force
        $RestoredHash = (Get-FileHash -LiteralPath $Bink -Algorithm SHA256).Hash.ToLowerInvariant()
        if ($KnownProxyHashes -contains $RestoredHash) {
            Fail 'The Bink restore did not produce the original DLL. Verify game files in Steam before retrying.'
        }
        Write-Host 'Restored original bink2w64.dll. No Luvvy proxy is loaded by Odyssey.' -ForegroundColor Green
    } else {
        Write-Host 'bink2w64.dll is already non-Luvvy/original. Leaving it untouched.'
    }
} elseif (Test-Path -LiteralPath $OriginalBink) {
    Copy-Item -LiteralPath $OriginalBink -Destination $Bink -Force
    Write-Host 'Restored missing bink2w64.dll from the pre-mod backup.' -ForegroundColor Green
} else {
    Fail 'bink2w64.dll is missing. Verify Odyssey files in Steam before retrying.'
}

# Remove stale active v1/v2 payloads from the game directory. Copies remain archived in the Source folder.
foreach ($Path in @($StaleMod,$StaleInjector)) {
    if (Test-Path -LiteralPath $Path) {
        Remove-Item -LiteralPath $Path -Force
        Write-Host "Removed stale in-process payload: $([IO.Path]::GetFileName($Path))"
    }
}

# Windows locks an executable while it is running. Stop a leftover external menu from a previous launch before replacing it.
$ExistingExternalMenu = Get-Process -Name 'LuvvyOdysseyExternalMenu' -ErrorAction SilentlyContinue
if ($ExistingExternalMenu) {
    Write-Host 'Stopping previous LuvvyOdysseyExternalMenu.exe so it can be updated...'
    $ExistingExternalMenu | Stop-Process -Force

    $StopDeadline = (Get-Date).AddSeconds(5)
    while ((Get-Process -Name 'LuvvyOdysseyExternalMenu' -ErrorAction SilentlyContinue) -and ((Get-Date) -lt $StopDeadline)) {
        Start-Sleep -Milliseconds 100
    }

    if (Get-Process -Name 'LuvvyOdysseyExternalMenu' -ErrorAction SilentlyContinue) {
        Fail 'The previous LuvvyOdysseyExternalMenu.exe process would not close. End it in Task Manager, then rerun the launcher.'
    }
}

# Retry briefly because Windows Security or another scanner can hold the file for a moment after process exit.
$MenuCopied = $false
for ($Attempt = 1; $Attempt -le 20; $Attempt++) {
    try {
        Copy-Item -LiteralPath $ExternalSource -Destination $ExternalDest -Force
        $MenuCopied = $true
        break
    } catch [System.IO.IOException] {
        Start-Sleep -Milliseconds 250
    }
}
if (!$MenuCopied) {
    Fail 'LuvvyOdysseyExternalMenu.exe is still locked after waiting 5 seconds. End any leftover LuvvyOdysseyExternalMenu.exe process in Task Manager and rerun the launcher.'
}
Write-Host 'Installed v4 external F10 menu. It does not load a DLL into ACOdyssey.exe.' -ForegroundColor Green

$VideoRoot = Join-Path $Root 'videos'
$SkipNames = @('Amd.bk2','BlackScreen.bk2','UbisoftLogo.bk2','Epilepsy.bk2','PC_WarningSaving.bk2','warning_disclaimer.bk2')
if (Test-Path -LiteralPath $VideoRoot) {
    Get-ChildItem -LiteralPath $VideoRoot -Recurse -File -ErrorAction SilentlyContinue | ForEach-Object {
        if ($SkipNames -contains $_.Name) {
            $Disabled = $_.FullName + '.luvvyskip'
            if (!(Test-Path -LiteralPath $Disabled)) {
                Move-Item -LiteralPath $_.FullName -Destination $Disabled
                Write-Host "Skipped startup video: $($_.FullName)"
            }
        }
    }
}

foreach ($Name in @('LuvvyProxy.log','LuvvyModMenu.log','LuvvyInjector.log','LuvvyExternalMenu.log')) {
    $Log = Join-Path $Root $Name
    if (Test-Path -LiteralPath $Log) {
        $Previous = $Log + '.previous'
        Copy-Item -LiteralPath $Log -Destination $Previous -Force
        Clear-Content -LiteralPath $Log
    }
}

Write-Host ''
Write-Host 'v4 startup path:' -ForegroundColor Cyan
Write-Host 'Steam -> normal Ubisoft session handoff -> final ACOdyssey.exe + visible game window stable for 20 seconds -> external F10 menu attaches.'
Write-Host 'No DLL proxy. No LoadLibrary injection. No game memory is changed until you actually toggle a menu feature.'
Write-Host 'Ubisoft Connect authentication itself is not bypassed.'
Write-Host 'F10: open/close menu   Up/Down: select   Enter: toggle   Esc: hide menu'
Write-Host ''
Write-Host 'Starting v4 external menu...'
Start-Process -FilePath $ExternalDest -WorkingDirectory $Root
