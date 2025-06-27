#include <vector>
#include <algorithm>
#include <stdexcept>

std::vector<int> sorted_list(const std::vector<int>& lst) {
    if (!std::all_of(lst.begin(), lst.end(), [](int i) { return std::is_integral<decltype(i)>::value; })) {
        throw std::invalid_argument("List must contain only integers");
    }

    std::vector<int> sorted_lst = lst;
    std::sort(sorted_lst.begin(), sorted_lst.end());
    return sorted_lst;
}
#include <iostream>
// Example usage of sorted_list function
// This function sorts a list of integers and handles exceptions if the input is invalid.   



int main() {
    std::vector<int> my_list = {5, 3, 8, 1, 2};
    try {
        std::vector<int> sorted = sorted_list(my_list);
        std::cout << "Sorted list: ";
        for (int i : sorted) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
} 
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
// function of sorting a list of vectors
std::vector<int> sorted_list(const std::vector<int>& lst) {
    if (!std::all_of(lst.begin(), lst.end(), [](int i) { return std::is_integral<decltype(i)>::value; })) {
        throw std::invalid_argument("List must contain only integers");
    }

    std::vector<int> sorted_lst = lst;
    std::sort(sorted_lst.begin(), sorted_lst.end());
    return sorted_lst;
}
// 实现一个二叉搜索树
class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRec(root, value);
    }
    

private:
    TreeNode* root;

    TreeNode* insertRec(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }
        if (value < node->value) {
            node->left = insertRec(node->left, value);
        } else {
            node->right = insertRec(node->right, value);
        }
        return node;
    }
};
