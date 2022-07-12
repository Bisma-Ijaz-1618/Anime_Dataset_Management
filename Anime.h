#pragma once
#include<string>
using namespace std;

enum typetree { //for input recognition in Tree_AnimePointerLists
   Episodes = 1,Rank=2,Popularity=3,Members=4,Favourites=5,
   Watching=6,Completed=7,OnHold=8,Dropped=9,PlanToWatch=10,AVGscore=11
};

//DECLARING CLASSES/
class ListNode_AnimePointer;
class Singly_Linked_List_Of_Anime_Pointers;
class ListNode_AVLPointer;
class Singly_Linked_List_Of_AVL_Node_Pointers;
class Anime;
class AnimeNode;
class AnimeTree;
class AVL_Tree;
class AVL_Node;
class Node_AnimePointersLists;
class Tree_AnimePointerLists;

class ListNode_AVLPointer { //list nodes of AVL trees
public:
	AVL_Node* AVL_Pointer = NULL;
	ListNode_AVLPointer* next = NULL;
};
class Singly_Linked_List_Of_AVL_Node_Pointers { //lists for storing multivalued producers, genres, licensors and studios
public:
	int Node_count = 0; //keeping track of number of nodes
	ListNode_AVLPointer* first = NULL;
	ListNode_AVLPointer* last = NULL;
	ListNode_AVLPointer* Lock = NULL;
	ListNode_AVLPointer* Plock = NULL;
	bool isEmpty();
	void InsertAtFront(AVL_Node* X);
	void Search(AVL_Node* value);
	void Print_Values_In_Node_Addresses(void);
	//void InsertAtEnd(AVL_Node* X);
	//void InsertSorted(AVL_Node* X);
	//void DeleteFront();
	//void DeleteLast();
	//void Delete(AVL_Node* X);
	//void Destroy_List();
};
class Anime { //contains info about a single anime
public:
	unsigned int ID = 0;
	string Name = "";
	float  Score = 0;//yet to decide
	short unsigned int Type=0;//enum  
	short unsigned int Episodes = 0;
	Singly_Linked_List_Of_AVL_Node_Pointers ProducersList; //multivalued attributes
	Singly_Linked_List_Of_AVL_Node_Pointers LiscensorsList;
	Singly_Linked_List_Of_AVL_Node_Pointers StudiosList;
	Singly_Linked_List_Of_AVL_Node_Pointers GenresList;
	string PrimierDate = "";
	string Source = "";
	string Duration = "";
	string Rating = "";
	unsigned int Rank = 0;
	unsigned int Popularity = 0;
	unsigned int Members = 0;
	unsigned int Favourites = 0;
	unsigned int Watching = 0;
	unsigned int Completed = 0;
	unsigned int OnHold = 0;
	unsigned int Dropped = 0;
	unsigned int PlanToWatch = 0;
	unsigned int AVGscore = 0;
	//~Anime();
};
class ListNode_AnimePointer { //list node of anime pointers
public:
	AnimeNode* Pointer = NULL;
	ListNode_AnimePointer* next = NULL;
};
class Singly_Linked_List_Of_Anime_Pointers { //list of anime pointers
public:
	int Node_count = 0; //keeping track of number of items
	ListNode_AnimePointer* first = NULL;
	ListNode_AnimePointer* last = NULL;
	ListNode_AnimePointer* Lock = NULL;
	ListNode_AnimePointer* Plock = NULL;
	bool isEmpty();
	void InsertAtFront(AnimeNode* X);
	void Search(AnimeNode* value);
	void Print_Names_At_Anime_Nodes();
	//void InsertAtEnd(AnimeNode* X);
	//void InsertSorted(AnimeNode* X);
	//void DeleteFront();
	//void DeleteLast();
	//void Delete(AnimeNode* X);
	//void Destroy_List();

};
class Node_AnimePointersLists { //node of trees storing anime pointer lists
public:
	unsigned int value = 0;
	Singly_Linked_List_Of_Anime_Pointers List;
	int height = 0;
	Node_AnimePointersLists* LeftChild = NULL;
	Node_AnimePointersLists* RightChild = NULL;
};
class Tree_AnimePointerLists { //tree storing anime pointers for sorted statistics
public:
	short unsigned int type_data = 0;
	int	Node_count = 0; //keeping track of number of items
	Node_AnimePointersLists* Root = NULL;
	Node_AnimePointersLists* Lock = NULL;
	Node_AnimePointersLists* PLock = NULL;
	//functions
	Node_AnimePointersLists* Continue_Traversal(Node_AnimePointersLists* Prior_Node, Node_AnimePointersLists* Node);
	int Height_Of_Node(Node_AnimePointersLists* Node);
	int Balance_Factor_At_Node(Node_AnimePointersLists* Node);
	void Left_Rotation(Node_AnimePointersLists* X, Node_AnimePointersLists* Parent_X, int Balance_Factor);
	void Right_Rotation(Node_AnimePointersLists* X, Node_AnimePointersLists* Parent_X, int Balance_Factor);
	void Correct_Tree_Balance(Node_AnimePointersLists* Prior_Node, Node_AnimePointersLists* Node);
	void Update_Heights(Node_AnimePointersLists* Pre_X, Node_AnimePointersLists* X);
	void switch_Search(unsigned int Val);
	string string_type_data(short unsigned int type_data); //type of data stored
	void Insert_Value_Without_Duplication(unsigned int,AnimeNode*);
	void Pre_Order_Printing(Node_AnimePointersLists* current);
	void In_Order_Printing(Node_AnimePointersLists* current);
	void Post_Order_Printing(Node_AnimePointersLists* current);
	//void Destroy_Tree(Node_AnimePointersLists* Node);
	//void Print(void);
	//print functions or questions
};
class AnimeNode {
public:
	Anime data;
	int height = 0;
	AnimeNode* LeftChild = NULL;
	AnimeNode* RightChild = NULL;
	void Print_Anime_Node_Data(void); //print all anime data for that anime
	void PrintAnimeName(void);// {
		//cout << data.Name << endl;
	//}
};
class AnimeTree { //tree containing all anime's
public:
	int	Node_count = 0; //keeping track of number of anime's
	AnimeNode* Root = NULL;
	AnimeNode* Lock = NULL;
	AnimeNode* PLock = NULL;
	//functions
	int Height_Of_Node(AnimeNode* Node);
	int Balance_Factor_At_Node(AnimeNode* Node);
	void Left_Rotation(AnimeNode* X, AnimeNode* Parent_X, int Balance_Factor);
	void Right_Rotation(AnimeNode* X, AnimeNode* Parent_X, int Balance_Factor);
	void Correct_Tree_Balance(AnimeNode* Prior_Node, AnimeNode* Node);
	void Update_Heights(AnimeNode* Pre_X, AnimeNode* X);
	//void PrintMenu();
	void Insert_Value_Without_Duplication(Anime A,Tree_AnimePointerLists* Episodes, Tree_AnimePointerLists* Rank, Tree_AnimePointerLists* Popularity, Tree_AnimePointerLists* Members, Tree_AnimePointerLists* Favourites, Tree_AnimePointerLists* Watching, Tree_AnimePointerLists* Completed, Tree_AnimePointerLists* OnHold, Tree_AnimePointerLists* Dropped, Tree_AnimePointerLists* PlanToWatch,Tree_AnimePointerLists* AVGscore);
	void Search_Value(int Val);
	void Pre_Order_Printing(AnimeNode* current);
	void In_Order_Printing_for_Menu(AnimeNode* current);
	void In_Order_Printing(AnimeNode* current);
	void Post_Order_Printing(AnimeNode* current);
	//void Delete_Value(int value);
	//void Destroy_Tree(AnimeNode* Node);
	//void Print(void);
	//print functions or questions
};


class AVL_Node {
public:
	int height = 0;
	string Name;
	Singly_Linked_List_Of_Anime_Pointers Anime_List; //list of pointers to anime's it belongs to
	AVL_Node* LeftChild = NULL;
	AVL_Node* RightChild = NULL;
	void PrintAVLName(void);
	void PrintAnimeList(void);
};
class AVL_Tree {
public:
	unsigned int print_count = 0; //printing count on menu screen
	int	Node_count = 0; //keeping track of number of nodes/items
	AVL_Node* Root = NULL;
	AVL_Node* Lock = NULL;
	AVL_Node* PLock = NULL;
	int Height_Of_Node(AVL_Node* Node);
	int Balance_Factor_At_Node(AVL_Node* Node);
	void Left_Rotation(AVL_Node* X, AVL_Node* Parent_X, int Balance_Factor);
	void Right_Rotation(AVL_Node* X, AVL_Node* Parent_X, int Balance_Factor);
	void Correct_Tree_Balance(AVL_Node* Prior_Node, AVL_Node* Node);
	void Update_Heights(AVL_Node* Pre_X, AVL_Node* X);
	AVL_Node* Insert_Value_Without_Duplication(string Name);
	void Search_Value(string Val);
	void Pre_Order_Printing(AVL_Node* current);
	void In_Order_Printing(AVL_Node* current);
	void In_Order_Printing_for_Menu(AVL_Node* current);
	void Post_Order_Printing(AVL_Node* current);
	//void Delete_Value(string value);
	//void Destroy_Tree(AVL_Node* Node);
	//void Print(void);
};