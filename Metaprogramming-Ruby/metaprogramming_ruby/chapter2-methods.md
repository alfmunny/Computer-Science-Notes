# Dynamic Methods

## Calling Methods Dynamically

use `send`

```ruby
obj.send(:my_method, 3)
```

Symbols are preferred to use in send function.


## Define Methods Dynamically

Duplicated Code:

```ruby
class Computer
    def initialize(computer_id, data_source)
        @id = computer_id
        @data_source = data_source
    end

    def mouse
        info = @data_source.get_mouse_info(@id)
        price = @data_source.get_mouse_price(@id)
        result = "Mouse. #{info} ($#{price})"
        return "* #{result}" if price >= 100
        result
    end

    def cpu
        info = @data_source.get_cpu_info(@id)
        price = @data_source.get_cpu_price(@id)
        result = "CPU. #{info} ($#{price})"
        return "* #{result}" if price >= 100
        result
    end

    def keyboard
        info = @data_source.get_keyboard_info(@id)
        price = @data_source.get_keyboard_price(@id)
        result = "Keyboard. #{info} ($#{price})"
        return "* #{result}" if price >= 100
        result
    end

    # ...
end

```


Dynamically:


```ruby
class Computer 
    def initialize(computer_id, data_source)
        @id = computer_id
        @data_source = data_source
    end

    def self.define_component(name)
        define_method(name) do
            info = @data_source.send "get_#{name}_info", @id
            price = @data_source.send "get_#{name}_price", @id
            result = "#{name.to_s.capitalize}: #{info} ($#{price})"
            return "* #{result}" if price >= 100
            result
        end
    end

    define_component :mouse
    define_component :cpu
    define_component :keyboard
end
```

Advanced Version

```ruby
class Computer 
    def initialize(computer_id, data_source)
        @id = computer_id
        @data_source = data_source
        data_source.methods.grep(/^get_(.*).info$/) { Computer.define_component $1}
    end

    def self.define_component(name)
        define_method(name) do
            info = @data_source.send "get_#{name}_info", @id
            price = @data_source.send "get_#{name}_price", @id
            result = "#{name.to_s.capitalize}: #{info} ($#{price})"
            return "* #{result}" if price >= 100
            result
        end
    end

end
```

## Method Missing


```ruby
class Computer 
    # only respond to methods begins with "__" or method_missing or respond_to?

    instance_methods.each do |m| 
        undef_method m unless m.to_s =~ /^__|method_missing|respond_to?/
    end

    def initialize(computer_id, data_source)
        @id = computer_id
        @data_source = data_source
    end

    def method_missing(name, *args)
        super if !respond_to?(name) # use inherited methods if not find
        info = @data_source.send "get_#{name}_info", args[0]
        price = @data_source.send "get_#{name}_price",args[0]
        result = "#{name.to_s.capitalize}: #{info} ($#{price})"
        return "* #{result}" if price >= 100
        result
    end
    
    # to be enable use respond_to? on these methods
    def respond_to?(method)
        @data_source.respond_to?("get_#{method}_info") || super
    end

end
```

