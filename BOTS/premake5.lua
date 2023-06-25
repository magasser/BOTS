project "BOTS"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    
    OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["glm"] = "vendor/glm"
    IncludeDir["glfw"] = "vendor/glfw/include"
    IncludeDir["glad"] = "vendor/glad/include"
    IncludeDir["spdlog"] = "vendor/spdlog/include"
    IncludeDir["stb"] = "vendor/stb"
    IncludeDir["ImGui"] = "vendor/ImGui"

    SourceDir = {}
    SourceDir["glfw"] = "vendor/glfw/src"
    SourceDir["glad"] = "vendor/glad/src"
    SourceDir["spdlog"] = "vendor/spdlog/src"
    SourceDir["stb"] = "vendor/stb"
    SourceDir["ImGui"] = "vendor/ImGui"

    targetdir ("bin/" .. OutputDir)
    objdir ("bin-int/" .. OutputDir)    

    pchheader "botspch.h"
    pchsource "src/botspch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",

        -- glfw
        "%{SourceDir.glfw}/glfw_config.h",
        "%{SourceDir.glfw}/context.c",
        "%{SourceDir.glfw}/init.c",
        "%{SourceDir.glfw}/input.c",
        "%{SourceDir.glfw}/monitor.c",
        "%{SourceDir.glfw}/vulkan.c",
        "%{SourceDir.glfw}/window.c",

        -- glad
        "%{SourceDir.glad}/glad.c",

        -- ImGui
        "%{SourceDir.ImGui}/*.h",
        "%{SourceDir.ImGui}/*.cpp",
        "%{SourceDir.ImGui}/backends/imgui_impl_glfw.h",
        "%{SourceDir.ImGui}/backends/imgui_impl_glfw.cpp",
        "%{SourceDir.ImGui}/backends/imgui_impl_opengl3.h",
        "%{SourceDir.ImGui}/backends/imgui_impl_opengl3.cpp",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs
    {
        "src",
        "%{IncludeDir.glm}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.stb}",
        "%{IncludeDir.ImGui}",
    }

    links
    {
		"opengl32.lib"
    }

    filter "files:vendor/**.c"
        flags { "NoPCH" }

    filter "files:vendor/**.cpp"
        flags { "NoPCH" }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "_GLFW_WIN32"
        }

        files
        {
            "%{SourceDir.glfw}/win32_init.c",
            "%{SourceDir.glfw}/win32_joystick.c",
            "%{SourceDir.glfw}/win32_monitor.c",
            "%{SourceDir.glfw}/win32_time.c",
            "%{SourceDir.glfw}/win32_thread.c",
            "%{SourceDir.glfw}/win32_window.c",
            "%{SourceDir.glfw}/wgl_context.c",
            "%{SourceDir.glfw}/egl_context.c",
            "%{SourceDir.glfw}/osmesa_context.c",
        }

    filter "configurations:Debug"
        defines "BOTS_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BOTS_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "BOTS_DIST"
        runtime "Release"
        optimize "on"