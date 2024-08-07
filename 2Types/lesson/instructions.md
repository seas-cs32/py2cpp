# Preface  

You've gotten past the biggest differences in syntax between Python and C. Congratulations!

In this second project, we will talk about:

1. **Types**, because C is a _statically typed language_.
2. **Arrays**, which are like a Python sequence where every element of the sequence has the same type.
3. **Comments**, because the comment characters are different between the two languages (and between versions of the C language).

## Feedback

This mini-curriculum is a work in progress. If you have thoughts about how it could be improved, please send them to mike_smith@harvard.edu.  If you're interested in helping improve the existing projects or create new ones, please say that in your email. I'd love the help!

## Types

In learning Python, we talked about the _type_ of an object, but we never explicitly expressed that type information in our programs. Well, except when we wanted to convert an object of one type into an object of a different type. For example, when we asked the user to input a number.

```python
a_number = int(input('Please type a number: '))
```

Recall that the `input` function in Python returns a string, but we wanted something we could treat in our script as an integer.

Notice how we talked about an object in the previous sentence. We said that `input` returns a string and what we wanted was an integer. We were talking about type information. 

> Types are attributes about a piece of data that tells the interpreter or compiler how to interpret the data's bit pattern and what operations are legal to perform on that data.

Python is a _dynamically typed language_, which means we don't have to state the type of a variable (e.g., a name like `a_number`). The Python figures it out the type of a new object from the context (e.g., adding an integer to an integer produces an integer). Here's that Python code again.

```python
# Python code, which doesn't require us to say the type of the
# name `a_number`. We made the object we name `a_number` into
# an integer with the `int` function, but we can name any
# object of any type with this name. 
a_number = int(input('Please type a number: '))
```

C, on the other hand, is a _statically typed language_, which means we MUST state the type of a variable when we declare it. We might write the Python statement above as the following sequence of three C statements:

```c
// C code with type declarations for the variable `a_number`
// and the function `input`.
int input(char *);
int a_number;
a_number = input("Please type a number: ");
```

To reiterate, a statically typed language like C requires us to write a declaration (e.g., `int a_number;`) that has no run-time purpose. Its only purpose is to tell the C compiler that the bit patterns I put into the memory location I've named `a_number` should be interpreted as an `int`. A dynamically typed language like Python allows us to just name an object without specifying any type information for that name.

In addition to declaring the type of the C variable `a_number`, I also had to declare the _signature_ (i.e., type information) for the function `input`. I did this because we are going to write this function `input`, and to use a function we've written, the C compiler needs to know its type information.

The C library does provide functions that are like Python's `input` function, but they aren't as easy to use as the one in Python. So we'll write a function in C that we'll call `input`, which will read a string from the user's terminal, convert the read string into an integer, and return that integer to the call site. As we write this function, we'll learn about specifying types, declaring and using arrays, commenting our code, and how not to allow bad guys to break our code.

## Diving into `main.c`

It's time to look at `main.c` in this project. This program doesn't do much. It prompts the user for a number, and then it prints a message saying what number the user typed.

The program has the following form, which I've written in pseudo code using Python comments. In this pseudo code, I explain why the file has this form.

```python
# Import the C libraries whose functions and constants we use.

# Define a local constant we use in our code.  By defining
# this constant in this manner, we differentiate it from the
# other place we use the number 10.  Can you find it?  In this
# way, we can change the number of digits allowed in the
# user's response without having to search through our code
# and hope we changed only the instances of `10` we
# want changed.

# The type declaration for the function `input` we wrote.  We
# will later notice that this declaration basically repeats
# the beginning of what we type when we give `input` a value
# (i.e., define it with a body of statements).  By putting
# this declaration at the top of our program, we can put the
# definition of `input` wherever we like in this file.

# Our `main` function, which should look very much like the
# code we started to write above.

# Our `input` function, which is explained below.
```

The `main` function contains 4 statements:

*   Line 10 declares the variable `a_number` to be of type `int`.
*   On line 11, we call the `input` function, which we know from the declaration of its signature on line 7 that this function takes a single input parameter of type `char *` and returns a value of type `int`. The returned value is stored in the variable `a_number`.
*   Line 12 prints the value in `a_number`.
*   Line 13 returns the value `0`, which indicates that the program completed successfully.

Let's now talk in detail about the syntax that you've seen and you will soon see in the function `input`.

## Comment characters

Go ahead and **comment out line 10** where we declare `a_number`. To do this, put two forward slash characters `//` at the start of line 10. You will see a red squiggle appear under `a_number` on line 11. Hover your cursor over `a_number` and read what the Replit IDE is trying to tell you. Yup, we need to declare this variable before we try to use it in a C expression or a C statement.

You just used one of the two ways you can comment code in a C program. Well, technically in a program that abides by _the 1990 ISO C standard_ (and later revisions). Two forward slashes have the same behavior as the `#` comment character in Python. The C compiler treats everything from the double slashes to the end of the file line as a comment (i.e., it ignore what's there).

The original C language defined a different mechanism for comments. This is what you see throughout this program. It uses a pair of matching characters: `/*` and `*/`. Anything you type between these bookends is ignored by the C compiler. I can even put a newline in the middle of this pair, and the C compiler will ignore that newline and will assume that the comment continues on the next line. You can see an example of this on lines 17-18.

As you write in C, you'll want to find a style of commenting your code that works for you. Notice that you can bury one style of comments inside the other. This means you can comment out a big block of your code if you were consistent in the way you used comments inside that big block. I chose to use the old-style comment characters in `main.c` so that you could use the new-type comment characters to play around with this program!

## Simple variable declarations

**Remove the comment characters you place at the start of line 10** so that we restore the declaration of `a_number`.

Declarations of variables with simple data types (e.g., `int` and `char`) have the form:

`<typename> <variablename>;`

You can declare multiple variables of the same type by separating their names with commas, as illustrated below.

`<typename> <variablename1>, <variablename2>, <variablename3>;`

And you can declare and initialize a variable (or variables) by adding an assignment.

`<typename> <variablename1> = <literal or variable of type typename>;`

This is illustrated on lines 21-23.

## Scope

Where you place the declaration matters. I placed `a_number` inside the body of the function `main`, which makes this variable local to this function. You cannot access it outside of `main`.

In general, scoping works similar to what you experienced in Python. There are two noticeable differences:

1. You can create blocks that aren't the body of a function using curly brackets, and declaring variables within these blocks makes those variables local to those blocks. You probably won't do that much, but you might see others do it.
2. Global variables in Python were tricky, but they are straightforward in C. Declare a global and use it wherever you'd like without the `global` keyword you had to use to update a Python global within a local context.

## Function declarations

When you declare a function, you are effectively describing the types of the formal parameters and the type of the return value. 

For example, line 7 says, "The function named `input` takes one parameter of type `char *` and returns a value of type `int`."

> We will talk more about the star and pointer variables in the next project. For now, just pretend that `char *` says `string`.

You see the same declaration information on line 16, where we wrote a function's interface in Python. The difference between lines 7 and 16 simply are that you don't give names to the formal parameters in a function declaration while you do at the top of a function definition.

You can see this in our example. On line 16, we specify that `prompt` is the name of the formal paramter to the function `input`. This variable is initialized with the value of the actual parameter at the call site (i.e., line 11 in our example) when `input` starts to execute.

## Strings and characters

Be sure to notice that a string literal in C is surrounded by double quote characters, as shown in line 11 (i.e., the actual parameter to the call to `input`).

Unlike Python, there is no formal string type, but there is a character type. You can define a character like this:

`char a_character = 'a';`

A character literal is a single character surrounded by single quotes. `char` is the type name for characters.

## Active learning interlude (ali1)

Using the empty `mycode.c` file, **experiment** with character initializations using different types of quotes. You'll want to start with a `main` routine like the following code:

```c
int main(void) {
    char c;

    // type your experimental statements here

    return 0;
}
```

What happens (i.e., what orange-squiggly, warning notifications does the Replit IDE give) when:

1.   You assign multiple characters surrounded by single quotes to the variable `c`?
2.   You assign a C string literal (i.e., a single character or multiple characters surrounded by double quotes) to the variable `c`?
3.   How do you correctly assign the character `a` to the variable `c`?

Please note that I'm not expecting you to understand the warning messages, but you should recognize that the C compiler will do something other than what you want to happen. Notice that you don't have to compile or run anything in this active learning interlude.

When you're done, you can see my solution in the file `solution-ali1.txt`.

## The `printf` function

We've used the `printf` function defined in `stdio.h`. Notice that this function takes _a variable number of arguments_.

The first argument is often written as a string literal. This literal is what you want printed, and it may contain what are called _format tags_. Format tags, in their simplest form, are written with a percentage sign (`%`) followed by a single character specifier.

For example, to print the input number, the `printf` statement in line 12 uses the format tag `%d`. This tag says that it should be replaced by a value of type `int`.

The rest of the arguments to `printf`, if any, are variables, literals, or expressions that produce values with a type corresponding to the desired format tags. In our example, we know that `a_number` is a variable of type `int`, and that's why the format tag we use is `%d`.

The order of the format tags in `printf`'s string literal must match the order of the rest of the arguments to `printf`.

`printf` is a very powerful function, and we have just skimmed the surface of what you can do with it. The format tags can get quite complex. To see what characters correspond to what types and how you can print values in some many different ways, please consult one of the many online tutorials about `printf`.

## The keyword `void`

Look at the definition of our `main` function (line 9). It returns an `int`, which is why we return `0` in line 13. The zero is a Unix convention that means the program completed without an error.

Line 9 also says that `main` takes no parameters, which we indicate by writing `void` in the parentheses. Whenever you write a function that doesn't return a value, you should set the return type of the function to `void`.

While `void` looks like a type here, it isn't. You cannot declare a variable like this:

`void not_a_variable;`

Try it in `mycode.c` and see what the Replit IDE says with its squiggly message. Remember that you can, but do not have to, write this declaration inside a function!

We will come back and talk about `void` when we talk about pointers.

## Understanding the `input` function

Let's now turn our attention to the implementation of `input`, which starts on line 16 and goes to the end of `main.c`.

You've already seen the interface for this function in its declaration on line 7.  The function takes a single input parameter, which we name `prompt`, of type `char *` (or what you should think of as the type for a string). This function returns a value, which is of type `int`.

Lines 17-18 contain a comment that acts like the docstrings we saw in Python, but without the nice tie into the help system. The comment simply says what the function does in English, and it includes any assumptions the function's implementation makes (e.g., the input number should be less than 10 digits in length).

The next set of C statements (lines 20-23) are declarations and initializations of the local variables used in `input`. We will talk about them in a moment.

Looking at the comments that preface each of the following blocks of C statements, we can understand `input` in pseudo code.

1.   The function prints the `prompt` string (i.e., the actual parameter at the call site), and it grabs the user's response as a string, which it stores in the variable `response`. We will talk more about `fgets` in a moment, and then we'll revisit it in the next project to understand how it returns its result through one of its input parameters.
2.   It next checks the first character in the `response` string. If the character is a plus or minus sign, it will skip over this character before converting the remaining string of digits into an `int` value. If the character is a minus sign, it will also record that the `result` should be negative, as indicated by the `is_neg` Boolean variable. We'll talk more about the `bool` type below.
3.   The function then loops over the remaining characters in the `response`. For each character, it checks to make sure that the character is a number between 0-9, and if it is, it adds that number to the running `result`. If it isn't, the program prints an error message and exits. Notice that `exit` is a function that takes a single integer argument, and this integer follows the Unix convention that says any number other than 0 means that the program failed to run correctly. I could have chosen different non-zero numbers for the different error conditions, but I simply exit with a `1` on every error condition. The `exit` function is defined in `stdlib.h`.
4.   Starting on line 49, the function checks to see how we exited the previous while-loop. If we made it to the end of the `response` in under 10 numerical characters, we have a well-formed response. If the character on which we exited the while-loop is not a newline character, then we have another error condition (i.e., the user typed too many digits).
5.   The work of the function is almost done, and lines 57-59 check to see if we earlier saw a minus character. If we did, we make `result` into a negative number.
6.   And finally, it returns the value of `result`.

> There is a lot going on in this function's body. In general:
>
> *   We read the user's input as a string of number characters with an optional `+` or `-` sign as the first character.
> *   We create the integer corresponding to the input sequence of digits by visiting each digit starting with the most-significant one.
> *   We turn that digit into a number between 0 and 9, multiple the current value of the result (which we initialized at the start of the loop to 0) by 10, and then adding in the new digit's value.
> *   We perform a bunch of error checking (e.g., inputting an unexpected character or too many digits).
> *   We make sure we return a negative result if the input started with a `-` character.
>
> Now that you have a big-picture view of the routine, you might want to back up and read the details again.

Phew! That was a lot of work. Are you ready to use this function as a way to learn a number of new concepts around types?

## The `bool` type

Line 23 defines `is_neg` as type `bool` and initializes its value to `false`. It is set to `true` on line 31 if the `response` starts with a `-` character.

> Line 31 demonstrates that you don't need to enclose the body of an if-statement (or in general any compound statement) in curly brackets _if this body comprises only a single C statement_. You could even add a newline after the closing parenthesis, making the C if-statement look a lot like a Python if-statement (minus the colon needed in Python).

The first thing you should know is that `bool` is not a type in the original C programming language. It is defined in `stdbool.h`, as are the constants `true` and `false`. Note that these constants are not capitalized as they are in Python.

The `bool` data type is basically an `int`, where `false` has the value `0` and `true` the value `1`. Go ahead and print the constants (or hover over the names in the Replit editor pane) if you want proof.

Now look at line 57. The condition in the if-statement checks only the value of the variable `is_neg`. If you think about this, it means that `0` evaluates to a false condition and all other integer values evaluate to a true condition.

We could have written either of these two equivalent C statements:

1.   `if (is_neg == true) result *= -1;`
2.   `if (is_neg != 0) result *= -1;`

You may be tempted to write the first as you are starting to learn to program, but if you name your variables well, you won't need it (and you won't see that in the code written by experienced programmers).

The second is what is actually taking place in the language, but it's very confusing for a human to read quickly. This comparison mixes a variable of type `bool` with a literal of type `int`. It works because of the fact that Booleans in C are just integers, but this statement discards all the abstraction we inserted to try to make the program easier to read.

In summary, try to get comfortable reading and using the form I used on line 57.

## Fancy assignments

You'll have noticed that C, like Python, allows you to write:

`result = result * -1;`

as

`result *= -1;`

You can substitute the `*` with most other binary operators. Line 32 uses this form with addition.

Unlike Python, C lets you be even more terse with two common additions and subtractions. While we can write:

`i += 1;`

we can equivalently write:

`i++;`

Both increment the variable `i` (or any other integer variable you place there) by `1`. Similarly, you can write:

`i -= 1;`

as

`i--;`

Just remember that you can't do this with multiplication (`**` means something else as we'll learn in our next project) or with division (since `//` starts a comment).

## Active learning interlude (ali2)

Copy the following code into `mycode.c`, deleting whatever was previously there.

```c
#include <stdio.h>
#include <stdbool.h>

#define STRING char *

int main(void) {
    bool is_capital;
    char c = 'x';
    int i;
    STRING s;

    /* Play with fancy assignments */
    i = 42;
    i /= 7;
    /* here the value of i is: ?? */
    i++;
    /* here the value of i is: ?? */
    i *= i;
    /* here the value of i is: ?? */
    i--;
    /* here the value of i is: ?? */
    i -= (i / 10);
    /* here the value of i is: ?? */

    printf("i was 42 and is now %d\n", i);

    /* Play with Boolean type */
    is_capital = (c == 'X');
    if (is_capital) {
        s = "a capitalized X";
    } else {
        s = "a little x";
    }
    printf("We found %s ('%c').\n", s, c);

    return 0;
}
```

The first part of the `main` function starts with `i` set to the integer value `42`. It then contains a sequence of "fancy assignment" statements. Can you change the `??` in each comment to say what value `i` has at each point in the program?  Try to figure this out before you compile (i.e., type `make mycode` at the shell prompt) and run the program (i.e., type `./mycode` at the shell prompt).

The second part of the `main` function works with characters and strings, and it shows how we can set a `bool` variable using a comparison operator. Make sure you understand what's taking place, and please notice the format tags you use for strings and characters.

Go ahead and experiment by changing the character you use to initialize `c`. How would you fix the code to handle the case where `c` is not an `x` or an `X`? Compile and run the program after your changes.

When you're done, you can see my solution in the file `solution-ali2.txt`.

## Derived data types

To this point, we've been talking about C's basic data types, i.e., integers (`int`), characters (`char`), and the two floating-point types `float` for single precision and `double` for double precision. Besides these basic types, C has four _derived_ data types:

*   arrays
*   structs
*   pointers
*   unions

They are called derived types because each form uses the basic types in their construction.

## Declaring an array data type

The variable `response` used throughout the function `input` is an example of a derived type. In particular, it is an array type. This variable is declared on line 20, and as you can see, it looks like the start of a declaration for a `char` variable. The difference is the addition of the square brackets at the end of the declaration. These square brackets indicate that I want not a single character, but an array of characters (i.e., what we thought of as a sequence in Python).

In fact, I have declared `response` to be an array of exactly `RESPONSE_MAXLEN` characters. This is important point. When you declare an array in C, you must specify its length _when you declare it_. In addition, this length must be known at compile time, i.e., not determined at run time. `RESPONSE_MAXLEN` is a constant in `main.c` and thus satisfies this requirement. This also explains why, if you think about it, I needed to specify that the input number couldn't be more than some specific number of digits: The array I'm using to capture the user's input was set to be a fixed size when I wrote the program!

We'll learn how to get around this limitation in the next project, but this need to define the size of your array before you know the size of the data you want to put into the array causes all kinds of headaches in C.

> For example, look at line 27 and the call to `fgets`. This function gets a string (i.e., an array of characters) from an open file.
>
> *   The first parameter to `fgets` is the start of the character array into which you want the string put.
> *   The second parameter is the length of the array; `fgets` won't read more than this number of characters from the open file.
> *   The third parameter is the file descriptor from which it should read. In our case, I specified that I wanted to use `stdin`, which tells the system to read from the user's terminal.
>
> `fgets` in C, which is defined in `stdio.h`, looks like Python's built-in `input` when we specify `stdin` as its third parameter. The big difference between these two "input" functions is that Python's `input` function returns a string large enough to hold whatever the user types (up to and including a typed newline), while C's `fgets` function can only capture as many characters (up to and including a typed newline) as you specify in its second parameter.
>
> And programs that don't have the declared size of the first parameter to `fgets` match the value of the second parameter create opportunities for nefarious actors to take over your program and make it do things you never intended it to do.
>
> This begins your education into errors and security vulnerabilities you'll encounter in C that you won't see in Python. Python does a lot of checking behind the scenes (often incurring runtime overheads), while C assumes you know what you're doing.
>
> For more on this topic, you might read some Stack Overflow threads about how to convert a string to an integer. You'll read about how you should never use seemingly useful library functions like `atoi`, which converts a string of numbers into an integer. Instead, you should use library functions like `strtol`, which provides success/failure feedback, as I've sorta done in my `input` function with the error checks. You should also be avoid as much as possible C library functions with _undefined behavior_ under certain inputs (or check for those inputs before calling these library functions). You'll learn a lot more about undefined behavior in CS 61.

## Indexing into an array

Once we have a variable of type array (like we declared on line 20) and filled it with a value (as we did on line 27), we can now access the individual elements in this array using square brackets.

The if-statement on line 30 illustrates this. Indexing in C looks just like indexing in Python. Plus, arrays in C start with index 0, just like our sequences in Python. Line 30 checks to see if the first character of the user's input is a sign instead of a number.

Note that the Boolean AND operator in C is `&&` and the Boolean OR operator is `||`, not `and` and `or` as we saw in Python.

The check for a sign character at the start of a variable `response` in Python is:

```python
if response[0] == '+' or response[0] == '-':
    if response[0] == '-':
        is_neg = true
    i += 1
```

and in C is:

```c
if (response[0] == '+' || response[0] == '-') {
    if (response[0] == '-') is_neg = true;
    i += 1;
}
```

## No slicing

Unfortunately, you cannot use any of the fancy slicing things you learned to do with Python sequences with C arrays. You either have to build these functions yourself, or find an equivalent in some C library.

## The `char` type, revisited

By the way, the `char` type also functions like an `int`, as demonstrated on line 44. The second parenthetical in this statement's expression accesses the ith character in the `response` array and subtracts this character from the character `0`.

Why does this work?

1.   It takes advantage of the fact that the `char` is just _a short integer_. In particular, `char` is an 8-bit integer (i.e., it can hold any value between `-128` and `127`). Unlike Python's integers, integers in C all have a size. `int` is typically a 32-bit quantity. There's also something called `short`, which is a 16-bit integer, and `long long`, which is a 64-bit integer. These are all signed integers. You can also create unsigned integers by adding the keyword `unsigned` before your integer type. For example, an `unsigned char` variable can hold any value between `0` and `255`. You can also build your own short integer type using the `enum` keyword. There's a lot of history and exceptions here, but this will get you started.
2.   Since C will treat a character value like an integer, I can subtract two characters and learn the distance between their ASCII representations.
3.   The expression also takes advantage of the fact that the ASCII encodings for `0` through `9` are sequential with `0` coming first. As such, `'1' - '0'` produces the integer `1`.

Now you know why I was able to use, on line 38, the less than (`<`) and greater than (`>`) operators to check if the characters in `response` were numbers!

## Active learning interlude (ali3)

We just learned that we can operate on values of type `char` as if they were values of type `int`. We also learned that the number characters in ASCII are next to each other with `'0'` having the smallest numerical value.

Look at the following C code:

```c
#include <stdio.h>

int main(void) {
    char s[5];

    /* Initialize s to "cs32" */
    s[0] = 'c';
    s[1] = 's';
    s[2] = '3';
    s[3] = '2';
    s[4] = '\0';  /* the null character */

    /* Change the characters "32" to "61" using
     * only the fancy assignments we learned. */
    printf("Preparing students from %s ", s);
    
    // INSERT YOUR CODE HERE
    
    printf("for %s\n", s);
    
    return 0;
}
```

The `main` routine declares an array of 5 characters named `s`. It then initializes this array by writing a character into each of the 5 array locations.

The last character we write looks a bit strange. We write the character `'\0'` into location `s[4]`. This character is called _the null character_.

> Every string in C must end with a null character. It is how C knows that where each string ends. 

Copy this code into `mycode.c` and see if you can use the fancy assignments we previously used on integers to modify two of the characters in `'cs32'` so that it becomes `'cs61'`. Do you remember how to compile and run `mycode.c`?

When you're done, you can see my solution in the file `solution-ali3.txt`.

## The other derived types

We will talk about structs in the fourth project, when we move from C to C++. C++ adds object-oriented ideas to C, and structs like classes are a way of grouping data together. C structs, however, are a bit more as they also allow the programmer to specify the layout of the elements of a data type in the computer's memory. This probably doesn't surprise you given what we discussed about C arrays and how specific we must be about their memory size. 

We won't discuss C unions, as you won't use them much unless you are writing C code for embedded systems. Plus, you should learn about structs before you attempt to understand unions.

The last derived type, pointers, we'll discuss in the next project.

## Summary

In this lesson, you learned that:

1.   C contains two different ways to include comments in your program, and if you carefully choose a style of commenting, you can more easily comment out large blocks of code during testing and debugging.
2.   You don't always need curly brackets in an if-statement (or looping statement).
3.   The C programming language requires you to be quite specific with the types of your C program's variables, and you must declare a variable's type before you initialize it with a value.
4.   C contains a handful of basic types and four categories of derived types.
5.   There are many integer types, and these integer types come in different sizes (i.e., they can hold a different range of values).
6.   The `bool` data type doesn't exist in C's core language, but can be used if you include `stdbool.h`.
7.   You must specify the size of a C array data type at compile time, and you use square brackets to index into this array. C arrays are 0-based.
8.   C strings must end with a null character. String literals in C automatically include this null character.
9.   You should use the keyword `void` if a function you write doesn't take any parameters. You should also start a function definition with the type of its return value, or `void` if it doesn't return a value.
