/**
Anagrams

An interesting problem is to print out all the anagrams of a given word.  That is, given an N-letter word with all letters different, print all the "words" you can form using each letter once, regardless of whether they are actual words in some language.  The number of such rearrangements is N-factorial where N is the number of letters.  The problem can be solved in several different ways, one of which uses one queue and one stack.  We illustrate the process here and leave the coding as a major programming project.

Say the word is abcdefgh and you have just printed ehcgfdba. The very next word in alphabetical order that you can form with those eight letters is ehdabcfg (compare the two to see why). The way one iteration of the main loop of the process goes from a stack 
containing ehcgfdba to that same stack containing ehdabcfg is as follows:

Initially you have the letters on the stack in reverse order, and you have an empty queue:
1.  Repeatedly pop a value from the stack and enqueue it on the queue, stopping as soon as you pop a value that comes alphabetically before the one you just enqueued.  Call that value the "pivot".
2.  Repeatedly dequeue a value and enqueue it, stopping as soon as you dequeue a value that comes alphabetically after the pivot.  Push that value onto the stack.
3.  Enqueue the pivot, then repeatedly dequeue a value and enqueue it, stopping as soon as you dequeue a value that is alphabetically before the pivot. Push it onto the stack.  
4. Repeatedly dequeue a value from the queue and push it on the stack until the queue is empty.
**/

#include <iostream>
#include <cstring>

using namespace std;

#define MAX 100
char output_anagrams[26];

/////////////////////////////////////<------------Stack Function-------------->/////////////////////////////////////////
class Stack
{
public:
    int top;
    char a[MAX];    //Maximum size of Stack
    Stack()  
	{ 
	top = -1; 
	}
    bool push(char x);
    char pop();
    char istop();
    bool isEmpty();
};


bool Stack::push(char x)
{
    if (top >= MAX)
    {
        cout << "Stack Overflow" << endl;
        return false;
    }
    else
    {
        a[++top] = x;
	//cout << x << " pushed from " << top << " position" << endl;
        return true;
    }
}
 
char Stack::pop()
{
    if (top < 0)
    {
        cout << "Stack Underflow" << endl;
        return 0;
    }
    else
    {
	//cout << a[top] << " pop from " << top << " position" << endl;
        char x = a[top--];
	
        return x;
    }
}
 
bool Stack::isEmpty()
{return (top < 0);}

char Stack::istop()
{return a[top];}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////<------------Queue Function-------------->/////////////////////////////////////////
class Queue{
    private:
        char item[MAX];
        int rear;
        int front;
    public:
        Queue();
        void enqueue(char);
        char dequeue();
        int size();
        void display();
        bool isEmpty();
        bool isFull();
	char isrear();
	char isfront();
};

char Queue::isrear()
{return item[rear];}

char Queue::isfront()
{return item[front];}

Queue::Queue()
	{
	rear = -1;
	front = 0;
	}

void Queue::enqueue(char data)
	{
        item[++rear] = data;
	//cout << data << " enqueue from " << rear << " position" << endl;
	}

char Queue::dequeue()
	{
	//cout << "Dequeue from " << front << " position" << endl;
        return item[front++];
	}

void Queue::display()
	{
	if(!this->isEmpty())
	{
        for(int i=front; i<=rear; i++)
	cout<<item[i]<<endl;
    	}
	else
	{
        cout<<"Queue Underflow"<<endl;
    	}
	}

int Queue::size()
	{
	return (rear - front + 1);
	}

bool Queue::isEmpty()
	{
	if(front>rear)
	{
        return true;
	}
	else
	{
        return false;
	}
	}

bool Queue::isFull()
	{
	if(this->size()>=MAX)
	{
        return true;
	}
	else
	{
        return false;
	}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////<------ANAGRAM GENERATION FUNCTION---->///////////////////////////////////////////
void anagram_output(char array[], int char_length)
{
	char pivot;
	struct Stack s;
	struct Stack new_stack;
	struct Queue q;
	for(int i=0;i<char_length;i++)
	{
		s.push(array[i]);
	}

//1.  Repeatedly pop a value from the stack and enqueue it on the queue, stopping as soon as you pop a value that comes alphabetically before the one you just enqueued.  Call that value the "pivot".
	
	while(1)
	{
		char ch = s.pop();
		if(ch < q.isrear())
		{
			pivot = ch;
			break;
		}
		else
		{
			q.enqueue(ch);
		}
	}

	//cout << "pivot value: " << pivot << endl;

//2.  Repeatedly dequeue a value and enqueue it, stopping as soon as you dequeue a value that comes alphabetically after the pivot.  Push that value onto the stack.

	while(1)
	{
	char ch = q.dequeue();
		if(ch < pivot)
		{
			q.enqueue(ch);
		}	
		else
		{
			s.push(ch);
			break;
		}
	}			

//3.  Enqueue the pivot, then repeatedly dequeue a value and enqueue it, stopping as soon as you dequeue a value that is alphabetically before the pivot.  Push it onto the stack. 
//4.Repeatedly dequeue a value from the queue and push it on the stack until the queue is empty.	
	
	q.enqueue(pivot);

	while(1)
	{
	char ch = q.dequeue();
		if(ch > pivot)
		{
			q.enqueue(ch);
		}	
		else
		{
			while(q.isEmpty() != true)
			{
			s.push(ch);
			ch = q.dequeue();
			}
			s.push(ch);		
			break;
		}
	}			

//5. Pop out the stack and reverse the stack and Output the string from output stack
	
	while(s.isEmpty() != true)
	{
		char ch = s.pop();
		new_stack.push(ch); 	
	}

	int i=0;
	//char out_str[26];

	while(new_stack.isEmpty() != true)
	{
		output_anagrams[i] = new_stack.pop(); 
		//cout << out_str[i] << " inserted at " << i << " position" << endl;
		i++;	
	}

	for(int i=0;i<char_length;i++)
	{
		cout << output_anagrams[i];
	}

cout << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Main Function
int main()
{  
	char input_str[26];
	cout << "Enter the string: "; 
	cin >> input_str;
	size_t len = strlen(input_str); // Size of characters entered in array

	if (len == 1)
	{
		cout << "You cannot enter single character" << endl;
		exit(0);
	}
	else
	{
		int i=2;
	
		//Character Array sorting using bubble sort
		for(int f=0;f<len-1;f++)
		{
			for(int j=0;j<len-f-1;j++)
				if(input_str[j]>input_str[j+1])
		                     {
					char temp=input_str[j];
					input_str[j]=input_str[j+1];
					input_str[j+1]=temp;
		                     }
		}
	
		//Function to check if all characters entered are unique in sorted array
		for(int f=0;f<len-1;f++)
		{
			if(input_str[f]==input_str[f+1])
			{
				cout << "You have entered two same characters in string | String must hold unique characters" << endl;
				exit(0);
			}
		}
		
		//Function to check if user enter only character and not numbers
		for(int j=0;j<len;j++)
		{
			char c = input_str[j]; 
			if (c >= '0' && c <= '9')
			{
				cout << "You can only enter characters and not numbers" << endl;
					exit(0);
			}
		}

		//Factorial finding
		int fact=1;
		for(int j=len;j>0;j--)
		{
			fact = fact * j;
		}
		cout << "Total number of rearrangements of entered string is: " << fact << endl;
		cout << "Sorted string is: " << input_str << endl;
		cout << "\n";
		cout << "Rearrangements are as follows" << endl;
		cout << input_str << endl;
	
		//sending character array to anagram_output function
		anagram_output(input_str, len);
	
		//output other strings except first
		int j = 2;
		while(j<=fact-1)
		{
			anagram_output(output_anagrams, len);
			j++;
		}
	}

return 0;
}
