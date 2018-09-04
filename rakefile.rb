task :prepare do
    sh "git submodule update --init extern/catch2"
end

task :run
