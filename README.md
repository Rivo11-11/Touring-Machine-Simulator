
## Turing Machine Simulator
This project is a simple Turing machine simulator implemented in C++. A Turing machine is a theoretical device that manipulates symbols on a tape according to a set of rules. It serves as a fundamental model of computation, capable of simulating the logic of any computer algorithm.

### Features
* Interactive Interface: Allows users to input details of the Turing machine and execute it step by step.

* Customizable Turing Machine: Users can define the number of states, tape alphabet, start state, and transition functions for the Turing machine.

* Step-by-Step Execution: The simulator executes the Turing machine, displaying each step's details, including the current state, tape content, and transition taken.

* Acceptance and Rejection: The Turing machine halts when it reaches an accepting or rejecting state, providing the final state, tape content, and an encoded string representing the machine's execution path.

**How to Use**

1. Enter the number of states (k).
2. Define the tape alphabet (gamma) as a string (e.g., "01#").
3. Specify the start state (S) as an integer between 0 and k-1.
4. Input transition function tuples, each consisting of the current state, input symbol, new state, new symbol, and action (R: Right, L: Left, Y: Accept, N: Reject).
5. Enter the initial tape content.
6. Provide the initial head position on the tape.
View Execution:

**Exemple of a Test Case How we input the program :
-length of even string :**    
2

ab#

0 

0 a 1 a R

0 b 1 b R

0 # 0 # Y

1 a 0 a R

1 b 0 b R

1 # 1 # N

abbabba 

**-adding 2 number :**

3

1#

0

0 1 0 1 R 

0 # 1 1 R 

1 1 1 1 R

1 # 2 # L

2 1 2 # Y

2 # 2 # N

11#111



