## A Sock Drawer
### SockDrawer.py

Let us model a sock drawer.  How does a sock drawer work?  Well, when you do the washing, you end up with a bunch of socks, and you just put them in the drawer. So one operation is "put sock in drawer".  The other thing you typically do is look for two matching socks.  For simplicity, we will have only one attribute that we use to match socks: their color.  So the operations, in detail, are: 

* `add_sock`: adds a sock of a given color
* `get_pair`: ask if there is a pair of a given color, and if so, remove it
* `available_colors`: returns the set of colors for which there is at least a pair. 

However, it is inefficient storing all socks as a list
Thus, this brings us to 

## A Better Sock Drawer
### SmartDrawer.py

This implementation uses a dictionary to store key, value pairs signifying color and number respectively. The code becomes much more efficient and concise.

The name of the data structure used to store this Sock Drawer is called an Arithmetic Dictionary

## Arithmetic Dictionary
### ArithmeticDictionary.py

A number is a number. An array, or vector, is a list of numbers that can be indexed by their position in the vector. An arithmetic dictionary is a set of numbers that can be addressed by their associated key. Just as numbers, and arrays, can be combined via +, -, *, /, and compared with >, <, etc, so can arithmetic dictionaries. 

This arithmetic dictionary contains the add, subtract, multiple, divide, and comparison operators to compare with other arithmetic dictionaries and/or integers.

Check test cases for more information on how to use.

An example of Arithmetic Dicionary is implemeted in Bag of Words

## Bag of Words
### BoW.py

In natural language processing, a common (if not very detailed!) representation for a piece of text is the (Bag of Words)[https://en.wikipedia.org/wiki/Bag-of-words_model] model. It's quite simple: we count how many times a word appears in a piece of text, and that's it! We can implement bag of words quite simply in terms of our Arithmetic Dictionaries.

