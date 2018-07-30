#if !defined list_h
#define list_h

template<typename T>
class List
{
    friend class Seq;
    public:
        List() : _pHead(0) {}
        ~List();
        void Add(T value);
        bool Find(T value) const;
    private: // nested class
        class Link
        {
            public:
                Link(Link* pNext, T value) : _pNext(pNext), _value(value) {}
                Link* Next() const { return _pNext; }
                int GetValue() const { return _value; }
            private:
                T _value;
                Link* _pNext;
        };
    public:
        class Seq
        {
            public:
                Seq(const List<T>& list) : _pLink(list.GetHead()) {}
                bool AtEnd() const { return _pLink == 0; }
                void Advance() { _pLink = _pLink->Next(); }
                int GetId() const { return _pLink->GetValue(); }
            private:
                List<T>::Link const *_pLink;
        };
    private:
        Link const* GetHead() const { return _pHead; }
        Link* _pHead;
};

template<typename T>
List<T>::~List()
{
    while (_pHead != 0) {
        Link* pLinkTmp = _pHead;
        _pHead = _pHead->Next();
        delete pLinkTmp;
    }
}

template<typename T>
void List<T>::Add(T value)
{
    Link* pLink = new Link(_pHead, value);
    _pHead = pLink;
}

template<typename T>
bool List<T>::Find(T value) const
{
    for (Link const *pLink = GetHead(); pLink != 0; pLink = pLink->Next()) {
        if (pLink->GetValue() = value)
            return true;
    }
    return false;
}

#endif
