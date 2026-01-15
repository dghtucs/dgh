#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Top-Down Splay 核心实现
Node* splay(Node* root, int key) {
    if (!root) return nullptr;

    Node header(0); // 辅助头节点
    header.left = header.right = nullptr;
    Node* LeftTreeMax = &header;
    Node* RightTreeMin = &header;

    while (true) {
        if (key < root->key) {
            if (!root->left) break;
            if (key < root->left->key) {
                // Zig-Zig (Rotate Right)
                Node* y = root->left;
                root->left = y->right;
                y->right = root;
                root = y;
                if (!root->left) break;
            }
            // Link to Right Tree
            RightTreeMin->left = root;
            RightTreeMin = root;
            root = root->left;
        } else if (key > root->key) {
            if (!root->right) break;
            if (key > root->right->key) {
                // Zig-Zig (Rotate Left)
                Node* y = root->right;
                root->right = y->left;
                y->left = root;
                root = y;
                if (!root->right) break;
            }
            // Link to Left Tree
            LeftTreeMax->right = root;
            LeftTreeMax = root;
            root = root->right;
        } else {
            break;
        }
    }

    // Assemble
    LeftTreeMax->right = root->left;
    RightTreeMin->left = root->right;
    root->left = header.right;
    root->right = header.left;

    return root;
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    root = splay(root, key);
    if (root->key == key) return root; // 已存在

    Node* newNode = new Node(key);
    if (root->key > key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    return newNode;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;
    root = splay(root, key);
    if (key != root->key) return root; // key不存在

    Node* leftTree = root->left;
    Node* rightTree = root->right;
    delete root;

    if (!leftTree) return rightTree;
    
    // 在左子树中伸展最大节点做新根
    leftTree = splay(leftTree, key); 
    leftTree->right = rightTree;
    return leftTree;
}

int findMaxLeq(Node*& root, int x) {
    if (!root) return -1;
    // Top-Down Splay 保证最后访问的节点变为根
    root = splay(root, x);

    if (root->key <= x) return root->key;

    
    if (root->left) {
        Node* curr = root->left;
        while(curr->right) curr = curr->right;
        return curr->key;
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    char op;
    if (!(cin >> n)) return 0;
    Node* root = nullptr;

    while (n--) {
        cin >> op >> x;
        if (op == 'A') {
            root = insert(root, x);
        } else if (op == 'B') {
            root = deleteNode(root, x);
        } else if (op == 'C') {
            cout << findMaxLeq(root, x) << "\n";
        }
    }
    return 0;
}