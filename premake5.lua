workspace "fpl"
	configurations { "debug", "release" }

	toolset "clang"
	cdialect "C89"
	warnings "Extra"

	BASE_DIR = path.getabsolute(".")
	targetdir (BASE_DIR .. "/bin")
	objdir (BASE_DIR .. "/bin/int")

	filter "configurations:debug"
		symbols "on"

	filter "configurations:release"
		defines { "NDEBUG" }
		optimize "on"

include "vm"
include "compiler"
include "cli"