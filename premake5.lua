workspace "Fountainhead"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buidcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Fountainhead/vendor/GLFW/include"
IncludeDir["Glad"] = "Fountainhead/vendor/Glad/include"
IncludeDir["ImGui"] = "Fountainhead/vendor/imgui"
IncludeDir["glm"] = "Fountainhead/vendor/glm"
IncludeDir["stb_image"] = "Fountainhead/vendor/stb_image"

include "Fountainhead/vendor/GLFW"
include "Fountainhead/vendor/Glad"
include "Fountainhead/vendor/imgui"


project "Fountainhead"
	location "Fountainhead"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fhpch.h"
	pchsource "Fountainhead/src/fhpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNING"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FH_PLATFORM_WINDOWS",
			"FH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FH_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Fountainhead/vendor/spdlog/include",
		"Fountainhead/src",
		"Fountainhead/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Fountainhead"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FH_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DIST"
		runtime "Release"
		optimize "on"