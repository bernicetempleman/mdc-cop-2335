#ifndef DYNCHARQUEUE_H
#define DYNCHARQUEUE_H


class DynCharQueue
{
    private:
        //structure for the queue
        struct QueueNode
        {
            char letter;
            QueueNode *next;

        };

        QueueNode *front;
        QueueNode *rear;
        int numItems;

    protected:

    public:
        DynCharQueue();
        ~DynCharQueue();

        //Queue operations
        void enqueue(char);
        void dequeue (char &);
        bool isEmpty() const;
        bool isFull() const;
        void clear();

};

#endif // DYNCHARQUEUE_H
