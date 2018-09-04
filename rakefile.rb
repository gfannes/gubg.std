task :prepare do
    Dir.chdir("extern") do
        sh "git submodule update --init extern/catch2"
    end
end

task :run
