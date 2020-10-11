workspace "Quantum"
	architecture "x64"
 
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Quantum/vendor/GLFW/include"
IncludeDir["Glad"] = "Quantum/vendor/Glad/include"
IncludeDir["ImGui"] = "Quantum/vendor/imgui"
IncludeDir["glm"] = "Quantum/vendor/glm"

group "Dependencies"
	include "Quantum/vendor/GLFW"
	include "Quantum/vendor/Glad"
	include "Quantum/vendor/imgui"
group ""

project "Quantum"
	location "Quantum"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "qupch.h"
	pchsource "Quantum/src/qupch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"QU_PLATFORM_WINDOWS",
			"QU_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "QU_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "QU_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QU_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Quantum/vendor/spdlog/include",
		"Quantum/src",
		"%{IncludeDir.glm}",
		"Quantum/vendor"
	}

	links
	{
		"Quantum"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"QU_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "QU_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "QU_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QU_DIST"
		runtime "Release"
		optimize "on"
