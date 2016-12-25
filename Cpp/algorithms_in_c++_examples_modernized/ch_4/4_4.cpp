template<class Item>
class STACK {
private:
    // Implementation-dependent code
public:
    STACK(int);

    int empty() const;

    void push(Item item);

    Item pop();
};

