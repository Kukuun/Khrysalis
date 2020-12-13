project "Khrysalis.Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Bin-Int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Khrysalis.Engine/Source",
		"%{wks.location}/Khrysalis.Engine/Vendor/spdlog/include",
		"%{wks.location}/Khrysalis.Engine/Vendor"
	}

	links
	{
		"Khrysalis.Engine"
	}

	filter "system:windows"
		systemversion "latest"

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
