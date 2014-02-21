

PATH=/home/denis/opt/mxe/usr/bin:$PATH
PKG_CONFIG_PATH=/home/denis/opt/mxe/usr/i686-pc-mingw32/lib/pkgconfig


mkdir win32-build
mkdir win32

cd win32-build

/home/denis/opt/mxe/usr/i686-pc-mingw32.static/qt/bin/qmake ..
make

make clean

mv release/* ../win32/

cd ..

rm -rf win32-build/
