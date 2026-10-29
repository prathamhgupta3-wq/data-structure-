
#include<iostream>

template<typename T>
class node {

public :
    T data;
    node<T>* rnode = NULL;
    node<T>* lnode = NULL;

    node(T x) {

        this->data = x;
        this->rnode = NULL;
        this->lnode = NULL;
    }

    T& operator*() {
        return this->data;
    }

};

template<typename T>
class bst {

public :
    node<T>* root = NULL;
    size_t n_count;

public :

    bst() {
        this->n_count = 0;
        this->root = NULL;
    }

    void insert(const T& x) {

        node<T>* n = new node<T>(x);

        if(root == NULL) {
            root = n;
            n_count++;
            return;
        }

        node<T>* temp = this->root;
        node<T>* temp1 = NULL;
        size_t count = 0;

        while(temp != NULL) {
            temp1 = temp;
            count++;

            if(n->data > temp->data) {
                temp = temp->rnode;
            }else if(n->data < temp->data) {
                temp = temp->lnode;
            }else if(n->data == temp->data) {
                delete n;
                return;
            }
        }

        if(temp1->data > n->data) {
            temp1->lnode = n;
        }else if(temp1->data < n->data) {
            temp1->rnode = n;
        }

        n_count++;
    }

    node<T>* search(T x) {

        node<T>* temp = this->root;

        if(root == NULL) {
            return temp;
        }

        while(temp != NULL && x != temp->data) {

            if(x < temp->data) {
                temp = temp->lnode;
            }else if(x > temp->data) {
                temp = temp->rnode;
            }
        }

        return temp;
    }

    void preorder(node<T>* temp) {

        if(temp == NULL) {
            return;
        }

        std::cout << temp->data << "-> ";
        preorder(temp->lnode);
        preorder(temp->rnode);
    }

    void postorder(node<T>* temp) {

        if(temp == NULL) {
            return;
        }

        postorder(temp->lnode);
        postorder(temp->rnode);

        std::cout << temp->data << "-> ";
    }

    void inorder(node<T>* temp) {

        if(temp == NULL) {
            return;
        }

        inorder(temp->lnode);
        std::cout << temp->data << "-> ";
        inorder(temp->rnode);
    }

    void min(node<T>* temp) {

        if(temp == NULL) {
            return;
        }

        if(temp->lnode == NULL) {
            std::cout << temp->data << std::endl;
            return;
        }

        min(temp->lnode);
    }

    void max(node<T>* temp) {

        if(temp == NULL) {
            return;
        }

        if(temp->rnode == NULL) {
            std::cout << temp->data << std::endl;
            return;
        }

        max(temp->rnode);
    }

    void erase(const T& x) {

        node<T>* temp = this->root;
        node<T>* temp1 = temp;

        if(root == NULL) {
            return;
        }

        while(temp != NULL && x != temp->data) {

            if(x < temp->data) {
                temp1 = temp;
                temp = temp->lnode;
            }else if(x > temp->data) {
                temp1 = temp;
                temp = temp->rnode;
            }
        }

        if(temp == NULL) {
            return;
        }

        if(temp == root) {

            if(temp->lnode == NULL && temp->rnode == NULL) {
                delete temp;
                this->n_count--;
                root = NULL;
                return;
            }

            if(temp->lnode != NULL && temp->rnode != NULL) {

                node<T>* temp2 = temp->lnode;

                while(temp2->rnode != NULL) {
                    temp2 = temp2->rnode;
                }

                std::cout << temp2->data << std::endl;

                temp2->rnode = temp->rnode;
                root = temp->lnode;

                this->n_count--;
                delete temp;
                return;
            }

            if(temp->lnode == NULL || temp->rnode == NULL) {

                if(temp->rnode == NULL) {
                    root = temp->lnode;
                }else {
                    root = temp->rnode;
                }

                delete temp;
                this->n_count--;
                return;
            }
        }

        if(temp->lnode == NULL && temp->rnode == NULL) {

            if(temp1->rnode == temp) {
                temp1->rnode = NULL;
                delete temp;
            }else {
                temp1->lnode = NULL;
                delete temp;
            }

            this->n_count--;
            return;
        }

        if(temp->rnode != NULL && temp->lnode != NULL) {

            if(temp1->rnode == temp) {
                temp1->rnode = temp->lnode;
            }else {
                temp1->lnode = temp->lnode;
            }

            node<T>* temp2 = temp->lnode;

            while(temp2->rnode != NULL) {
                temp2 = temp2->rnode;
            }

            temp2->rnode = temp->rnode;

            delete temp;
            this->n_count--;
            return;
        }

        if(temp->lnode == NULL || temp->rnode == NULL) {

            if(temp->rnode == NULL) {

                if(temp1->rnode == temp) {
                    temp1->rnode = temp->lnode;
                }else {
                    temp1->lnode = temp->lnode;
                }

            }else {

                if(temp1->rnode == temp) {
                    temp1->rnode = temp->rnode;
                }else {
                    temp1->lnode = temp->rnode;
                }
            }

            delete temp;
            this->n_count--;
            return;
        }
    }

    inline __attribute__((always_inline)) size_t node_count() {

        size_t node_c = this->n_count;
        return node_c;
    }

    long height(node<T>* temp) {

        long a_countr = -1;
        long a_countl = -1;

        if(temp == NULL) {
            return a_countr;
        }

        a_countl = 1 + height(temp->lnode);
        a_countr = 1 + height(temp->rnode);

        if(a_countl > a_countr) {
            return a_countl;
        }else {
            return a_countr;
        }
    }

    void clear(node<T>* temp) {

        if(temp == NULL) {
            return;
        }

        clear(temp->lnode);
        clear(temp->rnode);
        delete temp;
    }

    ~bst() {
        clear(this->root);
    }

    bst(const bst&) = delete;
    bst& operator=(const bst&) = delete;

};

int main() {

    bst<int> b;

    int choice;
    int x;
    int ch;

    do {

        std::cout << "\n========== BST MENU ==========\n1. Insert Node\n2. Delete Node\n3. Search Node\n4. Display Tree (Traversal)\n5. Display Depth of Tree\n6. Display Mirror Image\n7. Create Copy of Tree\n8. Display Parent Nodes with Child Nodes\n9. Display Leaf Nodes\n10. Display Tree Level Wise\n11. Exit" << std::endl;

        std::cout << "\nEnter your choice : ";
        std::cin >> choice;

        switch(choice) {

            case 1: {

                std::cout << "Enter value : ";
                std::cin >> x;

                b.insert(x);

                break;
            }

            case 2: {

                std::cout << "Enter value to delete : ";
                std::cin >> x;

                b.erase(x);

                break;
            }

            case 3: {

                std::cout << "Enter value to search : ";
                std::cin >> x;

                if(b.search(x) != NULL) {
                    std::cout << "Node found" << std::endl;
                }else {
                    std::cout << "Node not found" << std::endl;
                }

                break;
            }

            case 4: {

                std::cout << "\n1. Inorder" << std::endl;
                std::cout << "2. Preorder" << std::endl;
                std::cout << "3. Postorder" << std::endl;

                std::cout << "Enter choice : ";
                std::cin >> ch;

                switch(ch) {

                    case 1:
                        b.inorder(b.root);
                        break;

                    case 2:
                        b.preorder(b.root);
                        break;

                    case 3:
                        b.postorder(b.root);
                        break;

                    default:
                        std::cout << "Invalid choice" << std::endl;
                }

                std::cout << std::endl;

                break;
            }

            case 5: {

                std::cout << "Depth of tree : "
                          << b.height(b.root) << std::endl;

                break;
            }

            case 6: {

                std::cout << "Mirror image : " << std::endl;
                b.inorder(b.root);
                std::cout << std::endl;

                break;
            }

            case 7: {

                std::cout << "Creating copy of tree..." << std::endl;
                std::cout << "Implement copy() first" << std::endl;

                break;
            }

            case 8: {

                std::cout << "Parent nodes with child nodes : " << std::endl;

                // b.display_parent(b.root);

                break;
            }

            case 9: {

                std::cout << "Leaf nodes : " << std::endl;

                // b.display_leaf(b.root);

                std::cout << std::endl;

                break;
            }

            case 10: {

                std::cout << "Level wise traversal : " << std::endl;

                // b.level_order(b.root);

                std::cout << std::endl;

                break;
            }

            case 11: {

                std::cout << "Exiting..." << std::endl;
                break;
            }

            default: {

                std::cout << "Invalid choice" << std::endl;
                break;
            }
        }

    }while(choice != 11);

    return 0;
}