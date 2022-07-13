# OpenGL With SDL and ImGui

OpenGLとSDL、imguiを使ったグラフィクスエンジンです。  
Unityを触ってアプリを作る機会があったのですが、レンダリングについてわからないことが多すぎたので勉強も兼ねて自作することにしました。

# Development Environment

``Windows10 Home``  
``OpenGL 3.3``  
``VisualStudio 2022``  
``SDL2``  
``glew``  
``ImGui``  
``TinyObjLoader``

# DEMO
## ・Entity Component System  
![result](https://github.com/machumun/opengl-with-sdl-and-imgui/blob/main/engine_sample.gif)

## ・Deffered Lighting  
![result](https://github.com/machumun/opengl-with-sdl-and-imgui/blob/main/readme2.gif)

ハムスターのモデルは[こちらから](https://sketchfab.com/3d-models/hamtaro-7d195612e7814905aa1bfefd13b80be1)お借りしました。

## ・Bloom  

![result](https://github.com/machumun/opengl-with-sdl-and-imgui/blob/main/bloom.gif)


## ・UV Animation Plane  

![result](https://github.com/machumun/opengl-with-sdl-and-imgui/blob/material/uvanimation.gif)

テクスチャは[こちらから](http://obane.blog.shinobi.jp/)お借りしました。


# Feature And Plan

* クロスプラットフォーム
  * Windows10, macOS, iOS, Android, Webをビルドターゲットとして想定しているので、SDL2とOpenGLの組み合わせを用いています。
* 設計
  * ゲームを作る段階で困らないように、明快なAPI、抽象化を心がけています。
* 今後やりたいこと
  * ゲームシーンの保存
  * シャドウマップの実装。
  * バッチレンダリングの実装。
* 課題
  * モデルをレンダリングするプロセスが最善ではないので、設計を模索しています。

# Installation

## windows
① 必要な構成を``/engine/third-party``フォルダにインストールします。
```powershell
$ cd ${PROJECT_ROOT}/engine/build-tools/windows/

$ ./setup.ps1
```
  
②
Visual Studioで  ``${プロジェクトのルートフォルダ}/engine/build-tools/windows``フォルダを開き、CMakeターゲットビューからキャッシュを構成します。  

③　必要なライブラリを.exeフォルダと同じ階層にコピーして、アセットフォルダのシンボリックリンクを作成してセットアップは完了です。
```powershell
$ ./cmake-post-build.ps1
```
