// source: Benq https://codeforces.com/contest/1211/submission/60224051
// kotlin tips b/c I'm bad
 
/** useful links
 * https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/-array/index.html
 * https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-array-list/index.html
 * https://kotlinlang.org/docs/reference/ranges.html
 */

/** valid ways to sort (avoid quicksort ...)
 * 1
    val a = nextLongs().sorted() // a is mutable list
 * 2
    val a = arrayListOf<Long>() // or ArrayList<Long>()
    a.addAll(nextLongs())
    a.sort()
 */
 
/** Bit shift
 * 1 shl 20
 */
 
/** 2D array
 * val ori = Array(n, {IntArray(n)})
 * val ori = arrayOf(
    intArrayOf(8, 9, 1, 13),
    intArrayOf(3, 12, 7, 5),
    intArrayOf(0, 2, 4, 11),
    intArrayOf(6, 10, 15, 14)
    )
 */
 
/** printing variables:
 * println("${l+1} and $r")
 * evidently print has high constant factor
 * print stringbuilder instead?
 */
 
/** comparing pairs
    val pq = PriorityQueue<Pair<Long,Int>>({x,y -> x.first.compareTo(y.first)})
    val pq = PriorityQueue<Pair<Long,Int>>(compareBy {it.first})
 * https://alvinalexander.com/source-code-kotlin-sortedWith-syntax-lambda-examples
    val A = arrayListOf(Pair(1,3),Pair(3,2),Pair(2,3))
    val B = A.sortedWith(Comparator<Pair<Int,Int>>{x,y -> x.first.compareTo(y.first)})
    sortBy
 */
 
/** hashmap
 *  val h = HashMap<String,Int>()
    for (i in 0..n-2) {
        val w = s.substring(i,i+2)
        val c = h.getOrElse(w){0}
        h.put(w,c+1)
    }
 */
 
/** swap
 * https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/also.html
 * a = b.also { b = a }
 */
 
// lower bound: use binary search
// https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/binary-search.html
 
// if / switch (when)
// https://kotlinlang.org/docs/reference/control-flow.html
 
// print d to 8 decimal places: String.format("%.8g%n", d)
 
// arraylist remove element at index: removeAt, not remove ...
 
import java.util.*
 
val MX = 200005
val MOD = 1000000007
val SZ = 1 shl 18
val INF = (1e18).toLong()
 
fun add(a: Int, b: Int) = (a + b) % MOD // from tourist :o
fun sub(a: Int, b: Int) = (a - b + MOD) % MOD
fun mul(a: Int, b: Int) = ((a.toLong() * b) % MOD).toInt()
 
fun next() = readLine()!!
fun nextInt() = next().toInt()
fun nextLong() = next().toLong()
fun nextInts() = next().split(" ").map { it.toInt() }
fun nextLongs() = next().split(" ").map { it.toLong() }
 
val xd = arrayOf(1,0,-1,0)
val yd = arrayOf(0,1,0,-1)
 
val out = StringBuilder()
 
fun YN(b: Boolean) : String { return if (b) "YES" else "NO"  }
 
// source: tourist https://codeforces.com/contest/1211/submission/60223650
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles

/**
 * Description: Kotlin tips for dummies
 * Source: https://codeforces.com/blog/entry/71089, own
 */
 
// episode 1: https://codeforces.com/contest/1170
// episode 2: https://codeforces.com/contest/1211
/* sorting
 * 1 (ok)
	val a = nextLongs().sorted() // a is mutable list
 * 2 (ok)
	val a = arrayListOf<Long>() // or ArrayList<Long>()
	a.addAll(nextLongs())
	a.sort()
 * 3 (ok)
	val A = nextLongs()
	val a = Array<Long>(n,{0})
	for (i in 0..n-1) a[i] = A[i]
	a.sort()
 * 4 (ok)
	val a = ArrayList(nextLongs())
	a.sort()
 * 5 (NOT ok, quicksort)
	val a = LongArray(N) // or nextLongs().toLongArray()
	Arrays.sort(a)
 */
/* 2D array
 * val ori = Array(n, {IntArray(n)})
 * val ori = arrayOf(
	intArrayOf(8, 9, 1, 13),
	intArrayOf(3, 12, 7, 5),
	intArrayOf(0, 2, 4, 11),
	intArrayOf(6, 10, 15, 14)
	)
 */
/* printing variables:
 * println("${l+1} and $r")
 * print d to 8 decimal places: String.format("%.8g%n", d)
 * try to print one stringbuilder instead of multiple prints
 */
/* comparing pairs
	val pq = PriorityQueue<Pair<Long,Int>>({x,y -> x.first.compareTo(y.first)})
										~ (compareBy {it.first})
	val A = arrayListOf(Pair(1,3),Pair(3,2),Pair(2,3))
	val B = A.sortedWith(Comparator<Pair<Int,Int>>{x,y -> x.first.compareTo(y.first)})
	sortBy
 */
/* hashmap
	val h = HashMap<String,Int>()
	for (i in 0..n-2) {
		val w = s.substring(i,i+2)
		val c = h.getOrElse(w){0}
		h.put(w,c+1)
	}
 */
/* basically switch, can be used as expression
	when (x) {
		0,1 -> print("x <= 1")
		2 -> print("x == 2")
		else -> { // Note the block
			print("x is neither 1 nor 2")
		}
	}
*/
// swap : a = b.also { b = a }
// arraylist remove element at index: removeAt, not remove ...
// lower bound: use .binarySearch()

/**
 * Description: Kotlin tips for dummies
 * Source: https://codeforces.com/blog/entry/71089, Kotlin Reference
 */
 
/// episode 1: https://codeforces.com/contest/1170
/// episode 2: https://codeforces.com/contest/1211
/// episode 3: https://codeforces.com/contest/1297
 
import java.io.*
import java.util.* // do NOT use Arrays.sort()
 
//@JvmField val INPUT = File("inp.txt").inputStream()
@JvmField val INPUT = System.`in`
//@JvmField val OUTPUT = File("output.txt").outputStream()
@JvmField val OUTPUT = System.out
@JvmField val _reader = INPUT.bufferedReader()
@JvmField val _writer = PrintWriter(OUTPUT, false)
// call _writer.flush() at end
fun rLine(): String? = _reader.readLine()
fun rLn() = rLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer =
        StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
fun rInt() = read().toInt()
fun rDb() = read().toDouble()
fun rLong() = read().toLong()
fun rStrs(n: Int) = List(n,{read()})
fun rLns(n: Int) = List(n,{rLn()})
fun rInts(n: Int) = List(n,{rInt()})
fun rDbs(n: Int) = List(n,{rDb()})
fun rLongs(n: Int) = List(n,{rLong()})
 
/**val MOD = 1000000007
val INF = (1e18).toLong()
val SZ = 1 shl 17
 
fun YN(b: Boolean) : String { return if (b) "YES" else "NO"  }
fun add(a: Int, b: Int) = (a+b) % MOD // from tourist :o
fun sub(a: Int, b: Int) = (a-b+MOD) % MOD
fun mul(a: Int, b: Int) = ((a.toLong()*b)%MOD).toInt()*/
fun gcd(a: Int, b: Int) : Int = if (b == 0) a else gcd(b,a%b)
 
/**
class BIT() {
val v = LongArray(SZ)
fun upd(_a: Int, b: Long) {
var a = _a
while (a < SZ) {
v[a] += b
a += (a and -a)
}
}
fun query(_a: Int): Long {
var a = _a
var ans: Long = 0
while (a > 0) {
ans += v[a]
a -= (a and -a)
}
return ans
}
}*/

** IO code start */
//@JvmField val INPUT = File("input.txt").inputStream()
//@JvmField val OUTPUT = File("output.txt").outputStream()
@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out
 
@JvmField val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }
 
@JvmField val _writer = PrintWriter(OUTPUT, false)
 
/** shuffles and sort overrides to avoid quicksort attacks */
private inline fun <T> _shuffle(rnd: Random, get: (Int) -> T, set: (Int, T) -> Unit, size: Int) {
    // Fisher-Yates shuffle algorithm
    for (i in size - 1 downTo 1) {
        val j = rnd.nextInt(i + 1)
        val temp = get(i)
        set(i, get(j))
        set(j, temp)
    }
}
 
@JvmField var _random: Random? = null
val random get() = _random ?: Random(0x564E235C123 * System.nanoTime()).also { _random = it }
 
fun IntArray.shuffle(rnd: Random = random) = _shuffle(rnd, ::get, ::set, size)
fun IntArray.sort() { shuffle(); _sort() }
fun IntArray.sortDescending() { shuffle(); _sortDescending() }
 
fun LongArray.shuffle(rnd: Random = random) = _shuffle(rnd, ::get, ::set, size)
fun LongArray.sort() { shuffle(); _sort() }
fun LongArray.sortDescending() { shuffle(); _sortDescending() }
 
fun DoubleArray.shuffle(rnd: Random = random) = _shuffle(rnd, ::get, ::set, size)
fun DoubleArray.sort() { shuffle(); _sort() }
fun DoubleArray.sortDescending() { shuffle(); _sortDescending() }
 
fun CharArray.shuffle(rnd: Random = random) = _shuffle(rnd, ::get, ::set, size)
inline fun CharArray.sort() { _sort() }
inline fun CharArray.sortDescending() { _sortDescending() }
 
inline fun <T: Comparable<T>> Array<out T>.sort() = _sort()
inline fun <T: Comparable<T>> Array<out T>.sortDescending() = _sortDescending()
inline fun <T: Comparable<T>> MutableList<out T>.sort() = _sort()
inline fun <T: Comparable<T>> MutableList<out T>.sortDescending() = _sortDescending()
 
fun `please stop removing these imports IntelliJ`() {
    iprintln(max(1, 2))
}
 
val MOD = 1000000007
val SZ = 1 shl 18
val INF = (1e18).toLong()
 
fun add(a: Int, b: Int) = (a+b) % MOD // from tourist :o
fun sub(a: Int, b: Int) = (a-b+MOD) % MOD
fun mul(a: Int, b: Int) = ((a.toLong() * b) % MOD).toInt()
fun YN(b: Boolean):String { return if (b) "YES" else "NO"  }
 
fun example() {
    println(String.format("%.8f", 5.25)) // print to 8 decimals
    val arr2D = Array<IntArray>(5,{IntArray(5,{5})})
    var (x,y) = arrayOf(3,2) // or rInts(2)
    when (x) { //  switch, can be used as expression
        0,1 -> println("x <= 1")
        2 -> println("x == 2") // Note the block
        else -> { println("x is neither 1 nor 2") }
    }
    x = y.also { y = x } // swap x and y
    println("${maxOf(x+2,y)}") // (x,y)=(4,3) -> 4
    val h = HashMap<String,Int>()
    val s = "ababa"
    for (i in 0..s.length-2) {
        val w = s.substring(i,i+2)
        val c = h.getOrElse(w,{0})
        h.put(w,c+1)
    }
    for ((a,b) in h) println("${a} ${b}") // key,value
    val pq = PriorityQueue<Pair<Long,Int>>({x,y ->
        x.first.compareTo(y.first)}) // or compareBy{it.first}
    val A = arrayListOf(Pair(1,3),Pair(3,2),Pair(2,3))
    val B = A.sortedWith(Comparator<Pair<Int,Int>>{x,y ->
        x.first.compareTo(y.first)}) // or sortBy{it.first}
    val list = arrayListOf('a','b','c','d','e')
    println(list.binarySearch('d')) // 3
    list.remove('d')
    val actualInsertPoint = -(list.binarySearch('d')+1) // 3
    list.add(actualInsertPoint, 'd') // [a,b,c,d,e]
    list.removeAt(1) // remove at index -> [a,c,d,e]
}

/* IntArray maps to Java's int[], and IntArray.sort() maps to Java's Array.sort(), so yes, 
it does use the unfortunately hack-vulnerable quicksort. 
Better to use Array<Int> or MutableList<Int> for sortings. (Same goes for LongArray and DoubleArray.) 
Kotlin also supports List<T>.sorted() for read-only lists, which will return a new list with the sorting applied. */

// Type Alias
typealias PII = Pair<Int, Int>
typealias PPII = Pair<Int, PII>

// Imports
import kotlin.arrayOf as Arr
import kotlin.intArrayOf as Iarr
