#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <iostream>

using namespace std;

/*
Exemple of a Test Case How we input the program :
-length of even string :
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
-adding 2 number :
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
*/


struct TuringMachine {
    int k; 
    string gamma; 
    char S; 
    vector<tuple<char, char, char, char, char>> transfunc; 
};
std::map<char, std::string> globalMapGamma;
std::map<char,std::string> globalMapStates;


TuringMachine readTuringMachine() {
    TuringMachine tm;
    cout << "Enter number of states (k): ";
    cin >> tm.k;
    cout << "Enter tape alphabet (gamma, enter a string ,ex:ab#): ";
    cin >> tm.gamma;
    //if number of states (k) choosen = 2 then possible states in the system are 0,1 
    cout << "Enter start state (S,enter an int between 0 <= S < k,ex:0 ): ";
    cin >> tm.S; 
    std::string temp = "1" ;
    for (size_t i = 0; i < tm.gamma.length(); ++i) {
        char currentChar = tm.gamma[i];
        globalMapGamma[currentChar] = temp ;
        temp += "1" ;
    }
    temp = "1" ;
    for (int i = 0; i < tm.k; ++i) {
        char s = static_cast<char>('0' + i);
        globalMapStates[s] = temp ;
        temp += "1" ;   
    }
    cout << "Enter transition function Tuple by Tuple Space separated : current_state input_symbol new_state new_symbol action :" << endl;
    for (int i = 0; i < tm.k; i++) {
        for (char tape_symbol : tm.gamma) {
            char current_state, input_symbol, new_state, new_symbol, action;
            cout << "Enter transition for state " << (char)('0' + i) << " and tape symbol " << tape_symbol << ": ";
            cin >> current_state >> input_symbol >> new_state >> new_symbol >> action;
            tm.transfunc.push_back(make_tuple(current_state, input_symbol, new_state, new_symbol, action));
        }
    }
    cout << "List of Tuples:" << endl;
    for (const auto& rule : tm.transfunc) {
    cout << "(" << get<0>(rule) << "," << get<1>(rule) << "," << get<2>(rule) << "," << get<3>(rule) << "," << get<4>(rule) << ")" << endl;
            }
 
    return tm;
}


void executeTuringMachine(const TuringMachine& tm, const string& tape, int headPosition) {
    string current_tape = tape;
    int current_position = headPosition;
    char current_state = tm.S;

    cout << "Initial Tape: " << current_tape << endl;
    cout << "Initial State: " << current_state << endl;
    cout << "--------------" << endl ;
    std::string EncodedString = "" ;
    while (true) {
        
        cout << "Current State: " << current_state << endl;
        cout << "Current Character: " << current_tape[current_position] << endl ;
        cout << "Current Tape: " << current_tape << endl;
        cout << "--------------" << endl ;

       
        char current_symbol = current_tape[current_position];

        // Find transition rule
        bool transitionFound = false;
        for (const auto& rule : tm.transfunc) {
            if (get<0>(rule) == current_state && get<1>(rule) == current_symbol) {

                /*
                if found a transition function :
                3 steps : 1) Update with new Symbol .. 2) Take An Action ... 3) Update to the new State
                */
                EncodedString += globalMapStates[get<0>(rule)] ;
                EncodedString += "0" ;
                EncodedString += globalMapGamma[get<1>(rule)] ;
                EncodedString += "0" ;
                EncodedString += globalMapStates[get<2>(rule)] ;
                EncodedString += "0" ;
                EncodedString += globalMapGamma[get<3>(rule)] ;
                EncodedString += "0" ;


                

                // Update tape symbol
                current_tape[current_position] = get<3>(rule);

                // Move tape head
                if (get<4>(rule) == 'R') {
                    current_position++;
                    EncodedString += "11" ;
                    if (current_position >= current_tape.size()) {
                        current_tape += '#'; // Extend tape if needed
                    }
                } else if (get<4>(rule) == 'L') {
                    EncodedString += "1" ;
                    current_position--;
                    if (current_position < 0) {
                        current_tape = '<' + current_tape; // initialize left marker if needed
                        current_position = 0;
                    }
                } else if (get<4>(rule) == 'Y') {
                    EncodedString += "111" ;
                    cout << "Accepting state reached." << endl;
                    cout << "Final State: " << current_state << endl;
                    cout << "Final Tape: " << current_tape << endl;
                    cout << "Encoded String: " << EncodedString << endl;

                    return;
                } else if (get<4>(rule) == 'N') {
                    EncodedString += "1111" ;
                    cout << "Rejecting state reached." << endl;
                    cout << "Final State: " << current_state << endl;
                    cout << "Final Tape: " << current_tape << endl;
                    cout << "Encoded String: " << EncodedString << endl;
                    return;
                }
                // Update current state
                current_state = get<2>(rule);
                transitionFound = true;
                EncodedString += "00" ;
                break;
            }
        }
        

        if (!transitionFound) {
            cout << "No transition rule found for state " << current_state << " and symbol " << current_symbol << endl;
            return;
        }
    }
}


int main() {
   

    cout << "Enter details of Turing machine:" << endl;
    TuringMachine tm = readTuringMachine();

    
    string tape;
    cout << "Enter tape: ";
    cin >> tape;
    int headPosition = 0; 
    cout << "Enter head position: ";
    cin >> headPosition;
    cout << "Executing Turing machine..." << endl;
    executeTuringMachine(tm, tape, headPosition);

    return 0;