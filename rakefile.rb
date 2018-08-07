task :prepare do
    Dir.chdir("extern") do
        sh "git submodule update --init catch"
    end
end

task :run
