
namespace :release do
  desc "Uploads a new release to SourceForge Release System"
  task :upload do
    # find the file to be uploaded
    releases = FileList.new('wikt-*.tar.gz').to_a
    if releases.length() != 1 then
      puts "More than one release found. Aborting."
      exit
    end
    sh("sftp karelklic@frs.sf.net <<EOF\ncd uploads\nput #{releases.first}\nbye\nEOF")
    puts "Release uploaded, now continue to https://sourceforge.net/project/admin/editpackages.php?group_id=260074"
  end
end

namespace :web do
  desc "Uploads the local Wikt website to the internet server"
  task :upload do
    sh("cd web; /var/lib/gems/1.8/gems/jekyll-0.4.1/bin/jekyll")
    sh("rsync -avP -e ssh web/_site/ karelklic,wikt@web.sourceforge.net:htdocs/")
    puts "Website uploaded, now check wikt.sf.net"
  end

  desc "Runs a webserver with the local website on localhost:4000"
  task :run do
    sh("cd web; /var/lib/gems/1.8/gems/jekyll-0.4.1/bin/jekyll --server --auto")
  end
end

