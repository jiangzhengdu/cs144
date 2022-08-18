// #include "byte_stream.hh"

// // Dummy implementation of a flow-controlled in-memory byte stream.

// // For Lab 0, please replace with a real implementation that passes the
// // automated checks run by `make check_lab0`.

// // You will need to add private members to the class declaration in `byte_stream.hh`

// template <typename... Targs>
// void DUMMY_CODE(Targs &&.../* unused */) {}

// using namespace std;

// ByteStream::ByteStream(const size_t capacity) : buf({}), cap(capacity), is_eof(false), total_write(0), total_read(0) {}

// #include <iostream>

// size_t ByteStream::write(const string &data) {
//     if (data.size() == 0) {
//         return 0;
//     }
//     size_t byte_write = (data.size() > (cap - buffer_size())) ? cap - buffer_size() : data.size();
//     buf += data.substr(0, byte_write);
//     total_write += byte_write;
//     return byte_write;
// }

// //! \param[in] len bytes will be copied from the output side of the buffer
// string ByteStream::peek_output(const size_t len) const { return buf.substr(0, len); }

// //! \param[in] len bytes will be removed from the output side of the buffer
// void ByteStream::pop_output(const size_t len) {
//     total_read += len;
//     buf.erase(0, len);
// }

// //! Read (i.e., copy and then pop) the next "len" bytes of the stream
// //! \param[in] len bytes will be popped and returned
// //! \returns a string
// std::string ByteStream::read(const size_t len) {
//     size_t byte_read = (len > buffer_size()) ? buffer_size() : len;
//     string ret = peek_output(byte_read);
//     pop_output(byte_read);
//     return ret;
// }

// void ByteStream::end_input() { is_eof = 0; }

// bool ByteStream::input_ended() const { return is_eof; }

// size_t ByteStream::buffer_size() const { return buf.size(); }

// bool ByteStream::buffer_empty() const { return buffer_size() == 0; }

// bool ByteStream::eof() const { return is_eof & buffer_empty(); }

// size_t ByteStream::bytes_written() const { return total_write; }

// size_t ByteStream::bytes_read() const { return total_read; }

// size_t ByteStream::remaining_capacity() const { return cap - buffer_size(); }


#include "byte_stream.hh"

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

// 初始化字节流数据,设置缓冲区的最大容量
ByteStream::ByteStream(const size_t capacity) { 
    _capacity = capacity;
}

// 输入端写数据，存入到缓冲队列中
size_t ByteStream::write(const string &data) {
    // 如果队列满了，返回0不能写入数据，写入为0
    if(remaining_capacity() == 0) return 0;

    // 将数据写入
    size_t write_size = (data.size() <= remaining_capacity()) ? data.size(): remaining_capacity();
    for(size_t i = 0; i < write_size; i++){
        _buf.push_back(data[i]);
    }

    // 已经写入的数据长度更新
    _bytes_written += write_size;

    return write_size;
}

// 查看缓冲区的队列内容，但是不出队列
string ByteStream::peek_output(const size_t len) const {
    size_t buf_size = (len <= buffer_size()) ? len : buffer_size();
    string data;
    data.assign(_buf.begin(),_buf.begin()+buf_size);
    
    return data;
}

// 出队列，从缓冲区中删除len长度的数据
void ByteStream::pop_output(const size_t len) {
    size_t buf_size = (len <= buffer_size()) ? len : buffer_size();
    for(size_t i = 0; i < buf_size; i++){
        _buf.pop_front();
    }
    _bytes_read += buf_size;
}

// 从缓冲区队列中读取数据
std::string ByteStream::read(const size_t len) {
    string buf_read = peek_output(len);
    pop_output(len);

    return buf_read;
}

void ByteStream::end_input() {_is_end_input = true;}

bool ByteStream::input_ended() const { return _is_end_input; }

size_t ByteStream::buffer_size() const { return _buf.size(); }

bool ByteStream::buffer_empty() const { return _buf.size() == 0; }

bool ByteStream::eof() const { return input_ended() && buffer_empty(); }

size_t ByteStream::bytes_written() const { return _bytes_written; }

size_t ByteStream::bytes_read() const { return _bytes_read; }

size_t ByteStream::remaining_capacity() const { return _capacity - _buf.size(); }

