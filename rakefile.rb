task :prepare do
    Dir.chdir("extern") do
        unless File.exist?("catch/README.md")
            sh "git submodule update --init catch"
        end
    end
end

task :run
