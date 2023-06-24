project "BOTS"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. OutputDir)
    objdir ("bin-int/" .. OutputDir)    

    pchheader "botspch.h"
    pchsource "src/botspch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "src",
        "%{IncludeDir.glm}"
    }

    filter "system:windows"
        systemversion "latest"

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