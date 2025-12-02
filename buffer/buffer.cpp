#include "buffer.h"

namespace Aciv::utility{
    Buffer::Buffer(std::size_t _init_size)
        :m_capacity(_init_size)
    {
        m_data = new char[_init_size];
    }
    
    Buffer::~Buffer(){
        delete[] m_data;
        m_data = NULL;
    }

    int Buffer::resize(std::size_t _update_size){
        if(_update_size < m_capacity)
            return 0;
        
        char const* new_buffer = new char[_update_size];
        std::memcpy((void*)new_buffer, (void*)read_start_ptr(), readably_len());

        m_ReadPos.store(0);
        m_WritePos.store(readably_len());

        delete[] m_data;
        m_data = NULL;

        m_data = const_cast<char*>(new_buffer);
        m_capacity = _update_size;
        return _update_size;
    }

    void Buffer::adapt_len(std::size_t _len){
        if(_len <= 0)
            return;

        if(_len > writably_len_at_end()){
            if(_len <= writably_len_at_start() + writably_len_at_end())
                resize(m_capacity);
            else
                resize(std::max(m_capacity * 2, m_WritePos + _len));
        }
    }

    const char* Buffer::read(std::size_t _len){
        if(_len >= readably_len())
            return nullptr;
        const char* back_pointer = read_start_ptr();
        m_ReadPos.store(m_ReadPos.load() + _len);
        return back_pointer;
    }

    void Buffer::append(const char* _in_data, std::size_t _data_size){
        if(_in_data == nullptr || _data_size == 0)
            return;

        adapt_len(_data_size);
    
        std::memcpy((void*)read_end_ptr(), (void*)_in_data, _data_size);
        m_WritePos += _data_size;
    }

    void Buffer::append(std::string_view _in_data){
        this->append(_in_data.data(), _in_data.size());
    }
    
    void Buffer::append(char _in_data){
        this->append(&_in_data, 1);
    }

    void Buffer::append(Buffer &_in_buffer){
        this->append(_in_buffer.read_start_ptr(), _in_buffer.readably_len());
    }

    void Buffer::erase_start(std::size_t _len){
        erase(read_start_ptr(), _len);
    }

    void Buffer::erase_end(std::size_t _len){
        erase(read_end_ptr() - _len, _len);
    }

    void Buffer::erase(std::size_t _pos, std::size_t _len){
        erase(read_start_ptr() + _pos, _len);
    }
    void Buffer::erase(char* _start, size_t _len){
        assert(_start >= read_start_ptr() && _start + _len <= read_end_ptr());

        std::memcpy((void*)_start, (void*)(_start + _len), read_end_ptr() - (_start + _len));
        m_WritePos.store(m_WritePos.load() - _len);
    }


    
    void Buffer::insert(std::size_t _insert_pos, const char* const __restrict _in_data, std::size_t _data_size){
        if(_in_data == nullptr || _data_size == 0)
            return;

        adapt_len(_data_size);

        std::memcpy((void*)(read_start_ptr() + _insert_pos + _data_size),
               (void*)(read_start_ptr() + _insert_pos),
               read_end_ptr() - (_insert_pos + read_start_ptr()));

        std::memcpy((void*)(read_start_ptr() + _insert_pos),
               (void*)_in_data, _data_size);

        m_WritePos.store(m_WritePos.load() + _data_size);
    }

    void Buffer::insert(std::size_t _insert_pos, std::string_view _in_data){
        insert(_insert_pos, _in_data.data(), _in_data.size());
    }

    void Buffer::insert(std::size_t _insert_pos, char _in_char){
        insert(_insert_pos, &_in_char, 1);
    }

    void Buffer::replace(std::size_t _start_pos, size_t _replace_len,
                    const char* const __restrict _replace_data, std::size_t _replace_data_size){
        assert(_start_pos + _replace_len <= readably_len());
        long long change_len = _replace_data_size - _replace_len;
        if(change_len > 0)
            adapt_len(change_len);

        std::memcpy((void*)(read_start_ptr() + _start_pos + _replace_data_size),
               (void*)(read_start_ptr() + _start_pos + _replace_len),
               read_end_ptr() - (read_start_ptr() + _start_pos + _replace_len));
        std::memcpy((void*)(read_start_ptr() + _start_pos),
                    (void*)_replace_data, _replace_data_size);

        m_WritePos.store(m_WritePos.load() + change_len);
        
    }
    

    void Buffer::reset(){
        m_ReadPos.store(0);
        m_WritePos.store(0);
    }

    char* Buffer::buffer_start_ptr() const {
        return m_data;
    }

    char* Buffer::read_start_ptr() const {
        return m_data + m_ReadPos.load();
    }

    char *Buffer::read_end_ptr() const {
        return m_data + m_WritePos.load();
    }

    std::size_t Buffer::writably_len_at_end() const {
        return m_capacity - m_WritePos.load(); 
    }

    std::size_t Buffer::writably_len_at_start() const {
        return m_ReadPos.load();
    }

    std::size_t Buffer::readably_len() const{
        return m_WritePos.load() - m_ReadPos.load();
    }

    std::string Buffer::retrieve_to_string(std::size_t _len){
        assert(_len <= readably_len());
        std::string back_str(read_start_ptr(), _len);
        m_ReadPos.store(m_ReadPos.load() + _len);
        return back_str;
        
    }

}