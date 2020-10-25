Stack CreateStack(int MaxSize) {
    Stack S = (Stack)malloc(sizeof(Stack));
    S->Data = (ElementType *)malloc(MaxSize*sizeof(ElementType));
    S->Top1 = -1;
    S->Top2 = MaxSize;
    S->MaxSize = MaxSize;
    return S;
}

