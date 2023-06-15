#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>

using namespace std;

char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "573lau573";

int main() {
	
	MYSQL* obj;    //One to manage MYSQL sessions
	
	char name[100];
	char email[50];  
	
	bool ProgramIsOpened = true;  // To keep the program opened
	int answer;
	
	char* consult;
	char* sentence;
	string sentence_aux;     /// These are to add data to the table
	
	//Connecting
	if(!(obj = mysql_init(0))){
		cout << "ERROR: MYSQL object could not be created. " << endl;
	}else{
		if(!mysql_real_connect(obj, HOST, USER, PASS, "nepractice", 3306, NULL, 0)){
			cout << "ERROR: Some database info is wrong or doesn't exit" << endl;
			cout << mysql_error(obj) << endl;
		}else{
			cout << "Logged in." << endl << endl;
			while(ProgramIsOpened){
				cout << "Name: ";
				cin >> name;
				cin.getline(name,100, '\n'); 
				
				cout << "Email: ";
				cin >> email;
				cout << endl;
				
				sentence_aux = "INSERT INTO dsapractice(name, email) VALUES('%s', '%s')";
				sentence = new char[sentence_aux.length()+1];
				strcpy(sentence, sentence_aux.c_str());    //We copy our string statement into *char[]
				
				consult = new char[strlen(sentence) + strlen(name) + strlen(email)];
				sprintf(consult, sentence, name, email); //Substitutes %d... for actual values
				
				//Make our attempt
				if(mysql_ping(obj)){
					cout << "ERROR: Impossible to connect." << endl;
					cout << mysql_error(obj) << endl;
				}
				if(mysql_query(obj, consult)){
					cout << "ERROR: " << mysql_error(obj) << endl;
					rewind(stdin);
					getchar();
				}else{
					cout << "Info added correctly" << endl;
				}
				mysql_store_result(obj);
				
				cout << endl << "Anoter ?" << endl;
				cout << "[1]: Yes" << endl;
				cout << "[2]: No" << endl;
				cout << "Answer: ";
				cin >> answer;
				cin.ignore(100, '\n');
				
				if(answer ==0){
					ProgramIsOpened = false;
				}
				cout << endl;
			}
		}
	}
	
	cout << "BYE!!" << endl;
	
	return 0; 
}
