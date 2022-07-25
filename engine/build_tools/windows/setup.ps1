$ErrorActionPreference = "Stop"


if (!(Test-Path "..\..\third_party")) {
    Push-Location -Path "..\..\"
        New-Item -ItemType Directory -Path "third_party"
    Pop-Location
}


# sdl
if (!(Test-Path "..\..\third_party\sdl-windows")) {
    Write-Host "Downloading SDL Windows Dev library into third party folder sdl-windows ..."
    
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://www.libsdl.org/release/SDL2-devel-2.0.9-VC.zip", "..\..\third_party\SDL2-devel-2.0.9-VC.zip")

    Invoke-WebRequest -Uri "https://www.libsdl.org/release/SDL2-devel-2.0.9-VC.zip" -OutFile "..\..\third_party\SDL2-devel-2.0.9-VC.zip"

    Push-Location -Path "..\..\third_party"
        Write-Host "Unzipping SDL Windows Dev library into third_party\sdl-windows ..."
        cmd.exe /c 'tar -xf SDL2-devel-2.0.9-VC.zip'
        Move-Item -Path SDL2-2.0.9 -Destination sdl-windows
        Remove-Item -Path SDL2-devel-2.0.9-VC.zip
    Pop-Location
}

# glew
if (!(Test-Path "..\..\third_party\glew")) {
    Write-Host "Downloading GLEW into third party folder glew ..."
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0-win32.zip", "..\..\third_party\glew-2.1.0-win32.zip")

    Invoke-WebRequest -Uri "https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0-win32.zip" -OutFile "..\..\third_party\glew-2.1.0-win32.zip"

    Push-Location -Path "..\..\third_party"
        Write-Host "Unzipping GLEW library into third_party\glew ..."
        cmd.exe /c 'tar -xf glew-2.1.0-win32.zip'
        Move-Item -Path glew-2.1.0 -Destination glew
        Remove-Item -Path glew-2.1.0-win32.zip
    Pop-Location
}

# glm
if (!(Test-Path "..\..\third_party\glm")) {
    Write-Host "Downloading GLM into third party folder glm ..."
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://github.com/g-truc/glm/releases/download/0.9.9.3/glm-0.9.9.3.zip", "..\..\third_party\glm-0.9.9.3.zip")

    Invoke-WebRequest -Uri "https://github.com/g-truc/glm/releases/download/0.9.9.3/glm-0.9.9.3.zip" -OutFile "..\..\third_party\glm-0.9.9.3.zip"

    Push-Location -Path "..\..\third_party"
        Write-Host "Unzipping GLM into third_party\glm ..."
        cmd.exe /c 'tar -xf glm-0.9.9.3.zip'
        Remove-Item -Path glm-0.9.9.3.zip
    Pop-Location
}

# tinyobjloader
if (!(Test-Path "..\..\third_party\tiny-obj-loader")) {
    Write-Host "Downloading Tiny OBJ Loader into third party folder tiny-obj-loader ..."
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://github.com/syoyo/tinyobjloader/archive/v1.4.1.zip", "..\..\third_party\tiny-obj-loader-v1.4.1.zip")
    Invoke-WebRequest -Uri "https://github.com/tinyobjloader/tinyobjloader/archive/refs/heads/master.zip" -OutFile "..\..\third_party\master.zip"
    Push-Location -Path "..\..\third_party"
        Write-Host "Unzipping Tiny OBJ Loader into third_party\tiny-obj-loader ..."
        cmd.exe /c 'tar -xf master.zip'
        Move-Item -Path tinyobjloader-master -Destination tiny-obj-loader
        Remove-Item -Path master.zip
    Pop-Location
}

# SDL2_image
if (!(Test-Path "..\..\third_party\sdl-image-windows")) {
    Write-Host "Downloading SDL Image Windows library into third party folder sdl-image-windows ..."
    # $WebClient = New-Object System.Net.WebClient
    # $WebClient.DownloadFile("https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.4-VC.zip", "..\..\third_party\SDL2_image-devel-2.0.4-VC.zip")
    Invoke-WebRequest -Uri "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.4-VC.zip" -OutFile "..\..\third_party\SDL2_image-devel-2.0.4-VC.zip"
    Push-Location -Path "..\..\third_party"
        Write-Host "Unzipping SDL Image Windows library into third_party\sdl-image-windows ..."
        cmd.exe /c 'tar -xf SDL2_image-devel-2.0.4-VC.zip'
        Move-Item -Path SDL2_image-2.0.4 -Destination sdl-image-windows
        Remove-Item -Path SDL2_image-devel-2.0.4-VC.zip
    Pop-Location
}

# Dear imgui
if (!(Test-Path "..\..\third_party\imgui")) {
    Write-Host "Downloading ImGui library into third party folder imgui ..."
   
    Invoke-WebRequest -Uri "https://github.com/ocornut/imgui/archive/refs/heads/docking.zip" -OutFile "..\..\third_party\docking.zip"
    Push-Location -Path "..\..\third_party"
        Write-Host "Unzipping ImGui library into third_party\imgui ..."
        cmd.exe /c 'tar -xf docking.zip'
        Move-Item -Path imgui-docking -Destination imgui
        Remove-Item -Path docking.zip
    Pop-Location
}

# NFD
# if (!(Test-Path "..\..\third_party\nfd")) {
#     Write-Host "Downloading native file dialog library into third party folder nfd ..."
   
#     Invoke-WebRequest -Uri "https://github.com/mlabbe/nativefiledialog/archive/refs/tags/release_116.zip" -OutFile "..\..\third_party\nfd.zip"
#     Push-Location -Path "..\..\third_party"
#         Write-Host "Unzipping native file dialog library into third_party\nfd ..."
#         cmd.exe /c 'tar -xf nfd.zip'
#         Move-Item -Path nativefiledialog-release_116 -Destination nfd
#         Remove-Item -Path nfd.zip
#     Pop-Location
# }

#cerial
if (!(Test-Path "..\..\third_party\cereal")) {
    Write-Host "Downloading cereal into third party folder cereal ..."
   
    Invoke-WebRequest -Uri "https://github.com/USCiLab/cereal/archive/v1.3.2.zip" -OutFile "..\..\third_party\cereal.zip"
    Push-Location -Path "..\..\third_party"
        Write-Host "Unzipping cereal library into third_party\cereal ..."
        cmd.exe /c 'tar -xf cereal.zip'
        Move-Item -Path "cereal-1.3.2" -Destination cereal
        Remove-Item -Path cereal.zip
    Pop-Location
}


# ImGui FileBrowser Addon
if (!(Test-Path "..\..\third_party\imgui_addons")) {
    Write-Host "Downloading Imgui addons library into third party folder imgui_addons ..."
   
    Invoke-WebRequest -Uri "https://github.com/gallickgunner/ImGui-Addons/archive/refs/heads/master.zip" -OutFile "..\..\third_party\imgui-addons.zip"
    Push-Location -Path "..\..\third_party"
        Write-Host "Unzipping native file dialog library into third_party\nfd ..."
        cmd.exe /c 'tar -xf imgui-addons.zip'
        Move-Item -Path ImGui-Addons-master -Destination imgui_addons
        Remove-Item -Path imgui-addons.zip
    Pop-Location
}

# vert,frag->spir-v compile
.\compile_shaders.ps1
