workspace "Apocalypse"
    architecture "x64"
    startproject "Apocalypse"

    configurations
    {
        "Debug",
        "Release"
    }


-- Ouput directories for bin and intermediate files
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glad"] = "vendor/glad/include"
IncludeDir["glfw"] = "vendor/glfw/include"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb"] = "vendor/stb"


project "glfw"
    location "bin-int/project-files"
    kind "StaticLib"
    language "C"
    
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "vendor/glfw/include/GLFW/glfw3.h",
        "vendor/glfw/include/GLFW/glfw3native.h",
        "vendor/glfw/src/**.c",
        "vendor/glfw/src/**.h"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

        defines 
        { 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

        
project "glad"
    location "bin-int/project-files"
    kind "StaticLib"
    language "C"
    
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "vendor/glad/src/glad.c"
    }

    includedirs
    {
        "%{IncludeDir.glad}"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

        defines 
        { 
            "_GLAD_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"


project "Apocalypse"
    location "Apocalypse"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.vert",
        "%{prj.name}/**.frag"
    }

    includedirs
    {
        "%{IncludeDir.glad}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb}"
    }

    links
    {
        "glfw",
        "glad"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"

        defines
        {
            "DEBUG"
        }

    filter "configurations:Release"
        optimize "On"

        defines
        {
            "NDEBUG"
        }

