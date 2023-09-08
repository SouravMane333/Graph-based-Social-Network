// Graph based social network
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

class SocialNetwork {
private:
    unordered_map<string, set<string> > network;

public:
    void addFriend(const string& user, const string& frnd) {
        network[user].insert(frnd);
        network[frnd].insert(user);
    }

    void removeFriend(const string& user, const string& frnd) {
        network[user].erase(frnd);
        network[frnd].erase(user);
    }

    void suggestConnections(const string& user) {
        set<string> suggestions;

        for (const string& frnd : network[user]) {
            for (const string& suggestedFrnd : network[frnd]) {
                if (suggestedFrnd != user && network[user].find(suggestedFrnd) == network[user].end()) {
                    suggestions.insert(suggestedFrnd);
                }
            }
        }

        cout << "Suggestions for " << user << ":\n";
        for (const string& suggestedFrnd : suggestions) {
            cout << suggestedFrnd << "\n";
        }
    }

    void findShortestPath(const string& start, const string& end) {
        unordered_map<string, string> parent;
        queue<string> q;
        set<string> visited;

        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            if (current == end) {
                vector<string> path;
                string node = end;

                while (node != start) {
                    path.push_back(node);
                    node = parent[node];
                }

                path.push_back(start);

                cout << "Shortest path between " << start << " and " << end << ":\n";
                for (int i = path.size() - 1; i >= 0; --i) {
                    cout << path[i] << " ";
                }
                cout << "\n";
                return;
            }

            for (const string& frnd : network[current]) {
                if (visited.find(frnd) == visited.end()) {
                    q.push(frnd);
                    visited.insert(frnd);
                    parent[frnd] = current;
                }
            }
        }

        cout << "No path found between " << start << " and " << end << ".\n";
    }

    void displayMutualFriends(const string& user1, const string& user2) {
        set<string> mutualFriends;

        for (const string& frnd : network[user1]) {
            if (network[user2].count(frnd)) {
                mutualFriends.insert(frnd);
            }
        }

        cout << "Mutual friends between " << user1 << " and " << user2 << ":\n";
        for (const string& mutualFrnd : mutualFriends) {
            cout << mutualFrnd << "\n";
        }
    }
};

int main() {
    SocialNetwork network;
    string command;

    while (true) {
        cout << "Enter command (add, remove, suggest, path, mutual, quit): ";
        cin >> command;

        if (command == "add") {
            string user, frnd;
            cout << "Enter usernames (user friend): ";
            cin >> user >> frnd;
            network.addFriend(user, frnd);
        } else if (command == "remove") {
            string user, frnd;
            cout << "Enter usernames (user friend): ";
            cin >> user >> frnd;
            network.removeFriend(user, frnd);
        } else if (command == "suggest") {
            string user;
            cout << "Enter username: ";
            cin >> user;
            network.suggestConnections(user);
        } else if (command == "path") {
            string start, end;
            cout << "Enter start and end usernames: ";
            cin >> start >> end;
            network.findShortestPath(start, end);
        } else if (command == "mutual") {
            string user1, user2;
            cout << "Enter usernames (user1 user2): ";
            cin >> user1 >> user2;
            network.displayMutualFriends(user1, user2);
        } else if (command == "quit") {
            break;
        } else {
            cout << "Invalid command. Try again.\n";
        }
    }

    return 0;
}
