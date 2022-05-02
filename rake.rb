namespace :std do
	task :prepare do
		sh "git submodule update --init --recursive"
	end
end