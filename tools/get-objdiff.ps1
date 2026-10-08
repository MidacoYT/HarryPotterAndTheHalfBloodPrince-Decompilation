param([string]$Destination = (Join-Path $PSScriptRoot 'objdiff-cli.exe'))
$ErrorActionPreference = 'Stop'
$uri = 'https://github.com/encounter/objdiff/releases/download/v3.8.2/objdiff-cli-windows-x86_64.exe'
$expected = '36d229ac6ce74a26b47f42cf86ea8e808d8cd834a54aa62d7ed3f47b765d971b'
$parent = Split-Path -Parent $Destination
New-Item -ItemType Directory -Force -Path $parent | Out-Null
if (-not (Test-Path -LiteralPath $Destination) -or
    (Get-FileHash -LiteralPath $Destination -Algorithm SHA256).Hash.ToLowerInvariant() -ne $expected) {
    Invoke-WebRequest -Uri $uri -OutFile $Destination
}
$actual = (Get-FileHash -LiteralPath $Destination -Algorithm SHA256).Hash.ToLowerInvariant()
if ($actual -ne $expected) { throw "objdiff-cli checksum mismatch: $actual" }
Write-Output $Destination
