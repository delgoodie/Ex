#include "Encoder.h"

#include <string>
#include <string.h>
#include <fstream>

#include "../CompilerCore.h"

static size_t EvalChainSize(EvalLink* chain)
{
    size_t size = 0;
    EvalLink* link = chain;
    while (link)
    {
        size += 1; // Flags
        if (link->type == EvalLink::Type::OP)
            size += 1; // op index
        else
        {
            size += 1; // Expr Type
            switch (link->expr.type)
            {
            case Expr::Type::EX_BOOLEAN:
                size += 1;
                break;
            case Expr::Type::EX_NUMBER:
                size += sizeof(ex_number_t);
                break;
            case Expr::Type::EX_STRING:
            case Expr::Type::EX_VARIABLE:
                size += link->expr.string.length() + 1;
                break;
            case Expr::Type::EX_OBJECT:
                size += ChainSize(link->expr.object.link_head);
                break;
            }
        }
        link = link->next;
    }
    // Null link for termination
    size += 1;
    return size;
}

static void StoreBlob(Blob blob, const std::string& filename)
{
    std::ofstream(filename, std::ios::binary).write((const char*)blob.data, blob.size);
    delete blob.data;
}


namespace Compiler
{
    Blob Encode(EvalLink* head) {
        size_t size = EvalChainSize(chain);
        // Allocate blob on heap
        unsigned char* data = (unsigned char*)malloc(size);

        // Write each link onto heap sequentially
        int index = 0;
        EvalLink* link = chain;
        while (link)
        {
            data[index++] = link->Flags(); // * Write Link Flags (1 byte)

            if (link->type == EvalLink::Type::OP)
            {
                data[index++] = (unsigned char)link->op_index;
            }
            else
            {
                data[index++] = (unsigned char)link->expr.type; // * Write Expr Type (1 byte)

                switch (link->expr.type)
                {
                case Expr::Type::EX_BOOLEAN:
                    data[index++] = (link->expr.boolean ? 0xFF : 0x00); // * Write boolean (1 byte)
                    break;
                case Expr::Type::EX_NUMBER:
                    data[index] = link->expr.number; // * Write number (8 bytes if ex_number_type == double)
                    index += sizeof(ex_number_t);
                    break;
                case Expr::Type::EX_STRING:
                case Expr::Type::EX_VARIABLE:
                    memcpy(&data[index], link->expr.string.c_str(), link->expr.string.length() + 1); // Write char* (n bytes)
                    index += link->expr.string.length() + 1;
                    break;
                case Expr::Type::EX_OBJECT:
                    Blob obj = EncodeChain(link->expr.object.link_head);
                    memcpy(&data[index], obj.data, obj.size); // * Write eval chain (n bytes)
                    index += obj.size;
                    delete obj.data;
                    break;
                }
            }
        }

        // Add null termination link
        data[index] = 0x08;

        // Return in blob form
        return { data, size };
    }

    namespace Debug
    {
        bool Enabled;

        void PrintBlob(const Blob& blob)
        {
            if (!Enabled)
                return;
        }
    }
}
