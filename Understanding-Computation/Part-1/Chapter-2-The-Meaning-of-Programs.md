# Chapter 2. The Meaning of Programs


## Small-Step Semantics

### Expressions

Represent SIMPLE expressions as Ruby Objects

#### Custom string representation for abstract syntax

```ruby
class Number < Struct.new(:value)
  def to_s
    value.to_s
  end

  def inspect
    "«#{self}»" 
  end

  def reducible?
    false
  end
end

class Add < Struct.new(:left, :right)
  def to_s
    "#{left} + #{right}"
  end

  def inspect
    "«#{self}»"
  end

  def reducible?
    true 
  end
end

class Multiply < Struct.new(:left, :right)
  def to_s
    "#{left} * #{right}"
  end

  def inspect
    "«#{self}»"
  end

  def reducible?
    true 
  end
end

p Add.new(
  Multiply.new(Number.new(1), Number.new(2)), 
  Multiply.new(Number.new(3), Number.new(4))
)

p Number.new(5)
```

```
«1 * 2 + 3 * 4»
«5»
```

We don't take operator precedence into account.

#### Reducible?

```ruby
class Number
  def reducible?
    false
  end
end

class Add
  def reducible?
    true
  end
end

class Multiply
  def reducible?
    true
  end
end
```

#### Reduce

```ruby
class Add
  def reduce
    if left.reducible?
      Add.new(left.reduce, right)
    else right.reducible?
      Add.new(left, right.reduce)
    else
      Number.new(left.value + right.value)
    end
  end
end

class Multiply 
  def reduce
    if left.reducible?
      Multiply.new(left.reduce, right)
    else right.reducible?
      Multiply.new(left, right.reduce)
    else
      Number.new(left.value * right.value)
    end
  end
end
```

```ruby

p expression = Add.new(
  Multiply.new(Number.new(1), Number.new(2)), 
  Multiply.new(Number.new(3), Number.new(4))
)
p expression.reducible?
p expression = expression.reduce
p expression.reducible?
p expression = expression.reduce
p expression.reducible?
p expression = expression.reduce
p expression.reducible?
```

#### Maintaining state: the current expression

```ruby
class Machine < Struct.new(:expression)
  def step
    self.expression = expression.reduce
  end

  def run
    while expression.reducible?
      puts expression
      step
    end
    puts expression
  end
end
```

```ruby
Machine.new(Add.new(
  Multiply.new(Number.new(1), Number.new(2)), 
  Multiply.new(Number.new(3), Number.new(4))
)).run
```

#### Boolean and LessThan

```ruby
class Boolean < Struct.new(:value)
  def to_s
    value.to_s
  end

  def inspect
    "«#{self}»"
  end

  def reducible?
    false
  end
end

class LessThan < Struct.new(:left, :right)
  def to_s
    "#{left} < #{right}"
  end

  def inspect
    "«#{self}»"
  end

  def reducible?
    true 
  end

  def reduce
    if left.reducible?
      LessThan.new(left.reduce, right)
    elsif right.reducible?
      LessThan.new(left, right.reduce)
    else
      Boolean.new(left.value < right.value)
    end
  end
end
```

```ruby
Machine.new(
  LessThan.new(Number.new(5), Add.new(Number.new(2), Number.new(2)))
).run
```

### Statements

#### Variable

```ruby
class Variable < Struct.new(:name)
  def to_s
    name.to_s
  end

  def inspect
    "«#{self}»"
  end

  def reducible?
    true
  end

  def reduce(environment)
    environment[name]
  end
end
```

Also adjust the other expressions' reduce function with environment.

```ruby
class Machine < Struct.new(:expression, :environment)
  def step
    self.expression = expression.reduce(environment)
  end

  def run
    while expression.reducible?
      puts expression
      step
    end
    puts expression
  end
end
```

```
x + y
3 + y
3 + 4
7
```

#### Assign

```ruby
class Assign < Struct.new(:name, :expression)
  def to_s
    "#{name} = #{expression}"
  end

  def inspect
    "«#{self}»" 
  end

  def reducible?
    true
  end

  def reduce(environment)
    if expression.reducible?
      [Assign.new(name, expression.reduce(environment)), environment]
    else
      [DoNothing.new, environment.merge({ name => expression })]
    end
  end
end
```

```ruby
class Machine < Struct.new(:statement, :environment)
  def step
    self.statement, self.environment = statement.reduce(environment)
  end

  def run
    while statement.reducible?
      puts "#{statement}, #{environment}"
      step
    end
    puts "#{statement}, #{environment}"
  end
end

Machine.new(
  Assign.new(:x, Add.new(Variable.new(:x), Number.new(1))), 
  { x: Number.new(2) }
).run
```

Output

```
x = x + 1, {:x=>«2»}
x = 2 + 1, {:x=>«2»}
x = 3, {:x=>«2»}
do-nothing, {:x=>«3»}
```

#### If

```ruby
class If < Struct.new(:condition, :consequence, :alternative)
  def to_s
    "if (#{condition}) { #{consequence} } else { #{alternative} }"
  end

  def inspect
    "«#{self}»" 
  end

  def reducible?
    true
  end

  def reduce(environment)
    if condition.reducible?
      [If.new(condition.reduce(environment), consequence, alternative), environment]
    else 
      case condition
      when Boolean.new(true)
        [consequence, environment]
      when Boolean.new(false)
        [alternative, environment]
      end
    end
  end
end
```

```ruby
Machine.new(
  If.new(
    Variable.new(:x),
    Assign.new(:y, Number.new(1)),
    Assign.new(:y, Number.new(2))
  ),
  { x: Boolean.new(true) }
).run
```

```
if (x) { y = 1 } else { y = 2 }, {:x=>«true»}
if (true) { y = 1 } else { y = 2 }, {:x=>«true»}
y = 1, {:x=>«true»}
do-nothing, {:x=>«true», :y=>«1»}
```

#### Sequence

```ruby
class Sequence < Struct.new(:first, :second)
  def to_s
    "#{first}: #{second}"
  end

  def inspect
    "«#{self}»" 
  end

  def reducible?
    true
  end

  def reduce(environment)
    case first
    when DoNothing.new
      [second, environment]
    else
      reduced_first, reduced_environment = first.reduce(environment)
      [Sequence.new(reduced_first, second), reduced_environment]
    end
  end
end
```

```ruby
Machine.new(
  Sequence.new(
    Assign.new(:x, Add.new(Number.new(1), Number.new(1))), 
    Assign.new(:y, Add.new(Variable.new(:x), Number.new(3)))
  ),
  { }
).run
```

```
x = 1 + 1: y = x + 3, {}
x = 2: y = x + 3, {}
do-nothing: y = x + 3, {:x=>«2»}
y = x + 3, {:x=>«2»}
y = 2 + 3, {:x=>«2»}
y = 5, {:x=>«2»}
do-nothing, {:x=>«2», :y=>«5»}
```

#### While

```ruby
class While < Struct.new(:condition, :body)
  def to_s
    "#{condition}: #{body}"
  end

  def inspect
    "«#{self}»" 
  end

  def reducible?
    true
  end

  def reduce(environment)
    [If.new(condition, Sequence.new(body, self), DoNothing.new), environment]
  end
end
```

```ruby
Machine.new(
  While.new(
    LessThan.new(Variable.new(:x), Number.new(5)),
    Assign.new(:x, Multiply.new(Variable.new(:x), Number.new(3)))
  ),
  { x: Number.new(1) }
).run
```

```
x < 5: x = x * 3, {:x=>«1»}
if (x < 5) { x = x * 3: x < 5: x = x * 3 } else { do-nothing }, {:x=>«1»}
if (1 < 5) { x = x * 3: x < 5: x = x * 3 } else { do-nothing }, {:x=>«1»}
if (true) { x = x * 3: x < 5: x = x * 3 } else { do-nothing }, {:x=>«1»}
x = x * 3: x < 5: x = x * 3, {:x=>«1»}
x = 1 * 3: x < 5: x = x * 3, {:x=>«1»}
x = 3: x < 5: x = x * 3, {:x=>«1»}
do-nothing: x < 5: x = x * 3, {:x=>«3»}
x < 5: x = x * 3, {:x=>«3»}
if (x < 5) { x = x * 3: x < 5: x = x * 3 } else { do-nothing }, {:x=>«3»}
if (3 < 5) { x = x * 3: x < 5: x = x * 3 } else { do-nothing }, {:x=>«3»}
if (true) { x = x * 3: x < 5: x = x * 3 } else { do-nothing }, {:x=>«3»}
x = x * 3: x < 5: x = x * 3, {:x=>«3»}
x = 3 * 3: x < 5: x = x * 3, {:x=>«3»}
x = 9: x < 5: x = x * 3, {:x=>«3»}
do-nothing: x < 5: x = x * 3, {:x=>«9»}
x < 5: x = x * 3, {:x=>«9»}
if (x < 5) { x = x * 3: x < 5: x = x * 3 } else { do-nothing }, {:x=>«9»}
if (9 < 5) { x = x * 3: x < 5: x = x * 3 } else { do-nothing }, {:x=>«9»}
if (false) { x = x * 3: x < 5: x = x * 3 } else { do-nothing }, {:x=>«9»}
do-nothing, {:x=>«9»}
```

### Correctness

### Applications
