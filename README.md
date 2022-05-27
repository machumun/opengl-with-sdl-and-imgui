# OpenGL With SDL and ImGui

OpenGLとSDL、imguiを使ったグラフィクスエンジンです。  
Unityを触ってアプリを作る機会があったのですが、レンダリングについてわからないことが多すぎたので勉強も兼ねて自作することにしました。

# Development Environment

``Windows10 Home``
``OpenGL 3.3``  
``VisualStudio 2022``

# DEMO

![result](https://github.com/machumun/opengl-with-sdl-and-imgui/blob/main/readme2.gif)

ハムスターのモデルは[こちらから](https://sketchfab.com/3d-models/hamtaro-7d195612e7814905aa1bfefd13b80be1)お借りしました。

# Feature And Plan

* クロスプラットフォーム
  * Windows10, macOS, iOS, Android, WebGLをビルドターゲットとして想定しているので、SDL2とOpenGLの組み合わせを用いています。
* 設計
  * 後々Vulkan(MoltenVK)パイプラインを実装することを想定して抽象化をしています。
  * ゲームを作る段階で困らないように、可能な限りカプセル化を意識しています。
  * 明快なAPIであることを心がけています。
* 今後の予定
  * シャドウマップ、Defferdレンダリング、Bloom等ポストプロセスを予定しています。

# Installation

## windows
```powershell
$ cd ${PROJECT_ROOT}/engine/build-tools/windows/

$ ./setup.ps1

$ ./cmake-post-build.ps1
```

上記を実行してから、Visual Studioで  ``${プロジェクトのルートフォルダ}/engine/build-tools/windows``フォルダを開いてデバッグビルドをします。
