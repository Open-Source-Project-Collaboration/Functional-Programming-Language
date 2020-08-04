project "cli"
	kind "ConsoleApp"
	language "C"
	targetname "fpl"

	includedirs {
		"inc",
		(BASE_DIR .. "/compiler/inc"),
		(BASE_DIR .. "/vm/inc")
	}

	files { "src/**.c" }

	links { "compiler", "vm" }