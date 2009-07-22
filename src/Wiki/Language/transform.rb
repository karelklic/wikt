#!/usr/bin/ruby
#
# Converts languages.yml data file to C++ include files with language data.
#
# Run without parameters. Recreates LanguagesGenerated.(h|cpp).inc files.
#
# This file is part of Wikt.
#
require "yaml"

languages = YAML::load_file("languages.yml")

header = <<END
/* This file is part of Wikt.
 *
 * Wikt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Wikt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Wikt. If not, see <http://www.gnu.org/licenses/>.
 */

// This file is automatically generated from languages.yml by transform.rb.

END

# Create LanguagesGenerated.h.inc from the loaded data.
File.open("LanguagesGenerated.h.inc", "w") do |file|
  file << header
  file << languages.keys.sort.join(",\n")
  file << ",\nUnknown // Always last!"
end

# Create LanguagesGenerated.cpp.inc from the loaded data.
File.open("LanguagesGenerated.cpp.inc", "w") do |file|
  file << header
  languages.each do |language, data|  
    file << "//-\n"
    
    if data.include?("code")
      if data["code"].is_a?(Array)
        # reverse makes QMap to sort entries properly,
        # but it does not work in all cases (maybe it works by accident)
        # must be done another way        
        data["code"].reverse.each do |code| 
          file << "_codeToType.insert(\"#{code}\", #{language});\n"
          file << "_typeToCode.insert(#{language}, \"#{code}\");\n"
        end
      else
        file << "_codeToType.insert(\"#{data["code"]}\", #{language});\n"
        file << "_typeToCode.insert(#{language}, \"#{data["code"]}\");\n"
      end
    end

    file << "_typeToInterwiki.insert(#{language}, fromWCharArray(L\"#{data["interwiki"]}\"));\n" if data.include?("interwiki")
    
    if data.include?("names")
      if data["names"].is_a?(Array)
        # reverse makes QMap to sort entries properly,
        # but it does not work in all cases (maybe it works by accident)
        # must be done another way        
        data["names"].reverse.each do |name|
          file << "_typeToNames.insert(#{language}, fromWCharArray(L\"#{name}\"));\n"
          file << "_nameToType.insert(fromWCharArray(L\"#{name}\"), #{language});\n"
        end
      else
        file << "_typeToNames.insert(#{language}, fromWCharArray(L\"#{data["names"]}\"));\n"
        file << "_nameToType.insert(fromWCharArray(L\"#{data["names"]}\"), #{language});\n"
      end
    end
  end
end
