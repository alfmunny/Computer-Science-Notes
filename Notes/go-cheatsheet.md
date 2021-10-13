# Go Cheatsheet


## Basics

```
$ go build
```

```go
package main
import ("math")
import (
  "fmt"
  "math/rand"
)
func main() {
  fmt.Printf("%g", math.Sqrt(7))
  fmt.Println("My favarite number is", rand.Intn(10))
  fmt.Println(add(42, 13))
}

```

Function

```go
func add(x int, y int) int {
  return x +y
}
// or
func add(x, y int) int {
  return x + y 
}
// multiple result
func add(x, y int) int {
  return y, x
}
// short version
func split(sum int) (x, y int) {
  x = sum * 4 / 9
  y = sum - x
  return 
}
```

Variables

```go
var c, python, java bool
var i, j int = 1, 2
k := 3
```

Types

```
bool

string

int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64 uintptr

byte // alias for uint8

rune // alias for int32
     // represents a Unicode code point

float32 float64

complex64 complex128
```

```
i := 42           // int
f := 3.142        // float64
g := 0.867 + 0.5i // complex128
```

Constant

```go
const pi = 3.14
1 << 100
1 >> 99
```

for

```go
for i := 0; i < 10; i++ {
  sum += 1
}

for ; sum < 1000; {
  sum += sum
}

for {
}
```

switch

```go
switch os_r runtime.GOOS; os {
case "darwin":
  fmt.Println("OS X.")
case "linux":
  fmt.Println("Linux.")
default:
  fmt.Printf("%s, \n", os)
}

switch { // same as "switch true"
case a:
  fmt.Println("a")
case b:
  fmt.Println("b")
case c:
  fmt.Println("c")
}
```

if

```go
if x < 0 {
  reutrn sqrt(-x) + "i"
}

if v := math.Pow(x, n); v < lim {
return v
} else {
}
```

Defer

```go
defer fm.Printlin("world")
```

Pointer

```go
var p *int
p = &i
*p = 21
```

Structs

```go
type Vertex struct {
  X int
  Y int
}

v := Vertext{1, 2}
v.X = 4
p := &v
p.X = 1e9

v1 = Vertext{X: 1}
v2 = Vertex{} // X:0 and Y:0
p = &Vertext{1, 2}
```

Array

```go
var a [10]int
primes := [6]int{2, 3, 5, 7, 11, 13}
var s[] int = primes[1:4]
len(s) // 3
cap(s) //6
primes[0:6]
primes[:6]
primes[0:]
primes[:]
b := make([]int 5) // [0, 0, 0, 0, 0]
b = append(b, 0, 1, 2, 3) // [0, 0, 0, 0, 0, 0, 1, 2, 3]
```

Range

```go
for i, v := range pow { // index, value
}
for i := range pow { // index
}
for _, value := range pow { // value
}
```

Maps

```go
var m map[string]Vertex

m = make(map[string]Vertext) // m == nil
m["a"] = Vertex{
  1, 2
}
var m = map[string]Vertex{
  "a": Vertex{1, 2},
  "b": Vertex{2, 4}
}

var m = map[string]Vertex{
  "a": {1, 2},
  "b": {2, 4}
}

m := make(map[string]int)
m["a"] = 1
delete(m, "a")
v, ok := m["a"] // value 0, present?: false
```

Function Values

```go
func compute(fn func(float64, float64) float64) float64 {
  return fn(3, 4)
}

hypot := func(x, y float64) float64 {
  return math.Sqrt(x*x, y*y)
}
compute(hypot)
```

Closures

```go

func adder() func(int) int {
  sum := 0
  return func(x int) {
    sum += x
    return sum
  }
}

pos, neg := adder(), adder()
for i := 0; i < 10; i++ {
  fmt.Println(
    pos(1)
    neg(2)
  )
}
```

## Methods and interfaces

Methods

```go
// value receiver
func (v Vertex) Abs() float64 {
  return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

v := Vertex{3, 4}
v.Abs()
Abs(v)

// pointer receiver
func (v *Vertex) Scale(f float64) {
  v.X = v.X * f
  v.Y = v.Y * f
}
v.Scale(10)
```

Interfaces

```go
func (v *Vertex) Abs() float64 {
  return math.Sqrt(v.X*v.X + v.Y*v.Y)
}
type Abser interface {
  Abs() float64
}

var a Abser
a = &v
```

Type assertion

```go
var i interface{} = "hello"
s := i.(string)
s, ok := i.(float64)
```

Stringers

```go
type Stringer interface {
    String() string
}
func (p Persion) String() string {
  return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
```

Errors

```go
type error interface {
}

func (e *Myerror) Error() string {
}
```

Readers

```go
package main

import (
  "fmt"
  "io"
  "strings"
)

func main() {
  r := strings.NewReader("Hello, Reader!")
  b := make([]byte, 8)
  for {
    n, err := r.Read(b)
    fmt.Printf("n = %v err = %v b = %v\n", n, err, b)
    if err == io.EOF {
      break
    }
  }
}
```

## Concurrency

Goroutines

```go
go f(x, y, z)
```

Channels

```go
ch = make(chan int)
ch < -v
v := <-ch

go sum(s[:len(s)/2], ch)
go sum(s[len(s)/2:], ch)
x, y := <-c, <-c
```

Range and Close

    sender can close the channel

```go
v, ok := <-ch
i := range c {
  fmt.Println(i)
}
```

Select

```go
select {
  case c <- x:
    x, y = y, x + y
  case <- quit
    fmt.Println("quit")
    return
}
```

Mutex

```go

type SafeCounter struct {
  v map[string] int
  mux sync.Mutex
}

func (c *SafeCounter) Inc(key string) {
  c.mux.Lock()
  c.v[key]++
  c.mux.Unlock
}
```
