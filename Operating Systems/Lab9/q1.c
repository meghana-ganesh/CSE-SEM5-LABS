#include<stdio.h>
#include<stdlib.h>
typedef struct mab* mptr;
typedef struct mab
{
    int offset;
    int size;
    int allocated;
    mptr next;
    mptr prev; 
}mab;

mptr creatememblock(int offset,int size,mptr prev,mptr next)
{
    mptr block = (mptr)malloc(sizeof(mab));
    block->offset = offset;
    block->size = size;
    block->allocated = 0;
    block->prev = prev;
    block->next = next;
    return block;
}

// check if memory available
mptr memChk(mptr m, int size)
{
    if(m->allocated != 1 && m->size >= size)
    {
        return m;
    }
    return NULL;
} 


// allocate a memory block
mptr memAlloc(mptr m, int size)
{
    if(memChk(m,size) != NULL)
    {
        m->allocated = 1;
        return m;
    }
    return NULL;
}

// free memory block
void memFree(mptr m)
{
    m->allocated = 0;
}

// merge two memory blocks
mptr memMerge(mptr m)
{
    if(m->allocated || (m->next != NULL && m->next->allocated))
        return NULL;
    if(m->next == NULL)
        return NULL;
    m->size = m->size + m->next->size;
    m->next->next->prev = m;
    m->next = m->next->next;
    return m;
}

// split a memory block
mptr memSplit(mptr m, int size)
{
    if(m->allocated == 1 && m->size > size)
    {
        mptr newblock = creatememblock(m->offset+size,m->size-size,m,m->next);
        m->size = size;
        m->next = newblock;
        if(newblock->next != NULL)
        {
            newblock->next->prev = newblock;
        }
        return m;
    }
    return NULL;
}

int FirstFit(mptr head, int size)
{
    printf("ghi");
    mptr current = head;
    while (1)
    {
        if(current == NULL)
        {
            current = head;
            return 0;
        }
        if (memChk(current, size) != NULL)
        {
            memAlloc(current, size);
            return 1; // Allocation successful
        }
        current = current->next;
    }
    return 0; // Allocation failed
}


int main()
{
    mptr block1,block2,block3,block4;
    block1 = creatememblock(0,100,NULL,block2);
    block2 = creatememblock(100,50,block1,block3);
    block3 = creatememblock(150,30,block2,block4);
    block4 = creatememblock(180,35,block3,NULL);
    int processes[4] = {20,60,70,40};
    for (int i = 0; i < 4; i++)
    {
        if (FirstFit(block1, processes[i]))
        {
            printf("Allocated process %d successfully\n", i + 1);
        }
        else
        {
            printf("Memory allocation for process %d failed\n", i + 1);
        }
    }

}
//https://prepinsta.com/operating-systems/page-replacement-algorithms/first-fit/