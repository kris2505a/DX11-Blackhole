workspace "Voxel Engine"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

    project "GL_Voxel-Engine"
        kind "ConsoleApp"
        language "C++"
    
        targetdir ("bin/" .. outputdir .. "/")
        objdir ("obj/" .. outputdir .. "/")

        files {
            "src/**.hpp",
            "src/**.cpp"
        }

        includedirs {
            "thirdparty/GLFW/include",
            "thirdparty/GLEW/include"
        }

        libdirs {
            "thirdparty/GLFW/lib",
            "thirdparty/GLEW/lib"
        }

        links {
            "opengl32.lib",
            "winmm.lib",
            "gdi32.lib",
            "glew32s.lib",
            "glfw3.lib"
        }

        defines {
            "GLEW_STATIC"
        }

filter "configurations:Debug"
        symbols "On"

filter "configurations:Release"
        optimize "On"