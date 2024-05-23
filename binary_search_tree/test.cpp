#include <cassert>
#include "BST.h"
#include <functional>
#include <vector>

using namespace std;

void testInsert() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    assert(tree.root != nullptr);
    assert(tree.root->val == 10);
    assert(tree.root->left != nullptr && tree.root->left->val == 5);
    assert(tree.root->right != nullptr && tree.root->right->val == 15);
}

void testSearch() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    BSTNode* foundNode = tree.search(10);
    assert(foundNode != nullptr && foundNode->val == 10);

    foundNode = tree.search(5);
    assert(foundNode != nullptr && foundNode->val == 5);

    foundNode = tree.search(15);
    assert(foundNode != nullptr && foundNode->val == 15);

    foundNode = tree.search(20);
    assert(foundNode == nullptr);
}

void testDelete() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(18);

    tree.deletNode(5);
    assert(tree.search(5) == nullptr);

    tree.deletNode(15);
    assert(tree.search(15) == nullptr);

    tree.deletNode(10);
    assert(tree.search(10) == nullptr);
    assert(tree.root != nullptr && tree.root->val == 13); // New root should be the inorder successor
}

void testInOrderTraversal() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(18);

    vector<int> expected = {3, 5, 7, 10, 13, 15, 18};
    vector<int> result;
    function<void(BSTNode*)> inOrder = [&](BSTNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            result.push_back(node->val);
            inOrder(node->right);
        }
    };
    inOrder(tree.root);

    assert(result == expected);
}

void testPreOrderTraversal() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(18);

    vector<int> expected = {10, 5, 3, 7, 15, 13, 18};
    vector<int> result;
    function<void(BSTNode*)> preOrder = [&](BSTNode* node) {
        if (node != nullptr) {
            result.push_back(node->val);
            preOrder(node->left);
            preOrder(node->right);
        }
    };
    preOrder(tree.root);

    assert(result == expected);
}

void testPostOrderTraversal() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(18);

    vector<int> expected = {3, 7, 5, 13, 18, 15, 10};
    vector<int> result;
    function<void(BSTNode*)> postOrder = [&](BSTNode* node) {
        if (node != nullptr) {
            postOrder(node->left);
            postOrder(node->right);
            result.push_back(node->val);
        }
    };
    postOrder(tree.root);

    assert(result == expected);
}

int main() {
    testInsert();
    testSearch();
    testDelete();
    testInOrderTraversal();
    testPreOrderTraversal();
    testPostOrderTraversal();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
