# MusicVisualizer
Customizable shader from Yandex music on C++
![Анимация](https://github.com/user-attachments/assets/7e2fd75a-b2bb-4f2a-badd-cfa90c9d99a5)
*yes, I know. the GIF is very laggy and not very beautiful. 10mb is too small for that :\\*

# Build on windows:
>
> Requirement:
> vcpkg, CMake, Git, Visual Studio 2022

1. Open folder by Visual Studio 2022
2. Wait until VS execute the vcpkg commands and other stuff
3. Select **MusicVisualizer.exe** and **configuration** for build
4. Build by VS 2022 
4. add folder **ShaderCode** and **audio.mp3** to the path where the exe file was created.

# Build on Linux (Ubuntu 24.04.1):
## Install vcpkg
instruction for install [vcpkg](https://www.followchain.org/install-vcpkg-on-ubuntu/)
in Ubuntu

## vcpkg install and get DCMAKE_TOOLCHAIN_FILE
```PowerShell
vcpkg integrate install
vcpkg install
```
## Building
```PowerShell
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg.cmake (from:vcpkg integrate install)
make
./MusicVisualizer 
```


# TODO:
* Refactoring
* Render:
	- Fullscreen mode
	- Resolution scale
	- Vsync
* Audio:
	- Add playback
	- Select output device
	- Change volume
	- play\pause for playback
	- progress bar reading of file
* FFT:
	- Settings:
		- frequency range for low, medium and high frequencies
		- Sensitivity of the analysis for each frequency range
	- Rewrite the smoothing method
	- Maybe, use Hamming window?
* Other:
	- Multithreading to separate rendering, analysis, and audio playback
	- Optimization CPU load
	- Remove magic numbers
	- Using ImGui::console, not std cout
	- ~~Understand how to compile for windows and linux using only console\terminal~~
	 