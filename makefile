src = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/*.c) $(wildcard src/**/*.c)
out = bin
args = 
buildArgs = 
debugArgs = 
libs = 
includeFolder = include
libsFolder = libs

exe = exe
debugExe = debugExe

make: build

build:
	g++ $(src) -o $(out)/$(exe) $(args) $(buildArgs) -I$(includeFolder) -L$(libsFolder) $(libs)

debug:
	g++ $(src) -o $(out)/$(debugExe) $(args) $(debugArgs) -I$(includeFolder) -L$(libsFolder) $(libs)

runBuild:
	cd ./$(out); ./$(exe);

runDebug:
	cd ./$(out); ./$(debugExe) prog;
