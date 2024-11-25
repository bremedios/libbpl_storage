//
// Created by Bradley Remedios on 11/20/24.
//
#include <iostream>
#include <fstream>
#include <cstring>

#include "bpl/storage/Payload.h"

#include "Debug.h"

namespace bpl::storage {

    Payload::Payload() = default;
    Payload::~Payload() {
        if (nullptr != m_buffer) {
          free(m_buffer);
        }
    }

    void Payload::Clear() {
        if (nullptr != m_buffer) {
            free(m_buffer);
            m_buffer = nullptr;
        }
        m_bufferSize = 0;
        m_dataSize = 0;
    } // Clear

    bool Payload::CopyChunk(const char* data, size_t size) {
        // Check if we have enough space.
        if ((m_dataSize + size + 1) > m_bufferSize) {
            // nothing allocated
            if (nullptr == m_buffer) {
                m_buffer = (char*)malloc(size + 1);

                if (nullptr == m_buffer) {
                    std::cerr << "Payload::CopyChunk: Failed to allocate memory for Payload::CopyChunk()" << std::endl;

                    return false;
                }
                m_bufferSize = size + 1;
            }
            else {
                m_buffer = (char*)realloc(m_buffer, m_dataSize + size + 1);

                if (nullptr == m_buffer) {
                    std::cerr << "Payload::CopyChunk: Failed to reallocate memory for Payload::CopyChunk()" << std::endl;
                    m_bufferSize = 0;
                    m_dataSize = 0;

                    return false;
                }
                m_bufferSize = m_dataSize + size + 1;
            }
        }

        memcpy (m_buffer + m_dataSize, data, size);
        m_buffer[m_dataSize + size] = '\0';
        m_dataSize += size;

        return true;
    } // CopyChunk

    bool Payload::Reserve(size_t size) {
        m_buffer = (char*)realloc(m_buffer, size+1);

        if (nullptr == m_buffer) {
            std::cerr << "Payload::Resize: realloc failed" << std::endl;

            m_bufferSize = 0;

            return false;
        }

        m_bufferSize = size;

        if (m_dataSize > m_bufferSize) {
            m_dataSize = m_bufferSize;
        }

        return true;
    } // Resize

    const char* Payload::getData() const {
        return m_buffer;
    } // getData

    size_t Payload::getSize() const {
        return m_dataSize;
    } // getSize

    bool Payload::Save(const std::string& filename) const {
        std::ofstream f;

        f.open(filename);

        f.write(m_buffer, m_dataSize);

        f.close();

        return true;
    }
} // bpl::storage
