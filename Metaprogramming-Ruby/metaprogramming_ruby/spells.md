# The Spells

## Argument Array

```ruby
def my_method(*args)
  args.map { |arg| arg.reverse }
end

puts my_method('abc', 'xyz', '123') # => ["cba", "zyx", "321"]
```


## Around Alias

```ruby
class String
  alias_method :old_reverse, :reverse

  def reverse
    "x#{old_reverse}x"
  end
end

puts "abc".reverse # => xcbax
```

## Class Extension

```ruby
class C; end

module M
  def my_method
    'a class method'
  end
end

class << C
  include M
end

C.my_method # => "a class method"
```

## Class Extension Mixin

```ruby
module M
  def self.included(base)
    base.extend(ClassMethods)
  end

  module ClassMethods
    def my_method
      'a class method'
    end
  end
end

class C 
  include M
end

C.my_method # => 'a class method'

```

## Class Instance Variable

```ruby
class C
  @my_class_instance_variable = "some value"

  def self.class_attribute
    @my_class_instance_variable
  end
end

C.class_attribute
```

## Class Macro

```ruby
class C; end

class << C
  def my_macro(arg)
    "my_macro(#{arg}) called"
  end
end

class C
  my_macro :x # => "my_macro(x) called"
end
```

## Clean Room

```ruby
class CleanRoom
  def a_useful_method(x); x ** 2; end
end

CleanRoom.new.instance_eval { a_useful_method(3) }
```

## Context Probe

```ruby
class C
  def initialize
    @x = "a private instance variable"
  end
end

obj = C.new
obj.instance_eval { @x }
```


## Deferred Evaluation

```ruby
class C
  def store(&block)
    @my_code_capsule = block
  end

  def execute
    @my_code_capsule.call
  end
end

obj = C.new
obj.store { $X = 1 }
$X = 0

obj.execute
$X # => 1
```

## Dynamic Method

```ruby
class C
end

C.class_eval do
  define_method :my_method do
    "a dynamic method"
  end
end

obj = C.new
obj.my_method
```

## Lazy Instance Variable

```ruby
class C
  def attribute
    @attribute ||= "some value"
  end
end

obj = C.new
obj.attribute
```

## Object Extension

```ruby
obj = Obj.new
module M
  def my_method
  end
end

class << obj
  include M
end

obj.my_method

```
## Singleton Method

```ruby
obj = "abc"

class << obj
  def my_singleton_method
    'x'
  end
end

obj.my_singleton_method
```
## String of Code

```ruby
my_string_of_code = "1 + 1"
eval(my_string_of_code)
```

## Self Yield

```ruby
obj = "abc"

class << obj
  def my_singleton_method
    "x"
  end
end

obj.my_singleton_method #=> "x"
```
