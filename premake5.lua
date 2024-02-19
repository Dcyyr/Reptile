workspace "Reptile"
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
	IncludeDir["GLFW"]  = "Reptile/vendor/GLFW/include"
	IncludeDir["Glad"]  = "Reptile/vendor/Glad/include"
	IncludeDir["ImGui"] = "Reptile/vendor/imgui"
	IncludeDir["glm"]   = "Reptile/vendor/glm"


	group "Dependencies"

		include "Reptile/vendor/GLFW"
		include "Reptile/vendor/Glad"
		include "Reptile/vendor/imgui"

	group ""
	


	project "Reptile"
		location "Reptile"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime"on"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "rppch.h"
		pchsource "Reptile/src/rppch.cpp"
		

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl"
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
			"ImGui",
			"opengl32.lib"
		}
	

		filter "system:windows"
			systemversion "latest"

			defines
			{
				"RP_PLATFORM_WINDOWS",
				"RP_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
			}

	filter "configurations:Debug"
		defines "PR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PR_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "PR_DIST"
		runtime "Release"
		symbols "on"



project "Sandbox"
	location "Sandbox"	
	kind "ConsoleApp"
	staticruntime "on"
	cppdialect "C++17"
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
			"Reptile/src",
			"Reptile/vendor",
			"%{IncludeDir.glm}"
		}


		filter "system:windows"
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
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PR_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "PR_DIST"
		runtime "Release"
		symbols "on"
