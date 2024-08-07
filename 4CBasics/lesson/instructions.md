# Preface

It's time for you to move from C to C++. For Bjarne Stroustrup, this transition occurred at the end of 1970s, when he decided that the world needed a better version of C. He envisioned a programming language that would continue to allow the programmer to deal directly with the machine (like C), but would also include the abstraction and expressibility he saw in the object-oriented languages of that time. His efforts produced C++, which he introduced to the world in the 1985 edition of his book titled _The C++ Programming Language_.

Since 1985, the C++ standard has gone through six revisions. It is an enormously popular language and powers many applications we use in our lives. It is also a large and complex language. You should definitely not feel that you need to understand the entire language before you begin to write C++ code.

Getting started is easy as nearly every valid C program is a valid C++ program. Because of this, you can learn bits and pieces of C++ at your leisure, but you will want to complete your transition from C to C++ because:

*   You will gain strong type checking (i.e., the C++ compiler will catch more errors for you) and exception handling (i.e., C++ makes error handling easier).
*   You will want, as a Python programmer, to return to the world of data abstraction, classes, and objects, which are not available in C.

This project is meant to just get you started in C++. I don't attempt to cover all of the features of the language. Specifically, this fourth project covers:

1.   Input/output objects in C++
2.   Namespaces and the C++ `std::` namespace
3.   Error handling in C++
4.   C++ strings and other objects
5.   Dynamic memory allocation in C++

## Feedback

This mini-curriculum is a work in progress. If you have thoughts about how it could be improved, please send them to mike_smith@harvard.edu.  If you're interested in helping improve the existing projects or create new ones, please say that in your email. I'd love the help!

## File extensions, compilation, and hello world

So let's get started! And getting started means a return to the program that Brian Kernighan and Dennis Ritchie used to teach us programmers how to code in C:

```c
#include <stdio.h>

int main(void) {
    printf("Hello World\n");
    return 0;
}
```

I'm about to show you the syntax for this simple program in C++, but first please notice that we're in a Replit C++ project now. Our source code files no longer have the extension `.c` as in our previous projects. They now have the extension `.cpp`, which stands for C-plus-plus.

> Compile `main.cpp` (i.e., you type `make clean` and then `make main` at the shell prompt). You'll also see that we're using a "plussed-up" version of the `clang` compiler. Otherwise, everything we learned about compilation of source files and running the resulting object files remains true.

The following is the "Hello World" program in C++, using its version of the standard I/O library (called `iostream`) and the stream facility that some programmers prefer over `printf`. It is also what you'll find in this project's `main.cpp` file.

```cpp
#include <iostream>

int main(void) {
    std::cout << "Hello World!\n";
    return 0;
}
```

You'll see a number of similarities between the C and C++ code.

*   Both languages require you to include a `main` function, where execution begins.
*   The signature for the `main` function is unchanged, and you still return `0` to indicate the successful conclusion of your program.
*   Both languages have you include a library to access the functions (and C++ objects) that allow you to read input from and write output to the terminal or files.

While you can use `printf` and `fgets` in C++ (go ahead and try adding a `printf` statement to `main.cpp`), you are given a new mechanism for reading and writing character data called _streams_. The `iostream` library defines a number of stream classes and pre-defined stream objects. We'll use the stream objects `cin` and `cout` here, as they provide us with functionality similar to `fgets` and `printf`.

You use the standard output stream object `std::cout` with the stream _insertion_ operator `<<`. What the first line in the body of the function `main` is effectively saying is, "to the end of the standard output stream, please insert (or append, if you prefer that imagery) the string 'Hello World!\n'."

You can equivalently write this as:

`std::cout << "Hello World!" << std::endl;`

This demonstrates two things:

1.   An alternative way to add a newline character to the output stream.
2.   That you can have muliple, sequential insertions in one statement.

Let's talk about `endl`, which you can assume stands for end-line. In C++, `endl` is called a _manipulator_. When you use it, you say that you not only want to add a newline to the stream at that point, but also that you want to flush the stream. You'll learn more about I/O and operations like flush in CS 61, but for now you can think of the flush operation effectively forcing the printing of the characters in the output stream (otherwise, the system is free to buffer additional output before actually printing the characters previously inserted into `cout`).

There are many [manipulators defined in C++](https://cplusplus.com/reference/library/manipulators/), which allow you to control the output exactly as you'd like (e.g., you might read about the `setw` manipulator). As I did with the format codes associated with `printf`, I'll leave this as something you can explore for yourself.


## Active learning interlude (ali1)

Go ahead and play with `cout` in `main.cpp`. Define a variable for yourself (e.g., `int i = 42`) and print it, and by this, I mean print the value of the variable `i` using `cout`. Can you figure out how to do it?

If you get stuck, you can look at my solution in `solution-ali1.txt`.

## Namespaces

You might be wondering what's the deal with the `std::` in front of `cout` and `endl`. Well, this is how C++ indicates that we want not any `cout` object or `endl` manipulator, but the ones from the `std` namespace. We encountered namespaces in Python, and we know that they help us to avoid name collisions that can happen when we import libraries created by two different developers.

You've probably also guessed that `std` stands for the _standard namespace_ in C++, which is where `cout` and `endl` are defined.

If you want to avoid the prepending of a particular namespace, you can place the `using namespace` directive at the top of your program (or in a code block). For example, this is an equivalent way to write the program in `main.cpp`:

```cpp
#include <iostream>

using namespace std;

int main(void) {
    cout << "Hello World!" << endl;
    return 0;
}
```

> Go ahead and copy this code. Paste it into `mycode.cpp` and then compile and run it. Remember to type `./mycode` to run it. It should work!

## Grabbing user input

Do you remember this C program from our second project?

```c
#include <stdio.h>

int input(char *);

int main(void) {
    int a_number;
    a_number = input("Please type a number: ");
    printf("You typed %d\n", a_number);
    return 0;
}
```

We had to write the function `input` ourselves because C didn't have a convenient way to grab user input. We also had to build our own character array to hold the user input and then use `fgets` on `stdin` with all the dangerous ways we could mess it up. And since we wanted our input string as a number, we had to convert the characters into an integer equivalent.

Well, here is that code in C++ using the `cin` object and the stream _extraction_ operator `>>`:

```cpp
#include <iostream>

using namespace std;

int main(void) {
    int a_number;
    
    // a_number = input("Please type a number: ");
    cout << "Please type a number: ";
    cin >> a_number;
    
    // printf("You typed %d\n", a_number);
    cout << "You typed " << a_number << endl;
    
    return 0;
}
```

Ok, still not as simple as what we can write in Python:

```python
a_number = int(input('Please type a number: '))
print('You typed', a_number)
```

But C++ did a lot for us in the simple line `cin >> a_number;`.

*   It grabbed what the user typed and converted that string of characters into an integer, which it stored in our variable `a_number`. It knew to do that type conversion because it looked at the type of `a_number` and assumed that that was what we wanted.
*   It didn't make us give it any storage for the input character array. The code that implements `cin` did all of the memory management involved in this operation for us. We'll talk more about the nice things that C++ does around memory management in a moment.

> Copy the code above and put it into `mycode.cpp`. Compile `mycode` and run it. When it asks for input, type `42`. Run it again and type `-56`. One more time with the input `+3`. These all work, right?

Now let's try to break the code.

> Run `mycode` and this time type `this is not a number` at the prompt. What did it do?

When I ran it, I was told that I typed `0`. The string `"this is not a number"` is clearly not `0`, but the C++ program happily did some conversion and continued. Clearly we need to do some error checking ourselves when we use `cin` and its automatic conversion functionality. Programmer beware!

## How `cin` basically operates

Before we discuss how we detect bad user input using `cin`, let's make sure we understand what it is doing.

> Run `./mycode` and type `55 66` at the prompt. What did the program do with your input?

That's right! It took just the first number from the input stream. In other words, it read enough of the input stream to satisfy what was asked of it. We asked it to grab a number and it returned the first number it found.

If you copy the `cin` statement and the second `cout` statement and then you place these two copies before `return` statement (as in the code that follows), you can prove to yourself that `cin`:

1.   reads and discards whitespace characters up to the first non-whitespace character it finds in the stream.
2.   Then it reads and processes characters that match what it was asked to find. In our case, that was numeric characters that it turns into an equivalent integer value.
3.   Finally, it leaves untouched any characters trailing the characters it converted.

```cpp
#include <iostream>

using namespace std;

int main(void) {
    int a_number;
    
    // a_number = input("Please type a number: ");
    cout << "Please type a number: ";
    cin >> a_number;
    
    // printf("You typed %d\n", a_number);
    cout << "You typed " << a_number << endl;

    // Did the user type a second number? If not, let's
    // wait forever (or until they do and hit return again).
    cin >> a_number;
    cout << "You typed " << a_number << endl;
    
    return 0;
}
```

Pay attention to the comment I added in the code above. This updated version of our program looks for _exactly two_ integer numbers, and it highlights that we need to type the return key to get `cin` to start processing the stream.

Ok, I hope this helped with your understanding. It might now make sense why we got a `0` when we typed the string `"this is not a number"` at the prompt. `cin` just defaulted to zero when it had no number at the head of the stream.

> Go ahead and try some inputs with our new program to verify this assertion.

But if `0` is what we get back as an `int` when it has no number to return, how do we tell the difference between the user typing something that isn't a number from her typing an actual `0`?

## Handling invalid input

We talked in CS 32 about the importance of checking the validity of whatever a user inputs. I found a nice, comprehensive article online about handling the many different kinds of invalid input with `cin`, and I encourage you to take a quick read through [it](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/). Focus on the four types of invalid text input that Alex describes in the article, and not the C++ details of how to handle each (at least not before you finish reading this section).

I want to focus on his third case: "input extraction fails," e.g., the user tries to enter a letter when `cin` was asked to read a numeric input. Think about what we need to know in this case:

*   If the extraction succeeds, we want the read value in the storage we specified as the target of the extraction operator.
*   If the extraction fails, we want to know this fact, and we probably want to clear the remaining input and ask the user to re-enter what we asked them to provide.

If you think about this, we're asking `cin` to return _multiple_ values to us: the hopefully correctly converted value, or an indication of an error, if one occurred.

If you now think about how this would work when you can only call _pure functions_ (i.e., functions that take their inputs and produce outputs while storing no state between calls), you'll quickly realize that you have to provide locations for the function to put all this information before you make the call. The more information you might possibly want to know about what happened during the function's execution, the more locations you need to setup. You need these locations even if errors are infrequent because you can't query what a pure function did once the call to it is over!

We did minimal error checking in the second project when we used `fgets`, and we should have done a lot more. In particular, we ignored the return value from `fgets`, and if you read [the man page for this function](https://man7.org/linux/man-pages/man3/fgets.3p.html), it says this about the return value:

> Upon successful completion, `fgets()` shall return `s` \[i.e., the pointer we provided to `fgets` as the first actual parameter in our call and where we wanted the string it read to be put\].  If the stream is at end-of-file, the end-of-file indicator for the stream shall be set and `fgets()` shall return a null pointer.  If a read error occurs, the error indicator for the stream shall be set, `fgets()` shall return a null pointer, and shall set `errno` to indicate the error.

Whoa, `fgets` uses its return value as an indicator of an error (i.e., there was an error if it returns a null pointer) and then it sets a whole bunch of global variables shared by many of the `stdio` library functions to communicate details about the error that occurred. Notice that this relieves the caller from allocating space for describing the error condition before the call (and makes `fgets` not a pure function), but the caller had better collect this information after the call in its own local state _and_ before any making any other `stdio.h` calls (since the next call will overwrite the shared state).

In object-oriented programming, we are not limited to interacting with pure functions or functions with side effects, which `fgets` is. Instead, our code can interact with objects, which can maintain state across our interactions with them. This might sound like what `fgets` was actually doing, but with real objects, they can have their own state that's not shared (unless the designer wanted that).

What do I mean? `cin` is an object of type `istream` and `cout` is a different object (of type `ostream`). The attributes of `cin` are separate from those of `cout`; they don't share `errno` like `fgets` and `printf` do in some implementations of the `stdio` library!

You now understand one of the many reasons why many programmers prefer object-oriented languages over simple procedural ones.

So, let's use the attributes and methods of `cin` to improve our program and catch the user inputting letters when we asked for a number.

```cpp
#include <iostream>

using namespace std;

int main(void) {
    int a_number;
    
    // a_number = input("Please type a number: ");
    cout << "Please type a number: ";
    cin >> a_number;

    // Make sure we got a valid response
    while (cin.fail()) {
        cout << "Just a number please: ";
        cin.clear();            // clears the error indication
        cin.ignore(256, '\n');  // clear the rest of the input
        cin >> a_number;
    }
    
    // printf("You typed %d\n", a_number);
    cout << "You typed " << a_number << endl;
    
    return 0;
}
```

You'll recognize this error-handling pattern from CS 32. We test the result returned from the method `fail` on the `cin` object, which returns `true` if some previous extraction it did failed. The state behind this method remains set until we actively clear it with the `clear` method call. And as we discussed earlier, we have decided to clear all the rest of the user's input at this point, which we do through the `ignore` method. This method is not perfect, since we have to specify how many characters we want removed from the stream (we specified 256 characters, which is a pretty big number for user input). The `ignore` method also stops if it encounters a newline character.

Yes, validating user input is better in C++ than C, but it still isn't easy. 

## Strings

So far, we've only read integers with `cin`. Let's read a string because `string` is an actual type in C++!

Do you remember the C program from the third project where we started learning about the difference between these two different declarations of a C-string variable called `response`?

*   `char response[RESPONSE_MAXLEN];`
*   `char *response;`

Here is that program rewritten using the C++ `std::string` type:

```cpp
#include <iostream>
#include <string>

int main(void) {    
    std::string response;

    int i = 0;

    printf("Please type something and hit return: ");
    std::cin >> response;
    while (response[i] != '\n') {
        i++;
    }
    printf("Your response was %d characters long\n", i);

    return 0;
}
```

Notice that I kept the `printf` calls from the original C program and only changed:

1.   the `#include` files;
2.   the declaration of the `response` variable; and
3.   replaced the call to `fgets` with a use of the `cin` object.

No more concerns about creating a character array of the right length to capture whatever the user might type! C++ will size a variable of type `string` to fit the string with which you initialize it.  

> Copy the code above into `mycode.cpp`, compile, and run it. At the program prompt asking you to type something, type `This is a test` and hit the return key. What did program say was the length of your response? Does that look right?

When I run this program, it tells me that the string typed was 616 characters long. That is clearly wrong, but what did we do wrong in our program?

Unfortunately, it isn't easy to tell and that's because _we are trying to use what we know about C to debug C++ code_. While you can run most C code in a C++ program, the designers of the functions and objects in C++ didn't necessarily make the same decisions that the designers of C functions made.

> Change the condition in the while-loop so the stopping condition becomes: `response[i] != 's'`. Re-compile and run the new `./mycode` executable with the same input: `This is a test`. What was the answer this time? Did it work correctly?

Well, what do I mean "correctly"? This time the program told me the number of characters up until the first instance of an `'s'` character. Of course, that's not the length of my input response, but ok that's progress.

The question becomes: what was wrong with our prior exit condition check? We typed a newline to end what we typed at the program's prompt, right? That newline was captured by `fgets` when we ran this as a C program, right? 

Ok, it's time to see what `cin` actually put in our `response` variable.

> Add `std::cout << response << std::endl;` immediately after the `cin` statement, and then recompile and rerun the program. What does `cin` think it should extract when you ask it to extract a `string`?

That's right. It ignores any leading whitespace and then extracts any consecutive non-whitespace characters up until the next occurrence of whitespace. In other words, it effectively extracts a word.

If we wanted a C++ function with behavior closer to `fgets`, we would want to use `std::getline` in the `string` library. You can find its reference information [here](https://cplusplus.com/reference/string/string/getline/), and below is our program written using that function.

```cpp
#include <iostream>
#include <string>

int main(void) {    
    std::string response;

    int i = 0;

    printf("Please type something and hit return: ");
    std::getline(std::cin, response);
    std::cout << response << std::endl;
    while (response[i] != '\n') {
        i++;
    }
    printf("Your response was %d characters long\n", i);

    return 0;
}
```

If you compile and run this version of our program, you'll find that it _still_ doesn't give the right answer for the length of our input, and that's because `std::getline` doesn't capture the newline. I did say "behavior closer to `fgets`."

I hope I've driven home the point that with this new language and new libraries, you have to read the reference pages carefully and not fall into thinking that the features that look like C (or Python) will act like the features you knew in those other languages.

For the program we were trying to rewrite in C++, you'd actually not count the number of characters in the response by hand, but use a method on the `string` variable, as we would have in Python. Here is that program (written entirely in C++):

```cpp
#include <iostream>
#include <string>

using namespace std;

int main(void) {    
    string response;

    cout << "Please type something and hit return: ";
    getline(cin, response);
    cout << "Your response was " << response.length() << " characters long" << endl;

    return 0;
}
```

`response.length()` invokes the `length` method on our `response` object and returns the number of bytes in the string. Notice that I didn't say characters in the string. The C++ `length` method isn't as smart as the Python `len` function concerning Unicode.

## Objects and pointers to objects

`string` is a C++ class, and the previous section demonstrates that using a C++ class is similar to the syntax we saw in using Python classes. If we have an object of some class, we can access an attribute of that class using the dot (`.`) operator.

But we also know that C++, like C, has pointer variables. See if you can explain in English what the following program does:

```cpp
#include <iostream>
#include <string>

using namespace std;

int main(void) {    
    string response;

    cout << "Please type something in ASCII and hit return: ";
    getline(cin, response);

    string *s = new string(response.length(), '\0');

    for (int i = 0; i < response.length(); i++) {
        (*s)[i] = toupper(response[i]);
    }
    
    cout << "Your response was " << (*s) << endl;

    return 0;
}
```

If you can't quite figure it all out, don't worry. You are still becoming comfortable with pointers. Let's take this code apart a piece at a time.

You should be comfortable with the first 3 statements in `main`, as we've seen them in our earlier examples. The fourth statement declares a new pointer variable `s` and initializes it, although you probably don't completely understand this initialization. It's because of the `*` in the declaration that we know that we're declaring a pointer variable. What kind of pointer variable? A pointer to a `string` object.

In the second `cout` statement, we dereference this pointer variable by saying `*s`. This means that we don't want the memory address of some `string` object, but the actual `string` object pointed at by `s`. In fact, we want to print this `string` object.

> If you want to see the memory address of the `string` object pointed to by `s`, change this second `cout` statement as follows:
>
> `cout << "Your response was " << s << endl;`
>
> And now compile and run the program. See, `s` is a memory address.
>
> Change the `cout` statement back to its original form.

With that explanation, can you now understand the statement in the body of the for-loop?

*   On the right-hand side of the assignment statement, we are using the `response` object to grab a character at index `i`. If that character is a letter, we make it into an uppercase letter, and if not, the character is left unchanged. Here's [a link to the documentation for `toupper`](https://cplusplus.com/reference/cctype/toupper/).
*   On the left-hand side of the assignment statement, we follow precedence rules and first do the work within the parentheses. We dereference the `string` pointer `s` to get an actual `string` object, and then we index into that `string` object to change the value of the character at location `i`.

And we're back to the declaration and its initialization. Let's first recall how we create objects in Python if we're being explicit about it.  For example, we could create an empty Python `str` object with the statement:

`s = str()`

Or a Python `str` object initialized with the string `"Hi mom!"` like this:

`s = str("Hi mom!")`

Well, in C++ we construct an object of a class in a similar manner, except that we have to use the keyword `new`.

`... = new string();`

Recall in Python that `s` was a _name_ for the `str` object our `str("Hi mom!")` expression created. In C and C++, variables aren't names, but actual blocks of memory.

How did we _dynamically_ create blocks of memory in C? Right! We used `malloc`. `new` is the replacement in C++ for `malloc`.

An expression like `new string()` in C++ says:

1.   Dynamically allocate a chunk of memory big enough to hold a `string` object.
2.   Run the constructor code to initialize this chunk of memory so that it acts like a `string` object. In this case without any parameters to the constructor, an empty string should be produced.

Almost there! Hang in there with me. What did `malloc` return? Yes, a pointer to the memory it allocated. What will `new` return in C++? Yes yes, a pointer to the allocated and initialized object (of type `string` in our example, but it is the same with any class).

Hopefully now you can see that this statement:

`string *s = new string(response.length(), '\0');`

Dynamically allocates a new `string` object and returns the memory address of that object, which we store in the memory location (i.e., pointer variable) we call `s`. The particular `string` constructor we called is [the _fill constructor_](https://cplusplus.com/reference/string/string/string/), which takes a size and a fill character. This gives us back a `string` object of a size large enough to hold the `response` string.

> You might take a moment to read through this program again and think about what happens in each statement. If you haven't run the program as originally written, do that and give it different inputs.

## A shorthand notation

Writing `(*s)` all over your program is a headache, especially when you simply want to call a method or access an attribute of the object pointed at by `s`. For example, if we wanted the length of `s`, we would have to write `(*s).length()`.

To avoid being overrun by parentheses, C++ allows you to express `(*s).length()` as `s->length()`. The `->` operator says to dereference the pointer on its left-hand side and then access the attribute on the right-hand side.

> Go ahead and try this in the following program.

```cpp
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    // Create a string using the copy constructor
    string *s = new string("The string data");

    // Change the 11th character
    (*s)[10] = 'y';
    
    cout << (*s) << endl;
    cout << "It's " << (*s).length() << " characters long." << endl;
    cout << "It's " << s->length() << " characters long." << endl;

    return 0;
}
```

## The errors `new` eliminates

Let's summarize the problems with `malloc` in C and highlight how `new` in C++ eliminates them:

*   `malloc` allows you to grab a raw (i.e., unstructured and uninitialized) block of memory. Since the input to `malloc` is a the number of bytes it should allocate, it is up to the programmer to make sure that this number is the number of bytes in an object of the type that this memory block will become. In other words, `malloc` disconnects the amount of space allocated from the amount of sapce needed for the type you cast the `void *` pointer to.
*   `malloc` does no initialization of the allocated memory. Again, it is up to the programmer to remember to initialize the memory before using it.
*   `malloc` sets the returned pointer to `NULL` if it is unable to allocate the specified number of bytes. It is up to the programmer to remember to explicitly check that they've been given a valid pointer.

What follows is an example of how you should dynamically allocate memory for an `int` and sets its value to `0`.

```c
// I've made sure that the type in the typecast and the number
// of bytes sent as input to `malloc` match.
int *ptr = (int *)malloc(sizeof(int));

// Before you do anything else, check if we got a valide pointer.
if (ptr == NULL) {
    exit(1);   // Ran out of memory. Force the program to exit.
}

// Initialize the allocated memory. I've chosen to initialize
// this int to 0.
(*ptr) = 0;

// Finally use the dynamically allocated memory as an int
```

All this goes away with `new` operator in C++.

```c++
int *ptr = new int(0);
```

As a programmer, you write the type of the memory you want dynamically allocated just once. You can think of `new` calling `malloc` to get the right amount of memory for an object of the specified type. And before `new` returns a memory pointer to you, it calls one of the constructors of the type so that you only get a properly sized and properly initialized object, just like we did in Python.

`new` also performs the check to verify that we didn't run out of memory during this dynamic allocation. If `new` can't allocate enough memory for the object we've requested, it doesn't rely on the programmer to perform a check. It throws a `std::bad_alloc` exception, which will end the program if the programmer doesn't protect the call to `new` in a C++ `try` block with an associated `catch`.

Exception handling via `try`, `catch`, and `throw` in C++ looks very similar to `try`, `except`, and `raise` respectively in Python. You should be able to pick up the syntax pretty quickly from any of the numerous tutorials on the Internet.

## `delete` replaces `free`

Remember how we said in C that any memory you dynamically allocate should eventually be freed? Unfortunately, C++ doesn't remove the need to free the memory you dynamically allocate with `new`. In C++, whenever you dynamically create a new object with `new`, you should later free it with `delete`.

We didn't do that with our toy program in which we dynamically allocated a `string`, and let's update that program now.

```cpp
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    // Create a string using the copy constructor
    string *s = new string("The string data");

    // Change the 11th character
    (*s)[10] = 'y';
    
    cout << (*s) << endl;
    cout << "It's " << (*s).length() << " characters long." << endl;
    cout << "It's " << s->length() << " characters long." << endl;

    // Give the memory for `s` back since we're done with it
    delete s;
    
    return 0;
}
```

I've shown you very simple examples of dynamic memory allocation since we've been focused on the rules and the syntax in C++. You might be wondering how memory allocation works in a complex program. Well, it's like this:

> Let's imagine that you have a bunch of cardboard boxes in your attic. When your mom yells, “Michaela, get me a box!” she’s asking you to grab a cardboard box from the attic. You oblige, and now you have one less box in the attic. No problem, you have many. Later, mom yells again, “Michaela, get me another box that is bigger than the last.” No problem, you go grab another. If your mom finishes with a box, she gives it to you and you return it to the attic. This continues without a problem until the day is over (i.e., the program finishes) and all boxes are automatically returned to the attic.
>
> However, your mom might ask one day for too many boxes. On this day, you go up to the attic and realize that there are no boxes left. You have to tell mom that you cannot satisfy her request. In C, you appearing back downstairs empty-handed is like C returning a NULL pointer. In C++, you yelling downstairs to your mom is like an exception being raised.

## Summary

In this lesson, you learned that:

1.   C++ provides a simpler and less error-prone way to capture user input using the `cin` stream. Use it! On the other hand, it's really up to you whether you like `printf` or `cout` for printing text and values to the user's terminal.
2.   C++ includes a mechanism for namespaces like we saw in Python.
4.   The error handling patterns we learned with Python don't look all that much different in C++.
5.   C++ has a real `string` type, but the methods and functions that operate on this type do not act exactly as we saw similiar functions and methods in C and Python.
6.   Dynamic memory allocation is much easier to do correctly in C++ through `new`, although we still are saddled with remembering to pair every `new` with a later `delete`.
7.   Dynamic memory allocation in C++ produces pointer variables, just as we saw in C. To get access to the fields and methods of a C++ object, we can use the arrow operator (`->`) as a shorthand way of saying we want to dereference an object pointer and access one of its fields/methods.
