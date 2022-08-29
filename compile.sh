g++ -o example.exe -isystem `root-config --incdir` -g `root-config --cflags` -Wall `root-config --glibs` `root-config --ldflags` example.cxx
