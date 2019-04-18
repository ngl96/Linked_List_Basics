//  Created by Nathanael Leyton on 11/15/18.
//  rec11
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
// Node to be used a part of linked list

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

// listInsertHead: adds a data item to the beginning of a [possibly empty] list
void listInsertHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}
// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like.
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index-1]);
    }
    return result;
}
void splice(Node* splice, Node*& list ) {
    Node* tail = splice;
    while (tail->next != nullptr){
        tail = tail->next;
    }
    tail->next = list->next;
    list->next = splice;
}
int listSize(const Node* list){
    int size = 0;
    while (list != nullptr) {
        size++;
        list = list->next;
    }
    return size;
}

bool findConsecutive(Node* listSearching, Node* sublist, int sublistSize) {
    int numItemsCorrect = 0;
    while (listSearching->data == sublist->data){
        numItemsCorrect++;
        if(numItemsCorrect == sublistSize) {return true;}
        if (sublist->next == nullptr) { return false; }
        listSearching = listSearching->next;
        sublist = sublist->next;
    }
    return false;
}
Node* isSublist(Node* sublist,Node* list) {
    Node* listSearching = list;
    int sublistSize = listSize(sublist);
    while(listSearching->next != nullptr){
        if (listSearching->data == sublist->data){
            Node* sublistHead = listSearching;
            if ( findConsecutive(listSearching, sublist, sublistSize)){
                return sublistHead;
            }
        }
        listSearching = listSearching->next;
    }
    cout << "Failed to match." << endl;
    return nullptr;

}

void listDisplay(const Node* headPtr){
    const Node* p = headPtr;
    while ( p != nullptr ) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

bool equalList(Node* list1, Node* list2) {
    while (list1 != list2){
        if(list1->next == nullptr){ break;}
        list1 = list1->next;
    }
    if (list1 == list2) {return true;}
    return false;
}

Node* sharedListBruteForce(Node* list1, Node* list2){
    Node* temp = list1;
    while (temp->next != nullptr){
        if (equalList(temp,list2)){
            return temp;
        }
        temp = temp->next;
        list2 = list2->next;
    }
    cout << "No Matched sublists" << endl;
    return nullptr;
}

Node* sharedListUsingSet(Node* list1, Node* list2){
    unordered_set<Node*> test;
    while (list1->next != nullptr){
        test.insert(list1);
        list1 = list1->next;
    }
    while (list2->next != nullptr){
        if (test.find(list2) != test.end()){
            return list2;
        }
        list2 = list2->next;
    }
    cout << "No Matched sublists" << endl;
    return nullptr;
}


int main() {
    Node* list1 = listBuild({5, 7, 9, 1});
    Node* list2 = listBuild({6, 3, 2});
    listDisplay(list1);
    listDisplay(list2);
    splice(list2,list1->next);
    listDisplay(list1);
    cout << endl;
    Node* list3 = listBuild({5, 7, 6, 3,6,3,2,9,1});
    Node* list4 = listBuild({6, 3, 2});
    listDisplay(list3);
    listDisplay(list4);
    Node* list5 = isSublist(list4, list3);
    listDisplay(list5);
    cout << endl;
    Node* list6 = listBuild({2,3});
    Node* list7 = listBuild({2,3,3});
    Node* list8 = listBuild({4,5});
    list6->next = list8;
    list7->next = list8;
    listDisplay(list6);
    listDisplay(list7);
    Node* list9 = sharedListBruteForce(list6, list7);
    listDisplay(list9);
    Node* list10 = sharedListUsingSet(list6, list7);
    listDisplay(list10);

    
    



    

    
    

    
    
    


}
