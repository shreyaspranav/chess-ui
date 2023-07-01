workspace "chess-ui"
    architecture "x64"
    configurations { "Debug", "Release" }

project "chess-ui"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
    objdir "bin/obj"

    files {"src/**.cpp", "src/**.h"}
    
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        defines "RELEASE"
        symbols "off"
        optimize "on"
        runtime "Release"
    