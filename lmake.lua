lmake_compatibility_version(1)

src_files = lmake_find("src/*c");
link_files = lmake_find("build/*.o");
function build()
    lmake_set_compiler("/bin/gcc")
    lmake_set_compiler_flags("-pthread -Wall -Iinclude -DDEBUG")
    lmake_set_compiler_out("build/%.o")
    lmake_compile("src/main.c src/func.c src/clock.c src/timer.c src/loader.c src/scheduler.c src/tree.c")
    lmake_set_linker("/bin/gcc")
    lmake_set_linker_flags("-pthread")
    lmake_set_linker_out("seso")
    lmake_link("build/main.c.o build/func.c.o build/clock.c.o build/timer.c.o build/loader.c.o build/scheduler.c.o build/tree.c.o")
end

function clean()
    lmake_exec("rm -rf build/main.c.o build/func.c.o build/clock.c.o build/timer.c.o build/loader.c.o build/scheduler.c.o build/tree.c.o")
end

function run()
    lmake_exec("seso")
end
