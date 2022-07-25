$ErrorActionPreference = "Stop"

Push-Location -Path "..\..\..\main\assets\shaders\"
if (!(Test-Path "spir_v")) {
    New-Item -ItemType Directory -Path "spir_v"
}


Push-Location -Path ".\vulkan"
# Write-Host "Compiling Vulkan shader file"$_"..."$Get-Location

Get-Location

Get-ChildItem -Name -Include *.vert,*.frag | Foreach-Object {
    $outputFileName = "..\spir_v\" + $_
    Write-Host "Compiling Vulkan shader file"$_"..."

    ..\..\..\..\engine\third_party\vulkan_windows\1.3.216.0\Bin\glslangValidator.exe -V --target-env vulkan1.0 -o $outputFileName $_

    if($LASTEXITCODE -eq 0)
    {
        Write-Host "Compiled"$_" into "$outputFileName" ..."
    } 
    else 
    {
        Write-Host "Error! $_ failed to validate with LASTEXITCODE is "$LASTEXITCODE
        Exit-PSSession
    }
}

Pop-Location
Pop-Location







