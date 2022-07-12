#include<iostream>
#include<fstream>
#include<string>
#include "Anime.h"
using namespace std;

enum Type { //storing type of anime with enum
	TV = 0, Movie, OVA, Special, ONA, Music, Unknown
};

string x;
int level = 0; unsigned int index_of_level = 0; unsigned int index_zero = -0;
unsigned int ID = 1048571;
bool check = true;
unsigned int get_Id(); 
int main() {
	//Tree objects with data//
	AnimeTree AnimeTree1;
	AVL_Tree Producer_Tree, Liscensor_Tree, Studio_Tree, Genre_Tree;
	// Tree objects with pointer lists//
	//type_data for input recognition
	Tree_AnimePointerLists* Episodes = new Tree_AnimePointerLists(); Episodes->type_data = 1;
	Tree_AnimePointerLists* Rank = new Tree_AnimePointerLists(); Rank->type_data = 2;
	Tree_AnimePointerLists* Popularity = new Tree_AnimePointerLists(); Popularity->type_data = 3;
	Tree_AnimePointerLists* Members = new Tree_AnimePointerLists(); Members->type_data = 4;
	Tree_AnimePointerLists* Favourites = new Tree_AnimePointerLists(); Favourites->type_data = 5;
	Tree_AnimePointerLists* Watching = new Tree_AnimePointerLists(); Watching->type_data = 6;
	Tree_AnimePointerLists* Completed = new Tree_AnimePointerLists(); Completed->type_data = 7;
	Tree_AnimePointerLists* OnHold = new Tree_AnimePointerLists(); OnHold->type_data = 8;
	Tree_AnimePointerLists* Dropped = new Tree_AnimePointerLists(); Dropped->type_data = 9;
	Tree_AnimePointerLists* PlanToWatch = new Tree_AnimePointerLists(); PlanToWatch->type_data = 10;
	Tree_AnimePointerLists* AVGscore = new Tree_AnimePointerLists(); AVGscore->type_data = 11;
	//temp variables//
	AVL_Node* AVL_Node_Pointer = NULL; string substring;  int eof = 0;
	ifstream f;
	//parsing file and inserting values in temp object//
	f.open("anime1.csv");
	if (f.is_open()) {
		if (f.good()) //if file is error free
			//while (!f.eof()) {
			//while (!f.eof()) {//read till end of file
				for (int i = 0; i < 20; i++) { //read for certain rows
				Anime A1;
				if (eof == 48492)
				{
					cout << "End of file reached" << endl;
					break;
				}
				if (f.good())
				{
					getline(f, x, '=');
					getline(f, x, ',');
					//A1.ID = stoi(x);
					eof = stoi(x);
					A1.ID = get_Id();
					cout << A1.ID << endl;
					getline(f, x, ',');
					A1.Name = x;
					cout << "\nname:" << A1.Name << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.Score = -1.0;
					else
						A1.Score = stof(x);
					cout << "\nscore" << A1.Score << endl;
					getline(f, x, ',');
					cout << "GENRE" << endl;
					if (x[0] == '"') {//many genres:: since they are in appostrophes reading them is a bit complicated
						x = x.substr(1);
						//inserting genre in tree
						AVL_Node_Pointer = Genre_Tree.Insert_Value_Without_Duplication(x);//tree node inserted and pointer to node returned
						//inserting node address of genre in anime node lists.
						A1.GenresList.InsertAtFront(AVL_Node_Pointer);//list in anime class object updated
						cout << x << endl; //
						getline(f, x, '"');
						unsigned short int countcommas = 0;
						for (size_t i = 0; x[i] != '\0'; i++) {
							if (x[i] == ',')
								countcommas++;
						}
						int pos = 0, y = 0;
						for (size_t i = 0; i <= countcommas; i++) {
							pos = x.find(',');
							substring = x.substr(y, pos);
							AVL_Node_Pointer = Genre_Tree.Insert_Value_Without_Duplication(substring);
							A1.GenresList.InsertAtFront(AVL_Node_Pointer);
							cout << x.substr(y, pos) << endl;
							//insert
							x = x.substr(pos + 1);
						}
						getline(f, x, ',');
					}
					else
					{
						//insert x into genre list
						cout << x;
						AVL_Node_Pointer = Genre_Tree.Insert_Value_Without_Duplication(x);
						A1.GenresList.InsertAtFront(AVL_Node_Pointer);
					}
					//using enum
					getline(f, x, ',');
					if (x == "TV")
						A1.Type = TV;
					else if (x == "Movie")
						A1.Type = Movie;
					else if (x == "OVA")
						A1.Type = OVA;
					else if (x == "Special")
						A1.Type = Special;
					else if (x == "ONA")
						A1.Type = ONA;
					else if (x == "Music")
						A1.Type = Music;
					else
						A1.Type = Unknown;
					cout << "\n." << A1.Type;
					getline(f, x, ',');
					if (x == "Unknown")//random value stored when unknown is encountered
						A1.Episodes = 9999;
					else
						A1.Episodes = stoi(x);
					cout << "\n." << A1.Episodes;
					getline(f, x, ',');
					A1.PrimierDate = x;
					cout << "\n." << A1.PrimierDate;
					//producers//
					//when we get producer data we may need to insert node/update list in data of anime and producer both//
					getline(f, x, ',');
					if (x[0] == '"') {//many producers:: since they are in appostrophes reading them is a bit complicated
						x = x.substr(1);
						//x = " " + x;
						cout << x << endl;
						AVL_Node_Pointer = Producer_Tree.Insert_Value_Without_Duplication(x);
						A1.ProducersList.InsertAtFront(AVL_Node_Pointer);
						//insert x
						getline(f, x, '"');
						unsigned short int countcommas = 0;
						for (size_t i = 0; x[i] != '\0'; i++) {
							if (x[i] == ',')
								countcommas++;
						}
						int pos = 0, y = 0;
						for (size_t i = 0; i <= countcommas; i++) {
							pos = x.find(',');
							substring = x.substr(y, pos);
							x.substr(y, pos);
							cout << x.substr(y, pos) << endl;
							x = x.substr(pos + 1);
							AVL_Node_Pointer = Producer_Tree.Insert_Value_Without_Duplication(substring);
							A1.ProducersList.InsertAtFront(AVL_Node_Pointer);
						}
						getline(f, x, ',');
					}
					else
					{
						//insert x into producer list
						cout << x;
						AVL_Node_Pointer = Producer_Tree.Insert_Value_Without_Duplication(x);
						A1.ProducersList.InsertAtFront(AVL_Node_Pointer);
					}
					//Liscensors//
					//when we get liscensor data we may need to insert node/update list in data of anime and liscensor both//
					getline(f, x, ',');
					if (x[0] == '"') {//many liscensors:: since they are in appostrophes reading them is a bit complicated
						x = x.substr(1);
						//x = " " + x;
						cout << x << endl;
						AVL_Node_Pointer = Liscensor_Tree.Insert_Value_Without_Duplication(x);
						A1.LiscensorsList.InsertAtFront(AVL_Node_Pointer);
						//insert x
						getline(f, x, '"');
						unsigned short int countcommas = 0;
						for (size_t i = 0; x[i] != '\0'; i++) {
							if (x[i] == ',')
								countcommas++;
						}
						int pos = 0, y = 0;
						for (size_t i = 0; i <= countcommas; i++) {
							pos = x.find(',');
							x.substr(y, pos);
							substring = x.substr(y, pos);
							cout << x.substr(y, pos) << endl;
							x = x.substr(pos + 1);
							AVL_Node_Pointer = Liscensor_Tree.Insert_Value_Without_Duplication(substring);
							A1.LiscensorsList.InsertAtFront(AVL_Node_Pointer);
						}
						getline(f, x, ',');
					}
					else
					{
						//insert x into producer list
						AVL_Node_Pointer = Liscensor_Tree.Insert_Value_Without_Duplication(x);
						A1.LiscensorsList.InsertAtFront(AVL_Node_Pointer);
						cout << x;
					}
					//Studios//
					//when we get studio data we may need to insert node/update list in data od anime and Studios both//
					getline(f, x, ',');
					if (x[0] == '"') {//many Studios:: since they are in appotrophes reading them is a bit complicated
						x = x.substr(1);
						//x = " " + x;
						cout << x << endl;
						AVL_Node_Pointer = Studio_Tree.Insert_Value_Without_Duplication(x);
						A1.StudiosList.InsertAtFront(AVL_Node_Pointer);
						//insert x
						getline(f, x, '"');
						unsigned short int countcommas = 0;
						for (size_t i = 0; x[i] != '\0'; i++) {
							if (x[i] == ',')
								countcommas++;
						}
						int pos = 0, y = 0;
						for (size_t i = 0; i <= countcommas; i++) {
							pos = x.find(',');
							x.substr(y, pos);
							substring = x.substr(y, pos);
							cout << x.substr(y, pos) << endl;
							x = x.substr(pos + 1);
							AVL_Node_Pointer = Studio_Tree.Insert_Value_Without_Duplication(substring);
							A1.StudiosList.InsertAtFront(AVL_Node_Pointer);
						}
						getline(f, x, ',');
					}
					else
					{
						//insert x into producer list
						cout << x;
						AVL_Node_Pointer = Studio_Tree.Insert_Value_Without_Duplication(x);
						A1.StudiosList.InsertAtFront(AVL_Node_Pointer);
					}
					getline(f, x, ',');
					A1.Source = x;
					cout << A1.Source << endl;
					getline(f, x, ',');
					A1.Duration = x;
					cout << A1.Duration << endl;
					getline(f, x, ',');
					A1.Rating = x;
					cout << A1.Rating << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.Rank = 9999;
					else
						A1.Rank = stoi(x);
					cout << A1.Rank << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.Popularity = 9999;
					else
						A1.Popularity = stoi(x);
					cout << A1.Popularity << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.Members = 9999;
					else
						A1.Members = stoi(x);
					cout << A1.Members << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.Favourites = 9999;
					else
						A1.Favourites = stoi(x);
					cout << A1.Favourites << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.Watching = 9999;
					else
						A1.Watching = stoi(x);
					cout << A1.Watching << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.Completed = 9999;
					else
						A1.Completed = stoi(x);
					cout << A1.Completed << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.OnHold = 9999;
					else
						A1.OnHold = stoi(x);
					cout << A1.OnHold << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.Dropped = 9999;
					else
						A1.Dropped = stoi(x);
					cout << A1.Dropped << endl;
					getline(f, x, ',');
					if (x == "Unknown")
						A1.PlanToWatch = 9999;
					else
						A1.PlanToWatch = stoi(x);
					cout << "PLantowatch" << A1.PlanToWatch << endl;
					//reading score and calculating average//
					int sum = 0;
					for (size_t i = 0; i < 10; i++) {
						getline(f, x, ',');
						//cout << x << endl;
						sum += stoi(x);
					}
					A1.AVGscore = sum / 10;
					cout << A1.AVGscore << endl;
					//A1.ProducersList.Print_Values_In_Node_Addresses();
					AnimeTree1.Insert_Value_Without_Duplication(A1, Episodes, Rank, Popularity, Members, Favourites, Watching, Completed, OnHold, Dropped, PlanToWatch, AVGscore);
				}
			}
	}
	string y; //for string input from user


	//////////////////////////MENU START////////////////////////////////
	int userOptionInput = -1; //user input variable
	while (userOptionInput != 0) {
		system("cls");
		cout << "MYANIMELIST DATABASE" << endl << "A DSA Project by" << endl << "Ayesha Tahir, CMS 340499" << endl << "Bisma Ijaz, CMS 351996" << endl << "BSCS-10A" << endl << endl;		//menu 
		cout << "\x1b[31mEXIT\t\t\t\t\t'0'" << endl << "\x1b[33mList all anime's with info\t\t'1'" << endl;
		cout << "List all producers\t\t\t'2'" << endl << "List all genres\t\t\t\t'3'" << endl;
		cout << "List all licensors\t\t\t'4'" << endl << "List all studios\t\t\t'5'" << endl;
		cout << "\x1b[35mInsert new anime\t\t\t'6'" << endl << "\x1b[33mList anime by episode number\t\t'7'" << endl;
		cout << "List anime by rank\t\t\t'8'" << endl << "List anime by popularity\t\t'9'" << endl;
		cout << "List anime by members\t\t\t'10'" << endl << "List anime by favourites\t\t'11'" << endl;
		cout << "List anime by watching\t\t\t'12'" << endl << "List anime by completed\t\t\t'13'" << endl;
		cout << "List anime by onhold\t\t\t'14'" << endl << "List anime by dropped\t\t\t'15'" << endl;
		cout << "List anime by Plan to Watch\t\t'16'" << endl << "List anime by Average Score\t\t'17'" << endl;
		cout << "List all anime's without info\t\t'18'\x1b[36m" << endl << "List anime by producer\t\t\t'19'" << endl;
		cout << "List anime by studio\t\t\t'20'" << endl << "List anime by licensor\t\t\t'21'" << endl;
		cout << "List anime by genre\t\t\t'22'" << endl << "\x1b[36mSearch anime by ID\t\t\t'23'" << endl;
		cout << "Search anime by Episode Number\t\t'24'" << endl << "Search anime by rank\t\t\t'25'" << endl << "Search anime by popularity\t\t'26'" << endl;
		cout << "Search anime by members number\t\t'27'" << endl << "Search anime by favourites number\t'28'" << endl;
		cout << "Search anime by watching number\t\t'29'" << endl << "Search anime by completed number\t'30'" << endl;
		cout << "Search anime by On Hold number\t\t'31'" << endl << "Search anime by dropped number\t\t'32'" << endl;
		cout << "Search anime by Plan to Watch number\t'33'" << endl << "Search anime by Average Score\t\t'34'" << endl << endl;
		cout << "\x1b[37mEnter option: (0-34) " << endl;

		cin >> userOptionInput;		//user input
		system("pause");
		system("cls");

		if (userOptionInput == 1) {	//list all anime's with info 
			cout << "DISPLAYING LIST OF ALL ANIME'S WITH INFO:: " << endl << endl;
			AnimeTree1.In_Order_Printing(AnimeTree1.Root);
		}

		else if (userOptionInput == 2) {		//list all producers
			cout << "DISPLAYING LIST OF ALL PRODUCERS :: " << endl << endl;
			Producer_Tree.In_Order_Printing_for_Menu(Producer_Tree.Root);
			Producer_Tree.print_count = 0;
		}

		else if (userOptionInput == 3) {		//list all genres
			cout << "DISPLAYING LIST OF ALL GENRES :: " << endl << endl;
			Genre_Tree.In_Order_Printing_for_Menu(Genre_Tree.Root);
			Genre_Tree.print_count = 0;
		}

		else if (userOptionInput == 4) {		//list all licensors
			cout << "DISPLAYING LIST OF ALL LICENSORS :: " << endl << endl;
			Liscensor_Tree.In_Order_Printing_for_Menu(Liscensor_Tree.Root);
			Liscensor_Tree.print_count = 0;
		}

		else if (userOptionInput == 5) {		//list all studios
			cout << "DISPLAYING LIST OF ALL STUDIOS :: " << endl << endl;
			Studio_Tree.In_Order_Printing_for_Menu(Studio_Tree.Root);
			Studio_Tree.print_count = 0;
		}

		else if (userOptionInput == 6) {		//insert new anime
			cout << "INSERT NEW ANIME :: " << endl << endl;
			unsigned short int numberOfItems;
			Anime UserAnime;
			UserAnime.ID = get_Id();
			cout << "Your Anime has been assigned ID = " << UserAnime.ID << endl;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //to ignore the "return" at the end of cin
			cout << "Enter name of anime :: ";
			getline(cin, UserAnime.Name);
			cout << endl << "Enter score of anime :: ";
			cin >> UserAnime.Score;
			cout << endl << "Enter type of anime (can be one of the following):" << endl << "TV=0, Movie=1, OVA=2, Special=3, ONA=4, Music=5, Unknown=6" << endl;
			cout << "Enter option (0-6) :: ";
			cin >> UserAnime.Type;
			cout << endl << "Enter episode number of anime :: ";
			cin >> UserAnime.Episodes;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter premier of anime :: ";
			getline(cin, UserAnime.PrimierDate);
			cout << endl << "Enter source of anime :: ";
			getline(cin, UserAnime.Source);
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter duration of anime :: ";
			getline(cin, UserAnime.Duration);
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter rating of anime :: ";
			getline(cin, UserAnime.Rating);
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter rank of anime :: ";
			cin >> UserAnime.Rank;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter popularity of anime :: ";
			cin >> UserAnime.Popularity;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter members of anime :: ";
			cin >> UserAnime.Members;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter number of favourites of anime :: ";
			cin >> UserAnime.Favourites;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter watching number of anime :: ";
			cin >> UserAnime.Watching;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter completed number of anime :: ";
			cin >> UserAnime.Completed;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter On Hold number of anime :: ";
			cin >> UserAnime.OnHold;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter dropped number of anime :: ";
			cin >> UserAnime.Dropped;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter Plan to Watch number of anime :: ";
			cin >> UserAnime.PlanToWatch;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter average user score of anime :: ";
			cin >> UserAnime.AVGscore;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Enter number of Producers :: ";
			cin >> numberOfItems;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (int i = 1; i <= numberOfItems; i++) { //loop for multiple producers
				string producerInput;
				cout << endl << "Enter name of producer # " << i << " :: ";
				getline(cin, producerInput);
				AVL_Node_Pointer = Producer_Tree.Insert_Value_Without_Duplication(producerInput);
				UserAnime.ProducersList.InsertAtFront(AVL_Node_Pointer);
			}
			cout << endl << "Enter number of Licensors :: ";	//loop for multiple licensors
			cin >> numberOfItems;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (int i = 1; i <= numberOfItems; i++) {
				string licensorInput;
				cout << endl << "Enter name of licensor # " << i << " :: ";
				getline(cin, licensorInput);
				AVL_Node_Pointer = Liscensor_Tree.Insert_Value_Without_Duplication(licensorInput);
				UserAnime.LiscensorsList.InsertAtFront(AVL_Node_Pointer);
			}
			cout << endl << "Enter number of Studios :: ";  //loop for multiple studios
			cin >> numberOfItems;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (int i = 1; i <= numberOfItems; i++) {
				string studioInput;
				cout << endl << "Enter name of studio # " << i << " :: ";
				getline(cin, studioInput);
				AVL_Node_Pointer = Studio_Tree.Insert_Value_Without_Duplication(studioInput);
				UserAnime.StudiosList.InsertAtFront(AVL_Node_Pointer);
			}
			cout << endl << "Enter number of Genres :: "; //loop for multiple genres
			cin >> numberOfItems;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (int i = 1; i <= numberOfItems; i++) {
				string genreInput;
				cout << endl << "Enter name of genre # " << i << " :: ";
				getline(cin, genreInput);
				AVL_Node_Pointer = Genre_Tree.Insert_Value_Without_Duplication(genreInput);//tree node inserted and pointer to node returned
				UserAnime.GenresList.InsertAtFront(AVL_Node_Pointer);//list in anime class object updated
			}
			AnimeTree1.Insert_Value_Without_Duplication(UserAnime, Episodes, Rank, Popularity, Members, Favourites, Watching, Completed, OnHold, Dropped, PlanToWatch, AVGscore);

		}

		else if (userOptionInput == 7) {		//list anime by episode number
			cout << "DISPLAYING LIST OF ANIME BY EPISODE NUMBER :: " << endl << endl;
			Episodes->In_Order_Printing(Episodes->Root);
		}

		else if (userOptionInput == 8) {		//list anime by rank
			cout << "DISPLAYING LIST OF ANIME BY RANK :: " << endl << endl;
			Rank->In_Order_Printing(Rank->Root);
		}

		else if (userOptionInput == 9) {		//list anime by popularity
			cout << "DISPLAYING LIST OF ANIME BY POPULARITY :: " << endl << endl;
			Popularity->In_Order_Printing(Popularity->Root);
		}

		else if (userOptionInput == 10) {		//list anime by members
			cout << "DISPLAYING LIST OF ANIME BY MEMBERS :: " << endl << endl;
			Members->In_Order_Printing(Members->Root);
		}

		else if (userOptionInput == 11) {		//list anime by favourites
			cout << "DISPLAYING LIST OF ANIME BY FAVOURITES ADDED :: " << endl << endl;
			Favourites->In_Order_Printing(Favourites->Root);
		}

		else if (userOptionInput == 12) {		//list anime by watching
			cout << "DISPLAYING LIST OF ANIME BY NUMBER OF WATCHING :: " << endl << endl;
			Watching->In_Order_Printing(Watching->Root);
		}

		else if (userOptionInput == 13) {		//list anime by completed
			cout << "DISPLAYING LIST OF ANIME BY NUMBER OF USERS MARKING COMPLETED :: " << endl << endl;
			Completed->In_Order_Printing(Completed->Root);
		}

		else if (userOptionInput == 14) {		//list anime by onhold
			cout << "DISPLAYING LIST OF ANIME BY NUMBER OF USERS MARKING ONHOLD :: " << endl << endl;
			OnHold->In_Order_Printing(OnHold->Root);
		}

		else if (userOptionInput == 15) {		//list anime by dropped
			cout << "DISPLAYING LIST OF ANIME BY NUMBER OF USERS MARKING DROPPED :: " << endl << endl;
			Dropped->In_Order_Printing(Dropped->Root);
		}

		else if (userOptionInput == 16) {		//list anime by Plan to Watch
			cout << "DISPLAYING LIST OF ANIME BY NUMBER OF USERS MARKING PLAN TO WATCH :: " << endl << endl;
			PlanToWatch->In_Order_Printing(PlanToWatch->Root);
		}

		else if (userOptionInput == 17) {		//list anime by Average Score
			cout << "DISPLAYING LIST OF ANIME BY AVERAGE USERS SCORE :: " << endl << endl;
			AVGscore->In_Order_Printing(AVGscore->Root);
		}

		else if (userOptionInput == 22) {		//list anime by entered genre
			cout << "DISPLAYING LIST OF ANIME BY ENTERED GENRE :: " << endl << endl;
			cout << "\x1b[32mPlease Enter Genre ::";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, y);
			Genre_Tree.Search_Value(y);
			if (Genre_Tree.Lock == NULL) {
				cout << "\x1b[37mGenre Not Found" << endl;
			}
			else {
				cout << "\x1b[37mAnime's with Genre \""; Genre_Tree.Lock->PrintAVLName(); cout << "\"are ::" << endl;;
				Genre_Tree.Lock->PrintAnimeList();
			}

		}

		else if (userOptionInput == 19) {		//list anime by entered producer
			cout << "DISPLAYING LIST OF ANIME BY ENTERED PRODUCER :: " << endl << endl;
			cout << "Please Enter Producer ::\x1b[32m";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, y);
			Producer_Tree.Search_Value(y);
			if (Producer_Tree.Lock == NULL) {
				cout << "\x1b[37mProducer Not Found" << endl;
			}
			else {
				cout << "\x1b[37mAnime's with Producer \""; Producer_Tree.Lock->PrintAVLName(); cout << "\"are ::" << endl;;
				Producer_Tree.Lock->PrintAnimeList();
			}
		}

		else if (userOptionInput == 20) {		//list anime by entered studio
			cout << "DISPLAYING LIST OF ANIME BY ENTERED STUDIO :: " << endl << endl;
			cout << "Please Enter Studio ::\x1b[32m";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, y);
			Studio_Tree.Search_Value(y);
			if (Studio_Tree.Lock == NULL) {
				cout << "\x1b[37mStudio Not Found" << endl;
			}
			else {
				cout << "\x1b[37mAnime's with Studio \""; Studio_Tree.Lock->PrintAVLName(); cout << "\"are ::" << endl;;
				Studio_Tree.Lock->PrintAnimeList();
			}
		}

		else if (userOptionInput == 21) {		//list anime by entered licensor
			cout << "DISPLAYING LIST OF ANIME BY ENTERED LICENSOR :: " << endl << endl;
			cout << "Please Enter Licensor ::\x1b[32m";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, y);
			Liscensor_Tree.Search_Value(y);
			if (Liscensor_Tree.Lock == NULL) {
				cout << "\x1b[37mLicensor Not Found" << endl;
			}
			else {
				cout << "\x1b[37mAnime's with Licensor \""; Liscensor_Tree.Lock->PrintAVLName(); cout << "\"are ::" << endl;;
				Liscensor_Tree.Lock->PrintAnimeList();
			}
		}

		else if (userOptionInput == 18) {		//list anime without info
			cout << "DISPLAYING LIST OF ANIME WITHOUT INFO :: " << endl << endl;
			AnimeTree1.In_Order_Printing_for_Menu(AnimeTree1.Root);
		}

		else if (userOptionInput == 23) {		//search for anime
			cout << "SEARCH FOR ANIME BY ID:: " << endl << endl;
			cout << "Please Enter Anime ID ::\x1b[32m";
			int x; cin >> x;
			AnimeTree1.Search_Value(x);
			if (AnimeTree1.Lock == NULL) {
				cout << "\x1b[37mAnime Not Found" << endl;
			}
			else {
				cout << "\x1b[37mData for Anime \""; AnimeTree1.Lock->PrintAnimeName(); cout << "\"is ::" << endl;;
				AnimeTree1.Lock->Print_Anime_Node_Data();
			}
		}
		else if (userOptionInput == 24) { //search for anime by episode number
			cout << "Please Enter Episode Number ::\x1b[32m";
			unsigned int x; cin >> x;
			Episodes->switch_Search(x);
			if (Episodes->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have Episodes = " << Episodes->Lock->value << endl;
				Episodes->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 25) { //search for anime by rank
			cout << "Please Enter Rank ::\x1b[32m";
			unsigned int x; cin >> x;
			Rank->switch_Search(x);
			if (Rank->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have Rank = " << Rank->Lock->value << endl;
				Rank->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 26) { //search for anime by popularity
			cout << "Please Enter Popularity ::\x1b[32m";
			unsigned int x; cin >> x;
			Popularity->switch_Search(x);
			if (Popularity->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have Popularity = " << Popularity->Lock->value << endl;
				Popularity->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 27) { //search for anime by members number
			cout << "Please Enter members count ::\x1b[32m";
			unsigned int x; cin >> x;
			Members->switch_Search(x);
			if (Members->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have Member count = " << Members->Lock->value << endl;
				Members->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 28) { //search for anime by favourites number
			cout << "Please Enter Favourites count ::\x1b[32m";
			unsigned int x; cin >> x;
			Favourites->switch_Search(x);
			if (Favourites->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have favourites count = " << Favourites->Lock->value << endl;
				Favourites->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 29) { //search for anime by watching number
			cout << "Please Enter Watching count ::\x1b[32m";
			unsigned int x; cin >> x;
			Watching->switch_Search(x);
			if (Watching->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have watching count = " << Watching->Lock->value << endl;
				Watching->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 30) { //search for anime by completed number
			cout << "Please Enter Completed count ::\x1b[32m";
			unsigned int x; cin >> x;
			Completed->switch_Search(x);
			if (Completed->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have completed count = " << Completed->Lock->value << endl;
				Completed->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 31) { //search for anime by on hold number
			cout << "Please Enter On Hold count ::\x1b[32m";
			unsigned int x; cin >> x;
			OnHold->switch_Search(x);
			if (OnHold->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have on hold count = " << OnHold->Lock->value << endl;
				OnHold->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 32) { //search for anime by dropped number
			cout << "Please Enter Dropped count ::\x1b[32m";
			unsigned int x; cin >> x;
			Dropped->switch_Search(x);
			if (Dropped->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have dropped count = " << Dropped->Lock->value << endl;
				Dropped->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 33) { //search for anime by plan to watch number
			cout << "Please Enter Plan to Watch count ::\x1b[32m";
			unsigned int x; cin >> x;
			PlanToWatch->switch_Search(x);
			if (PlanToWatch->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have Plan to Watch count = " << PlanToWatch->Lock->value << endl;
				PlanToWatch->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}

		else if (userOptionInput == 34) { //search for anime by average user score
			cout << "Please Enter average user score ::\x1b[32m";
			unsigned int x; cin >> x;
			AVGscore->switch_Search(x);
			if (AVGscore->Lock == NULL) {
				cout << "\x1b[37mNo Anime Found" << endl;
			}
			else {
				cout << "\x1b[37mFollowing Animes have the average user score = " << AVGscore->Lock->value << endl;
				AVGscore->Lock->List.Print_Names_At_Anime_Nodes();
			}

		}
		else {		//exit
			break;
		}

		system("pause");
		system("cls");
	}
	system("cls");
	system("pause");
	return 0;
} //end main

unsigned int get_Id() {
	//int level = 0; unsigned int index_of_level = 0; unsigned int index_zero = 0;
	//unsigned int ID = 1048571;
	if (check == true) {
		check = false;
		return ID;
	}
	if ((index_of_level + 1) == pow(2, level)) {
		level++;
		index_of_level = -1;
		index_zero = ID / pow(2, level);
	}
	index_of_level++;
	return index_zero + index_of_level * (ID / pow(2, level - 1));
}