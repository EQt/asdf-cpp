#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <cstdint>

#include "node.hpp"
#include "compression.hpp"
#include "block_manager.hpp"

namespace Asdf {

class AsdfFile
{
    public:
        /* Constructors */
        AsdfFile();
        /* TODO: consider providing a factory method here instead */
        AsdfFile(std::string filename);
        AsdfFile(std::stringstream &stream);
        ~AsdfFile(void);

        /* Getters/Setters */
        std::string get_filename(void);
        Node get_tree(void);
        Node operator[] (std::string key);

        friend std::ostream&
            operator<<(std::ostream& stream, const AsdfFile &af);

        void * get_block(int source) const;

    protected:
        BlockManager block_manager;

        template <typename T> friend class NDArray;
        template <typename T>
            int register_array_block(T *data, size_t size, CompressionType compression)
        {
            return block_manager.add_data_block<T>(data, size, compression);
        }

        void write_blocks(std::ostream &ostream) const;

    private:
        /* Private members */
        Node asdf_tree;

        int fd = -1;
        size_t data_size = 0;
        /* TODO: make this a shared pointer */
        uint8_t *data = nullptr;

        bool memmapped = false;

        std::streampos end_index = 0;

        std::vector<uint8_t *> blocks;

        /* Private methods */
        void setup_memmap(std::string filename);
        void copy_stream(std::iostream &stream);

        void find_blocks(void);

}; /* AsdfFile class */
} /* namespace Asdf */
