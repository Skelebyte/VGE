-- premake5.lua
workspace ""
   configurations { "Debug", "Release" }

project "vge"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "**.hpp", "**.cpp", "**.h", "**.c" }

   links { "SDL3", "m" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"