
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

  desc "Creates the Ubuntu package"
  task :deb do
    system "dpkg-buildpackage -rfakeroot"
  end
end

