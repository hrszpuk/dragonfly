# Dragonfly Language Specification v0.1 
This is my specification for the Dragonfly programming language.
Dragonfly is a personal project, a little challenge to make an LLVM frontend and design a language that doesn't have any keywords.
So this specification is more like a series of examples.

I do plan to write a series of tests against this specification first before coding to track progress and ensure I've implemented everything correctly :).

## Variables, Types, and Structures
```go
// This is a comment :)

// Declared then assigned
a : i32
a = 10

// Definition
b : i32 = a
c := 99 // With type inference, type is i32

// Using types allways follows a similar pattern SOMETHING COLON TYPE

// You can couple types together with brackets
point2d : (i32, i32)
point2d[0] = 3
a = point2d[1] // Initialises to 0

// With named parameters
point3d : (
    x: f64,
    y: f64,
    z: f64
)

point3d.x = 3.14 * point3d.y

// Constant Variables are all caps and underscores
BUFFER_LENGTH := 16

// Structures 
Dog : {
    id: i32,

    // Arrays are covered further down
    name: [u8; BUFFER_LENGTH],
    owner: [u8; BUFFER_LENGTH],
}

morris := Dog{0, "Morris", "David"}
goldie : Dog = { /* 0, "", "" */ }

// This will cause an error as the type can't be determined
errorous_dog := {0, "Alfie", ""} 

```

## Arrays, Loops, and Control flow
```go
@io

// Arrays type signature: [TYPE; LENGTH]
favourite_numbers : [i32; 5] = [42, 67, 17, 23, 0]

favourite_dogs : [Dog; 2] = [golide, Dog{}]
favourite_dogs[1] = morris

// Strings are not NULL terminated
// String lengths are accessible through .len()
message := "Hello, World!"

(i: i32 = 0; i < favourite_numbers.len(); i += 1) {
    io.print(favourite_numbers[i])
}

favourite_numbers[0] == 42 {
    // Runs if it is 42
} : {
    // Runs otherwise
}

// Returning values from control flow or functions can be done so long as an expression is the final line and all blocks result in the same type
result := favourite_dogs[1].id == 0 {
    "Morris" // Result has a type of [u8; 6]
} favourite_dogs[1].id == 1 {
    "Goldie"
} { "None" } // else block

```

## Functions, Associated Functions and Namespaces
```go
@io // This is a library 
// Standard libraries such as io are included with the compiler
// Any .df file can be a library!
// Any code in the file will be ran when it is imported.
@lib "some/path/to/lib.df"
lib.some_function()
lib.SOME_CONST
p : lib.SomeStruct // ...etc

// You can create your own name space within a file as well:
@mathz {
    // Here is a function
    add : (i32, i32) (i32)
    add = (x, y) (i32) {
        x + y
    }

    // Variadic parameters
    add_all : (args: [i32..]) (i32) = {
        sum := 0
        (i: i32 = 0; i < args.len(); i += 1) {
            sum += args[i]
        }
        sum
    }
}

result := mathz.add(3, 4) + mathz.add_all(1, 2, 3, 4, 5)

// Finally, functions can be attached to structs
Point : {
    x : f32,
    y : f32,
    z : f32,
    scale : (i32) (),
}

Point::scale := (s: i32) () {
    // ~ allows you to access the members of a structure
    ~x = ~x * s
    ~y = ~y * s
    ~z = ~z * s
}

p := Point{2, 2, 2}
p.scale(10) // {20, 20, 20}
```

## What's next? 
What am I looking to add next? Well I think adding support for C libraries would be good for a little standard library / ecosystem.

I'm also interested in adding some new language features in the future too (I'm taking suggestions on Discord or GitHub issue)!