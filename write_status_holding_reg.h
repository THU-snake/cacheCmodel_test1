#ifndef WRITE_STATUS_HOLDING_REG_H
#define WRITE_STATUS_HOLDING_REG_H

#include "utils.h"
#include "parameter.h"
//#include "interfaces.h"

class wshr : public cache_building_block{
    public:
    wshr(){
        m_valid.fill(false);
    }

    bool is_full(){
        for(const auto& v : m_valid){
            if(v == false){
                return false;
            }
        }
        return true;
    }

    bool has_conflict(block_addr_t block_idx){
        for(int i=0;i<N_WSHR_ENTRY;++i){
            if(m_valid[i] && (m_entry[i] == block_idx)){
                return true;
            }
        }
        return false;
    }

    void push(block_addr_t block_idx, wshr_idx_t& idx){
        assert(!has_conflict(block_idx));
        for(int i=0;i<N_WSHR_ENTRY;++i){
            if(m_valid[i] == false){
                m_valid[i] = true;
                m_entry[i] = block_idx;
                idx = i;
            }
        }
    }

    void pop(wshr_idx_t idx){
        assert(m_valid[idx] == true);
        m_valid[idx] = false;
    }

    private:
    std::array<bool,N_WSHR_ENTRY> m_valid;
    std::array<block_addr_t,N_WSHR_ENTRY> m_entry;
};

#endif