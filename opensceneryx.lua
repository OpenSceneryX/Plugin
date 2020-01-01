require "zip"

-- This is a test case for basic LuaSocket functionality.

local http = require("socket.http")
--local https = require("ssl.https")

local body, code, headers, status = http.request("http://downloads.opensceneryx.com/repository/version.txt.zip")
--local body, code, headers, status = https.request("https://www.opensceneryx.com")
assert(body, code)

function OpenSceneryX()
  -- print("Complete: " .. response)
  local pos = 0
  pos = bubble(20, pos, "OpenSceneryX", "Version check complete: " .. code)
end

do_every_draw("OpenSceneryX()")
