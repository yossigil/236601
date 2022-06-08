# Standard ML

## lists

---

a list is an __immutable__ finite sequence of elements

```sml
[3, 5, 9]: int list
["a", "list"]: str list
[]: 'a list
```

<!--vert-->

order matters

```sml
[1, 2, 3] <> [3, 2, 1];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

and repetitions count

```sml
[3, 3, 3] <> [3];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

elements may have any type

```sml
[(1,"One"),(2,"Two")] : (int*string) list
[[3.1],[],[5.7, ~0.6]]: real list list
```

... but all elements must have the same type

```sml
[5, "five"]; (*ERROR*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

the empty list has a polymorphic type

```sml
[]: 'a list
```

`nil` is a synonym of `[]`

```sml
nil;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### building a list

a list is either *empty* or *a head followed by a tail*

`[1,2,3]` ➭ head: `1` tail: `[2,3]`

<!--vert-->

use the infix operator `::` (aka `cons`) to build a list

```sml
1 :: [2, 3];

1 :: 2 :: 3 :: [];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

`::` associates to the right, so

`x1 :: x2 :: ... :: xn :: nil`

\=

`(x1 :: (x2 :: (... :: (xn :: nil)...)`

<!--vert-->

`::` is a *constructor* so it can be used in patterns

```sml
fun replace_head (_::t) x = x :: t
  | replace_head [] _ = []
;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### builtin fundamental functions

<!--vert-->

`null` - tests whether a list is empty

```sml
fun null [] = true
  | null (_::_) = false;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

`hd` - evaluates to the head of a non-empty list

```sml
fun hd (x::_) = x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
hd[ [ [1,2], [3] ], [ [4] ] ];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
hd it;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
hd it;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

`tl` - evaluates to the tail of a non-empty list

```sml
fun tl (_::xs) = xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
tl ["how", "are", "you?"];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
tl it;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
tl it;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
tl it;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### example - building a list of integers

```sml
fun range (m, n) =
  if m = n then []
  else m :: (range (m+1, n));

range (2, 5);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
infix --;
val op-- = range;

2 -- 5;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### `take` and `drop`

$$xs = [x_1, x_2, x_3, \ldots, x_k, x_{k+1}, \ldots, x_n]$$
$$take(k, xs) = [x_1, x_2, x_3, \ldots, x_k]$$
$$drop(k, xs) = [x_{k+1}, \ldots, x_n]$$

<!--vert-->

### the computation of `take`

```sml
fun take (0, _)     = []
  | take (i, x::xs) = x :: (take (i-1, xs));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
take (3, [9,8,7,6,5,4])
9 :: take (2, [8,7,6,5,4])
9 :: (8 :: take (1, [7,6,5,4]))
9 :: (8 :: (7 :: take (0, [6,5,4])))
9 :: (8 :: (7 :: []))
9 :: (8 :: [7])
9 :: [8,7]
[9,8,7]
```

<!--vert-->

### the computation of `drop`

```sml
fun drop (0, xs)    = xs
  | drop (i, _::xs) = drop (i-1, xs);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
drop (3, [9,8,7,6,5,4])
drop (2,   [8,7,6,5,4])
drop (1,     [7,6,5,4])
drop (0,       [6,5,4])
[6,5,4]
```

---

### tail recursion

<!--vert-->

normal recursion

```sml
fun take(0, _)     = []
  | take(i, x::xs) = x::(take(i-1, xs));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

tail recursion

```sml
fun drop (0, xs)    = xs
  | drop (i, _::xs) = drop (i-1, xs);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

### normal to tail recursive

```sml
fun length []      = 0
  | length (_::xs) = 1 + length xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

use an **accumulator** to make it iterative

```sml
local
  fun ilen (n, [])    = n
    | ilen (n, _::xs) = ilen (n+1, xs)
in
  fun length xs = ilen (0, xs)
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### builtin append operator

`[x1,...,xm] @ [y1,...,yn] = [x1,...,xm,y1,...,yn]`

```sml
infix @;
fun []      @ ys = ys
  | (x::xs) @ ys = x :: (xs @ ys);

["Append", "is"] @ ["never", "boring"];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

* is it tail recursive?
* why can't it be used in patterns?

---

### side note - `orelse` and `andalso`

they are short-circuiting boolean operators

```sml
B1 andalso B2 = if B1 then B2  else false;

B1 orelse  B2 = if B1 then true else B2;
```

<!--vert-->

```sml
fun even n = (n mod 2 = 0); 

fun powoftwo n =
  (n=1) orelse
  (even n andalso powoftwo (n div 2));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

is `powoftwo` tail-recursive?

---

### builtin function `map`

```sml
fun map f []      = []
  | map f (x::xs) = (f x) :: (map f xs);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
val sqlist = map (fn x => x*x);

sqlist [1,2,3];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

transposing a matrix using `map`

![transp gif](./imgs/matrix_transpose.gif)

```sml
fun transp ([]::_) = []
  | transp rows =
      (map hd rows) :: (transp (map tl rows));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### builtin function `filter`

```sml
fun filter pred []      = []
  | filter pred (x::xs) =
       if pred x then (x:: filter pred xs)
                 else      filter pred xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
filter (fn x => x mod 2 = 0) [1,2,3,4,5];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

`filter` is bound as `List.filter`

---

### using `map` and `filter`

a polynomial is represented as a list of `$(coeff,degree)$` pairs

$$5x^3 + 2x + 7$$

```sml
type polynomial = (int*int) list;
val a = [(5,3), (2,1), (7,0)]: polynomial;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

taking the derivative of a polynomial

```sml
fun derive (p: polynomial): polynomial =
    List.filter
        (fn (coeff, deg) => deg >= 0)
        (map
            (fn (coeff, deg) => (coeff*deg, deg-1))
            p
        )
;

derive a;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### `find`

```sml
fun find f [] = NONE
  | find f (x::xs) = if f x then SOME x else find f xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

bound as `List.find`

---

### `foldl` and `foldr`

<!--vert-->

### builtin function `foldl`

```sml
fun foldl f init []      = init
  | foldl f init (x::xs) = foldl f (f (x, init)) xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

calculates `$[x_1, x_2, … ,x_n] \rightarrow f(x_n, … ,f(x_2, f(x_1,init)))$`

<!--vert-->

### builtin function `foldr`

```sml
fun foldr f init []      = init
  | foldr f init (x::xs) = f (x, foldr f init xs);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

calculates `$[x_1, x_2, … ,x_n] \rightarrow f(x1, … ,f(xn-1, f(xn,init)))$`

<!--vert-->

### using `foldl` and `foldr`

let's redefine some functions...

```sml
fun sum l = foldl op+ 0 l;

fun reverse l = foldl op:: [] l;

fun xs @ ys = foldr op:: ys xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### `exists` and `all`

<!--vert-->

### builtin function `exists`

```sml
fun exists p []      = false
  | exists p (x::xs) = (p x) orelse exists p xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

checks if the predicate `p` is satisfied by at least one element of the list

```sml
exists (fn x => x < 0) [1, 2, ~3, 4];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

bound as `List.exists`

<!--vert-->

### builtin function `all`

```sml
fun all p []      = true
  | all p (x::xs) = (p x) andalso all p xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

checks if the predicate `p` is satisfied by **all** elements of the list

```sml
all (fn x => x >= 0) [1, 2, ~3, 4];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

bound as `List.all`

<!--vert-->

```sml
fun disjoint (xs, ys) =
  all (fn x => all (fn y => x<>y) ys) xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### equality in polymorphic functions

equality is polymorphic in a restricted sense

* defined for values constructed of integers, strings, booleans, chars, tuples, lists and datatypes
* not defined for values containing
  * functions: equality is undecidable (halting problem)
  * reals, because e.g. nan != nan
  * elements of abstract types

<!--vert-->

ML has a polymorphic equality type `''a`

```sml
op=;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

somewhat like an interface/trait in other languages

---

### exam questions

<!--vert-->

#### exercise 1

implement `map` using `foldl`

```sml
val foldl = fn : ('a * 'b -> 'b) -> 'b -> 'a list -> 'b;
val map = fn : ('a -> 'b) -> 'a list -> 'b list;
```

```sml
fun map f inpList = foldl
    _
    _
    inpList
;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
map (fn x => x * 2) [1,2,3,4];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

#### exercise 2

`insSort` (insertion sort) sorts a list according to a given less-then function.

```sml
val foldr = fn : ('a * 'b -> 'b) -> 'b -> 'a list -> 'b;
val insSort : ('a * 'a -> bool) -> 'a list -> 'a list;
```

```sml
fun insSort lt inpList = foldr
    _
    _
    inpList
;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
insSort (op<) [1, ~3, 5, 0];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

#### exercise 3

```sml
fun upto m n = if (m > n)
    then []
    else m::(upto (m+1) n)
;

infix o;
fun f o g = fn x => f (g x);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

what will be printed?

```sml
val a = map (upto 2) (upto 2 5);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

what will be printed?

```sml
map
    (
        (fn f => null (f()))
        o
        (fn t => fn () => tl t)
    )
    a
;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

what will be printed?

```sml
map
    (List.filter (fn t => t mod 2 = 0))
    a
;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

#### exercise 4

implement a tail recursive `append`

**reminder**:

```sml
infix @;
fun []      @ ys = ys
  | (x::xs) @ ys = x :: (xs @ ys);
```

<!--vert-->

```sml
fun append ...
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE:

```sml
fun aux([], ys) = ys
  | aux(x::xs, ys) = aux (xs, x::ys);

fun append (xs, ys) = aux (aux (xs, []), ys);
```

<!--vert-->

#### exercise 5

implement `flatten` using `foldr`

```sml
flatten : 'a list list -> 'a list;
```

```sml
fun flatten ...
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
[1,2,3,4,5,6,7,8,9] = flatten [[1,2,3],[4,5,6],[],[7,8,9]];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE:

```sml
fun flatten xs = foldr (op@) [] xs;
```
