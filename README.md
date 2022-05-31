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

## Bloom  

![result](https://github.com/machumun/opengl-with-sdl-and-imgui/blob/main/bloom.png)


# Feature And Plan

* クロスプラットフォーム
  * Windows10, macOS, iOS, Android, Webをビルドターゲットとして想定しているので、SDL2とOpenGLの組み合わせを用いています。
* 設計
  * 後々Vulkan(MoltenVK)に対応することを想定して抽象化をしています。
  * ゲームを作る段階で困らないように、明快なAPIであることを心がけています。
* 今後の予定
  * シャドウマップ、Defferdレンダリング、Bloom等ポストプロセスを予定しています。
* 課題
  * モデルをレンダリングするプロセスが最善ではないので、設計を模索しています。

# Installation

## windows
```powershell
$ cd ${PROJECT_ROOT}/engine/build-tools/windows/

$ ./setup.ps1
```

Visual Studioで  ``${プロジェクトのルートフォルダ}/engine/build-tools/windows``フォルダを開いてCMakeターゲットビューからデバッグビルドをします。

```powershell
$ ./cmake-post-build.ps1
```
