project "GameLogic"
	kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ofpch.h"
	pchsource "src/ofpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}
    includedirs
	{
        "src",
        "src/ECF",
        "src/Data",
        "src/Misc",
        "src/Physics"
	}
    filter "system:windows"
        systemversion "latest"
	    defines
		{
		}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"



    filter "configurations:Release"
        runtime "Release"
        optimize "on"