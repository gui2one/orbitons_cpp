# Orbitons

Another attempt at building a small 3d engine ( currently openGL).
This is a personal / learning project mainly to "play" with C++

### Inspiration

As it turns out, this will be heavily inspired by "The Cherno" engine : Hazel.
His Youtube "Game engine" playlist is wonderfull. I learn a lot, even if, frankly , I wouldn't be able to come up with such nice and complicated code. But then again, I am here to learn.

### Rendering

That the part that is merely a copy of TheCherno's engine. ( plus some others bugs I guess :) )

OpenGL only ( for now ). But I am excited to try and add Direct3D ... this will be a first for me.

### Targets

Windows only for now. Even if I defenitely want to add other targets ( Linux mainly).

### Build

Relies heavily on vcpkg.exe.
when cloning this git repo, don't forget to use :

    git clone https://github.com/gui2one/orbitons_cpp --recurse-submodules

I am also using a manifest file, which is a new feature of vcpkg. Packages a defined in vcpkg.json.  
Pretty simple ... in theory.

ImGui is also included in the project as a git submodule in vendor/  
It is not correctly build with the base project though. I need to remedy that. i.e some Imgui source files are directly included in src/ directory.
