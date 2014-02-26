-- -------------------------------------------------------------------------- --
--                                                                            --
--                                                        :::      ::::::::   --
--   premake4.lua                                       :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2014/01/02 16:48:37 by jzak              #+#    #+#             --
--   Updated: 2014/01/02 16:48:37 by jzak             ###   ########.fr       --
--                                                                            --
-- -------------------------------------------------------------------------- --

solution "Solutions"
	configurations	{ "Release", "Debug" }
	targetdir "bin"
	objdir "bin/obj"
	language "C"
	version = "0.1.1"
	inc = { "includes/" }

	-- Build option
	configuration "Release"
		buildoptions { "-Wall -Wextra -Werror" }
		flags { "Optimize" }
	configuration "Debug"
		buildoptions { "-Wall -Wextra" }
		flags { "Symbols" }

	-- libnboon
	project "nboon"
		kind "StaticLib"
		files { "srcs/**.c" }
		includedirs { inc }

	-- test
	project "test"
		kind "ConsoleApp"
		links { "nboon" }
		files "test/*.c"
		includedirs { inc }
