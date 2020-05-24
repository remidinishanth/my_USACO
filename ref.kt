// Kotlin Variables and Basic Types

var language = "French"
val score = 95

// explicitly specify the type if you want 
var language: String = "French" 
val score: Int = 95

// language variable is not explicitly specified, 
// nor the variable is initialized during declaration.
var language           // Error 
language = "French" 

// Difference val (Immutable reference) var (Mutable reference)


// The built-in types in Kotlin can be categorized as:
// Numbers - Byte, Short, Int, Long, Float and Double
// Characters - Char, letter = 'k'
// Booleans - Boolean, either true or false
// Arrays

val distance = 100L // distance value of type Long
val distance = 19.5F // distance is of type Float

// If you are not sure what number value a variable will be 
// assigned in the program, you can specify it as Number type. 

// Kotlin Arrays
// An array is a container that holds data (values) of one single type.
// In Kotlin, arrays are represented by the Array class
// The class has get and set functions, size property, and a few other useful member functions.
// E.g: Array<String>

// Kotlin Strings
// String class, "this is a string"

// Arithmetic Operators +, -(minus), *(times), /(div) and %(mod)
// +	Addition (also used for string concatenation)
// Under the hood, the expression a + b calls a.plus(b) member function.
// The plus operator is overloaded to work with String values and other basic data types (except Char and Boolean).

// + operator for basic types
operator fun plus(other: Int): Int

// for string concatenation
operator fun String?.plus(other: Any?): String

// Assignment Operators
a +=b

// Unary prefix and Increment / Decrement Operators
++a, !a, -a

// Logical Operators
||(or), &&(and)

// in Operator to check whether an object belongs to a collection.
a in b -> b.contains(a)
a !in b	-> !b.contains(a)

// Index access Operator
a[i], a[i, n], a[i1, i2, ..., in]

// Bitwise Operation
shl - Signed shift left
shr - Signed shift right
ushr - Unsigned shift right
and - Bitwise and
or - Bitwise or
xor - Bitwise xor
inv - Bitwise inversion

// Kotlin Type Conversion
val number1: Int = 55
val number2: Long = number1   // Error: type mismatch.
val number2: Long = number1.toLong()

// Kotlin Expressions
// In Kotlin, if is an expression unlike Java(In Java, if is a statement)
max = if (a > b) a else b

print(), println() // 
// Print Variables and Literals
val score = 12.3
println("score") // score
println("$score") // 12.3
println("score = $score") // score = 12.3
println("${score + score}") // 24.6
String.format("%.8f", 5.25) // print d to 8 decimal places
println("${l+1} and $r") // printing variables
