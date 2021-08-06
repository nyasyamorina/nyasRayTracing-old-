/// @file GraphicsBuffer.h
#pragma once

#include "common/types.hpp"
#include <assert.h>
#include <fstream>
#include <functional>

#define GBUFF_CHECK_WRITING_DATA


namespace nyas
{
    /// Storing 2D RGB data.
    /// Note: indexes of buffer are start at left-bottom of image
    ///
    /// @tparam T data type, can be floating-point or integer
    template<typename T>
    class GraphicsBuffer
    {
        static_assert(is_number<T>(), "'GraphicsBuffer' accepts only floating-point or integer");

    public:
        typedef vec<3, T> Data;


        /* Constructors */
        GraphicsBuffer()
            : _size(0)
            , _data_ptr(nullptr)
        {}
        explicit GraphicsBuffer(length_t width, length_t height)
            : _size(width, height)
            , _data_ptr(new Data[width * height])
        {}
        explicit GraphicsBuffer(Length2D size)
            : _size(size)
            , _data_ptr(new Data[size.x * size.y])
        {}
        GraphicsBuffer(GraphicsBuffer<T> const& buff)
        {
            _copy_from(buff);
        }

        GraphicsBuffer<T> & operator=(GraphicsBuffer<T> const& buff)
        {
            _copy_from(buff);
            return *this;
        }
        GraphicsBuffer<T> & operator=(GraphicsBuffer<T> && buff)
        {
            std::swap(_size, buff._size);
            std::swap(_data_ptr, buff._data_ptr);
            return *this;
        }

        /* Destructor */
        ~GraphicsBuffer()
        {
            delete[] _data_ptr;
            _data_ptr = nullptr;
            _size = Length2D(0);
        }


        // Test graphics buffer is valid or not
        bool inline valid() const
        {
            return _data_ptr != nullptr;
        }

        /* getting size */
        length_t inline width() const
        {
            return _size.x;
        }
        length_t inline height() const
        {
            return _size.y;
        }
        length_t inline total() const
        {
            return _size.x * _size.y;
        }
        Length2D inline size() const
        {
            return _size;
        }

        /* getting data pointer */
        Data inline * data_pointer()
        {
            return _data_ptr;
        }
        Data inline const* data_pointer() const
        {
            return _data_ptr;
        }

        /* accessing data */
        Data inline & operator()(length_t w, length_t h)
        {
            assert((0 <= w && w < _size.x) &&( 0 <= h && h < _size.y));
            return *(_data_ptr + (w + _size.x * h));
        }
        Data inline & operator()(Length2D const& pos)
        {
            assert((0 <= pos.x && pos.x < _size.x) &&( 0 <= pos.y && pos.y < _size.y));
            return *(_data_ptr + (pos.x + _size.x * pos.y));
        }
        Data inline const& operator()(length_t w, length_t h) const
        {
            assert((0 <= w && w < _size.x) &&( 0 <= h && h < _size.y));
            return *(_data_ptr + (w + _size.x * h));
        }
        Data inline const& operator()(Length2D const& pos) const
        {
            assert((0 <= pos.x && pos.x < _size.x) &&( 0 <= pos.y && pos.y < _size.y));
            return *(_data_ptr + (pos.x + _size.x * pos.y));
        }


        /* applying function on data */
        /// Apply 'func' to each elements in buffer
        ///
        /// @param func accepts 'Graphics<Y>::Data &' input, and returns 'void'
        void for_each(std::function<void(Data &)> func)
        {
            Data * iter = _data_ptr;
            length_t const total_data = total();
            for (length_t i = 0; i < total_data; ++i) {
                func(*(iter++));
            }
        }

        /// Apply 'func' to each elements and return results in buffer
        ///
        /// @tparam U 'func' returned data type, must be floating-point or integer
        /// @param func accepts 'GraphicsBuffer<T>::Data const&' input, and returns 'GraphicsBuffer<U>::Data'
        template<typename U>
        GraphicsBuffer<U> map(std::function<vec<3, U>(Data const&)> func) const
        {
            GraphicsBuffer<U> new_buff(_size);
#ifdef GBUFF_CHECK_WRITING_DATA
            if (new_buff.valid()) {
#endif
                auto new_data_ptr = new_buff.data_pointer();
                Data * old_data_ptr = _data_ptr;
                length_t const totoal_data = total();
                for (length_t i = 0; i < totoal_data; ++i) {
                    *(new_data_ptr++) = func(*(old_data_ptr++));
                }
#ifdef GBUFF_CHECK_WRITING_DATA
            }
#endif
            return new_buff;
        }

        /// Apply 'func' for all elements index and write result into buffer
        ///
        /// @param func accepts 'length_t', 'length_t', 'Graphics<Y>::Data &', and returns 'void'
        void for_each_index(std::function<void(length_t, length_t, Data &)> func)
        {
            Data * iter = _data_ptr;
            for (length_t h = 0; h < _size.y; ++h) {
                for (length_t w = 0; w < _size.x; ++w) {
                    func(w, h, *(iter++));
                }
            }
        }

        /// Apply 'func' for all elements index and write result into buffer
        ///
        /// @param func accepts 'Length2D const&', 'Graphics<Y>::Data &', and returns 'void'
        void for_each_index(std::function<void(Length2D const&, Data &)> func)
        {
            Data * iter = _data_ptr;
            Length2D indexes;
            for (length_t h = 0; h < _size.y; ++h) {
                indexes.y = h;
                for (length_t w = 0; w < _size.x; ++w) {
                    indexes.x = w;
                    func(indexes, *(iter++));
                }
            }
        }

        // TODO: void for_each_multithreads(std::function<void(Data &)> func);
        // TODO: template<typename U> GraphicsBuffer<U> map_multithreads(std::function<vec<3, U>(Data const&)> func) const
        // TODO: void for_each_index_multithreads(std::function<void(length_t, length_t, Data &)> func)
        // TODO: void for_each_index_multithreads(std::function<void(Length2D const&, Data &)> func)


        /* changing data type */

        /// cast data to different type
        ///
        /// @tparam U new data type
        template<typename U>
        GraphicsBuffer<U> cast() const
        {
            GraphicsBuffer<U> new_buffer(_size);
#ifdef GBUFF_CHECK_WRITING_DATA
            if (new_buffer.valid()) {
#endif
                auto new_data_ptr = new_buffer.data_pointer();
                Data * old_data_ptr = _data_ptr;
                length_t const total_data = total();
                for (length_t i = 0; i < total_data; ++i) {
                    *(new_data_ptr++) = *(old_data_ptr++);
                }
#ifdef GBUFF_CHECK_WRITING_DATA
            }
#endif
            return new_buffer;
        }

        /// Wirte data into different data type buffer
        ///
        /// @tparam U data type in new buffer
        /// @param buff size of new buffer must equal this size
        template<typename U>
        GraphicsBuffer<U> & cast(GraphicsBuffer<U> & buff) const
        {
            assert(buff.size() == _size);
#ifdef GBUFF_CHECK_WRITING_DATA
            if (buff.valid()) {
#endif
                auto new_data_ptr = buff.data_pointer();
                Data * old_data_ptr = _data_ptr;
                length_t const total_data = total();
                for (length_t i = 0; i < total_data; ++i) {
                    *(new_data_ptr++) = *(old_data_ptr++);
                }
#ifdef GBUFF_CHECK_WRITING_DATA
            }
#endif
            return buff;
        }


    private:
        Length2D _size;
        Data * _data_ptr;

        void _copy_from(GraphicsBuffer<T> const& buff)
        {
            _size = buff._size;
            delete[] _data_ptr;
            length_t const total_data = total();
            _data_ptr = new Data[total_data];
#ifdef GBUFF_CHECK_WRITING_DATA
            if (_data_ptr != nullptr) {
#endif
                Data * old_data_ptr = buff._data_ptr;
                Data * new_data_ptr = _data_ptr;
                for (length_t i = 0; i < total_data; ++i) {
                    *(new_data_ptr++) = *(old_data_ptr);
                }
#ifdef GBUFF_CHECK_WRITING_DATA
            }
#endif
        }
    };


    /// Save 'uint8' buffer to a bmp image
    ///
    /// @param file_name bmp image path where save to
    /// @param buff size of buffer should smaller than [30000, 30000]
    void save_bmp(char const* file_name, GraphicsBuffer<uint8> const& buff)
    {
        length_t width = buff.width(), height = buff.height();

        char align_buff[3] {0, 0, 0};
        length_t const align = width % 4;
        length_t buffer_size = (3 * width + align) * height;
        length_t file_size = buffer_size + 54;
        length_t const color_depth = 24;

        uint8 header[54];
        uint8 * ptr = header;
        /* header */
        *(ptr++) = 0x42; *(ptr++) = 0x4D;     // BM
        *(ptr++) = file_size & 0xFF; file_size >>= 8;   // bfSize
        *(ptr++) = file_size & 0xFF; file_size >>= 8;
        *(ptr++) = file_size & 0xFF; file_size >>= 8;
        *(ptr++) = file_size & 0xFF;
        *(ptr++) = 0; *(ptr++) = 0;           // bfReserved1
        *(ptr++) = 0; *(ptr++) = 0;           // bfReserved2
        *(ptr++) = 0x36; *(ptr++) = 0;        // bfOffBits
        *(ptr++) = 0; *(ptr++) = 0;
        /* info header */
        *(ptr++) = 0x28; *(ptr++) = 0;        // biSize
        *(ptr++) = 0; *(ptr++) = 0;
        *(ptr++) = width & 0xFF; width >>= 8;       // biWidth
        *(ptr++) = width & 0xFF;
        *(ptr++) = 0; *(ptr++) = 0;
        *(ptr++) = height & 0xFF; height >>= 8;     // biHeight
        *(ptr++) = height & 0xFF;
        *(ptr++) = 0; *(ptr++) = 0;
        *(ptr++) = 1; *(ptr++) = 0;           // biPlanes
        *(ptr++) = 0x18; *(ptr++) = 0;        // biBitCount
        *(ptr++) = 0; *(ptr++) = 0;           // biCompression
        *(ptr++) = 0; *(ptr++) = 0;
        *(ptr++) = buffer_size & 0xFF; buffer_size >>= 8;   // biSizeImage
        *(ptr++) = buffer_size & 0xFF; buffer_size >>= 8;
        *(ptr++) = buffer_size & 0xFF; buffer_size >>= 8;
        *(ptr++) = buffer_size & 0xFF;
        *(ptr++) = 0; *(ptr++) = 0;           // biXPelsPerMeter
        *(ptr++) = 0; *(ptr++) = 0;
        *(ptr++) = 0; *(ptr++) = 0;           // biYPelsPerMeter
        *(ptr++) = 0; *(ptr++) = 0;
        *(ptr++) = 0; *(ptr++) = 0;           // biClrUsed
        *(ptr++) = 0; *(ptr++) = 0;
        *(ptr++) = 0; *(ptr++) = 0;           // biClrImportant
        *(ptr++) = 0; *ptr = 0;


        ::std::ofstream outfile;
        outfile.open(file_name, ::std::ios::out | ::std::ios::binary | ::std::ios::trunc);

        outfile.write(reinterpret_cast<char const*>(header), 54);
        GraphicsBuffer<uint8>::Data const* data_ptr = buff.data_pointer();

        for (length_t h = 0; h < buff.height(); ++h) {
            for (length_t w = 0; w < buff.width(); ++w) {
                outfile.write(reinterpret_cast<char const*>(&data_ptr->b), 1);
                outfile.write(reinterpret_cast<char const*>(&data_ptr->g), 1);
                outfile.write(reinterpret_cast<char const*>(&data_ptr->r), 1);
                ++data_ptr;
            }
            outfile.write(align_buff, align);
        }

        outfile.close();
    }


    /// Mapping floating-point color to display color
    DisplayRGBColor to_display(RGBColor const& color)
    {
        // pow(color, 1/2.2) is for gamma correction (https://en.wikipedia.org/wiki/Gamma_correction)
        return DisplayRGBColor(clamp(255.f * pow(color, 1.f/2.2f), 0.f, 255.f));
    }

} // namespace nyas
