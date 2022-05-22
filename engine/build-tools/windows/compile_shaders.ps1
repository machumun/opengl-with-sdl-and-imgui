$ErrorActionPreference = "Stop"

# Check that we have a 'vulkan' shader asset folder
Push-Location -Path "..\..\..\main\assets\shaders\"
if (!(Test-Path "vulkan")) {
    New-Item -ItemType Directory -Path "vulkan"
}
Pop-Location

# Grab all the files in the current directory ending with 'vert' or 'frag'
# and iterate them one at a time, invoking the Vulkan shader compiler for each.
Get-ChildItem -Name -Include *.vert,*.frag | Foreach-Object {
    $outputFileName = ".\" + $_
    Write-Host "Compiling Vulkan shader file"$_"..."

    ..\engine\third-party\vulkan-windows\Bin\glslangValidator.exe -V --target-env vulkan1.0 -o $outputFileName $_

    # Check if the compilation exit code was successful.
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
