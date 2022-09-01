# Ruby Cheatsheet

## String format

Debug information
```rust
format!
format!({:?}, Some("hi"))
```

## Shadowing

```rust
let x = 5
let x = x+1

{
    let x = "string"
}

```

