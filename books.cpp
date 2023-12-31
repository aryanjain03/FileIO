#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;
class Book{
    private:
        int book_no;
        string book_name, author_name;
    public:
        void display_books(){
            cout << endl;
            fstream myFile;
            myFile.open("books.txt", ios::in); // read
            
            string line, book_name, author_name;
            cout << std::left << std::setw(40) << "Book Name" << std::right << std::setw(3) << " Author Name" << endl << endl;
            while(!myFile.eof()){
                getline(myFile, line);
                int i;
                for(i = 0; line[i] != ','; i++) book_name += line[i];
                i++;
                while(i < line.size()){
                    author_name += line[i];
                    i++;
                }
                cout << std::left << std::setw(40) << book_name << std::right << std::setw(3) << author_name << endl;
                line.clear();
                book_name.clear();
                author_name.clear();
            }
            cout << endl;
            myFile.close();
        }
        void add_book(string book_name, string author_name){
            ofstream out("books.txt", ios::app); // write
            out << endl << book_name << ", " << author_name;
        }
        string find_author(string book_name){
            fstream myFile;
            myFile.open("books.txt", ios::in); // read
            string line, book, author;
            bool found = false;
            while(!myFile.eof() && !found){
                getline(myFile, line);
                int i;
                for(i = 0; line[i] != ','; i++) book += line[i];
                i += 2;
                if(book == book_name){
                    found = true;
                    while(i < line.size()){
                        author += line[i];
                        i++;
                    }
                    return author;
                }
                line.clear();
                book.clear();                
            }
            myFile.close();
            return "-1";
        }
        pair<int, int> get_line_no_and_line_size(string book_name){
            fstream myFile;
            string line, book, new_line;
            myFile.open("books.txt", ios::in);
            int line_no = 0; // 1-based
            while(!myFile.eof()){
                line_no++;
                getline(myFile, line);
                int i;
                for(i = 0; line[i] != ','; i++) book += line[i];
                i += 2;
                if(book == book_name){
                    break;
                }
                line.clear();
                book.clear();
            }
            myFile.close();
            return make_pair(line_no, line.size());
        }
        // void modify_book(string book_name, string new_book_name, string new_author_name){ // incomplete
        //     fstream myFile;
        //     string line, book, new_line;
        //     myFile.open("books.txt", ios::in | ios::out);
        //     int line_no = 0, req_line_no = get_line_no_and_line_size(book_name).first, req_line_size = get_line_no_and_line_size(book_name).second;
        //     while(!myFile.eof()){
        //         if(line_no == req_line_no - 1){
        //             break;
        //         }
        //         line_no++;
        //         line.clear();
        //         getline(myFile, line);
        //     }
        //     cout << "\r";
        //     if((new_book_name + ", " + new_author_name).size() >= req_line_size) myFile << new_book_name << ", " << new_author_name;
        //     else{
        //         myFile << new_book_name << ", " << new_author_name;
        //         for(int i = (new_book_name + ", " + new_author_name).size(); i < req_line_size; i++) myFile << ' ';
        //         myFile << endl;
        //     }
        //     myFile.close();
        // }
};
int main(){
    string choice;
    while(true){
        cout << "Press a number : \n1. Display books\n2. Add book\n3. Modify book\n4. Find author\n5. Exit\n";
        getline(cin, choice);
        if(choice == "1"){
            (new Book())->display_books();
        }
        else if(choice == "2"){ 
            string book_name, author_name;
            cout << "Enter book name : \n";
            cin >> book_name;
            cout << "Enter author name : \n";
            cin >> author_name;
            (new Book())->add_book(book_name, author_name); 
            cout << "Book added successfully !\n";
        }   
        else if(choice == "3"){
            string book_name, author_name; 
            cout << "Enter name of book to be modified : \n";
            cin >> book_name;
            author_name = (new Book())->find_author(book_name);
            if(author_name == "-1") cout << "Book not present in library !\n";
            else{
                string new_book_name, new_author_name;
                cout << "Enter new book name : \n";
                cin >> new_book_name;
                cout << "Enter new author name : \n";
                cin >> new_author_name;
                (new Book())->modify_book(book_name, new_book_name, new_author_name);
                cout << "Book modified successfully !\n";
            }
        }
        else if(choice == "4"){
            string book_name, author_name;
            cout << "Enter book name : \n";
            cin >> book_name;
            author_name = (new Book())->find_author(book_name);
            author_name != "-1" ? cout << author_name << endl : cout << "Book not present in library !\n";
        }
        else if(choice == "5"){
            cout << "Thank you for using my library !\n";
            break;
        }
        else cout << "Invalid input !" << endl;
    }
}
