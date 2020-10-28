void InorderTraversal(BinTree BT) {
  if (BT == NULL)
    return;
  InorderTraversal(BT->Left);
  printf(" %c", BT->Data);
  InorderTraversal(BT->Right);
}

void PreorderTraversal(BinTree BT){
  if (BT == NULL)
    return;
  printf(" %c", BT->Data);
  PreorderTraversal(BT->Left);
  PreorderTraversal(BT->Right);
}

void PostorderTraversal(BinTree BT){
  if (BT == NULL)
    return;
  PostorderTraversal(BT->Left);
  PostorderTraversal(BT->Right);
  printf(" %c", BT->Data);
}

void LevelorderTraversal(BinTree BT){
  if (BT==NULL)
    return;
  BinTree binTree[100];
  int head = 0, last = 0;
  binTree[last++] = BT;
  
  while (head < last)
  {
    BinTree temp = binTree[head++];
    printf(" %c", temp->Data);
    
    if(temp->Left)
      binTree[last++] = temp->Left;
    if(temp->Right)
      binTree[last++] = temp->Right;
  }
  
}
