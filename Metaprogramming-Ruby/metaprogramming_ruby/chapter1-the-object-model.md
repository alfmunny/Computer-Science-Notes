## Open Classes

The class will not be create again, if it already exsits.


```ruby
class D
    def x; 'x'; end
end

class D
    def y; 'y'; end
end

obj = D.new
obj.x # => x
obj.y # => y

```

It's called Open Class. The `class` keyword workds like a scope operator. 
You can always add method to a class by reopening the class. **Monkeypatch**

**The Problem**: 

if the method already exists, you will have a error.
To avoid the 

## What's in an Object

### Instance Variable

```ruby
obj.instance_variables
obj.instance_variable_set("@x", 1)
```

### Methods

```ruby
[].methods

[].methods.grep /^re/ # => [:replace, :reject, :reject!, .....

[].methods == Array.instance_methods

```

**Note**:

An instance variables lives in the object.
An object's methods lives in the object's class.

## Class is Object

```ruby
"hello".class   # => String
"String".class  # => Class

inherited = false
Class.instance_methods(inherited) # => [:superclass, :allocate, :new]

String.superclass # => Object
Object.superclass # => BasicObject
BasicObject.superclass # => nil

Class.superclass # => Module
Module.superclass # => Object
```

## Constants

Uppercased references are constants

Class name is a constants

```ruby
module MyModule

    MyConstants = 'Outer constants'

    class Myclass
        MyConstants = 'Inner constants'
    end
end


MyModule::MyConstants # => Outer constants
MyModule::MyClass::MyConstants # => Inner constants
```


## Modules and Lookup

When you call a method on an instance, it looks up for the method through the whole ancestor chain.

Any class includes module, it and its inheritance can use the methods from the moduele.


```ruby
moduel M
    def my_method
        'M#my_method'
    end
end

class C
    include M
end

class D < C

D.new.my_method()   # => 'M#my_method'
D.ancestors         # => [D, C, M, Object, Kernel, BasicObject]

```


## The Kernel
Kernel is a module. The class Object includes the Kernel.
```ruby
Kernel.private_instance_methods.grep(/^pr/) # => [:printf, :print, :proc]
```

## Ancestor Chain

Ervery time a class includes a module, the module is inserted in ancestors chain right above the class itself.

```ruby
class Book
    include Printable
    include Document
end

Book.ancestors # => [Book, Document, Printable, Object, Kernel, BasicObject]
```


## Private

Private methods can only called without explicit receiver (without `self`)

