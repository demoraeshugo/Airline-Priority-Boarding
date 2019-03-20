//
//  main.cpp
//  HDMHomework7
//
//  Created by Hugo De Moraes on 11/13/18.
//  Copyright © 2018 Hugo De Moraes. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


class Passanger
{
private:
    string lastName;
    string FFStatus;
    int price;
    int time;
    int points;
    
    int FFPoints(string status) //Function that takes FF number and calculates priority points
    {
        int value = 0;
        if(status.compare("NONE"))
        {
            value = 40;
        }
        else if(status.compare("SLVR"))
        {
            value = 30;
        }
        else if(status.compare("GOLD"))
        {
            value = 20;
        }
        else if(status.compare("PLAT"))
        {
            value = 0;
        }
        else
        {
            cout << "Invalid FF Status" << endl;
        }
        return value;
    }
    
    int pricePoints(int num1) //Function that takes Price Paid and calculates priority points
    {
        int value = 0;
        for(int i = 499; i >= num1; i -= 50)
        {
            value += 5;
        }
        return value;
    }
    
    int timePoints(int num1) //Function that takes Time of Arrival and calculates priority points
    {
        int value = 0;
        for(int i = 59; i >= num1; i--)
        {
            value++;
        }
        return value;
    }
    
public:
    Passanger(string a, string status, float num2, float num3) //Constructs a passanger object
    {
        lastName = a;
        FFStatus = status;
        price = num2;
        time = num3;
        calcPoints();
    }
    
    int calcPoints() //Function that calculates total priority points
    {
        points = 0;
        points += FFPoints(FFStatus);
        points += pricePoints(price);
        points += timePoints(time);
        return points;
    }
    
    int getPoints() //Gets the passanger's priority points
    {
        points = calcPoints();
        return points;
    }
    
    void display()
    {
        cout << right << setw(10) << lastName << setw(20) << FFStatus <<  setw(20) << "$" << price << setw(20) << time << setw(20) << points << endl;
    }
};

struct node
{
    Passanger* passangerInfo;
    int pPoints;
    node *next;
    node *previous;
};

void displayHeader()
{
    cout << right << setw(10) << "LASTNAME" << setw(22) << "FFSTATUS" << setw(22) << "PRICE" << setw(20) << "TIME" << setw(20) << "POINTS" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
}

class PQueue
{
private:
    node *head;
    node *tail;
public:
    PQueue()
    {
        head = NULL;
        tail = NULL;
    }
    
    node* getHead()
    {
        return head;
    }
    
    node* initilizeNode(Passanger* data)
    {
        node* newNode = createEmptyNode();
        newNode->passangerInfo = data;
        newNode->pPoints = data->getPoints();
        newNode->next = NULL;
        newNode->previous = NULL;
        return newNode;
    }
    
    node* createEmptyNode()
    {
        node* newNode = new node;
        newNode->next = NULL;
        newNode->previous = NULL;
        return newNode;
    }
    
    void insertAtLocation(node* newNode)
    {
        node* temp = createEmptyNode();
        temp = head;
        while(temp->next != NULL && temp->next->pPoints > newNode->pPoints)
        {
            temp = temp->next;
        }
        if(temp->next == NULL)
        {
            temp->next = newNode;
            newNode->previous = temp;
            tail = newNode;
        }
        else
        {
            temp->next->previous = newNode;
            newNode->next = temp->next;
            temp->next = newNode;
            newNode->previous = temp;
        }
    }
    
    void insert(node* newNode)
    {
        node* temp = createEmptyNode();
        temp = head;
        if(temp->pPoints < newNode->pPoints) //If heads points are less than the new nodes, make new node head
        {
            newNode->next = temp;
            temp->previous = newNode;
            head = newNode;
        }
        else if(temp->next == NULL) //If head is only node, insert after head
        {
            temp->next = newNode;
            newNode->previous = temp;
            newNode->next = NULL;
            tail = newNode->next;
        }
        else
        {
            insertAtLocation(newNode);
        }
    }
    
    void addToQueue(Passanger* data)
    {
        node* newNode = initilizeNode(data);
        if(head == NULL)
        {
            head = newNode;
            tail = newNode->next;
        }
        else
        {
            insert(newNode);
        }
    }
    
    void displayAll()
    {
        displayHeader();
        node *temp = new node;
        temp = head;
        while(temp != NULL)
        {
            Passanger* data;
            data = temp->passangerInfo;
            data->display();
            temp = temp->next;
        }
    }
};

int main()
{
    PQueue *queue = new PQueue; //Construct new Queue Class
    Passanger* data; //Pointer to Passanger Class
    
    //Construct 5 passanger objects
    Passanger p1("Jones", "GOLD", 437, 30);
    Passanger p2("Smith", "PLAT", 385, 38);
    Passanger p3("Lee", "NONE", 600, 58);
    Passanger p4("Harris", "SLVR", 486, 45);
    Passanger p5("White", "GOLD", 451, 60);
    
    cout << "Displaying from Class" << endl << endl;
    
    //Display 5 passanger objects
    displayHeader();
    p1.display();
    p2.display();
    p3.display();
    p4.display();
    p5.display();
    
    cout << endl << "Pushing into list" << endl;
    
    data = &p1;
    queue->addToQueue(data);
    
    data = &p2;
    queue->addToQueue(data);
    
    data = &p3;
    queue->addToQueue(data);
    
    data = &p4;
    queue->addToQueue(data);
    
    data = &p5;
    queue->addToQueue(data);
    
    cout << endl << "Displaying from list in order of Priority" << endl << endl;

    //Display 5 passanger objects from Queue in order of Priority
    queue->displayAll();
    
    cout << endl;
}
