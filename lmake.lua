lmake_compatibility_version(1)

src_files = lmake_find("src/*c");
link_files = lmake_find("bin/*.o");
function build()
    lmake_set_compiler("/bin/gcc")
    lmake_set_compiler_flags("-pthread -Wall -Iinclude")
    lmake_set_compiler_out("bin/%.o")
    lmake_compile("src/main.c src/func.c src/clock.c src/timer.c src/p_gen.c src/scheduler.c src/tree.c src/queue.c")
    lmake_set_linker("/bin/gcc")
    lmake_set_linker_flags("-pthread")
    lmake_set_linker_out("seso")
    lmake_link("bin/main.c.o bin/func.c.o bin/clock.c.o bin/timer.c.o bin/p_gen.c.o bin/scheduler.c.o bin/tree.c.o bin/queue.c.o")
end

function clean()
    lmake_exec("rm -rf bin/main.c.o bin/func.c.o bin/clock.c.o bin/timer.c.o bin/p_gen.c.o bin/scheduler.c.o bin/tree.c.o bin/queue.c.o")
end

function run()
    lmake_exec("seso")
end
