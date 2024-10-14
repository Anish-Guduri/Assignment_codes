#include <iostream>
using namespace std;


struct state {
    int person, wolf, goat, cabbages;
    state(){
        this->person = 0;
        this->wolf = 0;
        this->goat = 0;
        this->cabbages = 0;
    }

    state(int person, int wolf, int goat, int cabbages) {
        this->person = person;
        this->wolf = wolf;
        this->goat = goat;
        this->cabbages = cabbages;
    }
};


struct Node {
    state data;
    Node* next;
    
    Node(state s){
        data=s;
        next=nullptr;
    }
};


Node* head = nullptr;

void addState(state s){
    Node* newNode = new Node(s);
    if(!head){
        head=newNode;
    }
    else{
        Node* ptr = head;
        while(ptr->next){
            ptr=ptr->next;
        }
        ptr->next=newNode;
    }
}


void removeLastState() {
    if (!head) return;
    if (!head->next) {
        delete head;
        head = nullptr;
    } 
    else {
        Node* temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
}


void printPathStates() {
    Node* temp = head;
    cout<<endl;
    while (temp->next) {
        cout << "(" << temp->data.person << ", " << temp->data.wolf << ", "<< temp->data.goat << ", " << temp->data.cabbages << ") --> ";
        temp = temp->next;
    }
    cout << "(" << temp->data.person << ", " << temp->data.wolf << ", "<< temp->data.goat << ", " << temp->data.cabbages << ") ";
    cout <<"\n\n";
}
void printStateVisualization() {
    Node* temp = head;
    cout<<"\n-------------------------------------- VISUALIZATION --------------------------------------------------\n\n";
   
    cout<<"  INTIAL STATE (0, 0, 0, 0)"<<"\t\t\t\t\t\t\t\t\t"<<"  FINAL STATE (1, 1, 1, 1)\n\n";
    cout<<"  Left side of River       "<<"\t\t\t\t\t\t\t\t\t"<<"  Right side of River\n\n";

    while (temp) {
        cout<<"  ( ";
        if( temp->data.person == 0){
            cout<<"person ";
        }
        if( temp->data.wolf == 0){
            cout<<" wolf ";
        }
        if( temp->data.goat == 0){
            cout<<" goat ";
        }
        if( temp->data.cabbages == 0){
            cout<<" cabbages ";
        }
        // cout<<" )";
        cout<<" )  \t\t\t\t\t\t\t\t\t  ( ";

        if( temp->data.person == 1){
            cout<<" person ";
        }
        if( temp->data.wolf == 1){
            cout<<" wolf ";
        }
        if( temp->data.goat == 1){
            cout<<" goat ";
        }
        if( temp->data.cabbages == 1){
            cout<<" cabbages ";
        }
        // cout << "(" << temp->data.person << ", " << temp->data.wolf << ", "<< temp->data.goat << ", " << temp->data.cabbages << ") --> ";
        temp = temp->next;
        cout<<" ) \n\n";
    }
    // cout << "(" << temp->data.person << ", " << temp->data.wolf << ", "<< temp->data.goat << ", " << temp->data.cabbages << ") ";
    cout <<"\n\n";
}

bool isValidState(state nextState) {
    if((nextState.wolf == nextState.goat ) && nextState.person!= nextState.wolf ){
        return false;
    }
    else if((nextState.goat == nextState.cabbages ) && nextState.person!= nextState.goat){
        return false;
    }
    return true;
}



int stateIndex(state givenState){
    int index = 8*givenState.person +4*givenState.wolf + 2*givenState.goat + givenState.cabbages;
    return index;
}

bool isStateEqual(state CurrentState ,state finalState ){
    bool result = ((CurrentState.person == finalState.person )&& (CurrentState.wolf == finalState.wolf) && (CurrentState.goat == finalState.goat) && (CurrentState.cabbages == finalState.cabbages));
    return result;
}


// Function to find the path from initial to final state
void findPath(state CurrentState, state finalState, int visited[]) {
    static int numPaths=0;
    int index= stateIndex(CurrentState);
    if(visited[index]){
        return;
    }

    visited[index]=1;
    addState(CurrentState);

    if (isStateEqual(CurrentState,finalState)) {
        numPaths++;
        cout << "Path Found "<<numPaths<<": ";        
        printPathStates();
        printStateVisualization();
        removeLastState();                          // Backtracking after printing
        visited[index] = 0;                         // Unmarking the current state
        return;
    }
    
    if(CurrentState.person==0){
       if(CurrentState.wolf==0){
            state tempState(1, 1, CurrentState.goat, CurrentState.cabbages);
            if((!visited[stateIndex(tempState)]) && (isValidState(tempState))){
                findPath(tempState, finalState, visited);

            }
        }
        if(CurrentState.goat==0){
            state tempState(1, CurrentState.wolf, 1, CurrentState.cabbages);
            if((!visited[stateIndex(tempState)]) && (isValidState(tempState))){
                findPath(tempState, finalState, visited);

                }
            }
        if(CurrentState.cabbages==0){
            state tempState(1, CurrentState.wolf, CurrentState.goat, 1);
            if((!visited[stateIndex(tempState)]) && (isValidState(tempState))){
                findPath(tempState, finalState, visited);
                }
            }
        }
    else{
            state tempState(0,CurrentState.wolf , CurrentState.goat, CurrentState.cabbages);
            if((!visited[stateIndex(tempState)]) && (isValidState(tempState))){
                findPath(tempState, finalState, visited);

            }
            if(CurrentState.wolf==1){
                state tempState(0, 0, CurrentState.goat, CurrentState.cabbages);
                if((!visited[stateIndex(tempState)]) && (isValidState(tempState))){
                    findPath(tempState, finalState, visited);

                }
            }
            if(CurrentState.goat==1){
                state tempState(0, CurrentState.wolf, 0, CurrentState.cabbages);
                if((!visited[stateIndex(tempState)]) && (isValidState(tempState))){
                    findPath(tempState, finalState, visited);
                }
            }
            if(CurrentState.cabbages==1){
                state tempState(0, CurrentState.wolf, CurrentState.goat, 0);
                if((!visited[stateIndex(tempState)]) && (isValidState(tempState))){
                    findPath(tempState, finalState, visited);
                }
            }
        }
    
    visited[index]=0;
    removeLastState();

}




int main() {
    // Create an initial and final state
    state initialState(0, 0, 0, 0);
    state finalState(1, 1, 1, 1);

    int visited[16]={0};

    // Find the path from initial to final state
    findPath(initialState, finalState, visited);
    
    // cout << "Hello World" << endl;
    return 0;
}
