cmake_minimum_required(VERSION 3.20)
project(TarkvaraProjektI C)

set(CMAKE_C_STANDARD 11)

add_executable(TarkvaraProjektI
        cmd/main/main.c
        internal/app/digisim.c
        internal/app/funcs.h
        internal/pkg/boolean/boolean.h
        internal/pkg/boolean/boolean.c
        internal/pkg/cutils/panic.c
        internal/pkg/cutils/readtxt.c
        cmd/main/cli.c
        internal/app/service/output/output.c
        internal/app/service/update/update.c
        internal/app/service/parse/parse.c
        internal/app/service/create/create.c
        internal/app/service/simulate/simulate.c
        internal/app/service/parse/byindex.c
        internal/app/service/parse/byname.c)


