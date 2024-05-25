#ifndef BINARY_SAERCH_TREE
#define BINARY_SAERCH_TREE

#include <iostream>
#include <vector>
#include <queue>

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

    // Helper function to find height of tree
    int findHeight(BSTNode* node);

    // Helper function to check if tree is balanced
    bool isBalanced(BSTNode* node);

    // Helper function to find Lowest Common Ancestor
    BSTNode* findLCA(BSTNode* node,int valA, int valB);


    // Helper function to check if the tree is valid
    bool isValidBST(BSTNode* node, BSTNode* minNode = nullptr, BSTNode* maxNode = nullptr);

public:
    BSTNode* root;  // Root node of the BST

    // Constructor to initialize an empty BST
    BST() : root(nullptr) {};

    // Public function to insert a value recursively
    void insert(int valA);

    // Public function to insert a value iteratively
    void insertIterative(int valA);

    // Public function to search a value recursively

    // Helper function to count number of node in a tree
    int countNodes(BSTNode* node);
    
    BSTNode* search(int valA);

    // Public function to search a value iteratively
    BSTNode* searchIterative(int valA);

    // Public function to delete a node
    void deleteNode(int valA);

    // Public function to perform in-order traversal
    void inOrderTraversal();

    // Public function to perform pre-order traversal
    void preOrderTraversal();

    // Public function to perform post-order traversal
    void postOrderTraversal();

    // Public function to find min value in BST
    int findMin();

    // Public function to find max value in BST
    int findMax();

    // Public function to find height of tree
    int findHeight();

    // Public function to check if tree is balanced
    bool isBalanced();

    // Public function to count number of node in a tree
    int countNodes();

    // Public function to find Lowest Common Ancestor
    BSTNode* findLCA(int valA, int valB);

    // Public function to check if the tree is valid
    bool isValidBST();
   
    // Public function to perfom level order traversal
    void levelOrderTraversal();




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
void BST::deleteNode(int valA) {
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

// Public function to find min value in BST
int BST::findMin() {
    // Check if the tree is empty
    if (root == nullptr) {
        throw runtime_error("Tree is empty. Cannot find minimum value.");
    }

    // Initialize a pointer to traverse the tree, starting from the root
    BSTNode* currentNode = root;
    
    // Traverse the left subtree to find the minimum value
    while (currentNode->left != nullptr) {
        currentNode = currentNode->left; // Move to the left child
    }

    // Return the value of the leftmost (minimum) node
    return currentNode->val;
}

// Public function to find max value in BST
int BST::findMax() {
    // Check if the root of the BST is null
     if (root == nullptr) {
        throw runtime_error("Tree is empty. Cannot find minimum value.");
    }

    // Initialize a pointer to traverse the tree, starting at the root
    BSTNode* currentNode = root;
    
    // Traverse the tree to the rightmost node (which has the maximum value)
    while (currentNode->right != nullptr) {
        currentNode = currentNode->right;
    }

    // Return the value of the rightmost node
    return currentNode->val;
}

// Helper function to find height of tree
int BST::findHeight(BSTNode* node) {
    // Check if the current node is null
    if(node == nullptr) {
        // If the node is null, return 0 to indicate an empty subtree
        return 0;
    }

    // Recursively find the height of the left subtree
    int leftSubTreeHeight = findHeight(node->left);

    // Recursively find the height of the right subtree
    int rightSubTreeHeight = findHeight(node->right);

    // Return the maximum height of the left and right subtrees, plus 1
    return max(leftSubTreeHeight, rightSubTreeHeight) + 1;
}

// Helper function to check if tree is balanced
bool BST::isBalanced(BSTNode* node) {
    // If the current node is null, it is balanced
    if(node == nullptr) {
        return true;
    }

    // Calculate the height of the left subtree
    int leftSubtreeHeight = findHeight(node->left);

    // Calculate the height of the right subtree
    int rightSubtreeHeight = findHeight(node->right);

    // Check if the absolute difference between the heights of left and right subtrees is at most 1,
    // and recursively check if both left and right subtrees are balanced
    return abs(leftSubtreeHeight - rightSubtreeHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

// Helper function to count number of node in a tree
int BST::countNodes(BSTNode* node) {
    if(node == nullptr){
        return 0;
    }

    return 1 + countNodes(node->left) + countNodes(node->right);
}

// Public function to find height of tree
int BST::findHeight() {
    return findHeight(root);
}

// Public function to check if tree is balanced
bool BST::isBalanced() {
  return isBalanced(root);
}

// Public function to count number of node in a tree
int BST::countNodes() {
    return countNodes(root);
}

// Helper function to find Lowest Common Ancestor
BSTNode* BST::findLCA(BSTNode* node, int valA, int valB) {
    // If the current node is null, return null (base case for recursion)
    if (node == nullptr) {
        return nullptr;
    }

    // If both values are less than the current node's value,
    // the LCA must be in the left subtree
    if (node->val > valA && node->val > valB) {
        return findLCA(node->left, valA, valB);
    }

    // If both values are greater than the current node's value,
    // the LCA must be in the right subtree
    if (node->val < valA && node->val < valB) {
        return findLCA(node->right, valA, valB);
    }

    // If one value is less than or equal to the current node's value and the other is greater than or equal to it,
    // then the current node is the LCA
    return node;
}
// Public function to find Lowest Common Ancestor
BSTNode* BST::findLCA(int valA, int valB) {
   return findLCA(root, valA,valB);
}

 // Helper function to check if the tree is valid
bool BST::isValidBST(BSTNode* node, BSTNode* minNode, BSTNode* maxNode) {
    // If the current node is null, the subtree is valid (base case for recursion)
    if (node == nullptr) {
        return true;
    }

    // If the current node's value is not within the valid range, return false
    if ((minNode != nullptr && node->val <= minNode->val) || (maxNode != nullptr && node->val >= maxNode->val)) {
        return false;
    }

    // Recursively validate the left and right subtrees
    return isValidBST(node->left, minNode, node) && isValidBST(node->right, node, maxNode);
}

 // Public function to check if the tree is valid

 bool BST::isValidBST() {
    return isValidBST(root);
 }

// Public function to perfom level order traversal
void BST::levelOrderTraversal() {
    // If the tree is empty, print a message and return
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return;
    }

    // Create a queue to hold nodes to visit, starting with the root node
    queue<BSTNode*> q;
    q.push(root);

    // While there are still nodes to visit
    while (!q.empty()) {
        // Get the front node from the queue and remove it
        BSTNode* currentNode = q.front();
        q.pop();

        // Print the value of the current node
        cout << currentNode->val << " ";

        // If the left child exists, add it to the queue
        if (currentNode->left != nullptr) {
            q.push(currentNode->left);
        }

        // If the right child exists, add it to the queue
        if (currentNode->right != nullptr) {
            q.push(currentNode->right);
        }
    }

    // Print a newline character after all nodes have been visited
    cout<< endl;   
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