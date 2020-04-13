// we are using this file as a proxy,
// if we don't do that, snapshots file ends up in
// lib/js/__tests__/__snapshots__
// which gets deleted on bsb -clean-world
require("../lib/js/__tests__/Test.bs.js");
