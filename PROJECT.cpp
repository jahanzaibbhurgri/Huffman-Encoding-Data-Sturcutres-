#include "bits/stdc++.h"
#include "conio.h"
#include "windows.h"
#include "cstring"
#include <unordered_map>

using namespace std;


void gotoxy(int column, int line)
{
    COORD coordinates;     // coordinates is declared as COORD
    coordinates.X = column;     // defining x-axis
    coordinates.Y = line;     //defining  y-axis
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}
// A Tree node
struct Node
{
	char ch;
	int freq;
	Node *left, *right;

	//Constructor

	Node(char ch, int freq, Node* left, Node* right)
	{
    this->ch = ch;
	this->freq = freq;
	this->left = left;
	this->right = right;
	}
};

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		if(l->freq > r->freq)
		return true;
		else
            return false;
	}
};

// traverse the Huffman Tree and store Huffman Codes
// in a map.

void encode(Node* root, string str,unordered_map<char, string> &huffmanCode)
{
	if (root == NULL)
         return;

	// found a leaf node
	if (root->left==NULL && root->right==NULL) {
		huffmanCode[root->ch] = str;
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// traverse the Huffman Tree and decode the encoded string
void decode(Node* root, int &index, string str, fstream &off)
{
	if (root == NULL) {
		return;
	}

	// found a leaf node
	if (root->left==NULL && root->right==NULL)
	{
	  //  cout<<root->ch;
	    off<<root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str,off);
	else
		decode(root->right, index, str,off);
}
// Builds Huffman Tree and decode given input text

int buildHuffmanTree(string text)
{
    int cal = 0,num;
    string save,temp,temp1;
    char ch;
    unsigned char result;
	// count frequency of appearance of each character
	// and store it in a map
	//we use unordered_map instead of map because we did not know the order of characters in file because they are unordered
	// that's why we used unordered_map to store their frequencies

	unordered_map<char, int> freq;

	for (int i = 0 ; i < text.length() ; i ++) {
        ch = text[i] ;
		freq[ch]++;   // it calculates how many times the character came int whole file
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue<Node*,vector<Node*>,comp> pq; // it is used as a min heap

	// Create a leaf node for each character and add it
	// to the priority queue.

	unordered_map<char,int>::iterator itr; // iterator used
	pair<char,int> p;
	Node *node ;
	for(itr = freq.begin() ; itr!=freq.end() ; itr++)
    {
        p.first = itr->first;
        p.second = itr->second;
        node = new Node(p.first, p.second, NULL, NULL); // left->nullptr and right->nullptr
        pq.push(node);
    }

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		node = new Node('\0', sum, left, right);
		pq.push(node);
	}

	// root stores pointer to root of Huffman Tree
	Node* root = pq.top();

	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	   unordered_map<char, string> huffmanCode;

	   encode(root, "", huffmanCode);

        unordered_map<char, string>::iterator it;
        pair<char,string> pr;
	    cout << "\n\nHuffman Codes are :\n" << '\n';
	    for(it = huffmanCode.begin() ; it!= huffmanCode.end() ; it++)
        {

        pr.first = it->first ;
        pr.second = it->second ;
		cout << pr.first << " " << pr.second << '\n';
        }
        ofstream onf("BYTES.txt",ios::out);
	    ofstream of("BITS.txt",ios::out);
	    int j = 0 , k = 0 ,l = 0 ,x = 0;
	    string str;
	    for(int i = 0 ; i < text.length() ; i ++)
        {
		ch = text[i];
		str += huffmanCode[ch];
		temp1 = huffmanCode[ch];
        save+=temp1;


		if(save.length()==8)
		{
		x = 0 ;
        while(save[++x]!='\0'){
        result=(result<<1)|save[x]; // converting bits into byte and saving it into BYTES.txt file
        }
        onf<<result;
		num = stoi(save);
        of<<num;
        result = '\0';
        num = 0 ;
		}
		else if(save.length()>8)
        {
            if(temp.length()>0)
            save+=temp;
            else{
            l = 0 ;
            }
            while(k<save.length())
            {
                if(k >= 8)
                {
                    temp[l] = save[k];
                    save[k] = '\0';
                    l++;
                }
                k++;
            }
             x = 0 ;
             while(save[++x]!='\0'){
             result=(result<<1)|save[x];
             }
             onf<<result;
             num = stoi(save);
             of<<num;
             k = 0 ;
             save = "";
             result = '\0';
             l = 0 ;
             num = 0 ;
           }
        }
        onf.close();
	    of.close();
        //cout<<"\nENCODED VERSION :\n\n";
        //cout<<str<<endl;
	// traverse the Huffman Tree again and this time
	// decode the encoded string
	int index = -1;
	for(int i = 0 ; i < str.length() ; i++)
        cal++;

	fstream off("DECODED DATA.txt",ios::out);
	while (index < (int)str.size()) {
		decode(root, index, str,off);
	}
	off.close();
	return cal;
}
void square()
{
       int i,j;
       gotoxy(20,5);
       cout<<"\t\t";
       for(int i=0;i<50;i++)
       {
        Sleep(50);
        cout<<"* ";
       }
       cout<<"\n";
       for(i=1;i<=30;i++)
         {
	      cout<<"\t\t\t\t";
	      Sleep(45);
	      for(j=1;j<=50;j++)
	      {
	       if((i==4||i==50)||(j<=1||j>=50))
           {
	        Sleep(45);
            cout<<"* ";
	       }
	       else
	        cout<<"  ";
	      }
	      cout<<"\n";
        }
        gotoxy(32,35);
        for(int i=0;i<50;i++)
        {
         Sleep(45);
         cout<<"* ";
        }
}
//FUNCTION END
void fun(char a[],int l)
{
    gotoxy(40,7);
    char ch = 179;
	for(int i = 0; i < 10; i++)
        cout<<ch;
    ch--;
    Sleep(50);
    for(int i = 0; i < 10; i++)
        cout<<ch;
    ch--;
    Sleep(50);
    for(int i = 0; i < 10; i++)
        cout<<ch;
    fflush(stdout);

    for(int i = 0 ; i < l ; i ++)
    {
        cout<<a[i];
        Sleep(50);
    }
        Sleep(50);
        for(int i = 0; i < 10; i++)
        cout<<ch;

       Sleep(50);

       ch++;
       for(int i = 0; i < 10; i++)
        cout<<ch;

       Sleep(50);
       ch++;
       for(int i = 0;i < 10; i++)
        cout<<ch;
}
void fun1(char arr[],int len)
{
    fflush(stdout);
    for(int i = 0 ; i < len ; i ++)
    {
        cout<<arr[i];
        Sleep(60);
    }
}
void load(int i)
{
	if(i==1)
	return ;
	else
	{
	cout<<".";
    cout<<".";
    Sleep(1000);
    cout<<".";
    cout<<".";
    Sleep(1000);
    cout<<".";
    cout<<".";
    Sleep(1000);
    cout<<".";
    Sleep(1000);
    cout<<".";
    cout<<".";
    Sleep(1000);
    cout<<".";
    Sleep(1000);
    cout<<".";
    cout<<".\n";
    Sleep(1000);
    cout<<".";
    return load(i+1);
	}

}
int main()
{
    time_t start,endd;
    time(&start);
    system("COLOR 1");
	string text;
	char ch;
	square();
	fun("DATA COMPRESSION !!",strlen("DATA COMPRESSION !!"));
	gotoxy(38,14);
	fun1("NAME : ",strlen("NAME : "));
	gotoxy(52,14);
	fun1("USAMA BALOCH AND AZAIN ADAM",strlen("USAMA BALOCH AND AZAIN ADAM"));
	gotoxy(38,16);
	fun1("NU-ID : ",strlen("NU-ID : "));
	gotoxy(52,16);
	fun1("19K-1459 AND 19K-0282",strlen("19K-1459 AND 19K-0282"));
	gotoxy(38,18);
	fun1("ALGORITHM : ",strlen("ALGORITHM : "));
    gotoxy(52,18);
    fun1("HUFFMAN TREE",strlen("HUFFMAN TREE"));
    gotoxy(38,20);
    fun1("OTHER MAIN FEATURES : ",strlen("OTHER MAIN FEATURES : "));
	gotoxy(38,22);
	fun1("1) UNORDERED MAPS",strlen("1) UNORDERED MAPS"));
	gotoxy(38,23);
	fun1("2) PRIORITY QUEUE",strlen("2) PRIORITY QUEUE"));
	gotoxy(38,24);
	fun1("3) PRIR ORDER CONTAINER",strlen("3) PRIR ORDER CONTAINER"));
    gotoxy(38,28);
    fun1("PLEASE ENTER KEY TO CONTINUE TO COMPRESS YOUR PROVIDED FILE.",strlen("PLEASE ENTER KEY TO CONTINUE TO COMPRESS YOUR PROVIDED FILE."));
	getch();
	system("cls");
	system("COLOR 2");
    ifstream inf("DATA.txt",ios::in);
    if(inf.is_open())
    {
        while(inf>>noskipws>>ch)
        {
        	text+=ch;
        }
        inf.close();
    }
    int bits_ori = (text.length()*8);
    cout<<endl<<"-------------------------FILE DATA----------------------------\n\n"<<text<<" \n ";
	cout<<"ORIGINAL SIZE IN BITS = "<<bits_ori;
    cout<<"\nORIGINAL SIZE IN BYTE = "<<bits_ori/8<<endl;
    getch();
    system("cls");
	cout<<"COMPRESSING:";
	load(0);
    system("cls");
	int ans = buildHuffmanTree(text);
    cout<<"\nNO OF BITES = "<<ans<<endl;
    ans/=8;
    cout<<"\nSIZE IN BYTES  = "<<ans<<endl;
	time(&endd);
    double timeTaken = double(endd-start);
    cout<<"TIME TAKEN : "<<timeTaken<<setprecision(4)<<" Seconds"<<endl;
	return 0;
}
