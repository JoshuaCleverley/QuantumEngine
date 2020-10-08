workspace "Quantum"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Quantum"
	location "Quantum"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"QU_PLATFORM_WINDOWS",
			"QU_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "QU_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "QU_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "QU_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Quantum/src"
	}

	links
	{
		"Quantum"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"QU_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "QU_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "QU_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "QU_DIST"
		optimize "On"
