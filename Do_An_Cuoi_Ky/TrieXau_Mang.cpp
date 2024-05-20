const int max_nodes = ...;

struct Trie
{
    struct Node
    {
        int child[26];   // mảng lưu địa chỉ các nút con của nút hiện tại
        int exist, cnt;  // exist sẽ lưu vị trí cuối cùng của các xâu kết thúc
    				// tại đỉnh này, cnt là số các xâu đi qua đỉnh này
    } nodes[max_nodes];

    int cur = 0; // Hiện trong trie đang có bao nhiêu đỉnh.

    // Tạo nút gốc cho Trie là đỉnh 0 khi khởi tạo Trie.
    Trie() : cur(0)
    {
        memset(nodes[0].child, -1, sizeof(nodes[cur].child));
        nodes[0].exist = nodes[0].cnt = 0;
    };

    // Tạo và trả về giá trị của đỉnh mới được tạo ra.
    int new_node()
    {
        ++cur;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;

        return cur;
    }

    // Thêm xâu s vào cây Trie
    void add_string(string s)
    {
        int pos = 0;
        for (auto f : s)
        {
            int c = f - 'a';
            // Nếu cạnh tương ứng chữ cái c chưa tồn tại thì ta tạo ra đỉnh mới.
            if (nodes[pos].child[c] == -1)
                nodes[pos].child[c] = new_node();

            // Có thêm một xâu trong trie có tiền tố là xâu được thể hiện
            // bằng đỉnh hiện tại.
            pos = nodes[pos].child[c];
            ++nodes[pos].cnt;
        }

        // Đã tìm được đỉnh tương ứng với xâu s, ta tăng biến exist của đỉnh lên 1.
        ++nodes[pos].exist;
    }

    // Trả về liệu đỉnh pos có thể bị xóa đi hay không, đồng thời xóa xâu s nếu có thể.
    bool delete_string_recursive(int pos, string& s, int i)
    {
        // Nếu chưa đến đỉnh tương ứng với xâu s thì tiếp tục đệ quy xuống dưới.
        if (i != (int) s.size())
        {
            int c = s[i] - 'a';
            bool is_child_deleted = delete_string_recursive(nodes[pos].child[c], s, i + 1);
            // Nếu đỉnh con tương ứng bị xóa thì ta gán lại đỉnh tương ứng bằng -1.
            if (is_child_deleted)
                nodes[pos].child[c] = -1;
        }
        // Nếu đã đến đỉnh tương ứng với xâu s thì ta giảm biến exist của đỉnh đi 1
        else
            --nodes[pos].exist;

        // Nếu đỉnh đang xét không phải gốc thì ta giảm biến cnt của đỉnh đi 1
        // và kiểm tra đỉnh có bị xóa đi hay không?
        // Đỉnh bị xóa nếu không còn xâu nào đi qua nó, nói cách khác là
        // không còn xâu nào có tiền tố là xâu được thể hiện bởi đỉnh pos.
        if (pos != 0)
        {
            --nodes[pos].cnt;

            if (nodes[pos].cnt == 0)
                return true;
        }

        return false;
    }

    // Thủ tục:
    // Truyền vào xâu s.
    // Thủ tục sẽ nhận xâu s và kiểm tra xâu x có trong Trie hay không.
    // Nếu có thì xóa xâu s ra khỏi Trie.
    void delete_string(string s)
    {
        // Kiểm tra xâu s có trong Trie hay không.
        if (find_string(s) == false)
            return;

        // Gọi hàm đệ quy xóa xâu s khỏi Trie.
        delete_string_recursive(0, s, 0);
    }

    // Hàm:
    // Nhận vào xâu s.
    // Hàm sẽ trả về “true” nếu có xâu s trong cây Trie,
    // ngược lại trả về false.
    bool find_string(string s)
    {
        int pos = 0;
        for (auto f: s)
        {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1)
                return false;

            pos = nodes[pos].child[c];
        }

        // Kiểm tra có xâu nào kết thúc tại đỉnh này hay không.
        return (nodes[pos].exist != 0);
    }
};
