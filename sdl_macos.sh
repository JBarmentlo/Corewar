#!bin/bash

if [ -d ~/.brew ]
then
	echo "\033[33mbrew already installed.\033[00m\n"
else
	echo "\033[31minstalling brew...\033[00m"
	rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc
	rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && export PATH=$HOME/.brew/bin:$PATH && echo "export PATH=$HOME/.brew/bin:$PATH" >> ~/.zshrc
	echo "\n"
fi
echo "\033[31mbrew update :\033[00m"
brew update
echo "\n"
if [ -d ~/.brew/Cellar/sdl2 ]
then
	echo "\033[33msdl2 already installed.\033[00m"
else
	echo "\033[31minstalling sdl2...\033[00m"
	brew install sdl2
	echo "\n"
fi
if [ -d ~/.brew/Cellar/sdl2_image ]
then
	echo "\033[33msdl2_image already installed.\033[00m"
else
	echo "\033[31minstalling sdl2_image...\033[00m"
	brew install sdl2_image
	echo "\n"
fi
if [ -d ~/.brew/Cellar/sdl2_ttf ]
then
	echo "\033[33msdl2_ttf already installed.\033[00m"
else
	echo "\033[31minstalling sdl2_ttf...\033[00m"
	brew install sdl2_ttf
fi
if [ -d includes/sdl_include ]
then
	rm -Rf includes/sdl_include/*
else
	mkdir includes/sdl_include
fi
echo "\n\033[32mcopy all brew .h in includes/sdl_include\033[00m"
cp ~/.brew/Cellar/sdl2/*/include/SDL2/*.h includes/sdl_include/
cp ~/.brew/Cellar/sdl2_image/*/include/SDL2/*.h includes/sdl_include/
cp ~/.brew/Cellar/sdl2_ttf/*/include/SDL2/*.h includes/sdl_include/
if [ -d srcs/sdl_src ]
then
	rm -Rf srcs/sdl_src/*
else
	mkdir srcs/sdl_src
fi
echo "\033[32mcopy all brew .a and .dylib in srcs/sdl_src\033[00m"
cp ~/.brew/Cellar/sdl2/*/lib/*.a srcs/sdl_src/
cp ~/.brew/Cellar/sdl2/*/lib/*.so srcs/sdl_src/
cp ~/.brew/Cellar/sdl2_image/*/lib/*.so srcs/sdl_src/
cp ~/.brew/Cellar/sdl2_image/*/lib/*.a srcs/sdl_src/
cp ~/.brew/Cellar/sdl2_ttf/*/lib/*.a srcs/sdl_src/
cp ~/.brew/Cellar/sdl2_ttf/*/lib/*.so srcs/sdl_src/

