# Ruby Cheatsheet


## String

```ruby
puts "This is a string. \r\n".chomp
puts "   word  ".chomp
puts "word".chomp
puts "word".chop
puts "word \r\n".chop
puts "   word  \r\n".strip
```

## switch case

Case uses `===`, which means subsumption. "If I have a drawer labeled a would it make sense to put b in that drawer?"

```ruby
puts (1..5) === 3
puts (1..5) === 6
puts Integer === 1
puts Integer === "ADIOASJDAS"

```

```ruby
obj = 1
puts obj.class
case obj
when Fixnum
  puts "It's Fixnum"
when String
  puts "It's String"
else
  puts "It's somehing else"
end
```

## lambda and Proc

Two differences:

1.  lambda checks the arguments
2.  lambda returns the value of the lambda, but Proc returns from the enclosure block

```ruby
l = lambda {|a, b| a**2 + b**2 }
l.call 1, 2     # 5
l.call 1, 2, 3  #ArgumentError: wrong number of arguments (3 for 2)
p = Proc.new {|a, b| a**2 + b**2}
p.call 1, 2     # 5
p.call 1        # NoMethodError: undefined method `**' for nil:NilClass
```

```ruby
lambda { return :foo }.call # => :foo
return # => LocalJumpError: unexpected return
Proc.new { return :foo }.call # => LocalJumpError: unexpected return
```

## Cheatsheet of Rails Development

### Basics

Create app

```bash
rails new sample_app
```

Generate controller

```bash
rails generate controller Users new
```

Generate model

```bash
rails generate model User name:string email:string
```

Add index to column

```bash
rails generate migration add_index_to_users
```

```ruby
class AddIndex < ActiveRecord::Migration[6.0]
  def change
    add_index :users, :email, unique: true
  end
end
```

Generate integration test

```bash
rails generate integration_test users_signup
```

Migration

```bash
rails db:migrate
rails db:migrate:reset #run all the migrations
rails db:reset  # drop create seed
rails db:rollback STEP=2
```

### Deployment

heroku

```bash
heroku create
git push heroku
heroku login --interactive
git push heroku
heroku run rails db:migrate
heroku run rails console --sandbox
```

SSL

```ruby
Rails.application.configure do
  config.force_ssl = true
end
```

Puma configuration

```ruby
max_threads_count = ENV.fetch("RAILS_MAX_THREADS") { 5 }
min_threads_count = ENV.fetch("RAILS_MIN_THREADS") { max_threads_count }
threads min_threads_count, max_threads_count
port        ENV.fetch("PORT") { 3000 }
environment ENV.fetch("RAILS_ENV") { ENV['RACK_ENV'] || "development" }
pidfile ENV.fetch("PIDFILE") { "tmp/pids/server.pid" }
workers ENV.fetch("WEB_CONCURRENCY") { 2 }
preload_app!
plugin :tmp_restart
```

### Helper

flash

```ruby
flash.now[:success] = "Welcome"
flash.now[:danger] = "Error"
```

```html
<% flash.each do |message_type, message| %>
  <%= content_tag(:div, message, class: "alert alert-#{message_type}") %>
<% end %>
```

### Bootstrap

```bash
yarn add jquery@3.5.1 bootstrap@3.4.1
```

`config/webpack/environment.js`

```javascript
const { environment } = require('@rails/webpacker')
const webpack =require('webpack')
environment.plugins.prepend('Provide',
  new webpack.ProvidePlugin({
    $: 'jquery/src/jquery',
    jQuery: 'jquery/src/jquery',
    Popper: ['popper.js', 'default']

  })
)
module.exports = environment
```

`app/javascript/packs/application.js`

```javascript
require("@rails/ujs").start()
require("turbolinks").start()
require("@rails/activestorage").start()
require("channels")
import "bootstrap"
```

`app/assets/stylesheets/application.scss`

```
@import "bootstrap";
```
