$ErrorActionPreference = "Stop"

# third-party
Push-Location -Path "..\..\"
if (!(Test-Path "third-party")) {
    New-Item -ItemType Directory -Path "third-party"
}
Pop-Location

# sdl
if (!(Test-Path "..\..\third-party\sdl-windows")) {
    Write-Host "Downloading SDL Windows Dev library into third party folder sdl-windows ..."
    
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://www.libsdl.org/release/SDL2-devel-2.0.9-VC.zip", "..\..\third-party\SDL2-devel-2.0.9-VC.zip")

    Invoke-WebRequest -Uri "https://www.libsdl.org/release/SDL2-devel-2.0.9-VC.zip" -OutFile "..\..\third-party\SDL2-devel-2.0.9-VC.zip"

    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping SDL Windows Dev library into third-party\sdl-windows ..."
        cmd.exe /c 'tar -xf SDL2-devel-2.0.9-VC.zip'
        Move-Item -Path SDL2-2.0.9 -Destination sdl-windows
        Remove-Item -Path SDL2-devel-2.0.9-VC.zip
    Pop-Location
}

# glew
if (!(Test-Path "..\..\third-party\glew")) {
    Write-Host "Downloading GLEW into third party folder glew ..."
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0-win32.zip", "..\..\third-party\glew-2.1.0-win32.zip")

    Invoke-WebRequest -Uri "https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0-win32.zip" -OutFile "..\..\third-party\glew-2.1.0-win32.zip"

    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping GLEW library into third-party\glew ..."
        cmd.exe /c 'tar -xf glew-2.1.0-win32.zip'
        Move-Item -Path glew-2.1.0 -Destination glew
        Remove-Item -Path glew-2.1.0-win32.zip
    Pop-Location
}

# glm
if (!(Test-Path "..\..\third-party\glm")) {
    Write-Host "Downloading GLM into third party folder glm ..."
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://github.com/g-truc/glm/releases/download/0.9.9.3/glm-0.9.9.3.zip", "..\..\third-party\glm-0.9.9.3.zip")

    Invoke-WebRequest -Uri "https://github.com/g-truc/glm/releases/download/0.9.9.3/glm-0.9.9.3.zip" -OutFile "..\..\third-party\glm-0.9.9.3.zip"

    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping GLM into third-party\glm ..."
        cmd.exe /c 'tar -xf glm-0.9.9.3.zip'
        Remove-Item -Path glm-0.9.9.3.zip
    Pop-Location
}

# tinyobjloader
if (!(Test-Path "..\..\third-party\tiny-obj-loader")) {
    Write-Host "Downloading Tiny OBJ Loader into third party folder tiny-obj-loader ..."
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://github.com/syoyo/tinyobjloader/archive/v1.4.1.zip", "..\..\third-party\tiny-obj-loader-v1.4.1.zip")
    Invoke-WebRequest -Uri "https://github.com/tinyobjloader/tinyobjloader/archive/refs/heads/master.zip" -OutFile "..\..\third-party\master.zip"
    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping Tiny OBJ Loader into third-party\tiny-obj-loader ..."
        cmd.exe /c 'tar -xf master.zip'
        Move-Item -Path tinyobjloader-master -Destination tiny-obj-loader
        Remove-Item -Path master.zip
    Pop-Location
}

# SDL2_image
if (!(Test-Path "..\..\third-party\sdl-image-windows")) {
    Write-Host "Downloading SDL Image Windows library into third party folder sdl-image-windows ..."
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.4-VC.zip", "..\..\third-party\SDL2_image-devel-2.0.4-VC.zip")
    Invoke-WebRequest -Uri "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.4-VC.zip" -OutFile "..\..\third-party\SDL2_image-devel-2.0.4-VC.zip"
    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping SDL Image Windows library into third-party\sdl-image-windows ..."
        cmd.exe /c 'tar -xf SDL2_image-devel-2.0.4-VC.zip'
        Move-Item -Path SDL2_image-2.0.4 -Destination sdl-image-windows
        Remove-Item -Path SDL2_image-devel-2.0.4-VC.zip
    Pop-Location
}

# Dear imgui
if (!(Test-Path "..\..\third-party\imgui")) {
    Write-Host "Downloading ImGui library into third party folder imgui ..."
   
    Invoke-WebRequest -Uri "https://github.com/ocornut/imgui/archive/refs/heads/docking.zip" -OutFile "..\..\third-party\docking.zip"
    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping ImGui library into third-party\imgui ..."
        cmd.exe /c 'tar -xf docking.zip'
        Move-Item -Path imgui-docking -Destination imgui
        Remove-Item -Path docking.zip
    Pop-Location
}

# NFD
if (!(Test-Path "..\..\third-party\nfd")) {
    Write-Host "Downloading NFD library into third party folder nfd ..."
   
    Invoke-WebRequest -Uri "https://github.com/mlabbe/nativefiledialog/archive/refs/tags/release_116.zip" -OutFile "..\..\third-party\nfd.zip"
    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping NFD library into third-party\nfd ..."
        cmd.exe /c 'tar -xf nfd.zip'
        Move-Item -Path nativefiledialog-release_116 -Destination nfd
        Remove-Item -Path nfd.zip
    Pop-Location
}

# vert,frag->spir-v compile
.\compile_shaders.ps1
