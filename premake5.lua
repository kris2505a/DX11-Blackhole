workspace "BlackHole"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }
	
	startproject "BlackHole"
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}" 

project "BlackHole"
    location "BlackHole"
    kind "consoleApp"
    language "C++"
    staticruntime "Off"
    
    entrypoint "mainCRTStartup"
    linkoptions { "/SUBSYSTEM:WINDOWS" }


    targetdir("Binaries/" .. outputDir .. "/%{prj.name}")
    objdir("Intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
    }

    libdirs {
        
    }
    
    links {
        "d3d11.lib",
        "dxgi.lib",
        "d3dcompiler.lib",
		"winmm.lib",
		"gdi32.lib",
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

    defines {
	
    }

    filter "configurations:Debug" 
        defines {"DEBUG"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {"RELEASE"}
        runtime "Release"
        optimize "On"

	