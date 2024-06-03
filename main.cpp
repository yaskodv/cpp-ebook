#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
//example of code review
using namespace std;

class UserManager {
public:
    void AddUserInformation(int user, int page) {
        if (user_stat.capacity() <= user) {
            user_stat.resize(user * 2);
        }

        int user_prev_page = user_stat[user];
        //увеличиваем число пользователей в системе, если ранее для этого пользователя не было команд READ (число прочитанных страниц = 0)
        if (user_prev_page == 0) {
            ++user_count;
        }

        user_stat[user] = page;

        if (page_stat.capacity() <= page) {
            page_stat.resize(page * 2);
        }
        // вносим изменения в статистику прочитанных пользователями страниц
        if (user_prev_page > 0) {
            --page_stat[user_prev_page];
        }
        if (page > 0) {
            ++page_stat[page];
        }
    }

    void CheerUser(int user) {
        double answer = 0;
        //если пользователя не было в системе, и его индекса вообще нет в uer_stat
        if (user_stat.size() <= user) {
            answer = 0;
        //если для пользователя не было команд READ (число прочитанных страниц = 0)
        } else if (user_stat.at(user) == 0) {
            answer = 0;
        // если пользователь есть в системе, но он один
        } else if (user_count == 1) {
            answer = 1;
        } else {
            answer = 1.0 * accumulate(page_stat.begin(), page_stat.begin() + user_stat.at(user), 0) / (user_count - 1);
        }
        cout << setprecision(6) << answer << endl;
    }

private:
    vector<int> user_stat; // элемент вектора с индексом [user] хранит количество страниц, прочитанных пользователем номер user
    vector<int> page_stat; // элемент вектора с индексом [page] хранит число пользователей, прочитавших page страниц
    int user_count = 0; //общее количество пользователей, данные о которых есть в UserManager (для ускорения выдачи ответа)
};



int main() {

    UserManager user_manager;

    int command_count;
    cin >> command_count;

    string command;

    for (int i = 0; i < command_count; ++i) {
        cin >> command;
        if (command == "READ"s) {
            int user;
            int page;
            cin >> user >> page;
            user_manager.AddUserInformation(user, page);
        } else if (command == "CHEER"s) {
            int user;
            cin >> user;
            user_manager.CheerUser(user);
        }
    }
}
