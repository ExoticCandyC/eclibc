![alt text](media/banner.png)
<h1 align="center">ExoticCandy C Collection</h1>
<h3 align="center">Shared C library for the common needs of any C projects</h3>
<h4 align="center">Free and Open Source library, used in all ECC softwares</h4>


## Table of contents
🔸 [Brief description](#brief-description) \
🔸 [Dependencies](#dependencies) \
🔸 [Installation](#installation) \
🔸 [Documentation](#documentation)




## Brief description

**eclibc** is a C library, containing everyday use functions implemented in ANSI C language. This library can be compiled by most 16bit, 32bit and 64bit compilers, including:

**Computer targets:**<br />
🔹 GCC<br />
🔹 Clang<br />
🔹 TCC<br />
🔹 ICC<br />
🔹 MinGW32-GCC<br />

**Espressif targets:**<br />
🔸 xtensa-esp32-elf-gcc<br />
🔸 xtensa-esp32s2-elf-gcc<br />
🔸 xtensa-esp32s2-elf-gcc<br />

**Micochip© micro-processor units:**<br />
🔸 xc16-gcc<br />
🔸 xc32-gcc<br />


## Dependencies

💠️ git: used to clone the repository<br />
💠️ cmake: used to generate the make scripts<br />
💠️ A C compiler of choice<br />
<br />

## Installation

This package will soon be added to Arch AUR. But the standard installation process appliees to this library:

```bash
git clone --depth=1 https://github.com/ExoticCandyC/eclibc.git
cd eclibc
./configure
make
sudo make install
```

Please note that in order to use non-standard C compilers, you should manually introduce the compiler of choice to the CMakeLists.txt file.

Basically since the library is targeted for C89 (ANSI) standard, and compiled using heavy warning eliminations and pedantic syntax, this source code should basically be able to be compiled with any compiler that contains C89 standard functions.

As an example, Micochip© XC8 doesn't have an implementation of "free" and "malloc" functions. So it will produce errors during compilation.

The testings and developements are done on:<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1️⃣ Arch Linux and Gentoo Linux, on X86-64 architecture, using GCC, Clang and TCC compilers.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2️⃣ Arch Linux, using xtensa-esp32-elf-gcc compiler for ESP32 target.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3️⃣ Arch Linux, using Micochip© XC16 for PIC24FJ256GA106 micro-controller unit and dsPIC33CK256MP406 micro-controller unit.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4️⃣ Gentoo Linux on Raspberry Pi 4.<br />

Since the standard C protocols are being followed, and CMake is available on most platforms, one should easily be able to compile this library on any other target including FreeBSD, OpenBSD, OSX. 

As of August 2022, there are no plans to enable official support for Microsoft Windows®. But generally speaking, making the library compatible with MinGW32-GCC is a future goal and that would enable the unofficial support for Microsoft Windows® targets.

## Documentation

Wiki pages are planned to be added to the git repository, and an official website is planned to be generated that will host a begginer friendly C tutorial, beginner friendly C++ tutorial and a comprehensive guide on how to use eclibc in both C and C++<br />
Considering my tight schedule and the fact that this project is a solo project, there is no expected date for the aforementioned documentations.

