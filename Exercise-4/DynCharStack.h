#ifndef DYNCHARSTACK_H
#define DYNCHARSTACK_H


class DynCharStack
{
    private:
        //Structure for stack nodes
        struct StackNode
        {
            char letter;        // Value in the node
            StackNode *next;    // Pointer to the next node
        };

        StackNode *top;         // Pointer to the stack top
    protected:

    public:
        //Constructor
        DynCharStack()
        {
            top = NULL;
        }
        //Destructor
        ~DynCharStack();

        // Stack operations
        void push(char);
        void pop(char &);
        bool isEmpty();
};

#endif // DYNCHARSTACK_H
