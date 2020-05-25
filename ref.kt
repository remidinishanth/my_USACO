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

val a: Int = 1  // immediate assignment
val b = 2   // `Int` type is inferred
val c: Int  // Type required when no initializer is provided
c = 3       // deferred assignment

var x = 5 // `Int` type is inferred

// Difference val (Immutable reference) var (Mutable reference)
// Variables that can be reassigned use the var keyword
// Read-only local variables are defined using the keyword val. They can be assigned a value only once.

// The built-in types in Kotlin can be categorized as:
// Numbers - Byte, Short, Int, Long, Float and Double
// Characters - Char, letter = 'k'
// Booleans - Boolean, either true or false
// Arrays

val distance = 100L // distance value of type Long
val distance = 19.5F // distance is of type Float
val pi = 3.14 // Double
val e = 2.7182818284 // Double
val eFloat = 2.7182818284f // Float, actual value is 2.7182817

import java.math.BigInteger
val second = BigInteger("1")

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

val number = -10
val result = if (number > 0) {
    "Positive number"
} else {
    "Negative number"
}
println(result) // Negative number

val result = if (number > 0) "Positive number" else "Negative number"

while (testExpression) {
    // codes inside body of while loop
}

do {
   // codes inside body of do while loop
} while (testExpression)

for (item in collection) {
    // body of loop
}

for (i in 1..5) print(i) // 12345
for (i in 5..1) print(i) // prints nothing 
for (i in 5 downTo 1) print(i) // 54321
for (i in 4 downTo 1 step 2) print(i) // 42

Using ranges
for (i in 1..100) { ... }  // closed range: includes 100
for (i in 1 until 100) { ... } // half-open range: does not include 100
for (x in 2..10 step 2) { ... }
for (x in 10 downTo 1) { ... }
if (x in 1..10) { ... }

var language = arrayOf("Ruby", "Koltin", "Python" "Java")
for (item in language) // Iterating over a collection
for (item in language.indices)
for (letter in text) // var text= "Kotlin"

// When Expression - when replaces the switch operator of C-like languages.
when (x) {
    1 -> print("x == 1") // 0, 1 -> print("x == 0 or x == 1")
    2 -> print("x == 2")
    else -> { // Note the block
        print("x is neither 1 nor 2")
    }
}

// Any expression in Kotlin may be marked with a label.

// There are 3 structural jump expressions in Kotlin: break, continue and return

// Kotlin Labeled break
first@ for (i in 1..4) {
    second@ for (j in 1..2) {
        println("i = $i; j = $j")
        if (i == 2)
            break@first // terminates the loop marked with label first@
    }
}
// Output
i = 1; j = 1
i = 1; j = 2
i = 2; j = 1

if (i == 2) break@second
// Output
i = 1; j = 1
i = 1; j = 2
i = 2; j = 1
i = 3; j = 1
i = 3; j = 2
i = 4; j = 1
i = 4; j = 2

// Similarly we have kotlin labelled continue, continue@label

// Kotlin Collections Overview
// source: https://kotlinlang.org/docs/reference/collections-overview.html

// List is an ordered collection with access to elements by indices.
// Set is a collection of unique elements. 
// Map (or dictionary) is a set of key-value pairs. Keys are unique.

// A pair of interfaces represent each collection type:
// A read-only interface that provides operations for accessing collection elements.
// A mutable interface that extends the corresponding read-only interface with write operations.

// Note that altering a mutable collection doesn't require it to be a var: 
// write operations modify the same mutable collection object, so the reference doesn't change.
// Although, if you try to reassign a val collection, you'll get a compilation error.
val numbers = mutableListOf("one", "two", "three", "four")
numbers.add("five")   // this is OK    
//numbers = mutableListOf("six", "seven")      // compilation error

// Collection - Collection<T> is the root of the collection hierarchy.
// Collection inherits from the Iterable<T> interface that defines the operations for iterating elements.
fun printAll(strings: Collection<String>) {
        for(s in strings) print("$s ")
        println()
    }
    
fun main() {
    val stringList = listOf("one", "two", "one")
    printAll(stringList)
    
    val stringSet = setOf("one", "two", "three")
    printAll(stringSet)
}

// List
// Indices start from zero – the index of the first element – and go to lastIndex which is the (list.size - 1).
val numbers = listOf("one", "two", "three", "four")
numbers.size // Number of elements = 4
numbers.get(2) // Third element = three
numbers[3] // Fourth element = four
numbers.indexOf("two") // Index of element "two" = 1
numbers.isEmpty() // false

// Returns an empty read-only list.
val list = listOf<String>()
val other: List<Int> = emptyList() 

// MutableList is a List with list-specific write operations, 
// for example, to add or remove an element at a specific position.
val numbers = mutableListOf(1, 2, 3, 4)
numbers.add(5)
numbers.removeAt(1)
numbers[0] = 0
numbers.shuffle()
val sortedNumbers = numbers.sorted() // creates a new collection that contains the same elements in the sorted order.
numbers.sort() // sorts a mutable collection in-place, so its state changes
println(numbers)

// Set
// Set<T> stores unique elements; their order is generally undefined. null elements are unique as well
val numbers = setOf(1, 2, 3, 4)
numbers.contains(1)

// The default implementation of Set – LinkedHashSet – preserves the order of elements insertion.
// Hence, the functions that rely on the order, such as first() or last(), return predictable results on such sets.
val numbers = setOf(1, 2, 3, 4)  // LinkedHashSet is the default implementation
val numbersBackwards = setOf(4, 3, 2, 1)
numbers.first() == numbersBackwards.last() // true

// MutableSet is a Set with write operations from MutableCollection

// Map
// Map<K, V> is not an inheritor of the Collection interface
val numbersMap = mapOf("key1" to 1, "key2" to 2, "key3" to 3, "key4" to 1)
numbersMap.keys // [key1, key2, key3, key4]
numbersMap.values // [1, 2, 3, 1]
numbersMap["key2"] // 2
if ("key2" in numbersMap) // true
if (1 in numbersMap.values) // true
numbersMap.containsValue(1) // true

val map = emptyMap<String, Int>()
val anotherMap = mapOf<String, Int>()
map == anotherMap // true

// MutableMap is a Map with map write operations
// The default implementation of Map – LinkedHashMap
val numbersMap = mutableMapOf("one" to 1, "two" to 2)
numbersMap.put("three", 3)
numbersMap["one"] = 11
