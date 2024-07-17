#include <iostream>
using namespace std;

struct node {
    node* left;
    node* right;
    int data;
};

node* insert(node* root, int val) {
    if (root == NULL) {
        node* newnode = new node();
        newnode->data = val;
        newnode->left = newnode->right = NULL;
        return newnode;
    }
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);

    return root;
}

node* min(node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

node* max(node* root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

node* del_from_bst(node* root, int val) {
    if (root == NULL)
        return root;

    if (val < root->data)
        root->left = del_from_bst(root->left, val);
    else if (val > root->data)
        root->right = del_from_bst(root->right, val);
    else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        } else if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        } else {
            node* success = min(root->right);
            root->data = success->data;
            root->right = del_from_bst(root->right, success->data);
        }
    }
    return root;
}

void inorder(node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(node* root) {
    if (root == NULL)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

node* search(node* root, int val) {
    if (root == NULL || root->data == val)
        return root;
    if (val < root->data)
        return search(root->left, val);
    return search(root->right, val);
}

int main() {
    cout << "no of nodes" << endl;
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    int dell;
    cout << "del node ???" << endl;
    cin >> dell;
    root = del_from_bst(root, dell);

    cout << "min node is: " << min(root)->data << endl;
    cout << "max node is: " << max(root)->data << endl;

    cout << "inorder is: ";
    inorder(root);
    cout << endl;
    cout << "postorder is: ";
    postorder(root);
    cout << endl;
    cout << "preorder is: ";
    preorder(root);
    cout << endl;

    int data;
    cout << "Enter value to search: ";
    cin >> data;
    if (search(root, data))
        cout << "Value found.\n";
    else
        cout << "Value not found.\n";

    return 0;
}

