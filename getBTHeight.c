int GetHeight(BinTree BT) {
    if (BT == NULL)
        return 0;
    int left  = GetHeight(BT->Left);
    int right =  GetHeight(BT->Right);
    return left > right ? 1+left:1+right;
}