#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Video
{
    int id;
    string name;
    string link;
    string genre;

    Video() : id(0), name(""), link(""), genre("") {}

    Video(int _id, const string &_name, const string &_link, const string &_genre)
        : id(_id), name(_name), link(_link), genre(_genre) {}
};

struct SplayTreeNode
{
    Video video;
    SplayTreeNode *left;
    SplayTreeNode *right;

    SplayTreeNode(const Video &v) : video(v), left(nullptr), right(nullptr) {}
};

class SplayTree
{
public:
    SplayTree() : root(nullptr) {}

    void insert(const Video &video)
    {
        root = insert(root, video);
        root = splay(root, video.id);
    }

    Video *find(int id)
    {
        root = splay(root, id);
        if (root && root->video.id == id)
        {
            return &root->video;
        }
        return nullptr;
    }

    void printTree() const
    {
        printTree(root, 0);
    }

    vector<Video> traverse() const
    {
        vector<Video> result;
        traverse(root, result);
        return result;
    }

    void traverse(SplayTreeNode *node, vector<Video> &result) const
    {
        if (node)
        {
            traverse(node->left, result);
            result.push_back(node->video);
            traverse(node->right, result);
        }
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

private:
    SplayTreeNode *root;

    SplayTreeNode *rightRotate(SplayTreeNode *x)
    {
        SplayTreeNode *y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    SplayTreeNode *leftRotate(SplayTreeNode *x)
    {
        SplayTreeNode *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    SplayTreeNode *splay(SplayTreeNode *root, int id)
    {
        if (!root || root->video.id == id)
            return root;

        if (root->video.id > id)
        {
            if (!root->left)
                return root;

            if (root->left->video.id > id)
            {
                root->left->left = splay(root->left->left, id);
                root = rightRotate(root);
            }
            else if (root->left->video.id < id)
            {
                root->left->right = splay(root->left->right, id);
                if (root->left->right)
                    root->left = leftRotate(root->left);
            }
            return (root->left) ? rightRotate(root) : root;
        }
        else
        {
            if (!root->right)
                return root;

            if (root->right->video.id > id)
            {
                root->right->left = splay(root->right->left, id);
                if (root->right->left)
                    root->right = rightRotate(root->right);
            }
            else if (root->right->video.id < id)
            {
                root->right->right = splay(root->right->right, id);
                root = leftRotate(root);
            }
            return (root->right) ? leftRotate(root) : root;
        }
    }

    SplayTreeNode *insert(SplayTreeNode *root, const Video &video)
    {
        if (!root)
            return new SplayTreeNode(video);

        if (video.id < root->video.id)
        {
            root->left = insert(root->left, video);
        }
        else
        {
            root->right = insert(root->right, video);
        }
        return root;
    }

    void printTree(SplayTreeNode *node, int depth) const
    {
        if (!node)
            return;

        printTree(node->right, depth + 1);

        for (int i = 0; i < depth; ++i)
        {
            cout << "    ";
        }
        cout << node->video.id << " (" << node->video.name << ")" << endl;

        printTree(node->left, depth + 1);
    }
};

#endif // SPLAY_TREE_H
