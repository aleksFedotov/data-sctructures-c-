#ifndef BINARY_SAERCH_TREE
#define BINARY_SAERCH_TREE

#include <iostream>
#include <vector>

using namespace std;

// Class representing a node in the BST
class BSTNode {
public:
    int val;          // Value of the node
    BSTNode* right;   // Pointer to the right child
    BSTNode* left;    // Pointer to the left child

    // Constructor to initialize a node
    BSTNode(int valA) : val(valA), right(nullptr), left(nullptr) {};
};

// Class representing the Binary Search Tree (BST)
class BST {
private:
    // Helper function for recursive insertion
    BSTNode* insert(BSTNode* node, int valA);

    // Helper function for recursive search
    BSTNode* search(BSTNode* node, int valA);

    // Helper function for recursive deletion
    BSTNode* deleteNode(BSTNode* node, int valA);

    // Helper function to find the in-order successor
    BSTNode* findInorderSuccessor(BSTNode* node);

    // Helper function for in-order traversal
    void inOrderTraversal(BSTNode* node);

    // Helper function for pre-order traversal
    void preOrderTraversal(BSTNode* node);

    // Helper function for post-order traversal
    void postOrderTraversal(BSTNode* node);

    // Helper function to delete the entire tree
    void deleteTree(BSTNode* node);

public:
    BSTNode* root;  // Root node of the BST

    // Constructor to initialize an empty BST
    BST() : root(nullptr) {};

    // Public function to insert a value recursively
    void insert(int valA);

    // Public function to insert a value iteratively
    void insertIterative(int valA);

    // Public function to search a value recursively
    BSTNode* search(int valA);

    // Public function to search a value iteratively
    BSTNode* searchIterative(int valA);

    // Public function to delete a node
    void deletNode(int valA);

    // Public function to perform in-order traversal
    void inOrderTraversal();

    // Public function to perform pre-order traversal
    void preOrderTraversal();

    // Public function to perform post-order traversal
    void postOrderTraversal();

    // Destructor to delete the entire BST
    ~BST();
};

// Recursive insert function
BSTNode* BST::insert(BSTNode* node, int valA) {
    if (node == nullptr) {
        return new BSTNode(valA);  // Create a new node if the current node is null
    }
    if (valA <= node->val) {
        node->left = insert(node->left, valA);  // Recursively insert in the left subtree
    } else {
        node->right = insert(node->right, valA);  // Recursively insert in the right subtree
    }
    return node;
}

// Iterative insert function
void BST::insertIterative(int valA) {
    if (root == nullptr) {
        root = new BSTNode(valA);  // Create a new root if the tree is empty
        return;
    }
    BSTNode* parent = nullptr;
    BSTNode* currentNode = root;
    while (currentNode != nullptr) {
        parent = currentNode;
        if (valA <= currentNode->val) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }
    if (valA <= parent->val) {
        parent->left = new BSTNode(valA);
    } else {
        parent->right = new BSTNode(valA);
    }
}

// Recursive search function
BSTNode* BST::search(BSTNode* node, int valA) {
    if (node == nullptr || node->val == valA) {
        return node;  // Return the node if found or if reached the end
    }
    if (valA <= node->val) {
        return search(node->left, valA);  // Recursively search in the left subtree
    }
    return search(node->right, valA);  // Recursively search in the right subtree
}

// Iterative search function
BSTNode* BST::searchIterative(int valA) {
    BSTNode* currentNode = root;
    while (currentNode != nullptr) {
        if (currentNode->val == valA) {
            return currentNode;  // Return the node if found
        }
        if (valA <= currentNode->val) {
            currentNode = currentNode->left;  // Move to the left subtree
        } else {
            currentNode = currentNode->right;  // Move to the right subtree
        }
    }
    return nullptr;  // Return null if not found
}

// Recursive delete function
BSTNode* BST::deleteNode(BSTNode* node, int valA) {
    if (node == nullptr) {
        return node;  // Return null if the node is not found
    }

    if (valA < node->val) {
        node->left = deleteNode(node->left, valA);  // Recursively delete in the left subtree
    } else if (valA > node->val) {
        node->right = deleteNode(node->right, valA);  // Recursively delete in the right subtree
    } else {
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;  // Return the right child if the left child is null
        } else if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;  // Return the left child if the right child is null
        }

        // Node with two children
        BSTNode* inorderSuccessor = findInorderSuccessor(node->right);
        node->val = inorderSuccessor->val;
        node->right = deleteNode(node->right, inorderSuccessor->val);
    }
    return node;
}

// Helper function to find the in-order successor
BSTNode* BST::findInorderSuccessor(BSTNode* node) {
    BSTNode* currentNode = node;
    while (currentNode != nullptr && currentNode->left != nullptr) {
        currentNode = currentNode->left;
    }
    return currentNode;
}

// Public function to insert a value recursively
void BST::insert(int valA) {
    root = insert(root, valA);
}

// Public function to search a value recursively
BSTNode* BST::search(int valA) {
    return search(root, valA);
}

// Public function to delete a node
void BST::deletNode(int valA) {
    root = deleteNode(root, valA);
}

// Helper function for in-order traversal
void BST::inOrderTraversal(BSTNode* node) {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        cout << node->val << " ";
        inOrderTraversal(node->right);
    }
}

// Helper function for pre-order traversal
void BST::preOrderTraversal(BSTNode* node) {
    if (node != nullptr) {
        cout << node->val << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

// Helper function for post-order traversal
void BST::postOrderTraversal(BSTNode* node) {
    if (node != nullptr) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        cout << node->val << " ";
    }
}

// Public function to perform in-order traversal
void BST::inOrderTraversal() {
    inOrderTraversal(root);
    cout << endl;
}

// Public function to perform pre-order traversal
void BST::preOrderTraversal() {
    preOrderTraversal(root);
    cout << endl;
}

// Public function to perform post-order traversal
void BST::postOrderTraversal() {
    postOrderTraversal(root);
    cout << endl;
}

// Destructor to delete the entire BST
BST::~BST() {
    deleteTree(root);
}

// Helper function to delete the entire tree
void BST::deleteTree(BSTNode* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

#endif //BINARY_SAERCH_TREE