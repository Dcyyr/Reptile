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

	include "Reptile/vendor/GLFW"

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
			"%{IncludeDir.GLFW}"
			
		}

		links
		{
			"GLFW",
			"opengl32.lib"
		}
	

		filter "system:windows"
			cppdialect "C++14"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"RP_PLATFORM_WINDOWS",
				"RP_BUILD_DLL"
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}

	filter "configurations:Debug"
		defines "PR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PR_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "PR_DIST"
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
			cppdialect "C++14"
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
		symbols "On"

	filter "configurations:Release"
		defines "PR_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "PR_DIST"
		symbols "On"
