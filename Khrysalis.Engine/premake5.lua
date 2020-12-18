project "Khrysalis.Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Binaries/Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "KalPch.h"
	pchsource "Source/KalPch.cpp"

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"Source",
		"Vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "KAL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KAL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "KAL_DIST"
		runtime "Release"
		optimize "on"
