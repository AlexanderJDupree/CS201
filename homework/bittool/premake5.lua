-- premake5.lua
-- To generate GNU make files run 'premake5 gmake'

workspace "bittool"
    configurations { "Debug", "Release" }

project "bittool"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

    files { "**.h", "**.c" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

