require_relative("../gubg.build/bootstrap.rb")
require("gubg/shared")

task :prepare do
    Dir.chdir(GUBG.mkdir("extern")) do
        sh "git clone https://github.com/catchorg/catch2" unless File.exist?("catch2/single_include/catch2/catch.hpp")
    end
end

task :run
task :proper do
    rm_rf "extern"
end
