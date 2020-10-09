#!/usr/bin/env ruby

require 'erb'

class Grid
  def initialize(size)
    @cells = {}
    0.upto(size-1) do |ii|
      0.upto(size-1) do |jj|
        @cells["#{ii},#{jj}"] =
      end
    end
  end
end

class MazeGen
  def initialize()
    @wall_ii = 0
  end

  def next_ii
    i0 = @wall_ii
    @wall_ii += 1
    i0
  end

  def wall(xx, yy, rot=false)
    aa = rot ? 0 : (Math::PI/2)
    %Q{
    <include>
      <uri>model://brick_box_3x1x3</uri>
      <name>wall#{(next_ii)}</name>
      <pose>#{xx} #{yy} -2.0 0 0 #{aa}</pose>
    </include>
    }
  end

  def roll
    1 + rand(4)
  end

  def gen
    tpl = ERB.new(File.read("template.xml.erb"), trim_mode: "-<>")
    walls = []
    (-9).upto(9) do |ii|
      xx = ii * 3
      walls.push(wall(xx, -28, true))
      walls.push(wall(xx, 28, true))
      walls.push(wall(-28, xx, false))
      walls.push(wall(28, xx, false))
    end

    puts tpl.run(binding)
  end
end

mg = MazeGen.new
mg.gen
