struct Trie
{
    struct Node
    {
        Node* child[26];
        int exist, cnt;

        Node()
        {
            for (int i = 0; i < 26; i++)
                child[i] = NULL;

            exist = cnt = 0;
        }
    };

    int cur;
    Node* root;
    Trie() : cur(0)
    {
        root = new Node();
    };

    void add_string(string s)
    {
        Node* p = root;
        for (auto f: s)
        {
            int c = f - 'a';
            if (p -> child[c] == NULL)
                p -> child[c] = new Node();

            p = p -> child[c];
            p -> cnt++;
        }

        p -> exist++;
    }

    bool delete_string_recursive(Node* p, string& s, int i)
    {
        if (i != (int) s.size())
        {
            int c = s[i] - 'a';
            bool is_child_deleted = delete_string_recursive(p -> child[c], s, i + 1);
            if (is_child_deleted)
                p->child[c] = NULL;
        }
        else
            p -> exist--;

        if (p != root)
        {
            p -> cnt--;
            if (p -> cnt == 0)
            {
                // Khác với cài đặt bằng mảng, ta có thể thực sự xóa đỉnh này đi.
                delete(p);

                return true;
            }
        }
        return false;
    }

    void delete_string(string s)
    {
        if (find_string(s) == false)
            return;

        delete_string_recursive(root, s, 0);
    }

    bool find_string(string s)
    {
        Node* p = root;
        for (auto f: s)
        {
            int c = f - 'a';
            if (p -> child[c] == NULL)
                return false;

            p = p -> child[c];
        }

        return (p -> exist != 0);
    }
};
