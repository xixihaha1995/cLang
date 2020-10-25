Stack CreateStack(int MaxSize) {
    Stack S = (Stack)malloc(sizeof(Stack));
    S->Data = (ElementType *)malloc(MaxSize*sizeof(ElementType));
    S->Top1 = -1;
    S->Top2 = MaxSize;
    S->MaxSize = MaxSize;
    return S;
}

bool Push(Stack S, ElementType X, int Tag) {
    if (S == NULL) return false;
    if (S->Top1+1 == S->Top2) {
        printf("Stack Full\n");
        return false;
    }
    if(Tag == 1) 
        S->Data[++S->Top1] =X;
    else
    {
        S->Data[--S->Top2] = X;
    }
    return true;
}
ElementType Pop(Stack S, int Tag) {
    if(S ==NULL)
        return ERROR;
    if(Tag == 1) {
        if(S->Top1 == -1) {
            printf("Stack 1 Empty\n");
            return ERROR;
        }
        return S->Data[S->Top1--];
    }else
    {
        if (S->Top2 == S->MaxSize){
            printf("Stack 2 Empty\n");
            return ERROR;
        }
        return S->Data[S->Top2++];
    }
    
}