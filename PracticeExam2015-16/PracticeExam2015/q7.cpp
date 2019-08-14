//
//  q7.cpp
//  PracticeExam2019
//
//  Created by Olivia Gallup on 06/01/2019.
//  Copyright © 2019 Olivia Gallup. All rights reserved.
//







//  NEED TO GO OVER DIS AGAIN, LOKE AT SOLUTIONS








#include "q7.hpp"
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class Node
{
private:
    string name;
    Node* p_next;
public:
    Node();
    Node(string name_in, Node* p_next_in);
    string getName();
    void setName(string name_in);
    Node* getNext();
    void setNext(Node* p_next_in);
};

class Queue
{
private:
    Node* p_head;
public:
    vector<Node> queue;
    Queue();
    void addNode(string name_in);
    string removeNode();
    void printQueue();
    ~Queue() {
        cout << "***erasing queue***" << endl;
        queue.erase(queue.begin(), queue.end());
    }
};

//Nodes
Node::Node() {
    name = "";
    p_next = nullptr;
}
Node::Node(string name_in, Node* p_next_in){
    name = name_in;
    p_next = p_next_in;
}
string Node::getName()
{
    return name;
}
void Node::setName(string name_in)
{
    name = name_in;
}
Node* Node::getNext()
{
    cout << "next: " << p_next << endl;
    return p_next;
}
void Node::setNext(Node* p_next_in)
{
    p_next = p_next_in;
    cout << "next is now: " << p_next << endl;
}


//Queue Functions
Queue::Queue() {
    p_head = nullptr;
}
void Queue::addNode(string name_in)
{
    
    p_head->setName(name_in);
    queue.push_back(*p_head);
    
    cout << "***node added***" << endl;
}
string Queue::removeNode()
{
//    string last = queue.back().getName();
//    queue.pop_back();
    cout << "***node removed***" << endl;
    return "hello";
}
void Queue::printQueue()
{
    cout << "Current Queue:" << endl;
    for(vector<Node>::iterator i=queue.begin(); i != queue.end(); ++i) {
        cout << "/t" << i->getName() << endl;
    }
}




int main()
{
    Queue line;
    line.addNode("james");
    line.addNode("greg");
    line.addNode("sarah");
    line.addNode("catherine");
    line.addNode("julie");
    line.addNode("alex");
    line.printQueue();
    cout<<" > removing "<<line.removeNode()<<" from queue."<<endl;
    cout<<" > removing "<<line.removeNode()<<" from queue."<<endl;
    line.printQueue();
    line.addNode("jack");
    line.addNode("angela");
    line.printQueue();
    return 0;
}
