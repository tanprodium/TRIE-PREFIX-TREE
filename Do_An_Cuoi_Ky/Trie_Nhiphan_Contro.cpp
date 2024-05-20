const int LOG = ...; // Giá trị lớn nhất của log(a[i]).

struct Trie
{
    struct Node
    {
        Node* child[2];
        int exist, cnt;

        Node()
        {
            for (int i = 0; i < 2; ++i)
                child[i] = NULL;

            exist = cnt = 0;
        }
    };

    Node* root;
    Trie() : cur(0)
    {
        root = new Node();
    };

     void add_number(int x)
     {
        Node* p = root;

        for (int i = LOG; i >= 0; --i)
        {
            int c = (x >> i) & 1;
            if (p -> child[c] == -1)
                p -> child[c] = new Node();

            p = p -> child[c];
            p -> cnt++;
        }

        p -> exist++;
    }

    void delete_number(int x)
    {
        if (find_number(x) == false)
            return;

        Node* p = root;
        for (int i = LOG; i >= 0; --i)
        {
            int c = (x >> i) & 1;
            Node* tmp = p -> child[c];
            tmp -> cnt--;

            if (tmp -> cnt == 0)
            {
                p -> child[c] = -1;
                return;
            }

            p = tmp;
        }

        p -> exist--;
    }

    bool find_number(int x)
    {
        Node* p = root;
        for (int i = LOG; i >= 0; --i)
        {
            int c = (x & (1 << i) ? 1 : 0);

            if (p -> child[c] == NULL)
                return false;

            p = p -> child[c];
        }

        return (p -> exist != 0);
    }
};
