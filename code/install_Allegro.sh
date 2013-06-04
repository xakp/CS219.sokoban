#!/bin/sh

# update
sudo apt-get update

# Required Dependencies
sudo apt-get install build-essential git cmake xorg-dev libgl1-mesa-dev libglu1-mesa-dev cowsay

# Optionnal dependencies
sudo apt-get install libpng12-dev libcurl4-openssl-dev libfreetype6-dev libjpeg-dev libvorbis-dev libopenal-dev libphysfs-dev libgtk2.0-dev libasound2-dev libpulse-dev libflac-dev libdumb1-dev

# Documentation Dependencies
# sudo apt-get install exuberant-ctags dvi2ps texlive-base latex2html pandoc

# download allego
git clone git://git.code.sf.net/p/alleg/allegro

# prepare cmake
cd allegro
git checkout 5.0
mkdir build; cd build

# running cmake
ccmake -DCMAKE_INSTALL_PREFIX=/usr ..

# compile allegro
make

#install allegro
sudo make install

clear

cowsay "Allegro is installed"
