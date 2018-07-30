#if !defined tree_h
#define tree_h

#include "store.h"
#include <vector>
#include <memory>
#include <iterator>

//const int MAX_CHILDREN = 8;

// abstract class
class Node 
{
    public:
        virtual ~Node() {}
        virtual double Calc() const = 0; // pure virtual function
        virtual bool IsLvalue() const
        {
            return false;
        }
        virtual void Assign(double value) {}
};

class MultiNode : public Node
{
    public:
        MultiNode(std::auto_ptr<Node>& pNode)
        {
            AddChild(pNode, true);
        }
        ~MultiNode();
        void AddChild(std::auto_ptr<Node>& pNode, bool isPositive)
        {
            _aChild.push_back(pNode.release());
            _aIsPositive.push_back(isPositive);
        }
    protected:
        std::vector<Node*> _aChild;
        std::vector<bool> _aIsPositive;
};

class SumNode : public MultiNode
{
    public:
        SumNode(std::auto_ptr<Node>& pNode) : MultiNode(pNode) {};
        double Calc() const;
};

class ProductNode : public MultiNode
{
    public:
        ProductNode(std::auto_ptr<Node>& pNode) : MultiNode(pNode) {};
        double Calc() const;
};

class BinNode : public Node
{
    public:
        BinNode(std::auto_ptr<Node>& pLeft, std::auto_ptr<Node>& pRight) : _pLeft(pLeft), _pRight(pRight) {}
    protected:
        std::auto_ptr<Node> _pLeft;
        std::auto_ptr<Node> _pRight;
};

class NumNode: public Node
{
    public:
        NumNode(double num): _num(num) {}
        double Calc() const;
    private:
        const double _num;
};

class VarNode : public Node
{
    public:
        VarNode(int id, Store& store) : _id(id), _store(store) {}
        double Calc() const;
        bool IsLvalue() const;
        void Assign(double val); 
    private:
        const int _id;
        Store& _store;
};

class AddNode : public BinNode
{
    public:
        AddNode(std::auto_ptr<Node>& pLeft, std::auto_ptr<Node>& pRight) : BinNode(pLeft, pRight) {}
        double Calc() const;
};

class MultNode : public BinNode
{
    public:
        MultNode(std::auto_ptr<Node>& pLeft, std::auto_ptr<Node>& pRight) : BinNode(pLeft, pRight) {}
        double Calc() const;
};

class SubNode : public BinNode
{
    public:
        SubNode(std::auto_ptr<Node>& pLeft, std::auto_ptr<Node>& pRight) : BinNode(pLeft, pRight) {}
        double Calc() const;
};

class DivideNode : public BinNode
{
    public:
        DivideNode(std::auto_ptr<Node>& pLeft, std::auto_ptr<Node>& pRight) : BinNode(pLeft, pRight) {}
        double Calc() const;
};

class AssignNode : public BinNode
{
    public:
        AssignNode(std::auto_ptr<Node>& pLeft, std::auto_ptr<Node>& pRight) : BinNode(pLeft, pRight)
        {
            assert(_pLeft->IsLvalue());
        }
        double Calc() const;
};

#endif
