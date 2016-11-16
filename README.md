# SpellChecker

###BTree spell checking
⋅⋅⋅by Roisin McLoughlin
⋅⋅⋅rem99 at georgetown dot edu
⋅⋅⋅Last Modified 11/15/16

Spell checks a file against a dictionary file.
Removes specified words from the dictionary file.

--------------------------
Running the Program
--------------------------
`g++ LinkedList.cpp BTree.h main.cpp [inputFile] [dictionaryFile] [removalFile]`

arguements:
* `inputFile` - Text file to be spell checked
* `dictionaryFile` - Text file containing a lexicon
* `removalFile` - Text file containing words to remove from the dictionary

------------------------
Implementation
------------------------
The B-Tree is implementated using a template class to determine
the number of children nodes that the parent node points to.
A linked list is implemented to provide runtime comparison with 
the B-Tree implementation.
