#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Book {
public:
    Book(int max_page)
        :pages_(max_page + 1) {
    }

    void ChangePages(int, int);
    double GetCheer(int) const;

private:
    unordered_map<int, int> readers_;
    vector<int> pages_;
};

void Book::ChangePages(int id, int page) {
    int& old_page = readers_[id];
    for(int i = old_page + 1; i <= page; ++i) {
        ++pages_[i];
    }
    old_page = page;
}

double Book::GetCheer(int id) const {
    double result = 0;
    auto it = readers_.find(id);
    if(it != readers_.end()) {
        if(readers_.size() == 1){
            result = 1;
        } else {
            int less_pages = readers_.size() - pages_[it->second];
            result = static_cast<double>(less_pages) / (readers_.size() - 1);
        }
    }
    return result;
}

int main() {
    const int max_page = 1000;
    Book ebook(max_page);
    int requests = 0;
    cin >> requests;
    for(int i = 0; i < requests; ++i) {
        string cmd;
        int id = 0;
        cin >> cmd >> id;
        if(cmd == "READ"sv) {
            int page = 0;
            cin >> page;
            ebook.ChangePages(id, page);
        } else if(cmd == "CHEER"sv) {
            cout << ebook.GetCheer(id) << endl;
        }
    }
    return 0;
}
