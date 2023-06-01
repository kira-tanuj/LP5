#include<iostream>
#include<stdlib.h>
#include<queue>

using namespace std;
class Node
{
    public:
        Node *left, *right;
        int data;
        Node(int data){
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class Tree
{
    Node* root = NULL;
    public:
        Node *insert(Node *root, int data){
        if(!root){
            root = new Node(data);
            return root;
        }
        if(data < root->data){
            root->left = insert(root->left,data);
        }
        else{
            root->right = insert(root->right,data);
        }
    return root;
    }

    bool bfs(Node *head,int data){
        queue<Node*> q;
        q.push(head);
        bool flag = 0;
        int qSize;

        while (!q.empty()){
            qSize = q.size();
            #pragma omp parallel for
            //creates parallel threads
            for (int i = 0; i < qSize; i++){
                Node* currNode;
                #pragma omp critical
                {
                    currNode = q.front();
                    q.pop();
                    cout<<currNode->data<<"\t";
                    if(currNode->data == data){
                // cout<<"Element Found";
                        flag = 1;
                    }
                }// prints parent Node
                #pragma omp critical
                {
                if(currNode->left)// push parent's left Node in queue
                    q.push(currNode->left);
                    if(currNode->right)
                        q.push(currNode->right);
                    }// push parent's right Node in queue
            }
        }
        // cout<<"Element Not found";
        cout<<endl;
        return flag;
    }
};
int main(){
    Node *root=NULL;
    int data;
    int n;
    char ans;
    Tree t;
    cout<<"Enter Number of Nodes : ";
    cin>>n;
    for(int i = 0; i < n; i++){
        cout<<"enter data:";
        cin>>data;
        root = t.insert(root,data);
    }
    // t.bfs(root,7);
    int search;
    cout<<"Enter Element to be search ";
    cin>>search;
    if(t.bfs(root,search)){
        cout<<"Element is present"<<endl;
    }
    else{
        cout<<"Element is not present"<<endl;
    }
    cout<<endl;
    return 0;
}