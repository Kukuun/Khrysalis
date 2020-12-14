include "./Vendor/Premake/Premake_customization/solution_items.lua"

workspace "Khrysalis"
	architecture "x86_64"
	startproject "Khrysalis.Game"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	solution_items
	{
		--".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Khrysalis.Engine/Vendor/glfw/include"

group "Dependencies"
	include "Vendor/Premake"
	include "Khrysalis.Engine/Vendor/glfw"
group ""

include "Khrysalis.Engine"
include "Khrysalis.Game"
