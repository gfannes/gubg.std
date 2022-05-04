here = File.dirname(__FILE__)

namespace :std do
	task :prepare do
		Dir.chdir(here) do
			sh "git submodule update --init --recursive"
		end
	end
end