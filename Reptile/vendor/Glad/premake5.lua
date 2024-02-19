project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/glad/glad.h",
        "include/KHR/khrplatform",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }
    
	filter "system:windows"
        systemversion "latest"
        
    filter "configurations:Debug"
		defines "PR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PR_RELEASE"
		runtime "Release"
		symbols "on"