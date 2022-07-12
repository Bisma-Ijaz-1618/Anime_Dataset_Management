#include"Anime.h"
#include<iostream>
using namespace std;
//general functions for main

//ANIME TREE FUNCTIONS //
void AnimeNode::Print_Anime_Node_Data() { //print all data for one anime (printing data in the anime node)
    cout << "ID = " << data.ID << endl;
    cout << "Name = " << data.Name << endl;
    cout << "List of Producers::\n";
    data.ProducersList.Print_Values_In_Node_Addresses(); //call respective avl tree printing
    cout << "Score = " << data.Score << endl;
    cout << "Type = ";
    switch (data.Type) {
    case 0:
        cout << "TV" << endl;
        break;
    case 1:
        cout << "Movie" << endl;
        break;
    case 2:
        cout << "OVA" << endl;
        break;
    case 3:
        cout << "Special" << endl;
        break;
    case 4:
        cout << "ONA" << endl;
        break;
    case 5:
        cout << "Music" << endl;
        break;
    default:
        cout << "Unknown" << endl;
    }
    cout << "Episodes = " << data.Episodes << endl;
    cout << "List of Licensors::\n"; //call respective avl trees printing
    data.LiscensorsList.Print_Values_In_Node_Addresses();
    cout << "List of Studios::\n";
    data.StudiosList.Print_Values_In_Node_Addresses();
    cout << "List of Genres::\n";
    data.GenresList.Print_Values_In_Node_Addresses();
    cout << "Premier date = " << data.PrimierDate << endl;
    cout << "Source = " << data.Source << endl;
    cout << "Duration = " << data.Duration << endl;
    cout << "Rating = " << data.Rating << endl;
    cout << "Rank = " << data.Rank << endl;
    cout << "Popularity = " << data.Popularity << endl;
    cout << "Members = " << data.Members << endl;
    cout << "Favourites = " << data.Favourites << endl;
    cout << "Watching = " << data.Watching << endl;
    cout << "Completed = " << data.Completed << endl;
    cout << "On hold = " << data.OnHold << endl;
    cout << "Dropped = " << data.Dropped << endl;
    cout << "Plan to watch = " << data.PlanToWatch << endl;
    cout << "Average User Score = " << data.AVGscore << endl << endl << endl;
}
int AnimeTree::Height_Of_Node(AnimeNode* Node) { //calculating height of node
    if (Node == NULL)
        return -1;
    else
        return 1 + fmax(Height_Of_Node(Node->LeftChild), Height_Of_Node(Node->RightChild));
}
int AnimeTree::Balance_Factor_At_Node(AnimeNode* Node) { //check balance factor
    int Height_LeftTree = 0;
    if (Node->LeftChild != NULL)
        Height_LeftTree = 1 + Node->LeftChild->height;
    int Height_RightTree = 0;
    if (Node->RightChild != NULL)
        Height_RightTree = 1 + Node->RightChild->height;
    return Height_LeftTree - Height_RightTree;
}
void AnimeTree::Left_Rotation(AnimeNode* X, AnimeNode* Parent_X, int Balance_Factor) {
    AnimeNode* Y = X->RightChild;//left rotation hence y is taken to be right child
    int Balance = Balance_Factor_At_Node(Y);//balance factor of right child
    if (Balance == -2) {//skipping rotation on nodes if the next nodes are also imbalaced by a factor of
        Left_Rotation(Y, X, Balance);
        goto skip;
    }
    else if (Balance == +2) {
        Right_Rotation(Y, X, Balance);
        goto skip;
    }
    else if (Balance == 1 && Balance_Factor == -2)//if orignal balance factor is -2
        Right_Rotation(Y, X, Balance);//leads to right-left rotation//
    //left rotation
    cout << "\n->Left rotation around Node " << X->data.ID << endl;
    Y = X->RightChild;
    X->RightChild = Y->LeftChild;
    Y->LeftChild = X;
    if (X != Root) {//if x is not root we update the parent node
        if (Parent_X->RightChild == X)
            Parent_X->RightChild = Y;
        else
            Parent_X->LeftChild = Y;
    }
    else//else y is the new root
        Root = Y;
    Update_Heights(Y, X);
skip:
    cout << "";
}
void AnimeTree::Right_Rotation(AnimeNode* X, AnimeNode* Parent_X, int Balance_Factor) {
    AnimeNode* Y = X->LeftChild;//left rotation hence y is taken to be right child
    int Balance = Balance_Factor_At_Node(Y);//balance factor of leftchild
    if (Balance == -2) {
        Left_Rotation(Y, X, Balance);
        goto skip;
    }
    else if (Balance == +2) {
        Right_Rotation(Y, X, Balance);
        goto skip;
    }
    else if ((Balance == -1) && Balance_Factor == 2) //if orignal balance factor is +2
        Left_Rotation(Y, X, Balance);//leads to left-right rotation//
    //right rotation
    cout << "->Right rotation around Node " << X->data.ID << endl;

    Y = X->LeftChild;
    X->LeftChild = Y->RightChild;
    Y->RightChild = X;

    if (X != Root) {//if x is not root we update the parent node
        if (Parent_X->RightChild == X)
            Parent_X->RightChild = Y;
        else
            Parent_X->LeftChild = Y;
    }
    else
        Root = Y;
    Update_Heights(Y, X);//heights are update after rotation.
skip:
    cout << "";
}
void AnimeTree::Correct_Tree_Balance(AnimeNode* Prior_Node, AnimeNode* Node) {
    int Balance_Factor = 0;
    AnimeNode* temp = NULL;
    while (Prior_Node != Node) {//traversing and checking if balance has been disrupted
        Balance_Factor = Balance_Factor_At_Node(Prior_Node);
        if (Balance_Factor == 2) {//right rotation called in case of +2 balance factor
            Right_Rotation(Prior_Node, temp, Balance_Factor);
            break;
        }
        else if (Balance_Factor == -2) {//left rotaiton called in case of -2 balance factor
            Left_Rotation(Prior_Node, temp, Balance_Factor);
            break;
        }
        else {//if balance factor is -1,+1 or 0 then traversal continues
            temp = Prior_Node;
            if (Prior_Node->data.ID > Node->data.ID)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild;
        }
    }
}
void AnimeTree::Update_Heights(AnimeNode* Pre_X, AnimeNode* X) {
    while (1) {//traversal from prenode to node X
        Pre_X->height = Height_Of_Node(Pre_X);//each nodes height is updated
        if (Pre_X == X)
            break;
        else {//traversal continues until final node reached
            if (X->data.ID < Pre_X->data.ID)
                Pre_X = Pre_X->LeftChild;
            else
                Pre_X = Pre_X->RightChild;
        }
    }
}
void AnimeTree::Search_Value(int Val) { //anime tree sorted on the basis of anime ID
    PLock = NULL;
    Lock = Root;
    while (Lock != NULL) {
        if (Lock->data.ID == Val)
            return;
        else if (Lock->data.ID > Val) {
            PLock = Lock;
            Lock = Lock->LeftChild;
        }
        else if (Lock->data.ID < Val) {
            PLock = Lock;
            Lock = Lock->RightChild;
        }
    }
}
void AnimeTree::Pre_Order_Printing(AnimeNode* current) {
    if (current != NULL) {
        current->Print_Anime_Node_Data();
        //cout << current->data.ID << " ";
        Pre_Order_Printing(current->LeftChild);
        Pre_Order_Printing(current->RightChild);
    }
}
void AnimeTree::In_Order_Printing_for_Menu(AnimeNode* current) { //info to be displayed in menu for printing anime's without info
    if (current != NULL) {
        In_Order_Printing_for_Menu(current->LeftChild);        
        cout << "ID = " << current->data.ID << endl << "Name = " << current->data.Name << endl << endl;
        In_Order_Printing_for_Menu(current->RightChild);
    }
}
void AnimeTree::In_Order_Printing(AnimeNode* current) { //for printing anime's with info
    if (current != NULL) {
        In_Order_Printing(current->LeftChild);
        //cout << current->data.ID << " ";        
        current->Print_Anime_Node_Data();
        In_Order_Printing(current->RightChild);
    }
}
void AnimeTree::Post_Order_Printing(AnimeNode* current)
{
    if (current != NULL) {
        Post_Order_Printing(current->LeftChild);
        Post_Order_Printing(current->RightChild);
        //cout << current->data.ID << " ";
        current->Print_Anime_Node_Data();
    }
}
void AnimeNode::PrintAnimeName() {
    cout << data.Name;
}
void AnimeTree::Insert_Value_Without_Duplication(Anime A, Tree_AnimePointerLists* Episodes, Tree_AnimePointerLists* Rank, Tree_AnimePointerLists* Popularity, Tree_AnimePointerLists* Members, Tree_AnimePointerLists* Favourites, Tree_AnimePointerLists* Watching, Tree_AnimePointerLists* Completed, Tree_AnimePointerLists* OnHold, Tree_AnimePointerLists* Dropped, Tree_AnimePointerLists* PlanToWatch, Tree_AnimePointerLists* AVGscore) {
    Search_Value(A.ID);
    if (Lock == NULL) {
        //cout << "\x1b[34mInserting ::" << A.ID << "\x1b[37m" << endl;
        AnimeNode* New_Node = new AnimeNode();
        New_Node->data = A;
        if (PLock != NULL) {
            if (A.ID < PLock->data.ID)
                PLock->LeftChild = New_Node;
            else
                PLock->RightChild = New_Node;
        }
        else
            Root = New_Node;
        New_Node->data.ProducersList.Print_Values_In_Node_Addresses();


        //accessing nodes pointed to by addresses in sublists
        //updating the anime list in those nodes by inserting the pointer of anime node
        ListNode_AVLPointer* ListPointerValue = New_Node->data.GenresList.first;
        AVL_Node* AVL_Node_Pointer_In_List;
        while (ListPointerValue != NULL) {
            AVL_Node_Pointer_In_List = ListPointerValue->AVL_Pointer;;
            AVL_Node_Pointer_In_List->Anime_List.InsertAtFront(New_Node);
            ListPointerValue = ListPointerValue->next;
        }
        ListPointerValue = New_Node->data.ProducersList.first;
        //Doubly_Linked_List_Of_AVL_Node_Pointers* list = New_Node->data.ProducersList;
        while (ListPointerValue != NULL) {
            AVL_Node_Pointer_In_List = ListPointerValue->AVL_Pointer;
            cout << "Inserting newnode in AVL NODE::" << AVL_Node_Pointer_In_List->Name << endl;
            AVL_Node_Pointer_In_List->Anime_List.InsertAtFront(New_Node);
            ListPointerValue = ListPointerValue->next;
        }
        ListPointerValue = New_Node->data.LiscensorsList.first;
        while (ListPointerValue != NULL) {
            AVL_Node_Pointer_In_List = ListPointerValue->AVL_Pointer;
            AVL_Node_Pointer_In_List->Anime_List.InsertAtFront(New_Node);
            ListPointerValue = ListPointerValue->next;
        }
        ListPointerValue = New_Node->data.StudiosList.first;
        while (ListPointerValue != NULL) {
            AVL_Node_Pointer_In_List = ListPointerValue->AVL_Pointer;
            AVL_Node_Pointer_In_List->Anime_List.InsertAtFront(New_Node);
            ListPointerValue = ListPointerValue->next;
        }
        //now we  insert pointer of Anime nodes in sorting trees//
        Episodes->Insert_Value_Without_Duplication(A.Episodes, New_Node);
        Rank->Insert_Value_Without_Duplication(A.Rank, New_Node);
        Popularity->Insert_Value_Without_Duplication(A.Popularity, New_Node);
        Members->Insert_Value_Without_Duplication(A.Members, New_Node);
        Favourites->Insert_Value_Without_Duplication(A.Favourites, New_Node);
        Watching->Insert_Value_Without_Duplication(A.Watching, New_Node);
        Completed->Insert_Value_Without_Duplication(A.Completed, New_Node);
        OnHold->Insert_Value_Without_Duplication(A.OnHold, New_Node);
        Dropped->Insert_Value_Without_Duplication(A.Dropped, New_Node);
        PlanToWatch->Insert_Value_Without_Duplication(A.PlanToWatch, New_Node);
        AVGscore->Insert_Value_Without_Duplication(A.AVGscore, New_Node);
        Update_Heights(Root, New_Node);//after insertion height is updated
        Correct_Tree_Balance(Root, New_Node);//after heights are updated, the tree balance is checked and corrected
    }
    else
        cout << "Duplicate ID =" << A.ID << " cannot be inserted" << "\n";
}

//Functions for AVL Trees Containing PRODUCERS/LICENSORS/GENRE/STUDIOS

int AVL_Tree::Height_Of_Node(AVL_Node* Node) { 
    if (Node == NULL)
        return -1;
    else
        return 1 + fmax(Height_Of_Node(Node->LeftChild), Height_Of_Node(Node->RightChild));
}
int AVL_Tree::Balance_Factor_At_Node(AVL_Node* Node) {
    int Height_LeftTree = 0;
    if (Node->LeftChild != NULL)
        Height_LeftTree = 1 + Node->LeftChild->height;
    int Height_RightTree = 0;
    if (Node->RightChild != NULL)
        Height_RightTree = 1 + Node->RightChild->height;
    return Height_LeftTree - Height_RightTree;
}
void AVL_Tree::Left_Rotation(AVL_Node* X, AVL_Node* Parent_X, int Balance_Factor) {
    AVL_Node* Y = X->RightChild;//left rotation hence y is taken to be right child
    int Balance = Balance_Factor_At_Node(Y);//balance factor of right child
    if (Balance == -2) {//skipping rotation on nodes if the next nodes are also imbalaced by a factor of
        Left_Rotation(Y, X, Balance);
        goto skip;
    }
    else if (Balance == +2) {
        Right_Rotation(Y, X, Balance);
        goto skip;
    }
    else if (Balance == 1 && Balance_Factor == -2)//if orignal balance factor is -2
        Right_Rotation(Y, X, Balance);//leads to right-left rotation//
    //left rotation
    cout << "\n->Left rotation around Node " << X->Name << endl;
    Y = X->RightChild;
    X->RightChild = Y->LeftChild;
    Y->LeftChild = X;
    if (X != Root) {//if x is not root we update the parent node
        if (Parent_X->RightChild == X)
            Parent_X->RightChild = Y;
        else
            Parent_X->LeftChild = Y;
    }
    else//else y is the new root
        Root = Y;
    Update_Heights(Y, X);
skip:
    cout << "";
}
void AVL_Tree::Right_Rotation(AVL_Node* X, AVL_Node* Parent_X, int Balance_Factor) {
    AVL_Node* Y = X->LeftChild;//left rotation hence y is taken to be right child
    int Balance = Balance_Factor_At_Node(Y);//balance factor of leftchild
    if (Balance == -2) {
        Left_Rotation(Y, X, Balance);
        goto skip;
    }
    else if (Balance == +2) {
        Right_Rotation(Y, X, Balance);
        goto skip;
    }
    else if ((Balance == -1) && Balance_Factor == 2) //if orignal balance factor is +2
        Left_Rotation(Y, X, Balance);//leads to left-right rotation//
    //right rotation
    cout << "->Right rotation around Node " << X->Name << endl;

    Y = X->LeftChild;
    X->LeftChild = Y->RightChild;
    Y->RightChild = X;

    if (X != Root) {//if x is not root we update the parent node
        if (Parent_X->RightChild == X)
            Parent_X->RightChild = Y;
        else
            Parent_X->LeftChild = Y;
    }
    else
        Root = Y;
    Update_Heights(Y, X);//heights are update after rotation.
skip:
    cout << "";
}
void AVL_Tree::Correct_Tree_Balance(AVL_Node* Prior_Node, AVL_Node* Node) {
    int Balance_Factor = 0;
    AVL_Node* temp = NULL;
    while (Prior_Node != Node) {//traversing and checking if balance has been disrupted
        Balance_Factor = Balance_Factor_At_Node(Prior_Node);
        if (Balance_Factor == 2) {//right rotation called in case of +2 balance factor
            Right_Rotation(Prior_Node, temp, Balance_Factor);
            break;
        }
        else if (Balance_Factor == -2) {//left rotaiton called in case of -2 balance factor
            Left_Rotation(Prior_Node, temp, Balance_Factor);
            break;
        }
        else {//if balance factor is -1,+1 or 0 then traversal continues
            temp = Prior_Node;
            if (Prior_Node->Name > Node->Name)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild;
        }
    }
}
void AVL_Tree::Update_Heights(AVL_Node* Pre_X, AVL_Node* X) {
    while (1) {//traversal from prenode to node X
        Pre_X->height = Height_Of_Node(Pre_X);//each nodes height is updated
        if (Pre_X == X)
            break;
        else {//traversal continues until final node reached
            if (X->Name < Pre_X->Name)
                Pre_X = Pre_X->LeftChild;
            else
                Pre_X = Pre_X->RightChild;
        }
    }
}
AVL_Node* AVL_Tree::Insert_Value_Without_Duplication(string name) {
    Search_Value(name);
    if (Lock == NULL) {
        cout << "\x1b[34mInserting ::" << name << "\x1b[37m" << endl;
        AVL_Node* New_Node = new AVL_Node();
        New_Node->Name=name;
        if (PLock != NULL) {
            if (name < PLock->Name) //sorting based on name entered
                PLock->LeftChild = New_Node;
            else
                PLock->RightChild = New_Node;
        }
        else
            Root = New_Node;
        return New_Node;
        Update_Heights(Root, New_Node);//after insertion height is updated
        Correct_Tree_Balance(Root, New_Node);//after heights are updated, the tree balance is checked and corrected
    }
    else {
        cout << "Duplicate name =" << name << " cannot be inserted" << "\n";
        return Lock;
    }
}
void AVL_Tree::Search_Value(string Val) {
    PLock = NULL;
    Lock = Root;
    while (Lock != NULL) {
        if (Lock->Name == Val)
            return;
        else if (Lock->Name > Val) {
            PLock = Lock;
            Lock = Lock->LeftChild;
        }
        else if (Lock->Name < Val) {
            PLock = Lock;
            Lock = Lock->RightChild;
        }
    }
}
void AVL_Tree::Pre_Order_Printing(AVL_Node* current) {
    if (current != NULL) {
        cout << "\nName:: ";
        current->PrintAVLName();
        cout << "\nAnime List:: \n";
        current->PrintAnimeList(); //print anime's that belong to the producer/studio/licensor/genre
        Pre_Order_Printing(current->LeftChild);
        Pre_Order_Printing(current->RightChild);
    }
}
void AVL_Tree::In_Order_Printing(AVL_Node* current) {
    if (current != NULL) {
        In_Order_Printing(current->LeftChild);
        cout << "\nName:: ";
        current->PrintAVLName();
        cout << "\nAnimeList:: \n";
        current->PrintAnimeList(); //print anime's that belong to the producer/studio/licensor/genre
        In_Order_Printing(current->RightChild);
    }
}
void AVL_Tree::In_Order_Printing_for_Menu(AVL_Node* current) { //print producer/studio/licensor/genre without anime info (general listing)
    if (current != NULL) {
        In_Order_Printing_for_Menu(current->LeftChild);
        cout << print_count++ << " : " << "\nName:: ";
        current->PrintAVLName();
        cout << endl << endl;
        In_Order_Printing_for_Menu(current->RightChild);
    }
}
void AVL_Tree::Post_Order_Printing(AVL_Node* current)
{
    if (current != NULL) {
        Post_Order_Printing(current->LeftChild);
        Post_Order_Printing(current->RightChild);
        //cout << current->Name << " ";
        cout << "\nName:: ";
        current->PrintAVLName();
        cout << "\tAnime List :: \n";
        current->PrintAnimeList(); //print anime's that belong to the producer/studio/licensor/genre
    }
}
void AVL_Node::PrintAVLName(void) { //must be producer/studio/licensor/genre
    cout << Name << endl;
}
void AVL_Node::PrintAnimeList(void) {
    Anime_List.Print_Names_At_Anime_Nodes(); //called to print anime's belonging to that particular avl type node
}
//List functions///for lists containing pointers to Anime nodes
bool Singly_Linked_List_Of_Anime_Pointers::isEmpty() {
    return first == NULL;
}
void Singly_Linked_List_Of_Anime_Pointers::InsertAtFront(AnimeNode*Value) {
    ListNode_AnimePointer* newnode = new ListNode_AnimePointer();		//make new node
    newnode->Pointer = Value;		//initialize value of node
    if (Singly_Linked_List_Of_Anime_Pointers::isEmpty()) {		//if list is empty, start and last will point to the same node
        first = newnode;
        last = newnode;
    }
    else {		//if list is non-empty the previous head node will go after the first node and its head node status will be shifted to the new node
        newnode->next = first;
        first = newnode;
    }
}
void Singly_Linked_List_Of_Anime_Pointers::Search(AnimeNode* value) {
    // Initialize loc & ploc
    Lock = first;
    Plock = NULL;
    //Search value until either 1) we reach the end of the list or 2) logical position of the value is passed.
    while (Lock != NULL && Lock->Pointer < value) {
        Plock = Lock;
        Lock = Lock->next;
    }
    if (Lock != NULL && Lock->Pointer != value) {
        Lock = NULL;	//as value is not found so set Loc_ equal to null.
        cout << "Value not found." << endl;
    }
}
void Singly_Linked_List_Of_Anime_Pointers::Print_Names_At_Anime_Nodes() { //locate anime's through pointers and print them
        if (first != NULL) {
            Plock = first;
            for (size_t i = 0; Plock != NULL;i++) {
                cout <<"\t" << i + 1 << " : ";
                Plock->Pointer->PrintAnimeName();
                cout << endl;
                Plock = Plock->next;
            }
        }
        else
        {
            cout << "No values to print!" << endl;
        }
    }
    
/////////////////////////////////////////////////////////////////////////////////////////
//List functions//for lists containing pointers to AVL_Tree nodes//
    bool Singly_Linked_List_Of_AVL_Node_Pointers::isEmpty() {
        return first == NULL;
    }
    void Singly_Linked_List_Of_AVL_Node_Pointers::InsertAtFront(AVL_Node* Value) {
        ListNode_AVLPointer* newnode = new ListNode_AVLPointer();		//make new node
        newnode->AVL_Pointer = Value;		//initialize value of node
        if (isEmpty()) {		//if list is empty, start and last will point to the same node
            first = newnode;
            last = newnode;
        }
        else {		//if list is non-empty the previous head node will go after the first node and its head node status will be shifted to the new node
            newnode->next = first;
            first = newnode;
        }
    }
    void Singly_Linked_List_Of_AVL_Node_Pointers::Search(AVL_Node* value) {
        // Initialize loc & ploc
        Lock = first;
        Plock = NULL;
        //Search value until either 1) we reach the end of the list or 2) logical position of the value is passed.
        while (Lock != NULL && Lock->AVL_Pointer < value) {
            Plock = Lock;
            Lock = Lock->next;
        }
        if (Lock != NULL && Lock->AVL_Pointer != value) {
            Lock = NULL;	//as value is not found so set Loc_ equal to null.
            cout << "Value not found." << endl;
        }
    }
    void Singly_Linked_List_Of_AVL_Node_Pointers::Print_Values_In_Node_Addresses(void) {
        if (!isEmpty()) {
            ListNode_AVLPointer* temp = new ListNode_AVLPointer();
            temp = first;
            while (temp != NULL) {
                temp->AVL_Pointer->PrintAVLName();
                temp = temp->next;
            }
        }
        else
        {
            cout << "No values to print!" << endl;
        }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TREES CONTAINING LISTS OF ANIME POINTERS////////////////// FOR SORTING///////////////////////////////////////////////////////////////
    void Tree_AnimePointerLists::Insert_Value_Without_Duplication(unsigned int value,AnimeNode * AnimeNodePointer) {
        switch_Search(value);//used to recognize which type of data is being accessed//
        if (Lock == NULL) {
            Node_AnimePointersLists* New_Node = new Node_AnimePointersLists();
            New_Node->value = value;
            New_Node->List.InsertAtFront(AnimeNodePointer);
            if (PLock != NULL) {
                if (value < PLock->value)
                    PLock->LeftChild = New_Node;
                else
                    PLock->RightChild = New_Node;
            }
            else
                Root = New_Node;
            Update_Heights(Root, New_Node);//after insertion height is updated
            Correct_Tree_Balance(Root, New_Node);//after heights are updated, the tree balance is checked and corrected
        }
        else {
            Lock->List.InsertAtFront(AnimeNodePointer);
        }
    }
    int Tree_AnimePointerLists::Height_Of_Node(Node_AnimePointersLists* Node) {
        if (Node == NULL)
            return -1;
        else
            return 1 + fmax(Height_Of_Node(Node->LeftChild), Height_Of_Node(Node->RightChild));
    }
    int Tree_AnimePointerLists::Balance_Factor_At_Node(Node_AnimePointersLists* Node) {
        int Height_LeftTree = 0;
        if (Node->LeftChild != NULL)
            Height_LeftTree = 1 + Node->LeftChild->height;
        int Height_RightTree = 0;
        if (Node->RightChild != NULL)
            Height_RightTree = 1 + Node->RightChild->height;
        return Height_LeftTree - Height_RightTree;
    }
    void Tree_AnimePointerLists::Left_Rotation(Node_AnimePointersLists* X, Node_AnimePointersLists* Parent_X, int Balance_Factor) {
        Node_AnimePointersLists* Y = X->RightChild;//left rotation hence y is taken to be right child
        int Balance = Balance_Factor_At_Node(Y);//balance factor of right child
        if (Balance == -2) {//skipping rotation on nodes if the next nodes are also imbalaced by a factor of
            Left_Rotation(Y, X, Balance);
            goto skip;
        }
        else if (Balance == +2) {
            Right_Rotation(Y, X, Balance);
            goto skip;
        }
        else if (Balance == 1 && Balance_Factor == -2)//if orignal balance factor is -2
            Right_Rotation(Y, X, Balance);//leads to right-left rotation//
        //left rotation
        Y = X->RightChild;
        X->RightChild = Y->LeftChild;
        Y->LeftChild = X;
        if (X != Root) {//if x is not root we update the parent node
            if (Parent_X->RightChild == X)
                Parent_X->RightChild = Y;
            else
                Parent_X->LeftChild = Y;
        }
        else//else y is the new root
            Root = Y;
        Update_Heights(Y, X);
    skip:
        cout << "";
    }
    void Tree_AnimePointerLists::Right_Rotation(Node_AnimePointersLists* X, Node_AnimePointersLists* Parent_X, int Balance_Factor) {
        Node_AnimePointersLists* Y = X->LeftChild;//left rotation hence y is taken to be right child
        int Balance = Balance_Factor_At_Node(Y);//balance factor of leftchild
        if (Balance == -2) {
            Left_Rotation(Y, X, Balance);
            goto skip;
        }
        else if (Balance == +2) {
            Right_Rotation(Y, X, Balance);
            goto skip;
        }
        else if ((Balance == -1) && Balance_Factor == 2) //if orignal balance factor is +2
            Left_Rotation(Y, X, Balance);//leads to left-right rotation//
        //right rotation

        Y = X->LeftChild;
        X->LeftChild = Y->RightChild;
        Y->RightChild = X;

        if (X != Root) {//if x is not root we update the parent node
            if (Parent_X->RightChild == X)
                Parent_X->RightChild = Y;
            else
                Parent_X->LeftChild = Y;
        }
        else
            Root = Y;
        Update_Heights(Y, X);//heights are update after rotation.
    skip:
        cout << "";
    }
Node_AnimePointersLists* Tree_AnimePointerLists::Continue_Traversal(Node_AnimePointersLists* Prior_Node, Node_AnimePointersLists* Node) { //traversing in respective tree
        switch (type_data) {
        case Episodes:
            if (Prior_Node->List.first->Pointer->data.Episodes > Node->List.first->Pointer->data.Episodes)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case Rank:
            if (Prior_Node->List.first->Pointer->data.Rank > Node->List.first->Pointer->data.Rank)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case Popularity:
            if (Prior_Node->List.first->Pointer->data.Popularity > Node->List.first->Pointer->data.Popularity)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case Members:
            if (Prior_Node->List.first->Pointer->data.Members > Node->List.first->Pointer->data.Members)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case Favourites:
            if (Prior_Node->List.first->Pointer->data.Favourites > Node->List.first->Pointer->data.Favourites)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case Watching:
            if (Prior_Node->List.first->Pointer->data.Watching > Node->List.first->Pointer->data.Watching)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case Completed:
            if (Prior_Node->List.first->Pointer->data.Completed > Node->List.first->Pointer->data.Completed)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case OnHold:
            if (Prior_Node->List.first->Pointer->data.OnHold > Node->List.first->Pointer->data.OnHold)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case Dropped:
            if (Prior_Node->List.first->Pointer->data.Dropped > Node->List.first->Pointer->data.Dropped)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case PlanToWatch:
            if (Prior_Node->List.first->Pointer->data.PlanToWatch > Node->List.first->Pointer->data.PlanToWatch)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        case AVGscore:
            if (Prior_Node->List.first->Pointer->data.AVGscore > Node->List.first->Pointer->data.AVGscore)
                Prior_Node = Prior_Node->LeftChild;
            else
                Prior_Node = Prior_Node->RightChild; break;
        }
        return Prior_Node;
    }
void Tree_AnimePointerLists::Correct_Tree_Balance(Node_AnimePointersLists* Prior_Node, Node_AnimePointersLists* Node) {
        int Balance_Factor = 0;
        Node_AnimePointersLists* temp = NULL;
        while (Prior_Node != Node) {//traversing and checking if balance has been disrupted
            Balance_Factor = Balance_Factor_At_Node(Prior_Node);
            if (Balance_Factor == 2) {//right rotation called in case of +2 balance factor
                Right_Rotation(Prior_Node, temp, Balance_Factor);
                break;
            }
            else if (Balance_Factor == -2) {//left rotaiton called in case of -2 balance factor
                Left_Rotation(Prior_Node, temp, Balance_Factor);
                break;
            }
            else {//if balance factor is -1,+1 or 0 then traversal continues
                temp = Prior_Node;
                Prior_Node=Continue_Traversal(Prior_Node,Node);

            }

        }

    }
    void Tree_AnimePointerLists::Update_Heights(Node_AnimePointersLists* Pre_X, Node_AnimePointersLists* X) {

        while (1) {//traversal from prenode to node X
            Pre_X->height = Height_Of_Node(Pre_X);//each nodes height is updated
            if (Pre_X == X)
                break;
            else {//traversal continues until final node reached
                Pre_X = Continue_Traversal(Pre_X,X);
            }
        }
    }
    void Tree_AnimePointerLists::switch_Search(unsigned int Val) { //search for anime pointers based on statistics and statistics type
        PLock = NULL;
        Lock = Root;
        switch (type_data) {
        case Episodes:
            while (Lock != NULL) {
            if (Lock->List.first->Pointer->data.Episodes == Val)
                return;
            else if (Lock->List.first->Pointer->data.Episodes > Val) {
                PLock = Lock;
                Lock = Lock->LeftChild;
            }
            else if (Lock->List.first->Pointer->data.Episodes < Val) {
                PLock = Lock;
                Lock = Lock->RightChild;
            }
            }
            break;
        case Rank:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.Rank == Val)
                    return;
                else if (Lock->List.first->Pointer->data.Rank > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.Rank < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        case Popularity:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.Popularity == Val)
                    return;
                else if (Lock->List.first->Pointer->data.Popularity > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.Popularity < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        case Members:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.Members == Val)
                    return;
                else if (Lock->List.first->Pointer->data.Members > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.Members < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        case Favourites:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.Favourites == Val)
                    return;
                else if (Lock->List.first->Pointer->data.Favourites > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.Favourites < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        case Watching:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.Watching == Val)
                    return;
                else if (Lock->List.first->Pointer->data.Watching > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.Watching < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        case Completed:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.Completed == Val)
                    return;
                else if (Lock->List.first->Pointer->data.Completed > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.Completed < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        case OnHold:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.OnHold == Val)
                    return;
                else if (Lock->List.first->Pointer->data.OnHold > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.OnHold < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        case Dropped:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.Dropped == Val)
                    return;
                else if (Lock->List.first->Pointer->data.Dropped > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.Dropped < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        case PlanToWatch:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.PlanToWatch == Val)
                    return;
                else if (Lock->List.first->Pointer->data.PlanToWatch > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.PlanToWatch < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        case AVGscore:
            while (Lock != NULL) {
                if (Lock->List.first->Pointer->data.AVGscore == Val)
                    return;
                else if (Lock->List.first->Pointer->data.AVGscore > Val) {
                    PLock = Lock;
                    Lock = Lock->LeftChild;
                }
                else if (Lock->List.first->Pointer->data.AVGscore < Val) {
                    PLock = Lock;
                    Lock = Lock->RightChild;
                }
            }break;
        }
    }
    string Tree_AnimePointerLists::string_type_data(short unsigned int type_data) { //printing statistics name
        switch (type_data) {
        case 1:return "Episodes";
            break;
        case 2:return "Rank"; break;
        case 3:return "Popularity"; break;
        case 4:return "Members"; break;
        case 5:return "Favourites"; break;
        case 6:return "Watching"; break;
        case 7:return "Completed"; break;
        case 8:return "OnHold"; break;
        case 9:return "Dropped"; break;
        case 10:return "PlanToWatch"; break;
        case 11:return "AVGscore"; break;
        }
    }
    void Tree_AnimePointerLists::Pre_Order_Printing(Node_AnimePointersLists* current) {
        if (current != NULL) {
            cout <<"Anime's with " << string_type_data(type_data)<<"=" << current->value<<" are ::";
            current->List.Print_Names_At_Anime_Nodes();
            Pre_Order_Printing(current->LeftChild);
            Pre_Order_Printing(current->RightChild);
        }
    }
    void Tree_AnimePointerLists::In_Order_Printing(Node_AnimePointersLists* current) {
        if (current != NULL) {
            In_Order_Printing(current->LeftChild);
            cout << "Anime's with " << string_type_data(type_data) << "=" << current->value << " are ::\n";
            current->List.Print_Names_At_Anime_Nodes();
            cout << endl;
            In_Order_Printing(current->RightChild);
        }
    }
    void Tree_AnimePointerLists::Post_Order_Printing(Node_AnimePointersLists* current)
    {
        if (current != NULL) {
            Post_Order_Printing(current->LeftChild);
            Post_Order_Printing(current->RightChild);
            cout << "Anime's with " << string_type_data(type_data) << "=" << current->value << " are ::";
            current->List.Print_Names_At_Anime_Nodes();
        }
    }
    /*
    void AnimeTree::Delete_Value(int value) {
    Search_Value(value);
    if (Lock == NULL)
        cout << "Value not found, deletion not possible.\n";
    else {
        cout << "\x1b[31mDeleting :: " << Lock->data.ID << "\x1b[37m" << endl;
        //deleting leafnode
        if (Lock->RightChild == NULL && Lock->LeftChild == NULL) {
            if (PLock == NULL)
                Root = NULL;
            else if (PLock->LeftChild == Lock)
                PLock->LeftChild = NULL;
            else
                PLock->RightChild = NULL;
        }
        //deleting a node with left child
        else if (Lock->LeftChild != NULL && Lock->RightChild == NULL) {
            if (PLock == NULL)
                Root = Lock->LeftChild;
            else if (PLock->LeftChild == Lock)
                PLock->LeftChild = Lock->LeftChild;
            else
                PLock->RightChild = Lock->LeftChild;
        }
        //deleting a node with right child only
        else if (Lock->LeftChild == NULL && Lock->RightChild != NULL) {
            if (PLock == NULL)
                Root = Lock->RightChild;
            else if (PLock->LeftChild == Lock)
                PLock->LeftChild = Lock->RightChild;
            else
                PLock->RightChild = Lock->RightChild;
        }
        //deleting a node with two children
        else {//replacing from left subtree
            AnimeNode* Pre_Replacement = Lock;
            AnimeNode* Replacement = Lock->LeftChild;
            while (Replacement->RightChild != NULL) {//finding largest node in left subtree
                Pre_Replacement = Replacement;
                Replacement = Replacement->RightChild;
            }
            //updating area of replacement node
            if (Pre_Replacement != Lock) {
                if (Replacement->LeftChild != NULL) //in case replacement node has a left subtree
                    Pre_Replacement->RightChild = Replacement->LeftChild;
                else//in case the replacement node is a leaf
                    Pre_Replacement->RightChild = NULL;
            }
            else
                Pre_Replacement->LeftChild = Replacement->LeftChild;
            //updating area of node to be deleted(lock) and replacing it with replacement node
            if (PLock != NULL) {
                if (PLock->RightChild == Lock)//when node to be deleted is right child
                    PLock->RightChild = Replacement;
                else//when node to be deleted is left child
                    PLock->LeftChild = Replacement;
            }
            else
                Root = Replacement;
            //updating right and left of node replaced
            Replacement->RightChild = Lock->RightChild;
            Replacement->LeftChild = Lock->LeftChild;
            PLock = Pre_Replacement;
        }
    }
    delete Lock;
    Update_Heights(Root, PLock);//updating heights of effected branches
    Correct_Tree_Balance(Root, PLock->LeftChild);//correcting balance
}

    void AnimeTree::Destroy_Tree(AnimeNode* Node) {
    if (Node != NULL) {
        Destroy_Tree(Node->LeftChild);
        Destroy_Tree(Node->RightChild);
        delete Node;
    }
    Root = NULL;
}

    void AnimeTree::Print(void) {
    if (Root != NULL) {
        cout << "\n->Pre-Order Printing::\x1b[32m\t";
        Pre_Order_Printing(Root);
        cout << "\n->In-Order Printing::\x1b[32m\t";
        In_Order_Printing(Root);
        cout << "\n->Post-Order Printing::\x1b[32m\t";
        Post_Order_Printing(Root);
        cout << endl;
    }
    else
        cout << "Three tree is empty." << endl;
}

    void AVL_Tree::Delete_Value(string value) {
    Search_Value(value);
    if (Lock == NULL)
        cout << "Value not found, deletion not possible.\n";
    else {
        cout << "\x1b[31mDeleting :: " << Lock->Name << "\x1b[37m" << endl;
        //deleting leafnode
        if (Lock->RightChild == NULL && Lock->LeftChild == NULL) {
            if (PLock == NULL)
                Root = NULL;
            else if (PLock->LeftChild == Lock)
                PLock->LeftChild = NULL;
            else
                PLock->RightChild = NULL;
        }
        //deleting a node with left child
        else if (Lock->LeftChild != NULL && Lock->RightChild == NULL) {
            if (PLock == NULL)
                Root = Lock->LeftChild;
            else if (PLock->LeftChild == Lock)
                PLock->LeftChild = Lock->LeftChild;
            else
                PLock->RightChild = Lock->LeftChild;
        }
        //deleting a node with right child only
        else if (Lock->LeftChild == NULL && Lock->RightChild != NULL) {
            if (PLock == NULL)
                Root = Lock->RightChild;
            else if (PLock->LeftChild == Lock)
                PLock->LeftChild = Lock->RightChild;
            else
                PLock->RightChild = Lock->RightChild;
        }
        //deleting a node with two children
        else {//replacing from left subtree
            AVL_Node* Pre_Replacement = Lock;
            AVL_Node* Replacement = Lock->LeftChild;
            while (Replacement->RightChild != NULL) {//finding largest node in left subtree
                Pre_Replacement = Replacement;
                Replacement = Replacement->RightChild;
            }
            //updating area of replacement node
            if (Pre_Replacement != Lock) {
                if (Replacement->LeftChild != NULL) //in case replacement node has a left subtree
                    Pre_Replacement->RightChild = Replacement->LeftChild;
                else//in case the replacement node is a leaf
                    Pre_Replacement->RightChild = NULL;
            }
            else
                Pre_Replacement->LeftChild = Replacement->LeftChild;
            //updating area of node to be deleted(lock) and replacing it with replacement node
            if (PLock != NULL) {
                if (PLock->RightChild == Lock)//when node to be deleted is right child
                    PLock->RightChild = Replacement;
                else//when node to be deleted is left child
                    PLock->LeftChild = Replacement;
            }
            else
                Root = Replacement;
            //updating right and left of node replaced
            Replacement->RightChild = Lock->RightChild;
            Replacement->LeftChild = Lock->LeftChild;
            PLock = Pre_Replacement;
        }
    }
    delete Lock;
    Update_Heights(Root, PLock);//updating heights of effected branches
    Correct_Tree_Balance(Root, PLock->LeftChild);//correcting balance
}
    void AVL_Tree::Print(void) {
    cout << "PRINTING AVL TREE" << endl;
    if (Root != NULL) {
        cout << "\n->Pre-Order Printing::\x1b[32m\t" << endl;;
        Pre_Order_Printing(Root);
        cout << "\n->In-Order Printing::\x1b[32m\t" << endl;;
        In_Order_Printing(Root);
        cout << "\n->Post-Order Printing::\x1b[32m\t" << endl;;
        Post_Order_Printing(Root);
        cout << endl;
    }
    else
        cout << "Three tree is empty." << endl;
}

    void AVL_Tree::Destroy_Tree(AVL_Node* Node) {
    if (Node != NULL) {
        Destroy_Tree(Node->LeftChild);
        Destroy_Tree(Node->RightChild);
        delete Node;
    }
    Root = NULL;
}


    void Singly_Linked_List_Of_Anime_Pointers::InsertAtEnd(AnimeNode* value) {
    ListNode_AnimePointer* newnode = new ListNode_AnimePointer();	//make new node
    newnode->Pointer = value;	//initialize value of node
    if (Singly_Linked_List_Of_Anime_Pointers::isEmpty()) {		//if list is empty, start and last will point to the same node
        first = newnode;
        last = newnode;
    }
    else {		//if list is non-empty the new node will go after the last one and the its last node status will be shifted to the new node
        last->next = newnode;
        last = newnode;
    }
}
    void Singly_Linked_List_Of_Anime_Pointers::InsertSorted(AnimeNode* X) {
    Singly_Linked_List_Of_Anime_Pointers::Search(X); //search for value first
    if (Lock != NULL) { //check using loc
        //cout << "Value already exists." << endl;
        return;
    }
    else {
        if (isEmpty() || Plock == NULL) {		//if list is empty or logical pos. is at the head node
            Singly_Linked_List_Of_Anime_Pointers::InsertAtFront(X);
        }
        else if (Plock != NULL && Plock == last) {		//if position of value is at the last node
            Singly_Linked_List_Of_Anime_Pointers::InsertAtEnd(X);
        }
        else { //Insert newnode after PredLoc_
            ListNode_AnimePointer* newnode = new ListNode_AnimePointer();	//make new node
            newnode->Pointer = X;	//initialize value of node
            newnode->next = Plock->next;
            Plock->next = newnode;
            //cout << "Value inserted in a sorted manner." << endl;
        }

    }
}			//end deletelast

    void Singly_Linked_List_Of_Anime_Pointers::DeleteFront() {	//delete head node value
        if (!isEmpty()) {
            ListNode_AnimePointer* temp = first;
            if (first != last)
            {
                first = first->next;
            }
            else {
                first = NULL;
                last = NULL;
            }
            delete temp;
            cout << "Value at the start deleted." << endl;
        }
        else {
            cout << "List is empty." << endl;
        }
    }		//end deletefront

    void Singly_Linked_List_Of_Anime_Pointers::DeleteLast() {		//delete last node
        if (!Singly_Linked_List_Of_Anime_Pointers::isEmpty()) {
            ListNode_AnimePointer* temp = last;
            if (first != last)
            {
                last->next = NULL;
            }
            else {
                first = NULL;
                last = NULL;
            }
            delete temp;
            cout << "Value at the end deleted." << endl;
        }
        else {
            cout << "List is empty." << endl;
        }
    }
    *     void Singly_Linked_List_Of_Anime_Pointers::Delete(AnimeNode* X) {
        if (!Singly_Linked_List_Of_Anime_Pointers::isEmpty()) {
            //if list empty then return
            Singly_Linked_List_Of_Anime_Pointers::Search(X);
            if (Lock != NULL) { //check loc
                if (Plock == NULL) {//check ploc
                    Singly_Linked_List_Of_Anime_Pointers::DeleteFront();
                    //delete head node and free memory
                }
                else if (Lock == last && Plock != NULL) {
                    Singly_Linked_List_Of_Anime_Pointers::DeleteLast();
                    //delete last node and free memory
                }
                else {
                    //update link using ploc
                    Plock->next = Plock->next;
                    //finally free memory using delete command.
                    delete Lock;
                    cout << "Value has been deleted." << endl;
                }
            }
            else {
                cout << "Value not found." << endl;
            }
        }
        else {
            cout << "List is empty." << endl;
        }
    } 
    * void Singly_Linked_List_Of_Anime_Pointers::Destroy_List() {
        if (!isEmpty()) {
            ListNode_AnimePointer* temp = NULL;
            while (first != NULL) {
                temp = first;
                first = first->next;
                delete temp;
            }
        }
    }

    *  void Singly_Linked_List_Of_AVL_Node_Pointers::InsertAtEnd(AVL_Node* value) {
        ListNode_AVLPointer* newnode = new ListNode_AVLPointer();	//make new node
        newnode->AVL_Pointer = value;	//initialize value of node
        if (isEmpty()) {		//if list is empty, start and last will point to the same node
            first = newnode;
            last = newnode;
        }
        else {		//if list is non-empty the new node will go after the last one and the its last node status will be shifted to the new node
            last->next = newnode;
            last = newnode;
        }
    }
    void Singly_Linked_List_Of_AVL_Node_Pointers::InsertSorted(AVL_Node* X) {
        Search(X); //search for value first
        if (Lock != NULL) { //check using loc
            //cout << "Value already exists." << endl;
            return;
        }
        else {
            if (isEmpty() || Plock == NULL) {		//if list is empty or logical pos. is at the head node
               InsertAtFront(X);
            }
            else if (Plock != NULL && Plock == last) {		//if position of value is at the last node
                InsertAtEnd(X);
            }
            else { //Insert newnode after PredLoc_
                ListNode_AVLPointer* newnode = new ListNode_AVLPointer();	//make new node
                newnode->AVL_Pointer = X;	//initialize value of node
                newnode->next = Plock->next;
                Plock->next = newnode;
               // cout << "Value inserted in a sorted manner." << endl;
            }
        }
    }
        void Singly_Linked_List_Of_AVL_Node_Pointers::DeleteFront() {	//delete head node value
        if (!isEmpty()) {
            ListNode_AVLPointer* temp = first;
            if (first != last)
            {
                first = first->next;
            }
            else {
                first = NULL;
                last = NULL;
            }
            delete temp;
            //cout << "Value at the start deleted." << endl;
        }
        else {
           // cout << "List is empty." << endl;
        }
    }		//end deletefront

        void Singly_Linked_List_Of_AVL_Node_Pointers::DeleteLast() {		//delete last node
        if (!isEmpty()) {
            ListNode_AVLPointer* temp = last;
            if (first != last)
            {
                last->next = NULL;
            }
            else {
                first = NULL;
                last = NULL;
            }
            delete temp;
          //  cout << "Value at the end deleted." << endl;
        }
        else {
            //cout << "List is empty." << endl;
        }
    }			//end deletelast

    void Singly_Linked_List_Of_AVL_Node_Pointers::Delete(AVL_Node* X) {
        if (!isEmpty()) {
            //if list empty then return
            Search(X);
            if (Lock != NULL) { //check loc
                if (Plock == NULL) {//check ploc
                   DeleteFront();
                    //delete head node and free memory
                }
                else if (Lock == last && Plock != NULL) {
                    DeleteLast();
                    //delete last node and free memory
                }
                else {
                    //update link using ploc
                    Plock->next = Plock->next;
                    //finally free memory using delete command.
                    delete Lock;
                    //cout << "Value has been deleted." << endl;
                }
            }
            else {
               // cout << "Value not found." << endl;
            }
        }
        else {
            //cout << "List is empty." << endl;
        }
    } //end deleting function
     void Singly_Linked_List_Of_AVL_Node_Pointers::Destroy_List()
    {
        if (!isEmpty()) {
            ListNode_AVLPointer*temp = NULL;
            while (first != NULL) {
                temp = first;
                first = first->next;
                delete temp;
            }
        }
    }
    void Tree_AnimePointerLists::Destroy_Tree(Node_AnimePointersLists* Node) {
        if (Node != NULL) {
            Destroy_Tree(Node->LeftChild);
            Destroy_Tree(Node->RightChild);
            delete Node;
        }
        Root = NULL;
    }
    void Tree_AnimePointerLists::Print(void) {
        if (Root != NULL) {
            cout << "\n->Pre-Order Printing::\x1b[32m\t";
            Pre_Order_Printing(Root);
            cout << "\n->In-Order Printing::\x1b[32m\t";
            In_Order_Printing(Root);
            cout << "\n->Post-Order Printing::\x1b[32m\t";
            Post_Order_Printing(Root);
            cout << endl;
        }
        else
            cout << "Three tree is empty." << endl;
    }
    */

