# Universal tree format v2.0

## How to save tree?

- [x] >note that is only guide how to save program tree in file so you can use any syntax in yours progs. But keep in mind that if you want to share your work to others, observe this simple rules

### In file it should look like this

```c
((30)+((40)*(10)))
```

this look like this in dot

![tree sample](picture.png)

### list of commands

#### Beginning of the program and ending

* "Init"
* "End"

#### Program line

* "line"
  
#### Basic

* '+'
* '-'
* '*'
* '/'
* "sin"
* "cos"
* number [-+]?[0-9]+[.]?[0-9]*
* variable name [a-zA-z][a-zA-Z0-9_$]*

#### Cycles

* "if"
* "while"

#### Boolean operator

* '<'
* \'>'
* '=='

#### Function

* "func"

>spaces aren't allowed
>do not do this "( 10 *( 5 ))", use this instead "(10*(5))"

### Left-Right leafSpec

1. We use left leave for every single argument function. For example: sin(0.5);

2. We use left leave for positive if, while and other functions that contains choice. For example: if(a > b){cos(10)} . We will use left leave for cos(10)

### Encoding options

1. "0" - is false
2. "1" or eny other number  - is true

### Data types

1. Basic - is double
2. text use char arrays