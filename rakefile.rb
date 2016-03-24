require(File.join(ENV['gubg'], 'shared'))
require('gubg/build/Executable')
include GUBG

task :default => :help
task :help do
    puts('declare: copy all headers to GUBG::shared')
    puts('define: build and copy libraries and executables to GUBG::shared')
end

task :declare do
    publish('src', pattern: '**/*.h*', dst: 'include')
    Dir.chdir(shared_dir('extern')) do
        git_clone('https://github.com/philsquared', 'catch')
    end
    publish(shared_dir('extern', 'catch', 'single_include'), pattern: '*.hpp', dst: 'include')
    publish('src', pattern: 'catch_runner.cpp', dst: 'source')
end

task :define => :declare

task :test do
    Rake::Task['ut:test'].invoke
end

namespace :ut do
    ut = nil
    task :setup => :declare do
        ut = Build::Executable.new('unit_tests')
        ut.add_define('DEBUG')
        ut.add_option('g')
        ut.add_include_path(shared_dir('include'))
        ut.add_sources(FileList.new('src/test/**/*_tests.cpp'))
        ut.add_sources(shared_file('source', 'catch_runner.cpp'))
        ut.add_sources(FileList.new('src/gubg/**/*.hpp'))
        ut.add_sources(FileList.new('src/gubg/**/*.h'))
    end
    task :test => :setup do
        ut.build
        options = %w[-a -d yes]
        options << '[ut]'
        ut.run(options)
    end
end
