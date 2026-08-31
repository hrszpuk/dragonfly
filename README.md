# dragonfly
Programming language and compiler. A fun little challenge to myself, without any keywords outside of basic types.

```c
@"path/to/lib.df"
@io
@string

// comment
x : i32 = 10
y : i32
z : i32 = 10 + x * 10 / 40
w := x // type inference

add : (i32, i32) = (x, y){ x + y }
y := add(x, z)


s : [i8; 11] = 'hello world'
sc : i8 = s[0] // 'h'

// Control flow
x > 0 {
    io.println('nice')
} : x > 10 {
    io.println('nice nice')
} : {
    io.println('nice nice nice')
}

// To assign with control flow each branch must end in an expression
flow : i32 = x > 0 {
    100
} : x > 10 {
    200
} : {
    300
}

// Looping (iterators)
[i : i32 = 0; i < 5; i++] {
    io.println("%d", i) // library function
}

// Structs
Point {
    x: i32 = 0
    y: i32 = 11
    scale: (s: i32) i32 {
        x *= s
        y *= s
    }
}
point : Point = {23, 24, ()}
point.x += point.y

io.println("%d", point.x)

// Building an array of 10 point structs
points : [Point; 10] = [
    i : Point; 
    i.x < 10 && i.y < 10; 
    {i.x += 1, i.y += 1}
]

// scaling everything
[i : i32 = 0; i < 10; i++] {
    points[i].scale(10)
}

// namespace
@mathz {
    add : (x: i32, y: i32) {x + y}
    sub : (x: i32, y: i32) {x - y}
}

mathz.add(30, 30)
mathz.sub(10, 10)

```
