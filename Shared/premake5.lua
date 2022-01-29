require "clion"
include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "OpenFighter"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
group "Dependencies"
    include "vendor/premake"

group ""
	include "Sandbox"
	include "GameLogic"

project "raylib"
	kind "SharedLib"
	filter "configurations:Debug.DLL OR Release.DLL"
		defines {"BUILD_LIBTYPE_SHARED"}
		
	filter "configurations:Debug OR Release"
		kind "StaticLib"
		
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		links {"winmm"}
				
	filter{}
	
	location "build"
	language "C"
	targetdir "bin/%{cfg.buildcfg}"
	
	includedirs { "vendor/raylib/src", "vendor/raylib/src/external/glfw/include"}
	vpaths 
	{
		["Header Files"] = { "vendor/raylib/src/**.h"},
		["Source Files/*"] = {"vendor/raylib/src/**.c"},
	}
	files {"vendor/raylib/src/*.h", "vendor/raylib/src/*.c"}
	
	defines{"PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33"}