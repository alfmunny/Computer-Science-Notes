## A Challenge

```ruby
class Person
  include CheckedAttributes

  attr_checked :age do |v|
    v >= 18
  end
end

me = Person.new
me.age = 39   # OK
me.age = 12   # Execption!
```

Implement `CheckedAttributes` and `attr_checked`.

Five stop to implement:

1. Write a Kernel method named `add_checked_attribute()` using eval() to add a super-simple validated attribute to a class
2. Refacotr `add_checked_attribtues()` to remove eval()
3. Validate attributes through a block
4. Change `add_checked_attribute()` to a Class Macro named `attr_checked()` that's available to all classes.
5. Write a module adding `attr_checked()` to selected classes through a hook.

To implement these two methods, you need to learn two things:

1. eval()
2. Hook Method


## Kernel#eval

Now let me introduce you to the third member of the *eval family - a Kernel Method that's simply named eval().
Instead of a block, it takes a string that contains Ruby code - a String of Code for short. 
Kernel#eval() executes the code in the string and returns the result.

```ruby
array = [10, 20]
element = 30
eval("array << element")    # => [10, 20, 30]

```

### Strings of Code vs. Blocks

* String of Code: eval()
* Block: class_eval(), instance_eval()

Although it's true that eval() always requires a string, instance_eval() and class_eval() can take either a String of Code or a Block.

```ruby
array = ['a', 'b', 'c']
x = 'd'
array.instance_eval "self[i] = x"
array   # => ["a", "b", "c"]
```

### Code Injection

Write an array explorer

```ruby
def explore_array(method)
    code = "['a', 'b', 'c'].#{method}"
    puts "Evaluating: #{code}"
    eval code
end
```
**find_index("b")**
Evaluating: ['a','b','c'].find_index("b")
1

**map! { |e| e.next }**
Evaluating: ['a','b','c'].map! { |e| e.next }
["b", "c", "d"]

But it is dangerous, because anyone can inject any code and excute it on your machine.

**object_id; Dir.glob("*")**
["a", "b", "c"].object_id; Dir.glob('*') => [your own private information here]


## Quiz: Checked Attributes(Step 1)

First step of the plan, we have to write an eval()-based method that adds a super-simple checked attribute to a class.
Let's call this method `add_checked_attribute()`. It should generate a reader method and a writer method.

Write a test suite.

```ruby
require 'test/unit'
class Person; end

class TestCheckedAttribute < Test::Unit::TestCase
  def setup
    add_checked_attribute(Person, :age)
    @bob = Person.new
  end

  def test_accepts_valid_values
    @bob.age = 20
    assert_equal 20, @bob.age
  end
  
  def test_refuses_nil_values
    assert_raises RuntimeError, 'Invalid attribute' do
      @bob.age = nil
    end
  end

  def test_refuses_false_values
    assert_raises RuntimeError, 'Invalid attributs' do
      @bob.age = false
    end
  end
end
```

The method to implement
```ruby
def add_checked_attribute(clazz, attribute)
  # ...
end
```

Quick Solution

```ruby
def add_checked_attribute(clazz, attribute)
  eval "
    class #{clazz}
      def #{attribute}=(value)
        raise 'Invalid attribute' unless value
        @#{attribute} = value
      end

      def #{attribute}()
        @#{attribute}
      end
    end
  "
end
```

Example when you call `add_checked_attribute` to class `String`.

```ruby
add_checked_attribute(String, :my_attr)

class String

  def my_attr=(value)
    raise 'Invalid attribute' unless value
    @my_attr = value
  end

  def my_attr
    @my_attr
  end 
end
```

## Quiz: Checked Attributes (Step 2)

Now we want to refactor the `add_checked_attribute()` and replace `eval()` with regular Ruby methods.

Use `class_eval` to get into the class instead of *Open Class*.

Use `define_method` instead of `def`.

Use `Object#instance_variable_get()` and `Object#instance_variable_set()` to manipulate instance variables.

```ruby
def add_checked_attribute(clazz, attribute)
  clazz.class_eval do
    define_method "#{attribute}=" do |value|
      raise 'Invalid attribute' unless value
      instance_variable_set("#{attribute}", value)
    end
    define_method attribute do
      instance_variable_get "@#{attribute}"
    end
  end
end
```

## Quiz: Checked Attributes (Step 3)

Support flexible validation through a block.

```ruby
class TestChekedAttribute < Test::Unit::TestCase
  def setup
    add_checked_attribute(Person, :age) { |v| v >= 18)
    @bob = Person.new
  end
  
  def test_accepts_valid_values
  end
  
  def test_refuses_invalid_values
    assert_raises RuntimeError, 'Invalid attribute' do
      @bob.age = 17
    end
  end
end

def add_checked_attribute(claszz, attribute, &validation)
  # ... (The code here doesn't pass the test. Modify it.    
end
```

Quick Solution

```ruby
def add_checked_attribute(clazz, attribubte, &validation)
  clazz.class_eval do
    define_method "#{attribute}=" do |value|
      raise 'Invalid attribute' unless validation.call(value)
      instance_variable_set(@#{attribute}", value)
    end

    define_method attribute do
      instance_variable_get "@#{attribute}"
    end
  end
end
```

## Quiz: Checked Attributes (Step 4)

Change the Kernel Method to a Class Macro that's available to all classes.


Quick Solution

```ruby
class Class
  def attr_checked(attribute, &validation)
    define_method "#{attribute, &validation)
      raise 'Invalid attribute' unless validation.call(value)
      instance_variable_srt("@#{attribubte}", value)
    end

    define_method attribute do
      instance_variable_get "@#{attribute}"
    end
  end
end
```

## Hook Methods

```ruby
class String
  def self.inherited(subclass)
    puts "#{self} was inherited by #{subclass}"
  end
end

class MyString < String; end

# => String was inherited by MyString
```

More hooks.

```ruby
module M
  def self.included(othermod)
   puts "M was mixed into #{othermod}"
  end
end

class C
  include M
end

# => M was mixed into C
```

`Module#extend_object()`

`Module#method_added()`

`Module#method_removed()`

`Module#method_undefined()`


## Quiz: Checked Attributes (Step 5)

The current `attr_checked` is available for all classes.

The next step is to restrict the access to `attr_checked`, it should be available only to those classes that include a module named `CheckedAttribubte`.

Class Macro is class method. You have to extend the class when you include the module to add the method into the eigenclass

Quick Solution

```ruby
module CheckedAttributes
  def self.included(base)
    base.extend ClassMethods
  end

  module ClassMethods
    def attr_checked(attribute, &validation)
      define_method "#{attribute}=" do |value|
        raise 'Invalid attribute' unless validation.call(value)
        instance_variable_set(@#{attribute}", value)
      end

      define_method attribute do
        instance_variable_get "@#{attribute}"
      end
    end
  end
end
```


