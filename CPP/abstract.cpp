#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;


struct Node {
    Node * next;
    Node * prev;
    int value;
    int key;
    Node(Node * p, Node * n, int k, int val): prev(p), next(n), key(k), value(val) {};
    Node(int k, int val): prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {
protected:
    map < int, Node * > mp; //map the key to the node in the linked list
    int cp; //capacity
    Node *tail; // double linked list tail pointer
    Node *head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function
};

class LRUCache : public Cache {
public:
    LRUCache(int capacity) {
        cp = capacity;
        head = new Node(nullptr, tail, 0, 0);
        tail = new Node(head, nullptr, 0, 0);
    }
    void set(int key, int value) override {
        if (mp.size() == 0) {
            Node *p_new = new Node(head, tail, key, value);
            tail->prev = p_new;
            head->next = p_new;
            mp[key] = p_new;
            return;
        }
        const auto it = mp.find(key);
        if (it != mp.end()) {
            it->second->value = value;
        } else {
            Node *p_first = head->next;
            Node *p_new = new Node(head, p_first, key, value);
            head->next = p_new;
            p_first->prev = p_new;
            mp[key] = p_new;
            if (mp.size() > cp) {
                Node *p_last = tail->prev;
                int key_to_remove = p_last->key;
                Node *p_p_last = p_last->prev;
                tail->prev = p_p_last;
                p_p_last->next = tail;
                auto it = mp.find(key_to_remove);
                mp.erase(it);
                delete p_last;
                p_last = nullptr;
            }
        }
    }
    int get(int key) override {
        const auto it = mp.find(key);
        return (it == mp.end()) ? -1 : it->second->value;
    }
};

int main() {
    const int& x = 5 + 7;
    std::cout << x << std::endl;
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        } else if (command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}
