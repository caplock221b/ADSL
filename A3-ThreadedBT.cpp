//Create inorder threaded binary tree and perform inorder, preorder traversal.
#include <iostream>
using namespace std;

class Node{
private:
    int data;
    Node *left;
    Node *right;
    int rflag;
public:
    Node(int data){
        this->data = data;
        left = NULL;
        right = NULL;
        rflag = 0;
    }
    friend class ThreadedBT;
};

class ThreadedBT{
private:
    Node *root;
public:
    ThreadedBT(){
        root = NULL;
    }
    void insertNode(int data){
        Node *p = new Node(data);
        if(root == NULL)
            root = p;
        else{
            Node *q = root;
            int flag = 0;
            while(flag == 0){
                if(p->data < q->data){
                    if(q->left==NULL){
                        p->right = q;
                        p->rflag = 1;
                        q->left = p;
                        flag = 1;
                    }
                    else
                        q = q->left;
                }
                else if(p->data > q->data){
                    if(q->rflag == 1){
                        p->right = q->right;
                        p->rflag = 1;
                        q->right = p;
                        q->rflag = 0;
                        flag = 1;
                    }
                    else if(q->right == NULL){
                        q->right = p;
                        flag = 1;
                    }
                    else
                        q = q->right;
                }
                else{
                    cout<<"The data already exists in the tree. Duplicates are not allowed!"<<endl;
                    delete p;
                    flag = 1;
                }
            }
        }
    }
    void inorderTraversal(){
        Node *p = root;
        int flag = 0;
        while(flag == 0){
            while(p->left!=NULL)
                p = p->left;
            cout<<p->data<<" ";
            while(p->rflag == 1){
                p = p->right;
                cout<<p->data<<" ";
            }
            if(p->right!=NULL)
                p = p->right;
            else
                flag = 1;
        }
        cout<<"\n";
    }
    void preorderTraversal(){
        Node *p = root;
        while(p!=NULL){
            cout<<p->data<<" ";
            if(p->left!=NULL)
                p = p->left;
            else{
                while(p->rflag == 1)
                    p = p->right;
                p = p->right;
            }
        }
        cout<<"\n";
    }
};

int main(){
    ThreadedBT ob;
    char ans;
    int data, choice;
    do{
        cout<<"Menu :\n1. Insert a node in the threaded binary tree\n2. Display the threaded binary tree\nEnter your choice 1 or 2 : ";
        cin>>choice;
        switch(choice){
        case 1:
            cout<<"Enter data to be inserted : ";
            cin>>data;
            ob.insertNode(data);
            break;
        case 2:
            cout<<"\n\t1. Display using Inorder Traversal\n\t2. Display using Preorder Traversal\n\tEnter your choice 1 or 2 : ";
            cin>>choice;
            switch(choice){
            case 1:
                cout<<"The threaded binary tree in inorder form is : ";
                ob.inorderTraversal();
                break;
            case 2:
                cout<<"The threaded binary tree in preorder form is : ";
                ob.preorderTraversal();
                break;
            default:
                cout<<"Invalid choice! Please enter valid choice next time."<<endl;
                break;
            }
            break;
        default:
            cout<<"Please enter valid choice next time."<<endl;
            break;
        }
        cout<<"Perform another operation? (Enter y for yes or n for no) : ";
        cin>>ans;
        cout<<"\n";
    }while(ans == 'y');
    return 0;
}
