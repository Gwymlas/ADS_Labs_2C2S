#include <iostream>
#include <string>
#include <exception>

using namespace std;



class MyMap {
    struct Node {
        int key;
        string data;
        Node* left;
        Node* right;
        uint8_t height;

        Node(int key, const string& data): key(key), data(data), left(nullptr), right(nullptr), height(0) { }
    };

    Node *root;

    uint8_t height(Node* p) {
        if (p) return p->height;
        else return 0;
    }

    int balance_factor(Node* p) {
        return height(p->left) - height(p->right);
    }

    void setHeight(Node* p) {
        uint8_t height_left = height(p->left);
        uint8_t height_right = height(p->right);
        p->height = (height_left > height_right?height_left:height_right) + 1;
    }

    Node* rotateLeft(Node* p) {
        Node* q = p->right;
        p->right = q->left;
        q->left = p;
        setHeight(p);
        setHeight(q);
        return q;
    }

    Node* rotateRight(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        setHeight(p);
        setHeight(q);
        return q;
    }

    Node* balance(Node* p) {
        setHeight(p);
        if (balance_factor(p) == -2) {
            if (balance_factor(p->right) == 1)
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if(balance_factor(p) == 2) {
            if (balance_factor(p->left) == -1)
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
        return p;
    }

    Node *insert(Node* tree, int key, const string &data, bool& flag) {
        if (tree == nullptr) {
            tree = new Node(key, data);
        } else if (tree->key < key) {
            tree->right = insert(tree->right, key, data, flag);
        } else if (tree->key > key) {
            tree->left = insert(tree->left, key, data, flag);
        } else {
            tree->data = data;
            flag = false;
        }
        return balance(tree);
    }

    Node* find(Node *tree, int key) const {
        if (tree == nullptr) {
            return nullptr;
        } else if (tree->key < key) {
            return find(tree->right, key);
        } else if (tree->key > key) {
            return find(tree->left, key);
        } else return tree;
    }

    Node *findMaxElem(Node *tree) {
        if (tree->right == nullptr) {
            return tree;
        } else return findMaxElem(tree->right);
    }

    Node *deleteMaxElem(Node *tree) {
        if (tree->right == nullptr) return tree->left;
        tree->right = deleteMaxElem(tree->right);
        return balance(tree);
    }

    Node *erase(Node *tree, int key, bool& flag) {
        if (tree == nullptr) return nullptr;
        else if (tree->key < key) {
            tree->right = erase(tree->right, key, flag);
        } else if (tree->key > key) {
            tree->left = erase(tree->left, key, flag);
        } else {
            Node *left = tree->left;
            Node *right = tree->right;
            delete tree;
            if (right == nullptr) return left;
            if (left == nullptr) return right;
            Node *necessary_elem = findMaxElem(left);
            necessary_elem->left = deleteMaxElem(left);
            necessary_elem->right = right;
            flag = true;
            return balance(necessary_elem);
        }
        return balance(tree);
    }

    void printTree(Node* tree, size_t level = 0) const {
        if(tree) {
            printTree(tree->right, level + 1);
            for (size_t i = 0; i < level; ++i) {
                cout << "\t";
            }
            cout << tree->key << ": " << tree->data << " " <<endl;
            printTree(tree->left, level + 1);
        }
        else {
            for (size_t i = 0; i < level; ++i) {
                cout << "\t";
            }
            cout << "NULL" << endl;
        }
    }


    void deleteTree(Node* tree) {
        if (tree) {
            deleteTree(tree->left);
            deleteTree(tree->right);
            delete tree;
        }
    }

public:
    MyMap() {
        root = nullptr;
    }


    bool insert(int key, const string& data) {
        bool flag = true;
        root = insert(this->root, key, data, flag);
        return flag;
    }

    const string& find(int key) const {
        Node* value = find(this->root, key);
        if (value) return value->data;
        else throw exception();
    }

    bool erase(int key) {
        bool flag = false;
        root = erase(this->root, key, flag);
        return flag;
    }

    void print() const {
        printTree(root);
    }


    ~MyMap() {
        deleteTree(root);
    }
};

int main() {

    MyMap m;
    m.insert(22, "323");
    m.insert(32, "fgfg");
    m.insert(11, "ewsdfas");
    m.insert(25, "dfv");
    m.insert(26, "sdfvd");
    m.insert(27, "ergberb");

    m.insert(24, "ergbfgferb");
    m.insert(23, "ergberb");
    m.insert(64, "345234");
    m.print();

    cout << "---------------" << endl;

    m.erase(22);
    m.erase(11);
    m.erase(25);
    m.erase(64);
    m.erase(27);
    m.erase(1111);
    m.print();
    return 0;
}
