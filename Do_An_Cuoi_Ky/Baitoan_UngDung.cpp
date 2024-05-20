// Cài đặt bằng con trỏ, chỉ cần thêm hàm này vào trong cấu trúc Trie nhị phân.
int query(int x)
{
    int res = 0;
    Node* p = root;

    for (int i = LOG; i >= 0; --i)
    {
        int c = (x >> i) & 1;

        if (p -> child[c ^ 1] != -1)
        {
            res += (1ll << i);
            p = p -> child[c ^ 1];
        }
        else
            p = p -> child[c];
    }

    return res;
}
