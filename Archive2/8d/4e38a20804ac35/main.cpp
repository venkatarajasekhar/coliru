

long aaa();
void bbb();
void ccc();


#if A
    
    void test()
    {
        if (__builtin_expect(aaa(), 0))
        {
            bbb();
        }
    }
    

#elif B
    
    void test()
    {
        if (aaa() == 0)
        {
            bbb();
        }
    }
    
#endif

