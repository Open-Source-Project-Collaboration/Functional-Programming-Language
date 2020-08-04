project "vm"
	kind "StaticLib"
	language "C"

	includedirs { "inc" }
	files { "src/**.c" }