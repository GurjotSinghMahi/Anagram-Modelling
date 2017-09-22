# Anagram-Modelling
An interesting problem is to print out all the anagrams of a given word.  That is, given an N-letter word with all letters different, print all the "words" you can form using each letter once, regardless of whether they are actual words in some language.  The number of such rearrangements is N-factorial where N is the number of letters.  The problem can be solved in several different ways, one of which uses one queue and one stack.  We illustrate the process here and leave the coding as a major programming project.

Say the word is abcdefgh and you have just printed ehcgfdba. The very next word in alphabetical order that you can form with those eight letters is ehdabcfg (compare the two to see why). The way one iteration of the main loop of the process goes from a stack 
containing ehcgfdba to that same stack containing ehdabcfg is as follows:

Initially you have the letters on the stack in reverse order, and you have an empty queue:
1.  Repeatedly pop a value from the stack and enqueue it on the queue, stopping as soon as you pop a value that comes alphabetically before the one you just enqueued.  Call that value the "pivot".
2.  Repeatedly dequeue a value and enqueue it, stopping as soon as you dequeue a value that comes alphabetically after the pivot.  Push that value onto the stack.
3.  Enqueue the pivot, then repeatedly dequeue a value and enqueue it, stopping as soon as you dequeue a value that is alphabetically before the pivot. Push it onto the stack.
4. Repeatedly dequeue a value from the queue and push it on the stack until the queue is empty.
