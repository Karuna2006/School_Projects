#include <iostream>
#include <string>

using namespace std;

// Node structure for the binary tree
struct Node {
    string description;
    bool hasTreasure;
    Node* left;
    Node* right;
   
    Node(string desc, bool treasure) {
        description = desc;
        hasTreasure = treasure;
        left = right = NULL;
    }
};

// Function to play the game
void playGame(Node* root) {
    Node* current = root;
    string choice;

    while (current != NULL) {
        cout << current->description << endl;
        if (current->hasTreasure) {
            cout << "🎉 You found the treasure! Game Over! 🎉" << endl;
            return;
        }

        cout << "Choose Left (L) or Right (R): ";
        cin >> choice;

        if (choice == "L" || choice == "l")
            current = current->left;
        else if (choice == "R" || choice == "r")
            current = current->right;
        else
            cout << "Invalid choice! Try again." << endl;
    }

    cout << "You reached a dead end! Game Over! ❌" << endl;
}

int main() {
    // Creating the map as a binary tree
    Node* root = new Node("You are at the starting point of the treasure hunt.", false);
    root->left = new Node("oh no you have 2 lives left", false);
    root->right = new Node("hurray", false);
   
    root->left->left = new Node("oh no you have 1 lives left!", false);
    root->left->right = new Node("hurray", false);
    root->right->left = new Node("hurray", false);
    root->right->right = new Node("oh no you have 1 lives left!", false);

    root->left->left->left = new Node("deadend", false);
    root->left->right->left = new Node("hurray", false);
    root->right->left->left= new Node("hurray", false);
    root->right->left->right= new Node("hurray", false);
    root->right->right->left = new Node("hurray", false);
    root->left->left->right = new Node("hurray", false);
    root->left->right->right = new Node("hurray", false);
    root->right->right->right = new Node("deadend", false);

    // root->left->left->left->left = new Node("oh no you have 2 lives left!", false);
    root->left->right->left->left = new Node("deadend", false);
    root->right->left->left->left = new Node("deadend", false);
    root->right->right->left->left = new Node("treasure", true);
    root->left->left->right->left = new Node("deadende", false);
    root->left->right->right->left = new Node("Hurry", true);
    root->right->left->right->left = new Node("hurry", true);
    root->right->right->right->left = new Node("deadend", true);
    root->left->left->left->right = new Node("deadend", false);
    root->left->right->left->right = new Node("hurry", true);
    root->right->left->left->right = new Node("hurry", true);
    root->right->right->left->right = new Node("deadends", false);
    root->left->left->right->right = new Node("Hurry", true);
    root->left->right->right->right = new Node("deadend", false);
    root->right->left->right->right = new Node("deadend", false);
    root->right->right->right->right = new Node("deadend", false);

    // Start the game
    playGame(root);

    return 0;
}
