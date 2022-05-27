# OpenGL With SDL and ImGui

OpenGLとSDL、imguiを使ったグラフィクスエンジンです。  
Unityを触ってアプリを作る機会があったのですが、レンダリングについてわからないことが多すぎたので勉強も兼ねて自作することにしました。

# DEMO

![result](https://github.com/machumun/opengl-with-sdl-and-imgui/blob/main/readme2.gif)

ハムスターのモデルは[こちらから](https://sketchfab.com/3d-models/hamtaro-7d195612e7814905aa1bfefd13b80be1)お借りしました。

# Feature And Plan

* クロスプラットフォーム化
  * SDL2とOpenGLの組み合わせでWindows10, macOS, iOS, Android, WebGLをターゲットにビルドできるようにする予定です。
  * レンダリングのパイプラインは後々Vulkanを実装することを想定して抽象化しています。  
* 設計
  * ゲームを作る段階で困らないように、可能な限りカプセル化を行い、明快なAPIになるように作成しています。 
* 実装予定
  * 直近ではシャドウマップ、Defferdレンダリング、Bloom等ポストプロセスを実装予定です。

# Requirement

現在デバッグをしているツールのバージョンです。

``OpenGL 3.3``  
``VisualStudio 2022``

# Installation

## windows
```powershell
$ cd ${プロジェクトのルートフォルダ}/engine/build-tools/windows/

$ ./setup.ps1

$ ./cmake-post-build.ps1
```

上記を実行してから、Visual Studioで  ``${プロジェクトのルートフォルダ}/engine/build-tools/windows``フォルダを開いてデバッグビルドをします。
