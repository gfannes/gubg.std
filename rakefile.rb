require_relative("../gubg.build/bootstrap.rb")
require("gubg/shared")

task :prepare do
  Rake.sh("git submodule update --init --checkout --recursive") unless File.exist?("extern/catch2/single_include/catch2/catch.hpp")
end

task :run
task :clean
task :proper do
    rm_rf "extern"
end
