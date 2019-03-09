-- premake5.lua
-- To generate GNU make files run 'premake5 gmake'
-- Author: Alexander DuPree

workspace "bigfib"
    configurations { "ADDC_ASM_ADC", "ADDC_C", "ADDC_ASM_JMP" }
    platforms { "release", "debug", "profile" }

    if _ACTION == "clean" then
        os.rmdir("bin/")
        os.rmdir("gmake/")
        os.rmdir("gmake2/")
    end

    local project_action = "UNDEFINED"
    if _ACTION ~= nill then project_action = _ACTION end

    location(project_action)

    filter "configurations:ADDC_C"
        defines { "ADDC_C" }

    filter "configurations:ADDC_ASM_JMP"
        defines { "ADDC_ASM_JMP" }

    filter "configurations:ADDC_ASM_ADC"
        defines { "ADDC_ASM_ADC" }

    filter "platforms:debug"
        symbols "On"

    filter "platforms:profile"
        buildoptions "-fno-inline -pg"

    filter "platforms:release or profile"
        buildoptions "-O4"

    filter {} -- close filter

project "bigint"
    kind "StaticLib"
    language "C"
    targetdir "bin/lib/"
    targetname "bigint_%{cfg.buildcfg}"
    buildoptions { "-Wall -Wextra -Werror" }

    local include = "include/"
    local source  = "src/"

    files { source .. "bigint.c" }
    includedirs(include)

project "bigadd"
    kind "ConsoleApp"
    language "C"
    links "bigint"
    targetdir "bin/"
    targetname "bigadd_%{cfg.buildcfg}"

    local source  = "src/"
    local include = "include/"

    files { source .. "bigadd.c" }
    includedirs(include)

project "bigfib"
    kind "ConsoleApp"
    language "C"
    links "bigint"
    targetdir "bin/"
    targetname "bigfib_%{cfg.buildcfg}"

    local source  = "src/"
    local include = "include/"

    files { source .. "bigfib.c" }
    includedirs(include)

project "unit"
    kind "ConsoleApp"
    language "C"
    links "bigint"
    targetdir "bin/"
    targetname "unit_%{cfg.buildcfg}"

    local source  = "src/"
    local include = "include/"

    files { source .. "unit.c" }
    includedirs(include)

