task :prepare do
    sh "git submodule update --init extern/catch2"
end

task :run
task :proper do
    rm_rf "extern"
end
