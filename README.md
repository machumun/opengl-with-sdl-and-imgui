# OpenGL With SDL and ImGui

OpenGLとSDL、imguiを使った自作グラフィクスエンジンです。  Unityを触ってアプリを作る機会があったのですが、レンダリングについてわからないことが多すぎたので勉強も兼ねて自作することにしました。

# DEMO

![result](https://github.com/machumun/opengl-with-sdl-and-imgui/blob/main/readme2.gif)

ハムスターのモデルは[こちらから](https://sketchfab.com/3d-models/hamtaro-7d195612e7814905aa1bfefd13b80be1)お借りしました。

# Feature And Plan

レンダリングのパイプラインは後々Vulkanを実装することを想定して抽象化しています。

直近ではシャドウマップ、Defferdレンダリング、Bloom等ポストプロセスを実装予定です。

# Requirement

現在開発をしているツールのバージョンです。

``OpenGL 3.3``  ``VisualStudio 2022``


# Installation

## windows
```bash
cd ${プロジェクトのルートフォルダ}/engine/build-tools/windows/

$ ./setup.ps1

$ ./cmake-post-build.ps1
```

上記を実行してから、Visual Studioで  ``${プロジェクトのルートフォルダ}/engine/build-tools/windows``フォルダを開きます。
