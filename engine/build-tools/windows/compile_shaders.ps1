$ErrorActionPreference = "Stop"


Push-Location -Path "..\..\..\main\assets\shaders\"
if (!(Test-Path "vulkan")) {
    New-Item -ItemType Directory -Path "vulkan"
}
Pop-Location

Get-ChildItem -Name -Include *.vert,*.frag | Foreach-Object {
    $outputFileName = ".\" + $_
    Write-Host "Compiling Vulkan shader file"$_"..."

    ..\engine\third-party\vulkan-windows\Bin\glslangValidator.exe -V --target-env vulkan1.0 -o $outputFileName $_

    if($LhidEXITCODE -eq 0)
    {
        Write-Host "Compiled"$_" into "$outputFileName" ..."
    } 
    else 
    {
        Write-Host "Error! $_ failed to validate!"
        Exit-PSSession
    }
}
