$ErrorActionPreference = 'Stop'
$Root = Split-Path -Parent $PSScriptRoot
$Bink = Join-Path $Root 'bink2w64.dll'
$OriginalBink = Join-Path $Root 'bink2w64_original.dll'
$ExternalDest = Join-Path $Root 'LuvvyOdysseyExternalMenu.exe'
$StaleMod = Join-Path $Root 'LuvvyOdysseyMod.dll'
$StaleInjector = Join-Path $Root 'LuvvyOdysseyInjector.exe'
$KnownProxyHashes = @(
    'b616f11f3fca61eef16d71301adb95ae4c5583dd612eb09eaa8c0db3e6c973a7',
    '251e861b06001e6747e15c31eaf7c2f83b4aa7a50ef16b6ec5d53e96a3d8ccf7'
)

if (Get-Process -Name 'ACOdyssey' -ErrorAction SilentlyContinue) {
    Write-Host 'Close Assassin''s Creed Odyssey before restoring files.' -ForegroundColor Yellow
    exit 1
}

if (Test-Path -LiteralPath $OriginalBink) {
    if (!(Test-Path -LiteralPath $Bink)) {
        Copy-Item -LiteralPath $OriginalBink -Destination $Bink -Force
        Write-Host 'Restored original bink2w64.dll'
    } else {
        $CurrentHash = (Get-FileHash -LiteralPath $Bink -Algorithm SHA256).Hash.ToLowerInvariant()
        if ($KnownProxyHashes -contains $CurrentHash) {
            Copy-Item -LiteralPath $OriginalBink -Destination $Bink -Force
            Write-Host 'Restored original bink2w64.dll over an older Luvvy proxy'
        }
    }
}

foreach ($Path in @($ExternalDest,$StaleMod,$StaleInjector)) {
    if (Test-Path -LiteralPath $Path) { Remove-Item -LiteralPath $Path -Force }
}

$VideoRoot = Join-Path $Root 'videos'
if (Test-Path -LiteralPath $VideoRoot) {
    Get-ChildItem -LiteralPath $VideoRoot -Recurse -File -Filter '*.luvvyskip' -ErrorAction SilentlyContinue | ForEach-Object {
        $Original = $_.FullName.Substring(0, $_.FullName.Length - '.luvvyskip'.Length)
        if (!(Test-Path -LiteralPath $Original)) {
            Move-Item -LiteralPath $_.FullName -Destination $Original
            Write-Host "Restored startup video: $Original"
        }
    }
}

Write-Host 'Vanilla loader state and startup videos restored.'
