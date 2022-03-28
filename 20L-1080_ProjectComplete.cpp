//---------------------------20L-1080 Nabeeha Mudassir-----------------------------------------
//---------------------------Complete Project--------------------------------------------------


#include <iostream>
#include <fstream>
using namespace std;

template <typename T1>
void DeleteTwoDArray(int Rows, T1 **&Pointer)
{
	for (int i = 0; i < Rows; i++)
	{
		if (Pointer[i])
		delete Pointer[i]; 
	}
	delete [] Pointer;
}


class User;
class Facebook;
class Page;
class Helper;
class Post;
class Comment;
class BaseClass;
class Date;
class Activity;


class Helper
{

public:
	//This Function will Concatenate 2 strings, and change the original string
	static void StringConcatenate(char*& str1, char* str2)
	{
		//Calculate the Lengths of the 2 strings
		int Length_1 = StringLength(str1);
		int Length_2 = StringLength(str2);
	

		//Create a new Array with this combined size
		int Combined_Length = Length_1 + Length_2 + 1; //1 more for space
		char* Appended = new char [Combined_Length];

		//Copy str1 and str2 into this New Array
		int i;
		int j = 0;
		for ( i = 0; i < Combined_Length; i++)
		{
			if (i < Length_1)
			{
				Appended[i] = str1[i];
			}
			else
				{
					Appended[i] = str2[j];
					j++;
				}
		
		}
		//at the last position of i there is null character already no need to add

		delete [] str1; //to prevent memory leakage
	
		str1 = Appended;
	
	}

	//Returns the Length of String without null character
	static int StringLength(char *str)
	{
		int length = 0;
			int i = 0;

			while ( str[i]!='\0')
			{
				length++;
				i++;
			}

			return length;
	}

	//Allocates string space on the heap and returns its pointer
	static char* GetStringFromBuffer(char* buffer)
	{
		//Calculate the Length of the buffer
		int Len = StringLength(buffer);
		char* str = 0;


		//Create a New Array on the Heap and Copy the contents of buffer into it
		if (Len > 0)
		{	
			str = new char[Len + 1]; //1 more for null
			int i = 0;
			for (i = 0; buffer[i]!='\0'; i++)
			{
				str[i] = buffer[i];
			}
			str[i] = '\0';
		}
		return str;
	}

	//Returns true if a certain substring is present inside the string
	static bool FindSubstring(char *FromWhat, char *toFind)
	{
		for (int i = 0; i < strlen(FromWhat); i++)
		{
			if  (FromWhat[i] == toFind[0])
			{
				int k = i+1;
				for (int j = 1; j < strlen(toFind); j++)
				{
					if (toFind[j] != FromWhat[k])
						return false;

					k++;
				}
				return true;
			}
		}
		return false;
	}

	//Returns true if a certain substring (in both upper case or lower) is present inside string
	static bool Search_Sub_String (char*toFind, char*str) //with upper and lower case
	{
		int toFind_Len = StringLength(toFind);

		//Does the first letter of the toFind string appear anywhere
	
		//Convert the First Letter of toFind into Upper or Lower case
		int index = -1;
		char Upper = 0, Lower = 0;
		if (toFind[0] <= 90)
		{
			Lower = toFind[0] + 32;
		}
		else
		{
			Upper = toFind[0] - 32;
		}

		//Set a new Array to Store the Matched Indices, initialise all indices with -1
		int Indices[10];
		for (int i = 0; i < 10; i++)
			Indices[i] = -1;
	
		//Iterator for Indices
		int I = 0;

		//Find All Possible Indexes after Which the Name could Start
		for (int a = 0; str[a]!='\0'; a++)
		{
			if (str[a] == Upper || str[a]==Lower || str[a] == toFind[0])
			{
			
				index = a;

				Indices[I] = a;

				I++;
			}
		}

		//Now For Each of these Index Positions, see if there is a match
		I = 0;
		while (Indices[I] != -1)
		{
			int indx = Indices[I];
			if (indx != -1)
			{
				indx++;

				int found = 1;

				for (int j = 1 ; j < toFind_Len ; j++)
				{

					if (str[indx] == toFind[j])
					{
						indx++;
						found++;
					}

				}

				if (found == toFind_Len)
				{
					return true;
				}
			}

			I++;
		}
		return false;
	}
};


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

class Date
{
private:
	int Day;
	int Month; 
	int Year;

public:
	Date()
	{
		Day = Month = Year = 0;
	}

	//It will Set the Day, Month, Year
	void SetDate(int d, int m, int y)
	{
		Day = d;
		Month = m;
		Year = y;
	}

	//Prints the Date in Correct Format
	void PrintDate()
	{
		cout << " ... (" << Day << "/" << Month << "/" <<Year << ")";
	}

	void ReadDatefromFile(ifstream& FIN)
	{
		FIN >> Day >> Month >> Year;
	}

	//Compares the given date with System's Date
	bool IsRecentDate()
	{
		if (Day == SystemDate.Day || Day == SystemDate.Day-1)
		{
			if (Month == SystemDate.Month && Year == SystemDate.Year)
				return true;
		}
		return false;
	}

	static Date SystemDate;

	static void SetSystemDate()
	{
		SystemDate.Day = 15;
		SystemDate.Month = 11;
		SystemDate.Year = 2017;

		cout << "\t"<<SystemDate.Day<<"/"<<SystemDate.Month<<"/"<<SystemDate.Year;
	}
};

//Initialising Static Variable in Global Scope
Date Date::SystemDate;



//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------


class BaseClass
{
private:
	char* ObjectID;    //the ID of either Page or User will be held here

public:
	BaseClass()
	{
		ObjectID = 0;
	}

	virtual ~BaseClass()
	{
		if (ObjectID)
			delete [] ObjectID;
	}
	
	virtual void AssociatePosts(Post* P)
	{
	}

	//It will Print the Author of Page / User
	virtual void PrintAuthorName() //and add the same function in PageClass and UserClass
	{
	}
	
	virtual void PrintIDAndName()
	{
	}


	//It will Print the Author ID of Page / User
	virtual void PrintAuthorID()
	{
		//does nothing.
	}
	
	char* GetObjectID()
	{
		return ObjectID;
	}
	
	void SetObjectID(char* Obj)
	{
		ObjectID = Helper::GetStringFromBuffer(Obj);
	}
};


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------


class Comment
{
private:
	char *Text;
	char *ID;
	
	BaseClass* Author;

public:
	Comment()
	{
		Text = ID = 0;
		Author = 0;
	}

	~Comment()
	{	
		if (Text)
			delete [] Text;
		if (ID)
			delete [] ID;
	}
	
	
	void SetData(char *tempID, char* tempText, BaseClass* _Author)
	{
		Text = Helper::GetStringFromBuffer(tempText);
		ID = Helper::GetStringFromBuffer(tempID);
		Author = _Author;
	}

	//It will Return the Author*
	BaseClass* ReturnAuthor()
	{
		//cout << "\t";
		return Author;
	}

	//Prints the Comment Text
	void Print_CommentData()
	{
		char Quote = '"';

		//Space is also read in the Text which is why quotation marks appear on far left
		cout << Quote << Text << Quote;
	}
};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

class Post
{
private:
	char *ID;
	char *Text;

	int Likes;
	int CommentNumber;

	Comment** AllComments;
	

	BaseClass* SharedBy;	//(AUTHOR) Only 1 user or 1 page can share it (association)
	BaseClass** LikedBy;	//Many people can like it
	Date SharedDate;		
	
public:
	virtual ~Post()
	{
		if (ID)
			delete [] ID;
		if (Text) 
			delete [] Text;

		DeleteTwoDArray(CommentNumber,AllComments);

		if (LikedBy)
			delete [] LikedBy;
	}

	Post()
	{
		AllComments = 0;
		CommentNumber = 0;
		ID = Text = 0;
		
		SharedBy = 0;
		LikedBy = 0;
		Likes = 0;
	}

	//Reads 1 Row of Post File
	virtual void LoadActivityORPostsFromFile(ifstream& FIN)
	{
		char Temp_ID[10];	char Temp_Text[200];

		FIN.getline(Temp_ID,10);
		
		ID = Helper::GetStringFromBuffer(Temp_ID);

		int day, month, year;

		SharedDate.ReadDatefromFile(FIN);

		FIN.getline(Temp_Text,20); //Blank space or whatever at the end is read

		FIN.getline(Temp_Text,100);

		char *Text_ = Helper::GetStringFromBuffer(Temp_Text);
		
		Post::SetData(ID,Text_);
	}

	//Allocates 10 Comments to 1 Comment*
	void Allocate_Comments()
	{
		//A Post can have 10 Comments at maximum
		AllComments = new Comment*[10];
	}

	//Assuming 1 Comment = 10 Likes maximum
	void Allocate_Likes()
	{
		LikedBy = new BaseClass*[10];
	}

	//It will store the pointer of Obj in LikedBy List
	void AssociateLikes(BaseClass* Obj)
	{
		if (Likes < 10)
		{
			LikedBy[Likes] = Obj;
			Likes++;
		}
	}
	
	//When Adding a new comment, a new comment ID is generated
	char* GenerateNewCommentId()
	{
		int tempCommentNum = CommentNumber + 1;
		
		char Commentnum;
		if (tempCommentNum < 10)
		{
			 
			Commentnum = tempCommentNum + '0';
			char NewID[4] = {'c',Commentnum,'\0'};
		
			char* New_ID = Helper::GetStringFromBuffer(NewID);
			return New_ID;
		}
		else
		{
			Commentnum = tempCommentNum; 
			char NewID[5] = {'c',Commentnum/10,Commentnum%10,'\0'};
			char* New_ID = Helper::GetStringFromBuffer(NewID);
			return New_ID;
		}

	}

	void AddComment(Comment* _comment)
	{
		if (CommentNumber < 10)
		{
			AllComments[CommentNumber] = _comment;
			CommentNumber++;
		}
	}

	//SETTERS:
	//Stores ID, Text, Author and then increments the Comment Number count

	void SetCommentsData(char *tempID, char* tempText, BaseClass* Author)
	{
		AllComments[CommentNumber]->SetData(tempID,tempText,Author);
		CommentNumber++;
	}

	void SetSharedBy(BaseClass* Obj)
	{
		//SharedBy = new BaseClass();
		SharedBy = Obj;
	}

	void SetLikedBy(BaseClass* Obj)
	{
		LikedBy[Likes] = Obj;
		Likes++;
	}

	void SetData( char *_ID, char *_Text)
	{
		ID = Helper::GetStringFromBuffer(_ID);
		
		Text = Helper::GetStringFromBuffer(_Text);
	}

	void SetPostSharedDate(int d, int m, int y)
	{
		SharedDate.SetDate(d,m,y);
	}


	//GETTERS
	//Prints Comments Data in a Loop

	void PrintCommentData()
	{
		for (int C = 0; C < CommentNumber; C++)
		{
			if (AllComments[C])
			{
				cout << endl;
				cout << "\t\t";
				BaseClass* Author = AllComments[C]->ReturnAuthor();
				Author -> PrintAuthorName();
				cout << " wrote: ";
				AllComments[C]->Print_CommentData();
			}
		}
	}

	//Return SharedDate
	Date ReturnSharedDate()
	{
		return SharedDate;
	}

	
	//Prints the SharedBy Name of Page or User
	/*void GetSharedBy()
	{
		SharedBy->PrintAuthorName();
	}*/

	//Used in SearchPostbyID
	char* GetPostID()
	{
		return ID;
	}

	void GetPostText()
	{
		char Quotes = '"';
		cout<< "\t "<< Quotes << Text << Quotes;
	}

	virtual void PrintData()
	{
		SharedBy -> PrintAuthorName();
		cout << " shared ";
		GetPostText();
	}

	void GetPostSharedDate()
	{
		SharedDate.PrintDate();
	}
	
	void PrintIDandName(BaseClass* &LikedBy)
	{
		if (LikedBy)
		{
			cout << "\t\t";
			LikedBy -> PrintAuthorID();
			cout << " - ";
			LikedBy -> PrintAuthorName();
			cout << endl;
		}
	}
										//changed here
	void PrintLikedList()
	{
		cout << endl;
		for (int i = 0; i < Likes ; i++) 
		{
				//PrintIDandName(LikedBy[i]);
			LikedBy[i]->PrintIDAndName();
		}
	}

	char* ReturnPostText()
	{
		return Text;
	}
	
	void PrintPostDetails()
	{
		cout << ID;
		cout << endl;
		SharedDate.PrintDate();
		cout<<endl;
		SharedBy->PrintAuthorName();
		cout << endl;
	}

	BaseClass* ReturnSharedBy()
	{
		return SharedBy;
	}
};


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

class Activity : public Post
{
private:
	int Type; //feeling, thinking about, making, celebrating
	char* Value; //happy,sad,etc
public:
	Activity()
	{
		Type = 0;
		Value = 0;
	}

	~Activity()
	{
		if (Value)
			delete [] Value;
	}
	
	//Reads 1 Row of Post File
	void LoadActivityORPostsFromFile(ifstream& FIN)
	{
		//Reusability
		Post::LoadActivityORPostsFromFile(FIN);

		
		FIN >> Type;
		
		char TempFeeling[100];
		FIN.getline(TempFeeling,100);

		Value = Helper::GetStringFromBuffer(TempFeeling);
		
	}

	//Post Class has virtual function of this
	void PrintData()
	{
		ReturnSharedBy()->PrintAuthorName();
		
		if (Type == 1)
		{
			cout << " is feeling ";
		}
		else if (Type == 2)
		{
			cout << " is thinking about ";
		}
		else if (Type == 3)
		{
			cout << " is making ";
		}
		else if (Type==4)
		{
			cout << " is celebrating ";
		}

		cout << Value;
		cout << endl;
		char Quotes = '"';
		cout << "\t\t\t" << Quotes << ReturnPostText() << Quotes;
	
		Post::GetPostSharedDate();
	}

	
	char* GetValue()
	{
		return Value;
	}
	
};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

	
class Page : public BaseClass
{
private:
	char *Page_title;

	Post** Timeline;

	int TotalPosts;
public:
	Page()
	{
		Page_title = 0;
		TotalPosts = 0;
	}

	~Page()
	{
		if (Page_title)
			delete [] Page_title;
		
		DeleteTwoDArray(TotalPosts,Timeline);
	}

	//Reads 1 Single Row from Page File & Allocates it on the Heap 
	void ReadMyPage(ifstream& FIN, Page *& PageList)
	{
		//HOW TO READ 2 WORD PAGE TITLE
		char PgID[5]; char Pgtitle1[50];
		
		FIN >> PgID;
		FIN.getline(Pgtitle1,50);
		
		BaseClass::SetObjectID(PgID);
		Page_title = Helper::GetStringFromBuffer(Pgtitle1);

	}

		//Assuming 10 Posts per Timeline
	void AllocateTimeline()
	{
		Timeline = new Post*[10];
	}

	//Stores pointer of Post in the Timeline
	void AssociatePosts(Post* PostPtr)
	{
		if (TotalPosts < 10)
		{
			Timeline[TotalPosts] = PostPtr;
			TotalPosts++;
		}
	}

	//Returns the Post* at specific index of the Timeline
	Post* AccessTimeline(int index)
	{
		return Timeline[index];
	}

	//GETTERS:

	//chnage
	void PrintPageData()
	{
		cout << "\t";
		cout << GetPageTitle();

		for (int i = 0; i < TotalPosts; i++)
		{
			cout << "\n\n\t\t---";
			Timeline[i]->PrintData();
			Timeline[i]->PrintCommentData();
		}
	}

	void PrintAuthorName()
	{
		cout << Page_title << " ";
	}

	void PrintAuthorID()
	{
		cout << GetObjectID();
	}

	void PrintIDAndName()
	{ 
		cout<< GetObjectID() << " - " << Page_title <<endl;
	}

	int GetPostNumber()
	{
		return TotalPosts;
	}

	char *GetPageTitle()
	{
		return Page_title;
	}

	void PrintPageDetail()
	{
		cout << "\t" << GetObjectID()<<"\t";
		cout << Page_title << endl;
	}

};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------


class User : public BaseClass
{
private:
	char *FirstName;
	char *LastName;

	User **FriendsList;
	Page **PagesLiked;

	Post** Timeline;

	int PostNumber;
	int FriendNumber;
	int PageNumber;
public:
	User()
	{
		FirstName = LastName = 0;
		FriendsList = 0;
		PagesLiked = 0;
		PostNumber = 0;
		FriendNumber = 0;
		PageNumber = 0;
		Timeline = 0;
	}

	~User()
	{
		if (FirstName)
			delete [] FirstName;
		if (LastName)
			delete [] LastName;
		if (FriendsList)
			delete [] FriendsList;
		if (PagesLiked)
			delete [] PagesLiked;

		DeleteTwoDArray(PostNumber,Timeline);
	}

	//It reads an entire row (1 User) from the User File
	void ReadUserData(ifstream& FIN , char **&TempFriendsList, char **&TempPagesLiked)
	{
		//Read into Temporary Buffers
		char I_D[5]; char FName[10]; char LName[10];
		FIN >> I_D >> FName >> LName;

		//Now Store them on the Heap & Get their Pointers
		
		BaseClass::SetObjectID(I_D);
		FirstName = Helper::GetStringFromBuffer(FName);
		LastName = Helper::GetStringFromBuffer(LName);

		//------------------Reading TempFriends------------------------------ 

		//Store into Temporary Pointer Array
		TempFriendsList = new char * [10]; // (10 friends max)
		for (int i = 0; i < 10; i++)
			TempFriendsList[i] = new char [5]; //5 Cols i.e. u 2 \0 max
		
		//Read the First User
		FIN >> TempFriendsList[0];

		//If it is not -1 then continue reading rest
		int t = 0;
		while (Helper::FindSubstring(TempFriendsList[t],"-1") == false)
		{
			t++;
			FIN >> TempFriendsList[t];
		}
		TempFriendsList[t] = "\0";


		//-----------------------Reading TempPages------------------------------


		TempPagesLiked = new char *[10]; //10 = Max Number of Pages that can be Liked
		for (int i = 0; i < 10; i++)
		{
			TempPagesLiked[i] = new char [4]; //Length format p2\0 is of 4 characters Max
		}

		FIN >> TempPagesLiked[0];
		
		t = 0;

		while (Helper::FindSubstring(TempPagesLiked[t],"-1") == false)
		{
			t++;
			FIN >> TempPagesLiked[t];
		}
		TempPagesLiked[t] = "\0";
	}

	//Allocates Space on Heap for 10 Friends for a User
	void Allocate_FriendsList(int Friends)
	{
		FriendsList = new User* [10];
	}

	//Allocates Space on Heap for 10 Pages 
	void Allocate_PagesLiked (int Pages)
	{
		PagesLiked = new Page *[10];
	}

	void PrintFriendHomeData(int TimelineIndex)
	{
		cout << endl << endl << "\t-->";
		Timeline[TimelineIndex]->PrintData();
		Timeline[TimelineIndex]->PrintCommentData();
	}

	//Prints Posts in the Timeline 
	void ViewHome()
	{
		//Friends Call their own Posts (and Activities) from specific date
		//Every Post will Call its own Comments List
		for (int i = 0; FriendsList[i]!=0; i++)
		{
			for (int j = 0; j < FriendsList[i]->GetPostNumber(); j++)
			{
				Date D = FriendsList[i]->Timeline[j]->ReturnSharedDate();

				if (D.IsRecentDate() == true)
				{
					FriendsList[i]->PrintFriendHomeData(j);
				}
			}
		}

		//this->will call its Liked Pages from specifc date
		//Every liked page will call its own Comments Lisr
		for (int i = 0; PagesLiked[i]!=0; i++)
		{

			for (int j = 0; j < PagesLiked[i]->GetPostNumber(); j++)
			{
				
				Date D = PagesLiked[i]->AccessTimeline(j)->ReturnSharedDate();
				if (D.IsRecentDate() == true)
				{
					cout << endl << endl << "\t-->";
					PagesLiked[i]->AccessTimeline(j)->PrintData();
					PagesLiked[i]->AccessTimeline(j)->PrintCommentData();
				}
			}
		}

	}


	//Stores the Post* in the Timeline
	void AssociatePosts(Post* P_Ptr)
	{
		Timeline[PostNumber] = P_Ptr;
		PostNumber++;
	}

	//Assuming 10 Posts per Timeline
	void Allocate_Timeline()
	{
		Timeline = new Post *[10];
	}
	
	//It simply points the index on the FriendList to a user on the User List
	void SetUserFriend(User*& U_Ptr)
	{
		if (FriendNumber < 10)
		{
			FriendsList[FriendNumber] = U_Ptr;
			FriendNumber++;
		}
	}

	//It simply points the index on the LikedPages to a page on the PageList
	void SetUserLikedPage(Page*& Pg_Ptr)
	{
		if (PageNumber < 12)
		{
			PagesLiked[PageNumber] = Pg_Ptr;
			PageNumber++;
		}
	}

	void PrintPost()
	{
		for (int i = 0 ; i < PostNumber ; i++)
		{
			cout << endl;
			cout << "\t";

			Timeline[i]->PrintData();
		
			Timeline[i] -> PrintCommentData();

			cout << endl;
		}
	}
	
	//GETTERS:

	int GetPostNumber()
	{
		return PostNumber;
	}

	void PrintName()
	{
		cout << FirstName << " "<< LastName << " ";
	}
	
	char* ReturnFullName()
	{
		//Concatenate the First and Last Names
		char* CompleteName = Helper::GetStringFromBuffer(FirstName);
		Helper::StringConcatenate(CompleteName,LastName);

		return CompleteName;
		//Return a total name & later delete it
	}

	void PrintFriendDetails()
	{
			cout << "\t" << GetObjectID() << "\t" ;
			cout << FirstName <<" ";
			cout << LastName << endl;
	}

	void PrintFriends()
	{
		cout << FirstName << " " << LastName << "'s Friends List = \n";
		bool FriendsFound = false;

		for (int i = 0; FriendsList[i]!=0; i++)
		{
			FriendsList[i]->PrintIDAndName();
			FriendsFound = true;
		}
		
		if (FriendsFound == false)
			cout << "\tNo Friends Found.\n";
	}

	void PrintLikedPage()
	{
		cout << "'s Liked Pages: \n";

		bool PagesLikedFound = false;

		for (int i = 0; PagesLiked[i]!=0; i++)
		{
			PagesLiked[i]->PrintIDAndName();//>PrintPageDetail();
			PagesLikedFound = true;
		}

		if (PagesLikedFound == false)
			cout << "\tNo Liked Pages.\n";
	}

	void PrintAuthorID()
	{
		cout << GetObjectID();
	}

	void PrintAuthorName()
	{
		cout << FirstName << " "<< LastName;
		cout << " ";
	}

	void PrintIDAndName()
	{ 
		cout<< GetObjectID() << " - " << FirstName << " "<< LastName <<endl;
	}

};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------


class Facebook : public BaseClass
{
private:
	
	int TotalUsers;
	int TotalPages;
	int TotalPosts;
	int TotalComments;

	User **User_List;
	Page **Page_List;

	Post **AllPosts;
	//All Comments will be in Post Class Onlyy...
	
public:
	
	User* CurrentUser;

	//Defined outside.
	void Run();

	Facebook()
	{
		TotalUsers = TotalPages = TotalComments = TotalPosts = 0;
		User_List = 0;
		Page_List = 0;
		AllPosts = 0;
		CurrentUser = 0;
	}
	

	~Facebook()
	{
		//Deleting Page_List
		
		DeleteTwoDArray(TotalPages,Page_List); 
		
		//Deleting User_List
		
		DeleteTwoDArray(TotalUsers,User_List);

		if (AllPosts)
			delete [] AllPosts;
	}

	
	
	//Calls HomePage of the User
	void ViewHomePage(char* _User)
	{
		User* UserID = SearchUserByID(_User);
		if (UserID)
			UserID->ViewHome();
	}

	//Calls the Post Data of all Posts
	void CallAllPosts()
	{
		for (int i = 0; i < TotalPosts; i++)
		{
			AllPosts[i]->PrintPostDetails();
		}
	}

	//Shows Page Data when given the ID
	void ViewPage(char* _PageID)
	{
		Page* PgID = SearchPageByID(_PageID);
		if (PgID)
			PgID->PrintPageData();
	}

	//Associates the Post with a User
	void Like_A_Post(char* UserID, char* PostID)
	{
		Post* _PostPointer = SearchPostByID(PostID);
		if (_PostPointer)
		{
				_PostPointer->AssociateLikes(CurrentUser);
		}
		
	}

	//Calls timeline by User ID
	void PrintTimeline (char* _User)
	{
			//Retrieve User Pointer
		User* User_ptr = SearchUserByID(_User);
		cout << endl << "\t";
		User_ptr->PrintName();
		cout << " - Timeline: \n";
		if (User_ptr)
			User_ptr -> PrintPost();

		cout << endl; 
	}

	//Calls the Liked List of a Specific Post
	void ViewLikedList(char* PostID )
	{
		cout << "\n\tPost Liked By:\n";
		Post* _PostID = SearchPostByID(PostID);
		if (_PostID)
			_PostID->PrintLikedList();
	}
	
	//Displays the Post Data of specific Post ID
	void ViewPost(char* _PostId)
	{
		Post* PostID = SearchPostByID(_PostId);
		cout << "\t\t---";
		PostID->PrintData();
		PostID->PrintCommentData();
	}

	//Adds a new comment on a specific post
	void PostComment(char* _PostID, char* _CommentText)
	{
		Post* PostID = SearchPostByID(_PostID);
		
		Comment* NewComment = new Comment();

		//New comment ID is generated based on previous comment number.
		char* newCommentID = PostID->GenerateNewCommentId();

		NewComment -> SetData(newCommentID,_CommentText,CurrentUser);
		
		PostID -> AddComment(NewComment);
	}
	
	//De-Allocation
	void DeleteTempLists(char ***&TempFriendsList, char ***&TempPagesLiked)
	{
		//Deleting TempFriendsList
		for (int i = 0; i < TotalUsers; i++)
		{
			for (int j = 0; TempFriendsList[i][j]!="\0";j++)
			{
				if (Helper::FindSubstring(TempFriendsList[i][j],"\0") == false)
				{
					delete [] TempFriendsList[i][j];	
				}
			}
			delete []TempFriendsList[i];
		}
		delete [] TempFriendsList;
		
		//Deleting TempPagesLists
		for (int i = 0; i < TotalPages; i++)
		{
			for (int j = 0; TempPagesLiked[i][j]!="\0";j++)
			{
				if (Helper::FindSubstring(TempPagesLiked[i][j],"\0") == false)
					delete [] TempPagesLiked[i][j];
			}
			delete [] TempPagesLiked[i];
		}
		delete [] TempPagesLiked;
	}

	//It will return the Current User's address from UserList 
	void SetCurrentUser(char *_user)
	{
		bool UserExists = false;
		for (int i = 0; i < TotalUsers; i++)
		{
			if (Helper::FindSubstring(User_List[i]->GetObjectID(),_user) == true)
			{
				UserExists = true;
				CurrentUser = User_List[i];
			}
		}
		if (UserExists == false)
			cout << "\n\t\t"<<_user<<" was not found in User List.\n";
	}

	
	//From the TempFriendsList, it will send a pointer of that User to FriendsList for every user
	void AssociateFriends(char ***&TempFriendsList)
	{
		//First Find Number of Friends of Every user and Allocate Space for them
		int* FriendsOfEveryUser = new int [TotalUsers];
		int F = 0;
		for (int i = 0; i < TotalUsers; i++)
		{
			F = 0;
			for (int j = 0; TempFriendsList[i][j]!="\0"; j++)
			{
				F++;
			}
			
			User_List[i] -> Allocate_FriendsList(F + 1);
		}
		delete [] FriendsOfEveryUser;
		
		//For 1 User: Scan its TempFriendsList
		//Call SearchUserbyID and retrieve an address
		int i, j;
		User * User_Ptr = 0;
		for (i = 0; i < TotalUsers; i++)
		{
			for (j = 0; TempFriendsList[i][j]!="\0"; j++)
			{
				User_Ptr = SearchUserByID(TempFriendsList[i][j]);
				if (User_Ptr)
					User_List[i] -> SetUserFriend(User_Ptr);
			}
			User* NullPtr = 0;
			User_List[i] -> SetUserFriend(NullPtr);
		}

	}


	//From the TempPagesLiked, it will send a pointer of that Page to PagesLiked for every user
	void AssociatePages(char ***&TempPagesLiked)
	{
		//First Find PagesLiked of Every user and Allocate Space for them
		int* PagesOfEveryUser = new int [TotalUsers];

		int P;

		for (int i = 0; i < TotalUsers; i++)
		{
			P = 0;
			for (int j = 0; TempPagesLiked[i][j]!="\0"; j++)
			{
				P++;
			}

			User_List[i]->Allocate_PagesLiked(P + 1);
		}

		delete [] PagesOfEveryUser;
		
		//For 1 User: Scan its TempPagesList
		//Call SearchPageID and retrieve an address
		int i, j;
		Page * Pg_Ptr = 0;
		for (i = 0; i < TotalUsers; i++)
		{
			for (j = 0; TempPagesLiked[i][j]!="\0"; j++)
			{
				Pg_Ptr = SearchPageByID(TempPagesLiked[i][j]);
				User_List[i] -> SetUserLikedPage(Pg_Ptr);
			}
			Page *Null_Ptr = 0;
			User_List[i] ->SetUserLikedPage(Null_Ptr);
		}

	}

					//--------Search Functionality---------

	User* SearchUserByID(char *ID)
	{
		//Scans User List when given an ID
		//Return Address of User in that List where ID is found

		for (int i = 0; i < TotalUsers; i++)
		{
			if (Helper::FindSubstring(User_List[i]->GetObjectID(),ID) == true)
			{
				return User_List[i];
			}
		}
		return 0;
	}

	
	Page *SearchPageByID(char *ID)
	{
		for (int i = 0; i < TotalUsers; i++)
		{
			if (Helper::FindSubstring(Page_List[i]->BaseClass::GetObjectID(),ID) == true)
			{
				return Page_List[i];
			}
		}
		return 0;
	}


	Post* SearchPostByID(char *ID)
	{
		for (int i = 0; i < TotalPosts; i++)
		{
			if (Helper::FindSubstring(AllPosts[i]->GetPostID(),ID) == true)	
			{
				return AllPosts[i];
			}
		}
		return 0;
	}

	
	void SearchPostbyWord(char* SearchWord)
	{
		//People Pages and Posts
		//Name, Title, Description

		//Convert the Word to initial letter Lowercase or initial letter UpperCase
		char* SearchWord_inDifferentCase = 0;
		if (SearchWord[0] <123 && SearchWord[0]>96)
		{
			SearchWord_inDifferentCase = Helper::GetStringFromBuffer(SearchWord);
			SearchWord_inDifferentCase[0] = SearchWord_inDifferentCase[0] - 32;
		}
		else
		{
			SearchWord_inDifferentCase = Helper::GetStringFromBuffer(SearchWord);
			SearchWord_inDifferentCase[0] = SearchWord_inDifferentCase[0] + 32;
		}

		bool DisplayOnce = false;

		
		//Checking for SearchWord in both Cases in the POSTS (Description)
		for (int i = 0; i < TotalPosts; i++)
		{
			char* toSearch = AllPosts[i]->ReturnPostText();
			bool Match1 = Helper::Search_Sub_String(SearchWord,toSearch);
			bool Match2 = Helper::Search_Sub_String(SearchWord_inDifferentCase,toSearch);

			if (Match1 == true || Match2 == true)
			{
				if (DisplayOnce == false)
				{
					cout << "\n\t\tPosts - \n\n";
					DisplayOnce = true;
				}
				cout << "\t\t\t->" << AllPosts[i]->GetPostID() << " - ";
				AllPosts[i]->PrintData();
				cout << endl << endl;
			}
		}
		
		//Checking for the SearchWord in the PAGE NAMES 
		DisplayOnce = false;
		for (int i = 0; i < TotalPages; i++)
		{
			char* toSearch = Page_List[i]->GetPageTitle();
			bool Match1 = Helper::Search_Sub_String(SearchWord,toSearch);
			bool Match2 = Helper::Search_Sub_String(SearchWord_inDifferentCase,toSearch);


			if (Match1 == true || Match2 == true)
			{
				if (DisplayOnce == false)
				{
					cout << "\n\t\tPages - \n\n";
					DisplayOnce = true;
				}
				cout << "\t\t\t->" << Page_List[i]->GetObjectID() << "-";
				Page_List[i]->PrintPageData();
				cout << endl << endl;
			}
		}

		//Search for SearchWord in the User Names

		DisplayOnce = false;
		for (int i = 0; i < TotalUsers; i++)
		{
			char* toSearch = User_List[i]->ReturnFullName();
			bool Match1 = Helper::Search_Sub_String(SearchWord,toSearch);
			bool Match2 = Helper::Search_Sub_String(SearchWord_inDifferentCase,toSearch);

			if (Match1 == true || Match2 == true)
			{
				if (DisplayOnce == false)
				{
					cout << "\n\t\tUsers - \n\n";
					DisplayOnce = true;
				}
				cout << "\t\t\t->" << User_List[i]->GetObjectID() << "-";
				User_List[i]->PrintName();
				cout << endl << endl;
			}
			delete [] toSearch; //Currently holds FullName which is on the Heap
		}
		delete [] SearchWord_inDifferentCase;
	}

	//Reads 2 Files: UserFile and PagesFile
	void LoadData(char ***&TempFriendsList, char ***&TempPagesLiked)
	{
		//------------------------LoadPagesFromFile----------------------------
		ifstream FIN("20.2.2. - Project-SocialNetworkPages.txt");
		if (!FIN)
		{
			cout<<"Project-SocialNetworkPages.txt Not found.\n";
			return;
		}
		
		FIN >> TotalPages;
		

		//3 Comments
		char Comment[200];
		for (int i = 0; i < 3; i++)
		{
			FIN.getline(Comment,200,'\n');
		}
		

		//Initialise PageList
		Page_List = new Page*[TotalPages];
		for (int i = 0; i < TotalPages; i++) //1 Page Object per List
			Page_List[i] = new Page();

		for (int i = 0; i < TotalPages; i++)
			Page_List[i]->AllocateTimeline();

		for (int i = 0 ; i < TotalPages; i++)
			Page_List[i] -> ReadMyPage(FIN,Page_List[i]);

		FIN.close();
		 

		//------------------------LoadUsersFromFile----------------------------

		ifstream InFile ("20.2.3 - Project-SocialNetworkUsers.txt");
		
		if (!InFile)
		{
			cout << "\nProject-SocialNetworkUsers.txt Not Found.\n";
			return;
		}
		
		InFile >> TotalUsers;

		//Read 3 Comments
		char Comment1[200];
		for (int i = 0; i < 3; i++)
		{
			InFile.getline(Comment1,200);
		}
		
		User_List = new User* [TotalUsers];
		
		
		for (int i = 0; i < TotalUsers; i++)
		{
			User_List[i] = new User();			//It Does not work without [1]
		}

		TempFriendsList = new char **[TotalUsers];
		TempPagesLiked = new char **[TotalUsers];
		//(Remaining Initialisation has been left to ReadUserData)
		

		//Because Association has not been done yet
		for (int i = 0; i < TotalUsers; i++)
		{
			//Friends & Liked Pages
			User_List[i]->ReadUserData(InFile,TempFriendsList[i], TempPagesLiked[i]);
		}
		
		InFile.close();
	}
	
	
	//Reads all the Posts from the Post File
	void LoadAllPosts()
	{
		
		ifstream FIN("24.1.1 - Project-SocialNetworkPosts.txt");
		if (!FIN)
		{
			cout << "\n24.1.1 - Project-SocialNetworkPosts Does Not Exist.\n";
			return;
		}

		FIN >> TotalPosts;
		AllPosts = new Post*[TotalPosts];

		
		char **TempLikedBy = 0;
		int Likes = 0;

		//First All Users will be Allocates 10 Posts Space
		for (int i = 0; i < TotalUsers; i++)
		{
			User_List[i]->Allocate_Timeline();
		}

		//Then Their Association will be done at respective indexes

		for (int p = 0; p < TotalPosts; p++)
		{
			int PostORActivity = 0; //Type

			FIN >> PostORActivity;

			if (PostORActivity == 2) 
				AllPosts[p] = new Activity;
			else 
				AllPosts[p] = new Post;


						//First 3 Rows are Read
			AllPosts[p] -> LoadActivityORPostsFromFile(FIN); 

						//Remaining 2 Rows are Read Here:

			//SharedBy can be Page or User so check:
			char _UserORPage[4]; 

			FIN >> _UserORPage;
			char *SharedBy = Helper::GetStringFromBuffer(_UserORPage);

			//---------------------Association of Post and User/Page-------------
			BaseClass* Obj = GetObjectbyID(SharedBy);
			AllPosts[p]->SetSharedBy(Obj);
			Obj->AssociatePosts(AllPosts[p]);

			
				//LikedBy:
			//A temporary list to store the Likes

			TempLikedBy = new char *[10]; //Maximum Likes can be 10
			for (int i = 0; i < 10; i++)
				TempLikedBy[i] = new char [4]; //columns = 4

			
			FIN >> TempLikedBy[0];
			
			int i = 0;  
			while (Helper::FindSubstring(TempLikedBy[i],"-1") == false)
				{
					if (Helper::FindSubstring(TempLikedBy[i],"-1") == false)
					{
						i++;
						FIN >> TempLikedBy[i];
					}
				}
			
			//Allocate Space of Total of 10 Likes
			AllPosts[p] -> Allocate_Likes(); 
			
			
			//Likedby can be Page or User so check:
			int t = 0;

			for ( ;Helper::FindSubstring(TempLikedBy[t],"-1") == false; t++)
				{
					BaseClass* obj = 0;
					if (TempLikedBy[t][0] == 'u')
						{
							obj = SearchUserByID(TempLikedBy[t]);
						}
					else
						{
							obj = SearchPageByID(TempLikedBy[t]);
						}
					AllPosts[p] -> SetLikedBy(obj);
				}

			for (int i = 0; i < 10; i++)
				delete [] TempLikedBy[i];
			delete [] TempLikedBy;

		}
		FIN.close();
	}

	BaseClass* GetObjectbyID(char* _Author)
	{
		BaseClass* B_Ptr = 0;

		if (_Author[0] == 'u')
			{
				B_Ptr = SearchUserByID(_Author);
			}
		else
			{
				B_Ptr = SearchPageByID(_Author);
			}

		return B_Ptr;
	}

	//Reads all the Comments in the Comment File
	void LoadAllComments()
	{
		ifstream FIN("24.1.0 - Project-SocialNetworkComments.txt");
		if (!FIN)
			cout << "\nFile does not exist\n";

		FIN >> TotalComments;

		//Allocate 10 Comments to every Post
		for (int p = 0; p < TotalPosts; p++)
			AllPosts[p]->Allocate_Comments();

	//	Comment** AllComments = new Comment*[TotalComments];
		

		char CommentID[4];
		char *C_ID = 0; char PostID[6]; char *_PostID = 0;char Author[4];
		char *_Author = 0;char TempText[150];char *_TempText = 0;

		for (int i = 0; i < TotalComments; i++)
		{
			Comment* commentPtr = new Comment();

			//Allocate Maximum of 10 Comments
			//Read CommentID,PostID,Author,CommentText
			FIN >> CommentID;

			//Read PostID
			FIN >> PostID;
			_PostID = Helper::GetStringFromBuffer(PostID);
		
			//Read Author
			FIN >> Author;
			_Author = Helper::GetStringFromBuffer(Author);
			BaseClass *Author = GetObjectbyID(_Author);
			
			
			//Read Text
			FIN.getline(TempText,150);

			commentPtr->SetData(CommentID,TempText,Author);

			//----------------Association of Post and Comment----------------
			Post* PostPtr = SearchPostByID(_PostID);
			
			if (PostPtr)
				PostPtr -> AddComment(commentPtr);
			
		}

		FIN.close();

	}


	int ReturnTotalUsers()
	{
		return TotalUsers;
	}

	int ReturnTotalPages()
	{
		return TotalPages;
	}

	
};


void Facebook::Run()
{
	cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
	cout << "\tCommand:\tSet Current User u7 \n";
	cout << "----------------------------------------------------------------------------------------------------------------------\n";

	SetCurrentUser("u7"); 

	if (CurrentUser)
	{
		cout << "\t";
		CurrentUser -> PrintName();
		cout << "successfully set as Current User. \n\n";
		
		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
		cout << "\tCommand:\tSet Current System Date 15 11 2017\n";
		cout << "----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\tSystem Date: ";
		Date::SetSystemDate();

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\tCommand:\tView Friend List";
		cout << "\n----------------------------------------------------------------------------------------------------------------------\n\t";
		CurrentUser -> PrintFriends();

		cout << "\n----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\tCommand:\tView Liked Pages\n";
		cout << "----------------------------------------------------------------------------------------------------------------------\n";
		cout << "\t";
		CurrentUser -> PrintName();
		CurrentUser -> PrintLikedPage();

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n";
		cout << "\tCommand:\tView Home\n";
		cout << "----------------------------------------------------------------------------------------------------------------------\n";
		cout << "\t";
		ViewHomePage("u7");

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n";
		cout << "\tCommand:\tView Timeline\n";
		cout << "----------------------------------------------------------------------------------------------------------------------\n\t";
		PrintTimeline("u7");

		cout << "\n----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\tCommand:\tView Liked List (post5)\n";
		cout << "----------------------------------------------------------------------------------------------------------------------\n";
		cout << "\t";
		ViewLikedList("post5");

		cout << "\n----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\tCommand:\tLike Post (post5)\n";
		Like_A_Post("u7","post5");
		cout << "\n\tCommand:\tView Liked List (post5)\n";
		cout << "----------------------------------------------------------------------------------------------------------------------\n";
		cout << "\t";
		ViewLikedList("post5");

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\tCommand:\tPost Comment (post4,GoodLuck for your Result)\n";
		PostComment("post4","Good Luck for your Result");
		cout << "\tCommand:\tView Post(post4)";
		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
		ViewPost("post4");

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n";
		cout << "\tCommand:\tPost Comment (post8,Thanks for Wishes)\n";
		cout << "\t";
		PostComment("post8","Thanks for wishes");
		cout << "\n\tCommand:\tView Post(post8)";
		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
		ViewPost("post8");

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\tCommand:\tView Page(p1)\n";
		cout << "----------------------------------------------------------------------------------------------------------------------\n\t";
		ViewPage("p1");

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\tCommand:\tSearch(Birthday)\n";
		cout << "----------------------------------------------------------------------------------------------------------------------\n\t";
		SearchPostbyWord("Birthday");

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\tCommand:\tSearch(Ali)\n";
		cout << "----------------------------------------------------------------------------------------------------------------------\n\t";
		SearchPostbyWord("Ali");
	}
	//No need for else statement: this is handled by SetCurrentUser
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

int main()
{
	cout << "\n\n\t\t\t--------------WELCOME TO MYFACEBOOK!-------------\n\n";
	
	Facebook FB;
	
	char ***TempFriendsList = 0;
	char ***TempPagesLiked = 0;

	FB.LoadData(TempFriendsList, TempPagesLiked);

	FB.AssociateFriends(TempFriendsList);
	FB.AssociatePages(TempPagesLiked);

	FB.DeleteTempLists(TempFriendsList,TempPagesLiked);

	FB.LoadAllPosts();
	
	FB.LoadAllComments();
	
	FB.Run();

	cout << "\n\n-----------------------------------------------------------";
	cout << "-----------------------------------------------------------\n\n";


	return 0;
}