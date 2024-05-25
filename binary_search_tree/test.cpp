#include <cassert>
#include "BST.h"
#include <functional>
#include <vector>
#include <iostream>
#include <sstream>


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

    tree.deleteNode(5);
    assert(tree.search(5) == nullptr);

    tree.deleteNode(15);
    assert(tree.search(15) == nullptr);

    tree.deleteNode(10);
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

void testFindMin() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(18);

    assert(tree.findMin() == 3);
}
void testFindMax() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(18);

    assert(tree.findMax() == 18);
}


void testFindHeight() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(18);

    assert(tree.findHeight() == 3);
}


void testIsBalanced() {
    BST balancedTree;
    balancedTree.insert(10);
    balancedTree.insert(5);
    balancedTree.insert(15);
    balancedTree.insert(3);
    balancedTree.insert(7);
    balancedTree.insert(13);
    balancedTree.insert(18);

    assert(balancedTree.isBalanced() == true);

    BST unBalancedTree;
    balancedTree.insert(5);
    balancedTree.insert(10);
    balancedTree.insert(15);
    balancedTree.insert(20);
    balancedTree.insert(25);
    balancedTree.insert(30);

    assert(balancedTree.isBalanced() == false);
}


void testCountNodes() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(18);

    assert(tree.countNodes() == 7);
}
void testFindLCA() {
    BST tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(30);
    tree.insert(25);
    tree.insert(35);

    BSTNode* lca = tree.findLCA(5, 15);
    assert(lca != nullptr && lca->val == 10);

    lca = tree.findLCA(5, 30);
    assert(lca != nullptr && lca->val == 20);

    lca = tree.findLCA(25, 35);
    assert(lca != nullptr && lca->val == 30);

    lca = tree.findLCA(5, 10);
    assert(lca != nullptr && lca->val == 10);

    lca = tree.findLCA(10, 30);
    assert(lca != nullptr && lca->val == 20);
}

void testIsValidBST() {
    BST tree;

   
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);

    
    assert(tree.isValidBST() == true);

    // Insert nodes to form an invalid BST
    // Manually create an invalid BST by breaking the BST property
    BSTNode* root = new BSTNode(20);
    root->left = new BSTNode(10);
    root->right = new BSTNode(30);
    root->left->left = new BSTNode(5);
    root->left->right = new BSTNode(25); // This makes the tree invalid
    root->right->left = new BSTNode(25);
    root->right->right = new BSTNode(35);

    tree.root = root;

    // Test that the tree is not a valid BST
    assert(tree.isValidBST() == false);

    
}

void testLevelOrderTraversal() {
    
    BST tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    
    ostringstream capturedOutput;
    streambuf* oldCoutBuffer = cout.rdbuf(capturedOutput.rdbuf());
    
    tree.levelOrderTraversal();

    cout.rdbuf(oldCoutBuffer);

    string output = capturedOutput.str();

    string expectedOutput = "5 3 7 2 4 6 8 \n";

    assert(output == expectedOutput);  
}



int main() {
    testInsert();
    testSearch();
    testDelete();
    testInOrderTraversal();
    testPreOrderTraversal();
    testPostOrderTraversal();
    testFindMin();
    testFindMax();
    testFindHeight();
    testIsBalanced();
    testCountNodes();
    testFindLCA();
    testLevelOrderTraversal();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
