#include <memory>
#include "wet1util.h"
using std::unique_ptr;
using std::shared_ptr;


template <typename T>
class AVL_tree {
    struct  Node {
        int key;
        T data;
        int height = 0;
        Node* parent = nullptr;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        Node(const int& key,const T& data) : key(key), data(data),left(nullptr), right(nullptr){}
    };
    unique_ptr<Node> root = nullptr;

    int get_height(Node* n) const {
        if (n== nullptr) {
            return -1;
        } else {
            return n->height;
        }
    }


    void update_height(Node* node){
        if (node == nullptr) {
            return;
        }
        int h_left = get_height(node->left.get());
        int h_right = get_height(node->right.get());
        int max = h_left > h_right ? h_left: h_right;
        node->height = 1 + max;
    }

    int balance_factor(Node* node) const{
        if (node == nullptr) return 0;
        return get_height(node->left.get())-get_height(node->right.get());
    }


    void AVL_LL(unique_ptr<Node>& node) {
        if (node == nullptr || node->left == nullptr) return;
        unique_ptr<Node> B = std::move(node); // the old root y
        unique_ptr<Node> A = std::move(B-> left); // the new  root A , B left is no more and now
        Node* allparent = B->parent;
        std::unique_ptr<Node> AR = std::move(A->right);
        B->left = std::move(AR);
        if (B->left != nullptr) {
            B->left->parent = B.get();
        }
        A->right= std::move(B);
        A->right->parent = A.get();
        A->parent= allparent;
        node = std::move(A);
        update_height(node->right.get()); // uppdate the height of OLD ROOT B
        update_height(node.get());// update height of new root A
    }
    void AVL_RR(unique_ptr<Node>& node) {
        if (node == nullptr || node->right == nullptr) return;
        unique_ptr<Node> B = std::move(node); // the old root y
        unique_ptr<Node> A = std::move(B->right); // the new  root A , B left is no more and now
        Node* allparent = B->parent;
        std::unique_ptr<Node> AL = std::move(A->left);
        B->right = std::move(AL);
        if (B->right != nullptr) {
            B->right->parent = B.get();
        }
        A->left= std::move(B);
        A->left->parent = A.get();
        A->parent= allparent;
        node = std::move(A);
        update_height(node->left.get()); // uppdate the height of OLD ROOT B
        update_height(node.get());// update height of new root A
    }
    void Rotate(unique_ptr<Node>& node) {
        if (node == nullptr) return;
        int bf = balance_factor(node.get());
        if (bf > 1 && balance_factor(node->left.get()) >=0) {
            AVL_LL(node);
        } else if(bf > 1 && balance_factor(node->left.get()) == -1){
            AVL_RR(node->left);
            AVL_LL(node);
        } else if (bf < -1 && balance_factor(node->right.get()) <= 0) {
            AVL_RR(node);
        }else if (bf < -1 && balance_factor(node->right.get()) == 1) {
            AVL_LL(node->right);
            AVL_RR(node);
        }
    }



    StatusType AVL_remove(unique_ptr<Node>& node,const int& key) {
        if (node == nullptr) return StatusType::FAILURE;
        StatusType res;
        if (key < node->key) {
            res = AVL_remove(node->left, key);
        }else if (key > node->key){
            res = AVL_remove(node->right, key);
        } else {
            if (node->left == nullptr && node->right == nullptr) { // no children
                node = nullptr;
                return res = StatusType::SUCCESS;
            }else if (node->left != nullptr && node->right == nullptr) { // only left
                unique_ptr<Node> y = std::move(node);
                node = std::move(y->left);
                node->parent= y->parent;
                return res = StatusType::SUCCESS;
            }else if (node->left == nullptr && node->right != nullptr) { // only right
                unique_ptr<Node> y = std::move(node);
                node = std::move(y->right);
                node->parent= y->parent;
                return res = StatusType::SUCCESS;
            }
            Node* next_inorder = node->right.get();
            while (next_inorder->left!= nullptr) {
                next_inorder = next_inorder->left.get();
            }
            node->key= next_inorder->key;
            node->data= next_inorder->data;
            res = AVL_remove(node->right,node->key);
        }
        if (res != StatusType::SUCCESS) return res;
        int old_height = node->height;
        update_height(node.get());
        if (node->height == old_height) {
            return StatusType::SUCCESS;
        }
        Rotate(node);
        return StatusType::SUCCESS;
    }

    StatusType AVL_insert(unique_ptr<Node>& node,Node* parent,const int& key,const T& data) {
        if (node == nullptr) {
            try {
                node = std::make_unique<Node>(key,data);
                node->parent = parent;
                return StatusType::SUCCESS;
            } catch (const std::bad_alloc&) {
                return StatusType::ALLOCATION_ERROR;
            }
        }
        StatusType res;
        if (key < node->key) {
            res = AVL_insert(node->left,node.get(), key, data);
        }else if (key > node->key){
            res = AVL_insert(node->right,node.get(), key, data);
        } else {
            res =StatusType::FAILURE;
            return res;
        }
        if (res != StatusType::SUCCESS) return res;
        int old_height = node->height;
        update_height(node.get());
        if (node->height == old_height) return StatusType::SUCCESS;
        Rotate(node);
        return StatusType::SUCCESS;
    }
    bool is_in_rec(const unique_ptr<Node>& node,const int& key ) const{
        if (node == nullptr) return false;
        if (key < node->key) {
            return is_in_rec(node->left, key);
        } else if (key > node->key) {
            return is_in_rec(node->right, key);
        } else {
            return true;
        }

    }
    T* find_rec(unique_ptr<Node>& node, const int& key) {
        if (node == nullptr) return nullptr;
        if (key < node->key) {
            return find_rec(node->left,key);
        }else if (key > node->key){
            return  find_rec(node->right, key);
        } else {
            return &(node->data);
        }

    }



public:
    AVL_tree() = default;
    ~AVL_tree()= default;
    AVL_tree(const AVL_tree&) = delete;
    AVL_tree& operator=(const AVL_tree&) = delete;
    bool is_in(const int& key) const{
        return is_in_rec(root,key);
    }
    T* find(const int& key) {
        return find_rec(root,key);
    }
    bool is_empty() const{
        return root == nullptr? true:false;
    }
    StatusType remove(const int& key) {
        return AVL_remove(root,key);
    }
    StatusType insert(const int& key, const T& data) {
        return AVL_insert(root, nullptr, key, data);
    }
};
