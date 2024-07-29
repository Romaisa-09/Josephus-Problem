#define _USE_MATH_DEFINES
#include <windows.h>
#include <WinCon.h>
#include <iostream>
#include <cmath>
#include "myconsole.h"
#include"mygraphics.h"
using namespace std;
struct node {
public:
	int data;
	node* next;
	node()
	{
		data = 0;
		next = NULL;
	}
	node(int a)
	{
		next = NULL;
		data = a;
	}
};
class CircularQueue {
public:
	node* front;
	node* rear;
	int maxSize;
	CircularQueue()
	{
		front = rear = NULL;
		maxSize = 0;
	}
	void EnQue(int val)
	{
		node* newNode = new node(val);
		if (front == NULL || rear == NULL)
		{
			front = newNode;
			rear = newNode;

		}
		else
		{
			rear->next = newNode;
			rear = newNode;
			newNode->next = front;
			
		}
		maxSize++;
	}
	void DeQue(int &x)		//x will have the recent popped value
	{
		if (front == NULL)
		{
			cout << "Queue is Empty" << endl;
			return;
		}
		maxSize--;
		if (front == rear)
		{
			x = front->data;
			delete front;
			front = rear = NULL;
			return;
		}
		node* newNode=new node;
		newNode = front;
		x = newNode->data;
		front = front->next;
		rear->next = front;
		delete (newNode);
		return;
	}
	int getMaxSize()
	{
		return maxSize;
	}
	void print()
	{
		if (maxSize == 0)
		{
			cout << "Queue is empty" << endl;
		}
		node* current = new node;
		current = front;
		//system("cls");
		ClearScreen();
		int total_num = this->getMaxSize(); //will have the total number of peoples
		double degrees = 0;
		float* x_axis=new float[total_num];
		float* y_axis = new float[total_num];
		double radius = 12;
		for (int i = 0; i < total_num; i++)
		{
			degrees = i * (360 / total_num); //for the equal distribution of the players
			float radian = (degrees * (M_PI / 180));  //for the radian
			x_axis[i] = 30 + radius * cos(radian); //for the x-coordinate
			y_axis[i] = 20 + radius * sin(radian); //for the y-coordinate
			PlaceCursor(x_axis[i], y_axis[i]);	//for the cursor which also tells the next player
			cout << current->data << "  ";
			current = current->next;
		}
		Sleep(300);		//for the time delay
		//system("pause");
	}
	int Josephus(int k)
	{
		int x=0;
		node* current = front; 
		while (front->next != front) //till the last person 
		{
			this->print();
			for (int i = 1 ;i < k; i++)
			{
				this->DeQue(x);		//will deque till the specific person to kill
				this->EnQue(x);		//will enque at the end
			}
			this->DeQue(x);
		}
		return front->data; //returns the winner
	}
};

int main()
{
	system("Color 0B");		 //0-Black BackGround and B-Light Aqua ForeGround
	CircularQueue c;
	int num, k;
	cout << "Enter the total number: ";
	cin >> num;
	cout << "Enter the k: ";
	cin >> k;
	for (int i = 0; i <= num; i++)
	{
		c.EnQue(i);		//total number of players
	}
	int win=c.Josephus(k);
	system("cls");
	cout <<"---------------" << win << " IS THE WINNER--------------- " << endl;
	system("pause");
	return 0;
}