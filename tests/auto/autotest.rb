#!/usr/bin/ruby

require 'find'
require 'fileutils'

numtests = numpassed = numfailed = numskipped = 0
Find.find(FileUtils.pwd) do |path|
  if FileTest.file?(path) && FileTest.executable?(path) && !(path =~ /.rb$/)
    #puts path
    result = `#{path}`

    startedandfinished = (result =~ /Start testing/ && result =~ /Finished testing/)
    unless startedandfinished
      puts "Error in test #{path}: did not executed!"
    end

    passed, failed, skipped = result.match(/Totals: (\d+) passed, (\d+) failed, (\d+) skipped/).captures

    numpassed += passed.to_i
    numfailed += failed.to_i
    numskipped += skipped.to_i

    if passed.to_i + failed.to_i + skipped.to_i == 0
      puts "Error in test #{path}: no results available!"
    end

    if (failed.to_i > 0 || skipped.to_i > 0)
      puts "Test #{path} failed:\n" + result
    end

    numtests += 1
  end
end

puts "Summary: #{numtests} test blocks executed, #{numpassed} tests passed, #{numfailed} tests failed, #{numskipped} tests skipped."
