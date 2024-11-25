//
// Created by Bradley Remedios on 11/20/24.
//
#ifndef BPL_STORAGE_PAYLOAD_H
#define BPL_STORAGE_PAYLOAD_H

namespace bpl::storage {

    class Payload {
    public:
        Payload();
        ~Payload();

        bool CopyChunk(const char* data, size_t size);
        bool Reserve(size_t size);
        void Clear();
        bool Save(const std::string& filename) const;

        [[nodiscard]] const char* getData() const;
        [[nodiscard]] size_t getSize() const;
    private:
        char* m_buffer=nullptr;
        size_t m_bufferSize=0;
        size_t m_dataSize=0;
    }; // Payload

} // bpl::storage

#endif // BPL_STORAGE_PAYLOAD_H
