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
	IncludeDir["GLFW"] = "Reptile/vendor/GLFW/include"
	IncludeDir["Glad"] = "Reptile/vendor/Glad/include"
	IncludeDir["ImGui"] = "Reptile/vendor/imgui"
	IncludeDir["glm"] = "Reptile/vendor/glm"

	include "Reptile/vendor/GLFW"
	include "Reptile/vendor/Glad"
	include "Reptile/vendor/imgui"


	project "Reptile"
		location "Reptile"
		kind "SharedLib"
		language "C++"
		staticruntime"off"

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
			cppdialect "C++17"
			systemversion "latest"

			defines
			{
				"RP_PLATFORM_WINDOWS",
				"RP_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
			}

	filter "configurations:Debug"
		defines "PR_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PR_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "PR_DIST"
		runtime "Release"
		symbols "On"



project "Sandbox"
	location "Sandbox"	
	kind "ConsoleApp"
	staticruntime "off"

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
			"%{IncludeDir.glm}"
		}


		filter "system:windows"
			cppdialect "C++17"
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
		symbols "On"

	filter "configurations:Release"
		defines "PR_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "PR_DIST"
		runtime "Release"
		symbols "On"
