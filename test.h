#include <stdexcept>

template <typename T>
class vector
{
public:
    // 构造函数
    vector() : m_size(0), m_capacity(0), m_data(nullptr) {}

    explicit vector(size_t size) : m_size(size), m_capacity(size)
    {
        m_data = new T[size];
    }

    // 拷贝构造函数
    vector(const vector &other) : m_size(other.m_size), m_capacity(other.m_capacity), m_data(new T[other.m_capacity])
    {
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }

    // 移动构造函数
    vector(vector &&other) noexcept : m_size(other.m_size), m_capacity(other.m_capacity), m_data(other.m_data)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // 析构函数
    ~vector()
    {
        delete[] m_data;
    }

    // 赋值运算符
    vector &operator=(const vector &other)
    {
        if (this != &other)
        {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = new T[other.m_capacity];
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    // 移动赋值运算符
    vector &operator=(vector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = other.m_data;
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    // 重载 [] 运算符
    T &operator[](size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    // 重载 const [] 运算符
    const T &operator[](size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    // 返回 vector 的大小
    size_t size() const
    {
        return m_size;
    }

    // 返回 vector 的容量
    size_t capacity() const
    {
        return m_capacity;
    }

    // 判断 vector 是否为空
    bool empty() const
    {
        return m_size == 0;
    }

    // 在 vector 的末尾添加元素
    void push_back(const T &value)
    {
        if (m_size == m_capacity)
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        m_data[m_size++] = value;
    }

    // 删除 vector 末尾的元素
    void pop_back()
    {
        if (m_size > 0)
        {
            m_size--;
        }
    }

    // 清空 vector
    void clear()
    {
        m_size = 0;
    }

    // 重新分配 vector 的容量
    void reserve(size_t new_capacity)
    {
        if (
            new_capacity <= m_capacity)
        {
            return;
        }
        T *new_data = new T[new_capacity];
        for (size_t i = 0; i < m_size; i++)
        {
            new_data[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }

    // 改变 vector 的大小
    void resize(size_t new_size)
    {
        if (new_size > m_capacity)
        {
            reserve(new_size);
        }
        if (new_size > m_size)
        {
            for (size_t i = m_size; i < new_size; i++)
            {
                m_data[i] = T();
            }
        }
        m_size = new_size;
    }

private:
    size_t m_size;     // vector 中元素的个数
    size_t m_capacity; // vector 的容量
    T *m_data;         // 指向 vector 数据的指针
};