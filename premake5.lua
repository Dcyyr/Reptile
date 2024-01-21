workspace "Reptile"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "Reptile/vendor/GLFW/include"
	IncludeDir["Glad"] = "Reptile/vendor/Glad/include"

	include "Reptile/vendor/GLFW"
	include "Reptile/vendor/Glad"

	project "Reptile"
		location "Reptile"
		kind "SharedLib"
		language "C++"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "rppch.h"
		pchsource "Reptile/src/rppch.cpp"
		

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}"
			
		}

		links
		{
			"GLFW",
			"Glad",
			"opengl32.lib"
		}
	

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"RP_PLATFORM_WINDOWS",
				"RP_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}

	filter "configurations:Debug"
		defines "PR_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "PR_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Dist"
		defines "PR_DIST"
		buildoptions "/MD"
		symbols "On"



project "Sandbox"
	location "Sandbox"	
	kind "ConsoleApp"

	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Reptile/vendor/spdlog/include",
			"Reptile/src"
		}


		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

		defines
		{
			"RP_PLATFORM_WINDOWS"
		}

		links
		{
			"Reptile"
		}

	filter "configurations:Debug"
		defines "PR_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "PR_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Dist"
		defines "PR_DIST"
		buildoptions "/MD"
		symbols "On"
