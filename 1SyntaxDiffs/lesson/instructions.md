## Welcome

Congratulations on completing either Harvard's CS 32 or CS 50 courses! I understand that you're interested in taking another CS class, and that's wonderful news.

This mini-curriculum is meant to help you begin your transition from programming in Python and/or C to programming in C++. It's specifically meant to help you successfully start in Harvard's CS 61 class, which uses C++ for its programming problem sets.

> _Why does CS 61 use C++ and not C or Python (i.e., why do I have to learn a new programming language)?_
>
> CS 61 focuses on the fundamentals of _systems programming_, which is different in some interesting ways from application programming. Most importantly, it about writing the code that helps application programmers write and run their application software.
>
> *   Who figures out how your application data structures are actually laid out in the computer's memory? A systems programmer.
> *   Who keeps your application from interfering in undesirable ways with another person's application? A systems programmer.
> *   Who wrote the shell program that responds to the commands you type at the shell prompt? A systems programmer.

To write the software that supports these kinds of things that application programmers expect, a systems programmer writes code closer to the computer hardware, and this requires a programming language that _allows you to get closer to the hardware_ than you can with Python. While C is a programming language that lets you get very close to the hardware, it isn't a language that helps you write large pieces of correct code. C++ is a programming language that does both these things, and it is a very popular one.

## Curriculum overview

The curriculum comprises 5 projects, all contained in this Replit unit called _Py2Cpp_. I suggest that you work through the projects in order, where the order corresponds to the number at the start of each project name. If you find any particular topic in this mini-curriculum easy or straightforward, please feel free to skip ahead!

**If you took CS 50**, I encourage you to use the first two projects as review of what you should already know about C. Do the active learning interludes and focus on shoring up your knowledge. The third project looks at pointers in C, and I encourage you to _work through this project in detail_. In my experience, every new programmer needs more practice with pointers. Finally, projects 4 and 5 should be new to you.

**If you took CS 32**, start with the first project. I ask you to learn C before C++ because a good number of the design decisions in C++ are a result of its backward compatibility with C. If you don’t know this history (or if you just know Python), a bunch of the design decisions in C++ are hard to defend.

Both CS 32 and CS 50 teach Python, and so I'll often use that language as a way to see what we're trying to accomplish in C or C++. And since I currently teach CS 32, I make reference to some of what we discussed in that class. If you didn't take CS 32, you can ignore these comments. 

So, let's get started!

This is the first project, and it explains:

1. a few of the most important, basic syntax differences between C programs and Python scripts; and
2. how to compile a C program into an executable that you can run.

By the way, I'll use the terms "programs" and "scripts" interchangeably. Both mean _a file containing a list of statements written in some high-level programming language_.

## Feedback and acknowledgments

This mini-curriculum is a work in progress. If you have thoughts about how it could be improved, please send them to mike_smith@harvard.edu.  If you're interested in helping improve the existing projects or create new ones, please say that in your email. I'd love the help!

I'd like to express my thanks to Michaela Bibby, who was the very first tester of this and the other projects in this unit. Thank you!

## C syntax

Both C and Python are _procedural languages_, and this means that you'll immediately see numerous syntactical structures in C that remind you of Python. Your first instinct should be to read the C code as you would Python code.

What's trickier is writing C code. There are a number of things you do in Python that don't matter in C, and things that you need to do in C that you don't do in Python. Let's talk about those things.

## The importance of the semicolon

Every simple C statement ends in a semicolon.

**Take a look at the function named `kandr` in `main.c`**, which is contains the core of traditional hello-world program from Kernighan and Ritchie's _The C Programming Language_ book.

In `kandr`, you'll see that I placed a semicolon at the end of line 4. The purpose of this semicolon is to mark the end of a statement.

> Why do we as C programmers have to mark the end of our statements?
> 
> Because the C compiler ignores whitespace.

As we learned in both CS 32 and CS 50, the Python interpreter is sensitive to whitespace. Python statements end with a newline character, and indentation demarcates the blocks that are part of a compound statement.

> **NOTE:** The big green button in Replit doesn't work in the `py2cpp`
> projects. I'll explain these commands in a moment. Just type them
> for now.

Go ahead and **run this program** by typing the following in the shell.

```none
~/py2cpp$ make -s; ./main
```

The C program `main.c` prints `Hello World` as expected.
 
Because C ignores whitespace, you can add as many spaces and newlines as you like in a C statement. I'm not saying you _should_ add lots of whitespace, but you _can_.

Let's try this. **Modify line 4 in `main.c`** in the following ways:

1. Add a newline between the "f" and the open parenthesis;
2. Add a newline between the string's closing double quote and the closing parenthesis; and
3. Add two newlines before the semicolon.

Now **run the program again** (i.e., type the same line as above, or use the up-arrow key in the shell). There's no change in the program's output. The compiler ignored all four of the newlines we added.

Of course we have to be a bit careful where we stick in extra whitespace. You cannot split something that we want parsed as a single thing. For example, you can't insert whitespace into the name `printf` without creating two new names, or insert extra whitespace into the string `"Hello World"` since whitespace is part of the string.

**Undo your changes** before moving on to the next section.

## Where you don't use semicolons

**Look at `main.c`** and write down the line numbers of the lines that do NOT end in a semicolon.

You should have written 1, 3, 5, 7, and 10. The last four of these lines are ones involving a curly bracket, which we'll discuss in a moment. Line 1 is something that looks like a simple statement, but it doesn't end in a semicolon. What gives?

Well, the statement in line 1 isn't a C _language_ statement, but a C _preprocessor_ statement. Preprocessor statements start with a hash symbol (`#`) and end with a newline. We will talk about preprocessing and compilation in a moment, but where everything we write in a Python script is a Python language statement, not everything we write in a C program is a C language statement.

To add to this confusion, the designers of the C preprocessor decided that (like Python) newlines terminate preprocessor statements and hence there is no need for a semicolon at the end of them.

This difference in how C preprocessor and C language statements end is a bug waiting to happen. At some point, you'll add a semicolon to the end of a C preprocessor statement and/or leave off a semicolon from the end C language statement.

* C preprocessors have become more tolerant over time of these unnecessary semicolons in preprocessing statement. Go ahead and **try adding a semicolon to the end of line 1**. Again, clean up your experiment before continuing.
* C compilers have become better over time at telling you where you forgot to type a semicolon. Go ahead and **remove the semicolon at the end of line 4**. Fix the code and then move on.

I wish I could say that things will always be this easy, but I can't. If you ever have a compilation error that makes no sense, you might first check your semicolons.

## Preprocessing

So, what is this preprocessing?

Preprocessing allows us to add additional directives in our program that save us typing time and do other types of text substitutions on our source code before it is sent to the C compiler.

You see one of these types of text substitutions in `main.c`. The `#include` directive is like the Python `import` command. It tells the C preprocessor to take the contents of the specified file and insert those contents into this file at this point.

In our example, `printf` is not a command built into the C programming language, but one defined in the file `stdio.h`. This is different than Python, where `print` is a built-in function. However, in Python, we had to (for example) import `sys` to get access to `sys.argv`.

There are more C preprocessing directives that you can use. For instance, the `#define` directive allows you to create macros. This might be as simple as giving a name to some special constant in your program:

`#define pi 3.1415926535`

Or you might wish to use the power of the C preprocessor's parameterized macros:

`#define MAX(x,y) ((x) > (y) ? (x) : (y))`

which allows you to write `MAX(var1, var2)` in different parts of your program, where `var1` and `var2` change at each use point depending upon the two variables you wish to compare. The C preprocessor would then substitute this phrase for the parameterized C code that ends the `#define` statement.

Don't worry if you don't understand the C code embedded in this preprocessor macro. The C code starts with the double open parentheses, and if you did understand it, you'd realize that it reminds you of conditional expressions in Python. Recall that you can write `MAX` in Python as follows:

```python
# Calculating max in Python
the_max = x if x > y else y
```

which looks like this in C:

```c
// Calculating max in C
the_max = x > y ? x : y;
```

All that the definition of `MAX` did for us was allow us to write the C statement above as:

```c
// Calculating max in C using the MAX macro
the_max = MAX(x,y);
```

Of course, we could have written the following in Python because Python defines `max` as a built-in function:

```python
# Calculating max in Python using the built-in function
the_max = max(x,y)
```

The fact that you have to define your own max function in C but not in Python hints at the reality that C provides a very minimal builtin core when compared with the core of the Python language.

Moving on, there are also C preprocessing directives that allow you to say at compile time whether you want certain code in your program compiled or not. This is very useful for debugging. In particular, you can simply put your debugging statements in the following directives and then define or not define the `DEBUG` name at compile time. The code within this directive appears in your program only when `DEBUG` is defined.

```c
#ifdef DEBUG
    /* Your debugging statements here */
#endif
```

My goal is not to make you an expert in C preprocessing directives, but to make you aware that the simple C program in `main.c` includes two different programming languages! There are many resources on the internet that will help you learn a bit about C preprocessing. Some of the examples above were taken from [the C preprocessing tutorial on tutorialspoint.com](https://www.tutorialspoint.com/cprogramming/c_preprocessors.htm).

## Preprocessing and compilation

Ok, you now understand a bit about preprocessing, but what exactly is happening in that command you wrote to run the program?

Let's start by recalling what happens when we ran a Python script. When we do this, Replit passes our script to the Python interpreter, which reads through our script, parsing and running each statement. If what we wrote didn't make syntactic and semantic sense, the interpreter stops and prints some sort of error message.

What we typed earlier was two commands. We first asked the shell to run `make -s`, which printed nothing. And then asked it run `./main`, which gave us our program's output. Recall that the semicolon is just the way we tell the shell to run a sequence of commands.

`make` is a command that runs the C preprocessor and the C compiler on our `main.c` program. It produces `./main`, along with a few other files.

We can see these files by **typing `ls` at the Console prompt.** This command tells the shell to list the files in the current directory.

Unsurprisingly, you will find `main.c` in this listing, which we knew would be there because it's also in Replit's file listing in the lefthand panel (assuming you have highlighted the "Files" icon).  You'll also see other files in both the `ls` listing and Replit Files view.

There are, however, several other files in the `ls` listing that Replit chose to suppress (i.e., hide). One of these is `main`, which is the same as `./main`. The latter just says, "I really want `main` in my current directory (as indicated by the `./` prefix)."

The `Makefile` file contains instructions that tell the `make` command what to do. If you want to see what's in it, type `cat Makefile`. I won't explain what you see except to say that you can see a command to `make` at end of this file that tells it what to do if you type `make clean` at the Console prompt.

Go ahead and **run `make clean`** in the shell.

What happened? You might want to run `ls` again. Yup, it removed all the files that `make` made in our previous runs. `make` is a powerful program that you can learn about from resources on the web.

Let's have `make` be a bit more talkative about what it is doing. Recall that we ran `make -s`. The `-s` parameter to `make` tells it to stay silent while it runs. We can remove it to see what `make` was doing for us.

**In the shell, type `make clean`, hit return, then type `make` and hit return**.

You should see to commands that both start with `clang`, which is one of the C compilers that you can use.

So, we're definitely running a C compiler. It just happens to be buried in this `make` command. This is done to try and hide the complexity of what it takes to compile a C program.

But what about the preprocessing step. Well, that is buried within the C compiler. It's one of the first things that the C compiler does with our `main.c`.

To see this, **type `clang -E main.c` in the shell and hit return**.

A whole bunch of stuff is printed on the Console. So much, in fact, that you might not be able to scroll back far enough to see everything (i.e., the shell's output buffer might not be big enough). At the end of this listing, however, you can see what looks like most of our `main.c` program.

What's missing is the `#include` statement, and that's because the C preprocessor run inside of clang's execution replaced that `#include` directive with the code in `stdio.h`. Thank goodness we didn't have to type all this, huh?

Notice that it also replaced `printf` with `__printf_chk` because `printf` happens to be a parameterized C preprocessor macro defined in `stdio.h`!

In summary, our command `clang -E main.c` told clang to run just the C preprocessor and print the result to the terminal. Normally, this output would be fed to the next step in the compilation phase. There are many steps run during compilation (i.e., inside our two runs of `clang`), but in the end, we get an executable, which Replit asked clang to call `./main`.

Lots of details and lots of work done for us, but no magic!

## Curly brackets

Let's return now to the examples in `main.c` where we didn't use a semicolon to end a statement. We dealt with line 1, in which we learned all about C preprocessing and the language in which we can write commands to direct it. The other examples are lines ending in a curly bracket.

> We don't use a semicolon in these cases because curly brackets in C are a way to wrap a sequence of statements together into what is called a _block_.

Our `main.c` program contains two function definitions. The first function is called `kandr` and the second called `main`.

In Python, we indicated a function definition by starting a Python statement with the keyword `def`. We followed this keyword with the function's name, then its parameter list in parentheses, and then colon, which indicated the start of the function's body. A function's body is just a sequence of statements, but Python indicated that sequence with indentation. C uses curly brackets to enclose the sequence of statements in its functions' bodies.

The body of `kandr` contains one statement and `main` two.

## A quick word about functions and `main`

Notice that this is no special keyword that indicates a function definition in C. The `void` and `int` names at the start of `kandr` and `main` respectively are the types of the return value of the function, as we'll discuss in the next lesson.

Written in Python, `main.c` would have looked like this:

```python
def kandr():
    print("Hello World")

def main():
    kandr()
    return 0

if __name__ == '__main__':
    main()
```

Again, don't worry about the fact that you probably don't understand how to write a function definition in C. We cover this in the next unit.

More importantly at this point, we could have written the Python code above like this:

```python
def kandr():
    print("Hello World")

# main, where the script starts its execution
kandr()
```

The Python interpreter doesn't need to see a `main` function, since it happily starts executing any statement it finds in your script.

In C, you can't have C statements outside of function definitions. You can define a lot of things (e.g., functions and datatypes) outside of functions, but no statements like:

`y = m * x + b`

or even:

`kandr()`

If a C program doesn't start running at the first statement in the program, where does it start?

It looks for a function called `main` and starts there. Every C program you write must have a `main` function.

## Active learning interlude (ali1)

I realize you don't have much C knowledge under your belt, but let's get into the groove of trying to write and run C code nonetheless.

I've created an empty C file called `mycode.c` in this project. It's in this file that you should try writing your own C code as you hit each of these active learning interludes.

I've configured the `Makefile` in this project to compile `mycode.c` as a standalone executable, which means it won't interfere with the code we have in `main.c`. To create a runnable version of `mycode.c`, you have to type `make mycode` in the shell, and then assuming you had no compile-time errors, you'd type `./mycode` to run it.

I've also made it so that your `mycode` executable is not a hidden file. You'll see it in the list of files to the left. This file will, however, disappear if you run `make clean`. That's ok, as you can recreate it typing `make mycode`!

Alright, let's try something. Click on `mycode.c` and write a C program that prints "I'm a C programmer!" when compiled and run.

You'll need:

*   A `main` function with an interface line just like the one in `main.c`.
*   A `#include` if you're going to use a `printf` statement, which you should!
*   There's no need for any functions except `main`.
*   Did you put semi-colons and curly brackets where you need them?
*   Did you compile `mycode.c` as mentioned above?
*   When it successfully compiles, run it as mentioned above!

When you're done, you can see my solution in the file `solution-ali1.txt`.

## If-statements

Ok, but back to these curly brackets. C not only uses curly brackets to indicate the bodies of functions, but it also uses them to indicate the bodies of compound statements like the ones we learned in Python.

Let's look at a C program with an if-statement that controls what our C program prints.

I've included three text files in this project.

* `main1.txt` is a copy of `main.c`
* `main2.txt` is a C program that wraps three `printf` statements in an if-statement
* `main3.txt` is the same as `main2.txt`, except it removes a lot of the newlines and spaces that made `main2.txt` easy for us as humans to read.

**In the shell, type `cp main2.txt main.c`**.

**Click on `main.c` and look at the C code.** You'll see that we've replaced the function `kandr` with a function named `who`. The body of this function contains a C if-statement, which looks a lot like the syntax for Python if-statement, except for three things:

1. The Python `elif` becomes `else if` in C.
2. The blocks of code dependent upon the condition in an `if`, `else if`, or `else` statement are enclosed in curly brackets.
3. The Boolean condition or expression that evaluates to a Boolean in a C `if` or `else if` statement must be enclosed in parentheses. This isn't obvious, but see what happens if you **remove the parentheses on line 6 and hit run**. Make sure you put them back before proceeding.

We will see these same curly brackets in a later lesson when we talk about loops in C.

**Go ahead and make and run this new `main.c`.** Feel free to change the constant integer defined as `STUDENT` on line 3 and see if you can get the other `printf` statements to execute.

## Style

You might wonder about the placement of the curly brackets. Must they be where you see them in the code I've written?

Short answer: No.

You're seeing my style. You might prefer to see `who` written in one of the following styles, where I've chosen a different style for each different if-clause:

```c
void who(void) {
    if (STUDENT == 32)
        {
        printf("Hello CS 32 star!\n");
        }
    else if (STUDENT == 50)
    {
        printf("Hello CS 50 friend.\n");
    }
    else {
        printf("Hi, nice to me you.\n"); }
}
```

To be clear, don't mix styles. Pick one that makes you happy and stick with it. All of this is illustrating that whitespace doesn't matter to the C compiler. How you use whitespace is up to you and for your benefit.

## Whitespace eliminated

Let's take this to the extreme. Copy `main3.txt` into `main.c` and run it. **Type `cp main3.txt main.c` in the shell, and then make and run it**.

Same output as the first time we ran `main2.txt` as `main.c`, right?

**Now look at our new `main.c`**. This program puts all the C language statements on one line (line 3), and it removes as much of the whitespace as possible. It uses whitespace only to separate keywords and names where we don't have any other reserved C character to separate them.

Go ahead and say it, "Yuk."

But it ran! Clearly I was right in my earlier comments about whitespace in the C language: You need only semicolons and curly brackets to know when things start and stop. The C compiler ignores whitespace; only humans need the whitespace that makes C programs readable.

## Clean-up

If you want to start this lesson again, just **type `cp main1.txt main.c` in the shell and hit return**.

## Active learning interlude (ali2)

Let's try a debugging exercise using what you have learned.

Copy the following code into `mycode.c`, erasing anything that you had in that file.

```c
#include <stdio.h>

#define MIN(x,y,z) ((x) < (y) ? ((x) < (z) ? (x) : (z)) : ((y) < (z) ? (y) : (z)))

int main(void) {
    int x = 1;
    int y = 3
    int z = 6;
    int answer

    answer = MIN(x, y, z)
    if (x % 2 != 0) {
        answer = x
    }
    if y % 2 != 0 && y > answer
        answer = y
    if (z % 2 != 0 && z > answer) {
        answer = z;
    printf("%d\n", answer)

    return 0;
}
```

This code _tries_ to implement in C the finger exercise on the bottom of page 24 of Guttag's textbook \[3rd edition\]. Unfortunately, I didn't do a good job. Your task is to fix my errors.

As John Guttag explains, this program "examines three variables--`x`, `y`, and `z`--and prints the largest odd number among them. If none of them are odd, it \[prints\] the smallest value of the three."

The errors are all in how I used curly brackets, semicolons, and parentheses in the if-statements and their conditions. See if you can get it to compile and run. Make sure to change the integer values assigned to `x`, `y`, and `z` to test all paths through the code!

When you're done, you can see my solution in the file `solution-ali2.txt`.

## Summary

In this lesson, you learned that:

1. Python and C take different approaches to indicating when a statement ends and how a sequence of statements is blocked together.
2. The C programming language requires you to compile your program into an executable before running it.
3. C programs often contain both C language statements and C preprocessor statements, which are two different languages.
