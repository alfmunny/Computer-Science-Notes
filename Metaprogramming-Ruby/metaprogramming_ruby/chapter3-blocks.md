## Basics

### Define a block 
* with curly braces
* do...end

```ruby
def a_method(a, b)
    a + yield(a, b)
end

a_method(1, 2) { |x, y| (x, y) * 3 } => 10
```

### current block

```ruby
def a_method
    return yield if block_given?
    'no block'
end

a_method    # => "no block"
a_method { "here's a block!" }    # => "here's a block"
```

## Flattening the scope

```ruby
my_var = "Success"
MyClass = Class.new do
    puts "#{my_var} in the class definition"
    define_method :my_method do
        puts "#{my_var} in the method!"
    end
end

MyClass.new.my_method  

# Success in the class definition
# Success in the mtrhod

```

## instance_eval()

To access **local variables** and **instance varaibles**.
Evalutes a block in the context of an object.

```ruby
class MyClass
    def initialize
        @v = 1
    end
end

v = 2
obj.instance_eval { @v = v }
obj.instance_eval { @v }
```

## instance_exec()

Similar to instance_eval, but allow you to pass arguments to the block

```ruby
class C
    def initialize
        @x, @y = 1, 2
    end
end

C.new.instance_exec(3) { |arg| (@x + @y) * arg }
```

## Clean Room

A Clean Room is an environment where you can evaluate your blocks, and it usually exposes a few usefule methods that the block can call.

```ruby
class CleanRoom
    def complex_caclation
    end

    def do_something
    end
end

clean_room = CleanRoom.new
clean_room.instance_eval do
    if complex_calculation > 0
        do_something
    end
end
```


## Callable Objects

### Proc Objects
A `Proc` is a block that has been turned into an object

```ruby
inc = Proc.new { |x| x + 1}
inc.call(2) # => 3
```

There are subtle differences between lambda(), proc(), Proc.new()
In most cases you can just use 
```ruby
dec = lambda { |x| x - 1}
dec.class   # => Proc
dec.call(2) # => 1
```

### & Operator

A block is like an additional, anonymous argument to a method.

There are two cases where **yield** is not enough

* You want to pass the block to anthor method
* You want to convert the block to a Proc

```ruby
def math(a, b)
    yield(a, b)
end

def teach_math(a, b, &operation)
    puts "Let's do the math:"
    puts math(a, b, &operation)
end

teach_math(2, 3) { |x, y| x + y}

# Let's do the math:
# 6
```

Convert the block to Proc, just drop the &

```ruby
def my_method(&the_proc)
    the_proc
end

p = my_method { |name| "Hello, #{name}!" }
puts p.class
puts p.call("Bill")

# Proc
# Hello Bill!
```

### Procs vs Lambda

#### return

Procs returns from the scope where itself was defined.

Lambda returns simple like a method.

#### arguments

Lambda tend to be les tolerant than procs when it comes to arguments

Procs dorps the excess arguments or assigns nil to the missing arguments

```ruby
p = Proc.new { |a, b| [a, b]}
p.call(1, 2, 3) # => [1, 2]
p.call(1) # => [1, nil]
```

## DSL
Example

```ruby redflag.rb
def event(name, &block) 
  @events[name] = block
end

def setup(&block)
  @setups << block
end

class Env
  attr_reader :sky_height, :mountains_height
end

Dir.glob('*events.rb').each do |file|
  @setups = []
  @events = {}
  load file
  @events.each_pair do |name, event|
    env = Env.new
    @setups .each do |setup|
      env.instance_eval &setup
      p env.sky_height
      p env.mountains_height
    end
    puts "ALERT: #{name}" if env.instance_eval &event
  end
end
```

```ruby
event "the sky is falling" do
  @sky_height < 300
end

event "it's getting closer" do
  @sky_height < @mountains_height
end

setup do
  puts "Setting up sky"
  @sky_height = 100
end

setup do
  puts "Setting up mountains"
  @mountains_height = 200
end
```
