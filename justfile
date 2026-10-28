cc := "clang"
cflags := "-Wall -Wextra -O2 -Iinclude"
src_files := `find src -name '*.c'`
target := "bin/http_server"

default: build

build:
    @mkdir -p bin
    {{cc}} {{cflags}} {{src_files}} -o {{target}}
    @echo "Build complete: {{target}}"

run: build
    ./{{target}}

clean:
    rm -rf bin/*
    @echo "Cleaned bin directory"

rebuild: clean build
