workspace "chess-ui"
    architecture "x64"
    configurations { "Debug", "Release" }

include "deps/glfw"

project "chess-ui"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
    objdir "%{wks.location}/bin/obj"

    files {
        "src/**.cpp", "src/**.h"
    }

    includedirs {
        "deps/glfw/include",
        "deps/glad/include",
        "deps/glm/include",
        "deps/imgui"
    }

    links { "GLFW" }

    filter "system:windows"
        links { "gdi32", "user32", "kernel32" }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        defines "RELEASE"
        symbols "off"
        optimize "on"
        runtime "Release"
    