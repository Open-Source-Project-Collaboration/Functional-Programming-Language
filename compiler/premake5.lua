project "compiler"
	kind "StaticLib"
	language "C"

	includedirs {
		"inc",
		(BASE_DIR .. "/compiler/inc")
	}

	files { "src/**.c" }